// PX2Robot.cpp

#include "PX2Robot.hpp"
#include "PX2Creater.hpp"
#include "PX2Project.hpp"
#include "PX2JSONData.hpp"
#include "PX2Timestamp.hpp"
#include "PX2Timespan.hpp"
#include "PX2VoxelPre.hpp"
#if defined PX2_USE_VOXEL
#include "PX2VoxelSection.hpp"
#endif
#include "PX2AIES.hpp"
#include "PX2Renderer.hpp"
#include "PX2Arduino.hpp"
#include "PX2ResourceManager.hpp"
#if defined PX2_USE_SLAM2D
#include "Slam2DPlugin.hpp"
#endif
#include "PX2PluginManager.hpp"
#include "PX2AIAgent.hpp"
#include "PX2EngineSceneCanvas.hpp"
#include "PX2AISteeringPath.hpp"
#include "PX2Creater.hpp"
#include "PX2Actor.hpp"
using namespace PX2;

#define M_PI 3.1415927
#define MAX_SPEED 0.2						//弧形轨迹：最大速度
#define MIN_SPEED 0.0							//弧形轨迹：最小速度
#define MAX_ACCELERATE 0.5						//动态窗口：最大加速度
#define MAX_ACCOMEGA 50.0 / 180.0 * M_PI		//动态窗口：最大角加速度
#define SAMPLING_SPEED 0.008					//速度采样间隔
#define DT 0.1									//采样时间间隔
#define PREDICT_TIME 1.8						//预测时间

#define WEIGHT_HEADING 0.05						//HEADING权重
#define WEIGHT_CLEARANCE 0.2					//CLEARANCE权重
#define WEIGHT_VELOCITY 0.1						//VELOCITY权重

#define GOAL_X 10								//目标横坐标
#define GOAL_Y 10								//目标纵坐标
#define ROBOT_RADIUS 0.1						//机器人半径

#if defined _WIN32 || defined WIN32
#include <windows.h> 
#endif
//----------------------------------------------------------------------------
Slam2DPlugin *Robot::mSlam2DPlugin = 0;
//----------------------------------------------------------------------------
Robot::Robot() :
mLiDar(0),
mOffsetDegree(0.0f),
mRobotMapX(0),
mRobotMapY(0),
m2DSlameAngle(0.0f),
mIsHasAxis(false),
mCurMoveDirectionAxisY(0.0f),
mFirstMoveDirectionAxisY(0.0f),
mMoveDirectionDegreeWithFirst(0.0f),
mIsHasEverSettedDirection(false),
mIsSlamMapUpdate(true),
mDegreeAdjust(0.0f),
mAgent(0),
mRotationRad(0.0f)
{
	mRoleType = RT_MASTER;

	mUIFrame = new0 UIFrame();

	mUIVlc = new0 UIVlc();
	mUIFrame->AttachChild(mUIVlc);
	mUIVlc->SetType(UIVlc::T_HARDCAMERA);
	mUIVlc->SetAnchorHor(0.0f, 1.0f);
	mUIVlc->SetAnchorVer(0.0f, 1.0f);

	mPosition = APoint::ORIGIN;

	mDirection = AVector::UNIT_Y;
	mRotationRad = 0.0f;
	mRight = AVector::UNIT_X;
	mUp = AVector::UNIT_Z;

	// leidar
	mPicBoxMap = new0 UIFPicBox();
	mPicBoxMap->GetUIPicBox()->GetMaterialInstance()
		->GetMaterial()->GetPixelShader(0, 0)->SetFilter(0,
		Shader::SF_NEAREST);

	mRobotMapData = new0 RobotMapData();
	_RecreateMapTex(mRobotMapData->MapStruct.MapSize);

	mRobotTex = new0 UIFPicBox();
	mPicBoxMap->AttachChild(mRobotTex);
	mRobotTex->LocalTransform.SetTranslateY(-1.0f);
	mRobotTex->GetUIPicBox()->SetTexture("Data/engine/white.png");
	mRobotTex->SetSize(2.0f, 6.0f);
	mRobotTex->SetPivot(0.5f, 0.0f);
	mRobotTex->SetAlphaSelfCtrled(true);

	UIFPicBox *tex = new0 UIFPicBox();
	mRobotTex->AttachChild(tex);
	tex->LocalTransform.SetTranslateY(-1.0f);
	tex->GetUIPicBox()->SetTexture("Data/engine/white.png");
	tex->SetSize(2.0f, 2.0f);
	tex->SetColor(Float3::RED);
	tex->SetAnchorHor(0.5f, 0.5f);
	tex->SetAnchorVer(0.0f, 0.0f);
	tex->SetPivot(0.5f, 0.5f);
	tex->SetAlphaSelfCtrled(true);

	mPathGraph = new0 PathingGraph();

	mIsInitSlamMap = false;
	mIsMapDataChanged = true;

	mArduino = new0 Arduino();

	mForceTimer = 0.0f;
	mSpeed = 0.0f;
	mIsAdjustToDirection = false;
	mIsUseForce = false;

	mLeftSpeed = 0.0f;
	mRightSpeed = 0.0f;

	mLeftSmoother = new Smoother<float>(16, 0.0f);
	mRightSmoother = new Smoother<float>(16, 0.0f);

	mVoxelSection = 0;

	mEnviroment = new0 Enviroment();
	mRRTRobot = new0 RRTRobot();
}
//----------------------------------------------------------------------------
Robot::~Robot()
{
	if (mRRTRobot)
	{
		delete0(mRRTRobot);
	}

	if (mEnviroment)
	{
		delete0(mEnviroment);
	}

	auto it = mObsts.begin();
	for (; it != mObsts.end(); it++)
	{
		delete0(*it);
	}
	mObsts.clear();

	if (mLiDar)
	{
		delete0(mLiDar);
	}

	if (mLeftSmoother)
	{
		delete0(mLeftSmoother);
	}

	if (mRightSmoother)
	{
		delete0(mRightSmoother);
	}

#if defined PX2_USE_SLAM2D
	if (mSlam2DPlugin)
		PX2_PLUGINMAN.UninstallPlugin(mSlam2DPlugin);
#endif
}
//----------------------------------------------------------------------------
void Robot::InitlizeSlam2D()
{
#if defined PX2_USE_SLAM2D
	mSlam2DPlugin = new Slam2DPlugin();
	PX2_PLUGINMAN.InstallPlugin(mSlam2DPlugin);
#endif
}
//----------------------------------------------------------------------------
void Robot::TernimateSlam2D()
{
#if defined PX2_USE_SLAM2D
	if (mSlam2DPlugin)
		PX2_PLUGINMAN.UninstallPlugin(mSlam2DPlugin);
#endif
}
//----------------------------------------------------------------------------
bool Robot::SaveMap(const std::string &filename)
{
	_UpdateMapObst();

	std::string writeablePath = PX2_RM.GetWriteablePath();
	std::string dstPath = writeablePath + "Write_ZERONE/";
	if (!PX2_RM.IsFileFloderExist(dstPath))
	{
		PX2_RM.CreateFloder(writeablePath, "Write_ZERONE/");
	}

	if (mRobotMapData)
	{
		mRobotMapData->SetResourcePath(filename);

		OutStream outStream;
		outStream.Insert(mRobotMapData);

		if (outStream.Save(dstPath+filename))
		{
			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
bool Robot::LoadMap(const std::string &filename, const APoint &initPos,
	float curAngle)
{
	mInitMapData = RobotMapData();

	std::string writeablePath = PX2_RM.GetWriteablePath();
	std::string dstPath = writeablePath + "Write_ZERONE/" + filename;

	InStream inStream;
	if (inStream.Load(dstPath))
	{
		mRobotMapData = DynamicCast<RobotMapData>(inStream.GetObjectAt(0));
		mInitMapData = *mRobotMapData;

		if (initPos != APoint::ORIGIN)
		{
			mInitMapData.MapStruct.CurPos = initPos;
		}
		if (0.0f != curAngle)
		{
			mInitMapData.MapStruct.CurAngle = curAngle;
		}
	}

	if (mRobotMapData)
	{
		InitSlamMap(mRobotMapData->MapStruct.MapSize,
			mRobotMapData->MapStruct.MapResolution);

		UpdateSceneObstacles();

		_UpdateMapObst();

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
int _Roundle(float number)
{
	return (number > 0.0) ? floor(number + 0.5f) : ceil(number - 0.5f);
} 
//----------------------------------------------------------------------------
void Robot::_UpdateMapObst()
{
	int mapSize = mRobotMapData->MapStruct.MapSize;
	float halfMapSize = mapSize * 0.5f;
	float resolution = mRobotMapData->MapStruct.MapResolution;
	float mapWidth = mapSize * resolution;
	std::vector<unsigned char> map = mRobotMapData->Map2DUsing;
	std::vector<unsigned char> maskData;
	maskData.resize(map.size());
	memset(&maskData[0], 0, maskData.size());

	int mapAllSize = mapSize * mapSize;
	int robotindex = 0;
	int x = 0;
	int y = 0;
	for (int i = 0; i < mapAllSize; i++)
	{
		x = (i + mapSize) % mapSize;
		y = ((mapSize - 1) - i / mapSize);

		bool isHasObst = false;
		int mapVal = 200;
		if (!map.empty())
		{
			mapVal = map[i];

			if (mapVal == 100)
			{
				// robot pos
				robotindex = i;
			}
			else if (mapVal == 10)
			{
			}
			else if (mapVal == 200)
			{
				// space can go
			}
			else
			{
				if (0 == mapVal)
				{
					// obst
					isHasObst = true;
				}
				else
				{
				}
			}
		}

		//int adjustVal = mRobotMapData->SelfDrawMapData2D[i];
		//if (0 == adjustVal)
		//{
		//	isHasObst = true;
		//}
		//else if (200 == adjustVal)
		//{
		//}
		//else if (201 == adjustVal)
		//{
		//	isHasObst = false;
		//}

		int graphMapSize = mPathGraph->GetMapSize();
		float xPercent = (float)x / (float)mapSize;
		float yPercent = (float)y / (float)mapSize;
		float fXIndex = xPercent * (float)graphMapSize;
		float fYIndex = yPercent * (float)graphMapSize;

		int xIndex = _Roundle(fXIndex);
		int yIndex = _Roundle(fYIndex);

		if (isHasObst)
		{
			_SetGraphValue(xIndex, yIndex, 1000.0f);
			_SetGraphValue(xIndex - 1, yIndex, 1000.0f);
			_SetGraphValue(xIndex + 1, yIndex, 1000.0f);
			_SetGraphValue(xIndex, yIndex - 1, 1000.0f);
			_SetGraphValue(xIndex, yIndex + 1, 1000.0f);

			_SetGraphValue(xIndex - 1, yIndex - 1, 1000.0f);
			_SetGraphValue(xIndex + 1, yIndex + 1, 1000.0f);
			_SetGraphValue(xIndex - 1, yIndex + 1, 1000.0f);
			_SetGraphValue(xIndex + 1, yIndex - 1, 1000.0f);
			
			maskData[i] = 1;
		}
		else
		{
			_SetGraphValue(xIndex, yIndex, PATHING_DEFAULT_ARC_WEIGHT);

			maskData[i] = 0;
		}
	}

	mPathGraph->SetMapData(maskData, mapSize, resolution);
}
//----------------------------------------------------------------------------
void Robot::_SetGraphValue(int x, int y, float val)
{
	int graphMapSize = mPathGraph->GetMapSize();
	if (x >= 0 && x < graphMapSize && y >= 0 && y < graphMapSize)
	{
		int iIndex = x + y * graphMapSize;
		mPathGraph->SetArcValue(iIndex, val);
	}
}
//----------------------------------------------------------------------------
const APoint &Robot::GetPosition() const
{
	return mPosition;
}
//----------------------------------------------------------------------------
RobotMapData &Robot::GetInitMapData()
{
	return mInitMapData;
}
//----------------------------------------------------------------------------
void Robot::ClearInitMapData()
{
	mInitMapData = RobotMapData();
}
//----------------------------------------------------------------------------
RobotMapData *Robot::GetCurMapData()
{
	return mRobotMapData;
}
//----------------------------------------------------------------------------
void Robot::SetValueAtPos(const APoint &pos, float range, int val)
{
	if (!mIsInitSlamMap)
		return;

	int mapSize = mRobotMapData->MapStruct.MapSize;
	float mapReso = mRobotMapData->MapStruct.MapResolution;

	float mapAllSize = mapSize * mapReso;

	float texX = 0.5f + (pos.X() / mapAllSize);
	float texY = 0.5f + (pos.Y() / mapAllSize);

	float texXStart = 0.5f + ((pos.X() - range) / mapAllSize);
	float texXEnd = 0.5f + ((pos.X() + range) / mapAllSize);
	if (texXStart <= 0.0f || texXStart>1.0f)
		return;
	if (texXEnd <= 0.0f || texXEnd > 1.0f)
		return;

	float texYStart = 0.5f + ((pos.Y() - range) / mapAllSize);
	float texYEnd = 0.5f + ((pos.Y() + range) / mapAllSize);
	if (texYStart <= 0.0f || texYStart > 1.0f)
		return;
	if (texYEnd <= 0.0f || texYEnd > 1.0f)
		return;

	int iTexXStart = (int)(texXStart*mapSize);
	int iTexXEnd = (int)(texXEnd*mapSize);
	int iTexYStart = (int)(texYStart*mapSize);
	int iTexYEnd = (int)(texYEnd*mapSize);

	for (int x = iTexXStart; x < iTexXEnd; x++)
	{
		for (int y = iTexYStart; y < iTexYEnd; y++)
		{
			int index = y*mapSize + x;
			mRobotMapData->SelfDrawMapData2D[index] = val;
		}
	}

	mIsMapDataChanged = true;
}
//----------------------------------------------------------------------------
void Robot::UpdateSceneObstacles()
{
	if (!mAgent)
		return;

	AIAgentWorld *agentWorld = mAgent->GetAIAgentWorld();
	std::vector<AIAgentObject*> objs = agentWorld->GetObjects();

	for (int i = 0; i < (int)objs.size(); i++)
	{
		AIAgentObject *obj = objs[i];
		float mass = obj->GetMass();
		if (mass > 0.0f || obj->IsMassZeroAvoid())
		{
			APoint pos = obj->GetPosition();
			float radius = obj->GetRadius();
			SetValueAtPos(pos, radius, 0);
		}
	}
}
//----------------------------------------------------------------------------
void Robot::SetLineValueAtPos(const APoint &pos, float range, int val)
{
	if (!mIsInitSlamMap)
		return;

	int mapSize = mRobotMapData->MapStruct.MapSize;
	float mapReso = mRobotMapData->MapStruct.MapResolution;

	float mapAllSize = mapSize * mapReso;

	float texX = 0.5f + (pos.X() / mapAllSize);
	float texY = 0.5f + (pos.Y() / mapAllSize);

	float texXStart = 0.5f + ((pos.X() - range) / mapAllSize);
	float texXEnd = 0.5f + ((pos.X() + range) / mapAllSize);

	float texYStart = 0.5f + ((pos.Y() - range) / mapAllSize);
	float texYEnd = 0.5f + ((pos.Y() + range) / mapAllSize);

	int iTexXStart = (int)(texXStart*mapSize);
	int iTexXEnd = (int)(texXEnd*mapSize);
	int iTexYStart = (int)(texYStart*mapSize);
	int iTexYEnd = (int)(texYEnd*mapSize);

	for (int x = iTexXStart; x < iTexXEnd; x++)
	{
		for (int y = iTexYStart; y < iTexYEnd; y++)
		{
			int index = y*mapSize + x;
			mRobotMapData->LineDrawMapData2D[index] = val;
		}
	}

	mIsMapDataChanged = true;
}
//----------------------------------------------------------------------------
void Robot::_RecreateMapTex(int mapSize)
{
	Texture::Format formatLidar = Texture::TF_A8R8G8B8;
	mTextureMap = new0 Texture2D(formatLidar, mapSize, mapSize, 1);
	char *pDest = mTextureMap->GetData(0);
	int offsetDst = 0;
	for (int row = 0; row < mapSize; ++row)
	{
		for (int col = 0; col < mapSize; ++col)
		{
			pDest[offsetDst + 0] = 0; // b
			pDest[offsetDst + 1] = 0; // g
			pDest[offsetDst + 2] = 0; // r
			pDest[offsetDst + 3] = 255;

			offsetDst += 4;
		}
	}

	mPicBoxMap->GetUIPicBox()->SetTexture(mTextureMap);
}
//----------------------------------------------------------------------------
void Robot::Update(float appseconds, float elpasedSeconds)
{
	PX2_UNUSED(appseconds);
	PX2_UNUSED(elpasedSeconds);


	if (mArduino)
	{
		mArduino->Update(elpasedSeconds);
	}

	if (mIsHasAxis)
	{
		Arduino::AxisObj curAxisObj = mArduino->GetCurAxisObj();
		
		float rad = curAxisObj.Y * Mathf::DEG_TO_RAD;
		float x = Mathf::Cos(rad);
		float y = Mathf::Sign(rad);

		mAxisDirection = AVector(x, y, 0.0f);
		mAxisUp = AVector::UNIT_Z;
		mAxisRight = mAxisDirection.Cross(mAxisUp);
		mAxisRotMatrix = HMatrix(mAxisRight, mAxisDirection, mAxisUp, APoint::ORIGIN, true);
	}

	//_UpdateMapObstDyn(mPosition);

	if (mLiDar)
	{
		mLiDar->Update(appseconds, elpasedSeconds);
	}

	mRight = mDirection.Cross(AVector::UNIT_Z);
	mUp = AVector::UNIT_Z;
	mMatrix = HMatrix(mRight, mDirection, mUp, mPosition, true);
	mRobotState = _GetCurRobotState();

	if (mIsAdjustToDirection)
	{
		if (!_IsInRightDirection(mAdjustToDirection))
		{
			_UpdateAdjustDirection(mAdjustToDirection);
		}
		else
		{
			mIsAdjustToDirection = false;
		}
	}

	_UpdateVirtualRobot1(elpasedSeconds);

	//if (mIsUseForce)
	//{
	//	mForceTimer += elpasedSeconds;
	//	//if (mForceTimer > 0.1f)
	//	{
	//		//_UpdateVirtualRobot(elpasedSeconds);
	//		mForceTimer = 0.0f;
	//	}
	//}

	int mapSize = mRobotMapData->MapStruct.MapSize;
	float resolution = mRobotMapData->MapStruct.MapResolution;
	std::vector<unsigned char> map2DUsing = mRobotMapData->Map2DUsing;

	if (mIsMapDataChanged && mIsInitSlamMap)
	{
		int mapAllSize = mapSize * mapSize;
		int robotindex = 0;
		int x = 0;
		int y = 0;
		int halfSize = mapSize * 0.5f;
		char *dst = mTextureMap->GetData(0);
		int width = mTextureMap->GetWidth();
		for (int i = 0; i < mapAllSize; i++)
		{
			x = (i + width) % width;
			y = ((width - 1) - i / width);

			unsigned char *pixel = (unsigned char*)dst + y * width * 4 + x * 4;

			*(pixel + 0) = 0;	// b
			*(pixel + 1) = 0;	// g
			*(pixel + 2) = 0;	// r
			*(pixel + 3) = 255;

			bool isHasObst = false;
			int mapVal = 200;
			if (!map2DUsing.empty())
			{
				mapVal = map2DUsing[i];

				if (mapVal == 100)
				{
					// robot pos
					robotindex = i;

					*(pixel + 0) = 255;	// b
					*(pixel + 1) = 255;	// g
					*(pixel + 2) = 255;	// r
					*(pixel + 3) = 255;

					mRobotMapX = x;
					mRobotMapY = y;
					mRobotMapData->MapStruct.IndexX = x;
					mRobotMapData->MapStruct.IndexY = y;
				}
				else if (mapVal == 10)
				{
					// none
					*(pixel + 0) = 0;	// b
					*(pixel+ 1) = 0;	// g
					*(pixel+ 2) = 0;	// r
					*(pixel+ 3) = 255;

					// set empty
				}
				else if (mapVal == 200)
				{
					// space can go
					*(pixel + 0) = 0;
					*(pixel + 1) = 255;
					*(pixel + 2) = 0;
					*(pixel + 3) = 255;

					// set space can go
				}
				else
				{
					if (0 == mapVal)
					{
						// obst
						*(pixel+0) = 0;
						*(pixel+1) = 0;
						*(pixel+2) = 255;
						*(pixel+3) = 255;

						isHasObst = true;
					}
					else
					{
						// will never go here
						*(pixel+0) = (unsigned char)mapVal;
						*(pixel+1) = (unsigned char)mapVal;
						*(pixel+2) = (unsigned char)mapVal;
						*(pixel+3) = 255;
					}
				}
			}

			int adjustVal = mRobotMapData->SelfDrawMapData2D[i];
			if (0 == adjustVal)
			{
				*(pixel + 0) = 255;
				*(pixel + 1) = 255;
				*(pixel + 2) = 255;
				*(pixel + 3) = 255;

				isHasObst = true;
			}
			else if (200 == adjustVal)
			{
			}
			else if (201 == adjustVal)
			{
				*(pixel + 0) = 0;
				*(pixel + 1) = 255;
				*(pixel + 2) = 0;
				*(pixel + 3) = 255;

				isHasObst = false;
			}

			if (isHasObst)
			{
#if defined PX2_USE_VOXEL
				float xPos = (x - halfSize) * resolution;
				float yPos = (halfSize - y) * resolution;
				APoint targetPos(xPos, yPos, 0.0f);
				APoint targetPos1(xPos, yPos, 0.05f);
				APoint targetPos2(xPos, yPos, 0.1f);

				// obst
				if (mVoxelSection)
				{
					mVoxelSection->SetBlock(targetPos, 1);
					mVoxelSection->SetBlock(targetPos1, 1);
					mVoxelSection->SetBlock(targetPos2, 1);
				}
#endif
			}

			int drawVaL = mRobotMapData->LineDrawMapData2D[i];
			if (0 != drawVaL)
			{
				*(pixel + 0) = 0;
				*(pixel + 1) = 0;
				*(pixel + 2) = drawVaL;
				*(pixel + 3) = 255;
			}
		}

		mUsingRunningMap2D.resize(mapAllSize);
		memcpy(&mUsingRunningMap2D[0], mTextureMap->GetData(0), mapAllSize);

		if (mTextureMap && mapSize > 0)
			Renderer::UpdateAll(mTextureMap, 0);

		mIsMapDataChanged = false;
	}
}
//----------------------------------------------------------------------------
void Robot::FakeGoForce(const AVector &force)
{
	mForce = force;
	mIsUseForce = true;
}
//----------------------------------------------------------------------------
float Robot::GetSpeed() const
{
	return mSpeed;
}
//----------------------------------------------------------------------------
AVector Robot::GetVelocity() const
{
	return mVelocity;
}
//----------------------------------------------------------------------------
void Robot::AdjustToDirection(const AVector &dir)
{
	mIsAdjustToDirection = true;
	mAdjustToDirection = dir;
}
//----------------------------------------------------------------------------
UIFrame *Robot::GetUIFrame()
{
	return mUIFrame;
}
//----------------------------------------------------------------------------
UIVlc *Robot::GetUIVlc()
{
	return mUIVlc;
}
APoint _ChangePoint(APoint from)
{
	APoint pt = from;
	pt.X() = from.X();
	pt.Y() = from.Z();
	pt.Z() = -from.Y();
	return pt;
}
//----------------------------------------------------------------------------
void Robot::SetOffset(const AVector &offset)
{
	mOffset = offset;
}
//----------------------------------------------------------------------------
void Robot::InitSlamMap(int mapSize, float resolution)
{
	// 这里在debug下需要很久, 所以我们将其变小
#if defined _DEBUG
	mPathGraph->InitSlamMap(mapSize/4, resolution*4);
#else
	mPathGraph->InitSlamMap(mapSize, resolution);
#endif

	mRobotMapData->MapStruct.MapSize = mapSize;
	mRobotMapData->MapStruct.MapResolution = resolution;

	int mapAllSize = mapSize * mapSize;
	if (mRobotMapData->SelfDrawMapData2D.empty())
	{
		mRobotMapData->SelfDrawMapData2D.resize(mapAllSize);
		memset(&(mRobotMapData->SelfDrawMapData2D[0]), 200, (int)mapAllSize);
	}

	if (mRobotMapData->LineDrawMapData2D.empty())
	{
		mRobotMapData->LineDrawMapData2D.resize(mapAllSize);
		memset(&(mRobotMapData->LineDrawMapData2D[0]), 0, (int)mapAllSize);
	}

	bool isNeedReCreateMapTex = false;
	if (!mTextureMap)
	{
		isNeedReCreateMapTex = true;
	}
	else
	{
		if (mapSize != mTextureMap->GetWidth())
			isNeedReCreateMapTex = true;
	}

	if (isNeedReCreateMapTex)
	{
		_RecreateMapTex(mapSize);
	}

	mIsInitSlamMap = true;
	mIsMapDataChanged = true;
}
//----------------------------------------------------------------------------
void Robot::SetSlam2DMap(std::vector<unsigned char> &map, int mapSize,
	float resolution)
{
	if (!mIsInitSlamMap)
		return;

	if (!map.empty())
	{
		mRobotMapData->Map2DOrigin = map;
		mRobotMapData->ConvertOriginToUsing(false);
		mIsMapDataChanged = true;
	}
	mRobotMapData->MapStruct.MapSize = mapSize;
	mRobotMapData->MapStruct.MapResolution = resolution;
}
//----------------------------------------------------------------------------
int Robot::GetMapSize() const
{
	return mRobotMapData->MapStruct.MapSize;
}
//----------------------------------------------------------------------------
float Robot::GetResolution() const
{
	return mRobotMapData->MapStruct.MapResolution;
}
//----------------------------------------------------------------------------
void Robot::_LargerMapObst(Texture2D *tex2D)
{
	unsigned char *dst = (unsigned char*)tex2D->GetData(0);
	int width = tex2D->GetWidth();
	int height = tex2D->GetHeight();
	unsigned char *toData = new unsigned char[width*height];
	memset(toData, 0, width*height);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int pixelIndex = y*width + x;
			unsigned char *pixel = dst + pixelIndex*4;
			if (255 == *(pixel+2))
			{
				_SetPixelVal(tex2D, toData, y, x);

				int left = x - 1;
				if (left < 0)
					left = 0;
				_SetPixelVal(tex2D, toData, y, left);

				int right = x + 1;
				if (right >= width)
					right = width - 1;
				_SetPixelVal(tex2D, toData, y, right);

				int down = y - 1;
				if (down < 0)
					down = 0;
				_SetPixelVal(tex2D, toData, down, x);

				int up = y + 1;
				if (up >= height)
					up = height - 1;
				_SetPixelVal(tex2D, toData, up, x);
			}
		}
	}
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int pixelIndex = y*width + x;
			unsigned char *pixel = dst + pixelIndex * 4;
			if (255 == *(toData+pixelIndex))
			{
				// obst
				*pixel++ = 0;
				*pixel++ = 0;
				*pixel++ = 255;
				*pixel++ = 255;
			}
		}
	}

	delete[] toData;
}
//----------------------------------------------------------------------------
void Robot::_SetPixelVal(Texture2D *tex2D, unsigned char *toData, 
	int indexY, int indexX)
{
	int width = tex2D->GetWidth();

	int pixelIndex = indexY*width + indexX;
	unsigned char *pixel = toData + pixelIndex;
	*pixel++ = 255;
}
//----------------------------------------------------------------------------
void Robot::SetSlam2DPosition(const APoint &pos, float angle)
{
	if (mPosition == pos && m2DSlameAngle == angle)
		return;

	mMapSlam2DMoveDirection = pos - mPosition;
	float moveDirectionSquare = mMapSlam2DMoveDirection.SquaredLength();
	if (moveDirectionSquare > 0.00000001f)
		mMapSlam2DMoveDirection.Normalize();
	mPosition = pos;
	m2DSlameAngle = angle;

	mRobotMapData->MapStruct.CurPos = pos;
	mRobotMapData->MapStruct.CurAngle = angle;

	Arduino::AxisObj axisObj = mArduino->GetCurAxisObj();
	mCurMoveDirectionAxisY = axisObj.Y;

	if (!mIsHasEverSettedDirection && moveDirectionSquare > 0.00000001f)
	{
		PX2_LOG_INFO("Has Ever setted Direction");

		mFirstMoveDirectionAxisY = axisObj.Y + mOffsetDegree;
		mFirstMoveDirection = mMapSlam2DMoveDirection;

		mIsHasEverSettedDirection = true;
	}

	if (mIsHasEverSettedDirection)
	{
		float dotVal = mFirstMoveDirection.Dot(mMapSlam2DMoveDirection);
		float rad = Mathf::ACos(dotVal);
		float degree = rad * Mathf::RAD_TO_DEG;

		AVector cross = mFirstMoveDirection.Cross(mMapSlam2DMoveDirection);
		if (cross.Z() > 0)
		{
		}
		else
		{
			degree *= -1.0f;
		}

		mMoveDirectionDegreeWithFirst = degree;
		mDegreeAdjust = (mMoveDirectionDegreeWithFirst - mCurMoveDirectionAxisY);
	}

	float xDir = Mathf::Sin(-angle);
	float yDir = Mathf::Cos(angle);
	AVector dir = AVector(xDir, yDir, 0.0f);
	dir.Normalize();
	mDirection = dir;
	mDirection.Normalize();

	mRight = mDirection.Cross(AVector::UNIT_Z);
	mUp = AVector::UNIT_Z;
	mMatrix = HMatrix(mRight, mDirection, mUp, mPosition, true);

	if (mLiDar)
	{
		mLiDar->SetCurTransform(mMatrix);
	}

	HMatrix mat;
	mat.MakeRotation(AVector::UNIT_Y, -angle);
	mRobotTex->LocalTransform.SetRotate(mat);

	float mapWidth = mRobotMapData->MapStruct.MapSize *
		mRobotMapData->MapStruct.MapResolution;

	float xPos = (pos.X() + mapWidth*0.5f) / mapWidth;
	float yPos = (pos.Y() + mapWidth*0.5f) / mapWidth;

	mRobotTex->SetAnchorHor(xPos, xPos);
	mRobotTex->SetAnchorVer(yPos, yPos);
}
//----------------------------------------------------------------------------
void Robot::SetRoleType(RoleType rtType)
{
	mRoleType = rtType;
}
//----------------------------------------------------------------------------
void Robot::CreateLidar()
{
	if (mLiDar)
	{
		mLiDar->Close();
		mLiDar = 0;
	}

	mLiDar = new0 LiDar();
	LiDar::LiDarType lidarType = mLiDar->GetLiDarType();
	if (LiDar::LT_III == lidarType)
	{
		mOffsetDegree = -90.0f;
	}
	else if (LiDar::LT_RP == lidarType)
	{
		mOffsetDegree = 90.0f;
	}
}
//----------------------------------------------------------------------------
bool Robot::LidarOpen(const std::string &portIP, int baudratePort)
{
	if (mLiDar)
	{
		return mLiDar->Open(portIP, baudratePort);
	}

	return false;
}
//----------------------------------------------------------------------------
void Robot::SetArduino(Arduino *arduino)
{
	mArduino = arduino;
}
//----------------------------------------------------------------------------
bool Robot::IsArduinoConnected() const
{
	return mArduino->IsInitlized();
}
//----------------------------------------------------------------------------
void Robot::SetOffsetDegree(float degree)
{
	mOffsetDegree = degree;
}
//----------------------------------------------------------------------------
float Robot::GetOffsetDegree() const
{
	return mOffsetDegree;
}
//----------------------------------------------------------------------------
float Robot::GetYawCrossValue() const
{
	LiDar::LiDarType lidarType = mLiDar->GetLiDarType();
	if (LiDar::LT_III == lidarType)
	{
		return -1.0f;
	}
	else if (LiDar::LT_RP == lidarType)
	{
		return 1.0f;
	}

	return 1.0f;
}
//----------------------------------------------------------------------------
void Robot::SetVoxelSection(VoxelSection *vs)
{
	mVoxelSection = vs;
}
//----------------------------------------------------------------------------
VoxelSection *Robot::GetVoxelSection()
{
	return mVoxelSection;
}
//----------------------------------------------------------------------------
AVector &Robot::GetAxisDirection()
{
	return mAxisDirection;
}
//----------------------------------------------------------------------------
HMatrix &Robot::GetAxisRotMatrix()
{
	return mAxisRotMatrix;
}
//----------------------------------------------------------------------------
void Robot::_UpdateVirtualRobot(float elaplseSeconds)
{
	if (!mAgent)
		return;

	float forceVal = mForce.Normalize();
	mDirection.Normalize();

	float width = 1;

	float forceGo = MAX_SPEED;
	float turnRoundSpeed = MAX_SPEED;
	float turnRoundDegree = 20;
	float turnRoundVal = Mathf::Cos(turnRoundDegree);

	float forceDotDirVal = mForce.Dot(mDirection);
	float radForce = Mathf::ACos(forceDotDirVal);
	float sinVal = Mathf::Sin(radForce);
	float cosVal = Mathf::Cos(radForce);

	float allSpdHor = forceGo * sinVal;
	allSpdHor = Mathf::FAbs(allSpdHor);

	AVector cross = mForce.Cross(mDirection);

	float leftSpeedA = 0.0f;
	float rightSpeedA = 0.0f;
	if (cross.Z() > 0.0f)
	{
		if (forceVal < 0.01f)
		{
			rightSpeedA = 0.0f;
			leftSpeedA = 0.0f;
		}
		else
		{
			if (forceDotDirVal >= turnRoundVal)
			{
				// go right
				rightSpeedA = forceGo - allSpdHor;
				leftSpeedA = rightSpeedA + allSpdHor;
			}
			else
			{
				rightSpeedA = -turnRoundSpeed;
				leftSpeedA = turnRoundSpeed;
			}
		}
	}
	else
	{
		if (forceVal < 0.01f)
		{
			rightSpeedA = 0.0f;
			leftSpeedA = 0.0f;
		}
		else
		{
			if (forceDotDirVal >= turnRoundVal)
			{
				// go left
				leftSpeedA = forceGo - allSpdHor;
				rightSpeedA = leftSpeedA + allSpdHor;
			}
			else
			{
				leftSpeedA = -turnRoundSpeed;
				rightSpeedA = turnRoundSpeed;
			}
		}
	}

	mLeftSpeed = leftSpeedA;
	mRightSpeed = rightSpeedA;

	mLeftSpeed = mLeftSmoother->Update(mLeftSpeed, elaplseSeconds);
	mRightSpeed = mRightSmoother->Update(mRightSpeed, elaplseSeconds);

	float rotSpeed = mRightSpeed - mLeftSpeed;
	float rotDist = rotSpeed * elaplseSeconds;
	float rotRad = (rotDist / width);
	mRotationRad += rotRad;

	mSpeed = (mLeftSpeed + mRightSpeed) * 0.5f;

	if (mArduino->IsInitlized())
	{
		int iLeftSpeed = (int)((mLeftSpeed / forceGo) * 60);
		int iRightSpeed = (int)((mRightSpeed / forceGo) * 60);
		mArduino->RunSpeed(0, iLeftSpeed);
		mArduino->RunSpeed(1, iRightSpeed);

		mVelocity = mDirection * mSpeed;
	}
	else
	{
		mDirection = AVector(-Mathf::Sin(mRotationRad), Mathf::Cos(mRotationRad), 0.0f);
		mDirection.Normalize();

		mVelocity = mDirection * mSpeed;

		mPosition += mVelocity * elaplseSeconds;
	}


	if (mCurPathPlan)
	{
		std::vector<PathingNode*> vec;
		std::list<PathingNode*> list = mCurPathPlan->m_path;
		auto it = list.begin();
		while (it != list.end())
		{
			PathingNode *pathNode = *it;
			APoint pos = pathNode->GetPos();

			vec.push_back(*it);
			it++;
		}

		for (int i = 0; i < (int)vec.size()-1; i++)
		{
			PathingNode *node = vec[i];
			PathingNode *nodeNext = vec[i + 1];

			Vector3f curPos = node->GetPos();
			Vector3f nextPos = nodeNext->GetPos();

			EngineSceneCanvas::GetSingleton().AddDebugLine(curPos, nextPos,
				Float4::BLUE);
		}
	}
}
//----------------------------------------------------------------------------
void Robot::_RunSpeed(float elaplseSeconds)
{
	if (mArduino && mArduino->IsInitlized())
	{

	}
	else
	{
		RobotState rs = Motion(mRobotState, mLeftSpeed, mRightSpeed, 
			elaplseSeconds);
		mPosition = APoint(rs.Pos.X(), rs.Pos.Y(), 0.0f);
		mRotationRad = rs.Orientation;
		mDirection = AVector(-Mathf::Sin(mRotationRad), Mathf::Cos(mRotationRad), 0.0f);
		mDirection.Normalize();
	}
}
//----------------------------------------------------------------------------
std::vector<Vector2f > Robot::GetNearObst(float radius)
{
	std::vector<Vector2f> obsts;

	std::vector<AIAgentObject*> objs =
		mAgent->GetSteeringBehavior()->GetNearbyObjects(radius);
	for (int i = 0; i < (int)objs.size(); i++)
	{
		APoint pos = objs[i]->GetPosition();
		obsts.push_back(pos.To2());
	}

	if (mRobotMapData)
	{
		int mapSize = mRobotMapData->MapStruct.MapSize;
		float halfMapSize = mapSize * 0.5f;
		float resolution = mRobotMapData->MapStruct.MapResolution;

		float fxPosStart = mPosition.X() - radius;
		int xPosStart = (int)(fxPosStart / resolution);
		xPosStart += halfMapSize;
		xPosStart = Math<int>::Clamp(xPosStart, 0, mapSize);

		float fxPosEnd = mPosition.X() + radius;
		int xPosEnd = (int)(fxPosEnd / resolution);
		xPosEnd += halfMapSize;
		xPosEnd = Math<int>::Clamp(xPosEnd, 0, mapSize);

		float fyPosStart = mPosition.Y() - radius;
		int yPosStart = (int)(fyPosStart / resolution);
		yPosStart = halfMapSize + yPosStart;
		yPosStart = Math<int>::Clamp(yPosStart, 0, mapSize);

		float fyPosEnd = mPosition.Y() + radius;
		int yPosEnd = (int)(fyPosEnd / resolution);
		yPosEnd = halfMapSize + yPosEnd;
		yPosEnd = Math<int>::Clamp(yPosEnd, 0, mapSize);

		for (int y = yPosStart; y < yPosEnd; y++)
		{
			for (int x = xPosStart; x < xPosEnd; x++)
			{
				int index = y * mapSize + x;
				int mapVal = mRobotMapData->Map2DUsing[index];

				bool isObjst = false;
				if (mapVal == 100)
				{			
					int a = 0;
				}
				else if (mapVal == 10)
				{
					//isObjst = true;
				}
				else if (mapVal == 200)
				{
					int a = 0;
				}
				else if (0 == mapVal)
				{
					isObjst = true;
					int a = 0;
				}
				else
				{
					int a = 0;
				}
				if (isObjst)
				{
					float xPos = (x - halfMapSize) * resolution;
					float yPos = (y - halfMapSize) * resolution;
					obsts.push_back(Vector2f(xPos, yPos));
				}
			}
		}
	}

	return obsts;
}
//----------------------------------------------------------------------------
void Robot::_UpdateVirtualRobot1(float elaplseSeconds)
{
	if (!mAgent)
		return;

	AISteeringPath &steerPath = mAgent->GetSteeringBehavior()->GetPath();

	std::vector<std::vector<RobotState> > outRobotStates;

	int selectIndex = -1;
	if (!steerPath.Finished())
	{
		Vector3f targetPos = steerPath.CurrentWaypoint();
		AVector diff = targetPos - mPosition;
		float distance = diff.Normalize();
		float dotDirVal = diff.Dot(mDirection);
		float radForce = Mathf::ACos(dotDirVal);
		float sinVal = Mathf::Sin(radForce);
		float cosVal = Mathf::Cos(radForce);

		float allSpdHor = MAX_SPEED * sinVal;
		allSpdHor = Mathf::FAbs(allSpdHor);

		AVector cross = diff.Cross(mDirection);

		float turnRoundDegree = 20;
		float turnRoundVal = Mathf::Cos(turnRoundDegree);

		bool goMoving = false;
		float leftSpeedA = 0.0f;
		float rightSpeedA = 0.0f;
		//if (cross.Z() >= 0.0f)
		//{
		//	if (dotDirVal >= turnRoundVal)
		//	{
		//		// go right
		//		goMoving = true;

		//		rightSpeedA = MAX_SPEED - allSpdHor;
		//		leftSpeedA = rightSpeedA + allSpdHor;
		//	}
		//	else
		//	{
		//		leftSpeedA = MAX_SPEED;
		//		rightSpeedA = -MAX_SPEED;
		//	}

		//}
		//else
		//{
		//	if (dotDirVal >= turnRoundVal)
		//	{
		//		goMoving = true;

		//		leftSpeedA = MAX_SPEED - allSpdHor;
		//		rightSpeedA = leftSpeedA + allSpdHor;
		//	}
		//	else
		//	{
		//		leftSpeedA = -MAX_SPEED;
		//		rightSpeedA = MAX_SPEED;
		//	}
		//}

		//if (!goMoving)
		//{
		//	mLeftSpeed = leftSpeedA;
		//	mRightSpeed = rightSpeedA;
		//}
		//else
		{
			APoint curWayPoint = steerPath.CurrentWaypoint();
			Vector2f curWayPoint2 = curWayPoint.To2();

			std::vector<Vector2f> obsts = GetNearObst(0.8f);

			RobotState ste = _GetCurRobotState();
			std::vector<float> selectPlan = DynamicWindowApproach(ste,
				curWayPoint2, obsts, outRobotStates);

			float leftSpeed = selectPlan[0];
			float rightSpeed = selectPlan[1];
			selectIndex = selectPlan[2];

			mLeftSpeed = leftSpeed;
			mRightSpeed = rightSpeed;
		}

		_RunSpeed(elaplseSeconds);
	}
	else
	{ 
		mLeftSpeed = 0;
		mRightSpeed = 0;
	}

	// draw paths
	for (int i = 0; i < (int)outRobotStates.size(); i++)
	{
		std::vector<RobotState> states = outRobotStates[i];
		if (states.size() > 1)
		{
			Float4 addColor = Float4::GREEN;
			if (selectIndex == i)
				addColor = Float4::RED;

			for (int j = 0; j < (int)states.size() - 1; j++)
			{
				RobotState roS0 = states[j];
				RobotState roS1 = states[j + 1];

				APoint pos0(roS0.Pos.X(), roS0.Pos.Y(), 0.0f);
				APoint pos1(roS1.Pos.X(), roS1.Pos.Y(), 0.0f);

				EngineSceneCanvas::GetSingleton().AddDebugLine(pos0, pos1,
					addColor);
			}
		}
	}
}
//----------------------------------------------------------------------------
void Robot::GoTarget(const APoint &targetPos, PathType type)
{
	mGoTargetPos = targetPos;

	std::vector<PathingNode*> vec;
	AISteeringPath aiAgentPath;

	if (type == PT_A)
	{
		mCurPathPlan = mPathGraph->FindPath(mPosition, mGoTargetPos);
		if (mCurPathPlan)
		{
			PathingNodeList list = mCurPathPlan->m_path;
			int numPoints = list.size();

			auto it = list.begin();
			for (; it != list.end(); it++)
			{
				PathingNode *node = *it;

				APoint pos = node->GetPos();
				aiAgentPath.AddWayPoint(pos);

				SetLineValueAtPos(node->GetPos(), 0.05f, 200.0f);
			}

			mCurPathPlan->ResetPath();
		}
	}
	else
	{
		if (mEnviroment)
		{
			APoint targetPos1 = targetPos;
			Vector2f pos2 = targetPos1.To2();
			mEnviroment->targetSet(pos2);
		}
	}


	if (mAgent)
	{
		mAgent->SetPath(aiAgentPath);
	}
}
//----------------------------------------------------------------------------
void Robot::_SetAIAgent(AIAgent *agent)
{
	mAgent = agent;
}
//----------------------------------------------------------------------------
AIAgent *Robot::GetAIAgent()
{
	return mAgent;
}
//----------------------------------------------------------------------------
bool Robot::_IsInRightDirection(const AVector &dir)
{
	float valDot = dir.Dot(mDirection);
	float degree = Mathf::ACos(valDot) * Mathf::RAD_TO_DEG;
	if (degree < 10.0f)
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void Robot::_UpdateAdjustDirection(const AVector &dir)
{
	float valDot = dir.Dot(mDirection);
	float degree = Mathf::ACos(valDot) * Mathf::RAD_TO_DEG;
	if (degree < 12.0f)
	{
	}
	else
	{
		if (mDirection != AVector::ZERO)
		{
			AVector right = mDirection.Cross(dir);
			if (right.Z() > 0.0f)
			{
				// move left
				mArduino->Run(Arduino::SDT_LEFT, 25.0f);
			}
			else
			{
				// move right
				mArduino->Run(Arduino::SDT_RIGHT, 25.0f);
			}
		}
	}
}
//----------------------------------------------------------------------------
RobotState Robot::Motion(RobotState curState, float leftSpeed, 
	float rightSpeed, float elapsedSeconds)
{
	RobotState afterMoveState;

	float rotSpeed = rightSpeed - leftSpeed;
	float rotDist = rotSpeed * elapsedSeconds;
	float rotRad = (rotDist / ROBOT_RADIUS);

	afterMoveState.Orientation = curState.Orientation + rotRad;
	afterMoveState.LeftSpeed = leftSpeed;
	afterMoveState.RightSpeed = rightSpeed;

	float speed = (leftSpeed + rightSpeed) / 2.0f;

	Vector2f direction(-Mathf::Sin(afterMoveState.Orientation), Mathf::Cos(afterMoveState.Orientation));
	direction.Normalize();
	afterMoveState.Pos = curState.Pos + direction * speed * elapsedSeconds;

	return afterMoveState;
}
//----------------------------------------------------------------------------
std::vector<RobotState> Robot::GenerateTraj(RobotState initState,
	float leftSpeed, float rightSpeed)
{
	RobotState tempState = initState;
	vector<RobotState> trajectories;
	float time = 0;
	trajectories.push_back(initState);
	while (time < PREDICT_TIME)
	{
		tempState = Motion(tempState, leftSpeed, rightSpeed, DT);
		trajectories.push_back(tempState);
		time += DT;
	}

	return trajectories;
}
//----------------------------------------------------------------------------
std::vector<float> Robot::CreateDW(RobotState curState)
{
	std::vector<float> dw(4);
	float tmpMinLeftSpeed = curState.LeftSpeed - MAX_ACCELERATE*DT;
	float tmpMaxLeftSpeed = curState.LeftSpeed + MAX_ACCELERATE*DT;

	float tmpMinRightSpeed = curState.RightSpeed - MAX_ACCELERATE*DT;
	float tmpMaxRightSpeed = curState.RightSpeed + MAX_ACCELERATE*DT;

	dw[0] = Mathf::Clamp(tmpMinLeftSpeed, MIN_SPEED, MAX_SPEED);
	dw[1] = Mathf::Clamp(tmpMaxLeftSpeed, MIN_SPEED, MAX_SPEED);

	dw[2] = Mathf::Clamp(tmpMinRightSpeed, MIN_SPEED, MAX_SPEED);
	dw[3] = Mathf::Clamp(tmpMaxRightSpeed, MIN_SPEED, MAX_SPEED);

	return dw;
}
//----------------------------------------------------------------------------
RobotState Robot::_GetCurRobotState()
{
	RobotState state;
	state.Pos = mPosition.To2();
	state.LeftSpeed = mLeftSpeed;
	state.RightSpeed = mRightSpeed;
	state.Orientation = mRotationRad;

	return state;
}
//----------------------------------------------------------------------------
float Robot::CalcHeading(RobotState rState, const Vector2f &goal)
{
	AVector diff = APoint(goal.X(), goal.Y(), 0.0f)
		- APoint(rState.Pos.X(), rState.Pos.Y(), 0.0f);
	float diffLength = diff.Normalize();
	if (diffLength < 0.01f)
		return 180.0f;

	AVector dir = AVector(-Mathf::Sin(rState.Orientation), 
		Mathf::Cos(rState.Orientation), 0.0f);
	dir.Normalize();

	float dotVal = diff.Dot(dir);

	float rad = Mathf::ACos(dotVal);
	float degree = rad * Mathf::RAD_TO_DEG;

	return 180.0f - degree;
}
//----------------------------------------------------------------------------
float Robot::CalcClearance(RobotState rState, std::vector<Vector2f> &obs)
{
	float dist = 100.0f;
	float distTemp;
	int numObs = (int)obs.size();
	for (int i = 0; i < numObs; i++)
	{
		Vector2f diff = rState.Pos - obs[i];
		float length = diff.Length();

		distTemp = length - ROBOT_RADIUS * 2;

		if (distTemp < dist)
		{
			dist = distTemp;
		}
	}

	if (dist >= 2 * ROBOT_RADIUS)
	{
		dist = 2 * ROBOT_RADIUS;
	}

	return dist;
}
//----------------------------------------------------------------------------
float CalcBreakingDist(float velo)
{
	float stopDist = 0;
	while (velo > 0)
	{
		stopDist = stopDist + velo*DT;
		velo = velo - MAX_ACCELERATE*DT;
	}

	return stopDist;
}
//----------------------------------------------------------------------------
std::vector<float> Robot::DynamicWindowApproach(RobotState rState,
	const Vector2f &target, std::vector<Vector2f> &obstacle, 
	std::vector<std::vector<RobotState> > &outRobotStates)
{
	// 0:leftMin, 1:leftMax, 2:rightMin, 3:rightMax
	std::vector<float> velocityAndOmegaRange = CreateDW(rState);

	std::vector<EvaluationPara> evalParas;
	float sumHeading = 0;
	float sumClearance = 0;
	float sumSpeed = 0;

	for (float l = velocityAndOmegaRange[0]; l < velocityAndOmegaRange[1]; l += SAMPLING_SPEED)
	{
		for (double r = velocityAndOmegaRange[2]; r < velocityAndOmegaRange[3]; r += SAMPLING_SPEED)
		{
			std::vector<RobotState> trajectories = GenerateTraj(rState, l, r);

			RobotState stateBack = trajectories.back();

			float speed = (l + r) / 2.0f;

			float tempClearance = CalcClearance(stateBack, obstacle);
			float stopDist = CalcBreakingDist(speed);

			if (tempClearance > stopDist)
			{
				outRobotStates.push_back(trajectories);

				EvaluationPara tempEvalPara;
				tempEvalPara.Index = (int)outRobotStates.size() - 1;

				tempEvalPara.DiffHeading = CalcHeading(stateBack, target);

				tempEvalPara.Clearance = tempClearance;
				tempEvalPara.Leftspped = l;
				tempEvalPara.RightSpeed = r;
				tempEvalPara.Speed = speed;

				sumSpeed += speed;
				sumHeading += tempEvalPara.DiffHeading;
				sumClearance += tempClearance;

				evalParas.push_back(tempEvalPara);
			}
		}
	}

	float selectedLeftSpeed = 0;
	float selectedRightSpeed = 0;
	int selectIndex = -1;

	std::vector<float> selVelocity;
	selVelocity.resize(3);

	if (evalParas.empty())
	{
		/*_*/
	}
	else
	{
		float G = 0;
		EvaluationPara selectEva;
		for (vector<EvaluationPara>::iterator i = evalParas.begin(); i < evalParas.end(); i++)
		{
			float smoothHeading = i->DiffHeading / sumHeading;
			float smoothClearance = i->Clearance / sumClearance;
			float smoothVelocity = i->Speed / sumSpeed;

			float tempG = WEIGHT_HEADING*smoothHeading + WEIGHT_CLEARANCE*smoothClearance + WEIGHT_VELOCITY*smoothVelocity;
			(*i).LastValue = tempG;

			if (tempG > G)
			{
				G = tempG;
				selectedLeftSpeed = i->Leftspped;
				selectedRightSpeed = i->RightSpeed;
				selectIndex = (*i).Index;

				selectEva = *i;
			}
		}
	}

	selVelocity[0] = selectedLeftSpeed;
	selVelocity[1] = selectedRightSpeed;
	selVelocity[2] = selectIndex;

	return selVelocity;
}
//----------------------------------------------------------------------------