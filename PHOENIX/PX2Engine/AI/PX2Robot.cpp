// PX2Robot.cpp

#include "PX2Robot.hpp"
#include "PX2Creater.hpp"
#include "PX2Project.hpp"
#include "PX2JSONData.hpp"
#include "PX2Timestamp.hpp"
#include "PX2Timespan.hpp"
#if defined PX2_USE_VOXEL
#include "PX2VoxelSection.hpp"
#endif
#include "PX2AIES.hpp"
#include "PX2Renderer.hpp"
#include "PX2Arduino.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2AIAgentPath.hpp"
#if defined PX2_USE_SLAM2D
#include "Slam2DPlugin.hpp"
#endif
#include "PX2PluginManager.hpp"
using namespace PX2;

#if defined _WIN32 || defined WIN32
#include <windows.h> 
#endif
//----------------------------------------------------------------------------
#define BUF_SIZE 1024*128
char szName[] = "PHOENIXSlam";    // 共享内存的名字
//----------------------------------------------------------------------------
Slam2DPlugin *Robot::mSlam2DPlugin = 0;
//----------------------------------------------------------------------------
Robot::Robot() :
mLiDar(0),
mIsSlamLost3D(false),
mVoxelSection(0),
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
mPathUpdateTiming(0.0f),
mDragingLeftMoveType(0),
mDragingLeftMoveSpeed(0.0f),
mDragingRightMoveType(0),
mDragingRightMoveSpeed(0.0f)
{
	mRoleType = RT_MASTER;

	mBufShare = 0;

#if defined _WIN32 || defined WIN32
	mHandler = 0;
#endif

	mUIFrame = new0 UIFrame();

	mUIVlc = new0 UIVlc();
	mUIFrame->AttachChild(mUIVlc);
	mUIVlc->SetType(UIVlc::T_HARDCAMERA);
	mUIVlc->SetAnchorHor(0.0f, 1.0f);
	mUIVlc->SetAnchorVer(0.0f, 1.0f);

	mPosition = APoint::ORIGIN;

	mCameraDirection = AVector::UNIT_Y;
	mCameraRight = AVector::UNIT_X;
	mCameraUp = AVector::UNIT_Z;

	mDirection = AVector::UNIT_Y;
	mRight = AVector::UNIT_X;
	mUp = AVector::UNIT_Z;

	// leidar
	mPicBoxMap = new0 UIFPicBox();
	mPicBoxMap->GetUIPicBox()->GetMaterialInstance()
		->GetMaterial()->GetPixelShader(0, 0)->SetFilter(0,
		Shader::SF_NEAREST);

	mRobotMapData = new0 RobotMapData();
	_RecreateMapTex(mRobotMapData->MapStruct.MapSize, mRobotMapData->MapStruct.MapSize/2);

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

	mIsGoPathPlan = false;
	mPathGraph = new0 PathingGraph();

	mIsInitSlamMap = false;
	mIsMapDataChanged = true;

	mArduino = new0 Arduino();

	mFakeFoceTimer = 0.0f;
	mFakeSpeed = 1.0f;
	mIsAdjustToDirection = false;
	mIsUseFakeForce = false;
}
//----------------------------------------------------------------------------
Robot::~Robot()
{
	if (mLiDar)
	{
		delete0(mLiDar);
	}

	ShutdownShareMenory();

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
	float resolution = mRobotMapData->MapStruct.MapResolution;
	std::vector<unsigned char> map = mRobotMapData->Map2D;
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

		int adjustVal = mRobotMapData->SelfDrawMapData2D[i];
		if (0 == adjustVal)
		{
			isHasObst = true;
		}
		else if (200 == adjustVal)
		{
		}
		else if (201 == adjustVal)
		{
			isHasObst = false;
		}

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
inline const APoint &Robot::GetPosition() const
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
void Robot::_RecreateMapTex(int mapSize, int smallMapSize)
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
void Robot::StartShareMemory()
{
	if (mBufShare)
	{
		ShutdownShareMenory();
	}

#if defined _WIN32 || defined WIN32
	HANDLE hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // 物理文件句柄  
		NULL,                    // 默认安全级别  
		PAGE_READWRITE,          // 可读可写  
		0,                       // 高位文件大小  
		BUF_SIZE,                // 地位文件大小  
		szName                   // 共享内存名称  
		);
	mHandler = hMapFile;

	mBufShare = (char *)MapViewOfFile(
		hMapFile,            // 共享内存的句柄  
		FILE_MAP_ALL_ACCESS, // 可读写许可  
		0,
		0,
		BUF_SIZE
		);

	memset(mBufShare, 0, BUF_SIZE);
#endif

	mIsSlamLost3D = false;
}
//----------------------------------------------------------------------------
void Robot::ShutdownShareMenory()
{
#if defined _WIN32 || defined WIN32
	if (mBufShare)
	{
		UnmapViewOfFile(mBufShare);
		CloseHandle((HANDLE)mHandler);
		mBufShare = 0;
		mHandler = 0;
	}
#endif
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

	if (mBufShare)
	{
		int bufShareLength = strlen(mBufShare);
		PX2_UNUSED(bufShareLength);

		JSONData data;
		if (data.LoadBuffer(mBufShare))
		{
			std::string cam_matrix = data.GetMember("cam_mat").ToString();
			bool isLost = data.GetMember("islost").ToBool();

			SetCurSlam3DTransformLost(isLost);

			HMatrix mat = _MatFromString(cam_matrix);
			SetCurSlam3DCameraMatrix(mat);

			AllPoints.clear();
			JSONValue jValPointsAll = data.GetMember("points");
			int arraySize = jValPointsAll.GetArraySize();
			for (int i = 0; i < arraySize; i++)
			{
				JSONValue jMPoint = jValPointsAll.GetArrayElement(i);
				std::string ptStraight = jMPoint.ToString();
				bool isBad = false;
				int key = 0;
				APoint pt = _PtFromString(ptStraight, key, isBad);
				Slam3DPoint spt;
				spt.Key = key;
				spt.Pos = pt;
				spt.IsBad = isBad;
				AllPoints.push_back(spt);
			}
			_RefreshVoxelSection(AllPoints, 1);

			CurPoints.clear();
			JSONValue jValPointsCur = data.GetMember("points_cur");
			for (int i = 0; i < jValPointsCur.GetArraySize(); i++)
			{
				JSONValue jMPoint = jValPointsCur.GetArrayElement(i);
				std::string ptStraight = jMPoint.ToString();
				bool isBad = false;
				int key = 0;
				APoint pt = _PtFromString(ptStraight, key, isBad);
				Slam3DPoint spt;
				spt.Key = key;
				spt.Pos = pt;
				spt.IsBad = isBad;
				CurPoints.push_back(spt);
			}
			_RefreshVoxelSection(CurPoints, 2);
		}
	}
	else
	{
		_RefreshVoxelSection(AllPoints, 1);
		_RefreshVoxelSection(CurPoints, 2);
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

	if (mLiDar)
	{
		mLiDar->Update(appseconds, elpasedSeconds);
	}

	if (mIsGoPathPlan)
		_CheckPathUpdateing(appseconds, elpasedSeconds);

	if (mIsAdjustToDirection)
	{
		if (!_IsInRightDirection(mAdjustToDirection))
		{
			_UpdateAdjustDirection(mAdjustToDirection);
		}
		else
		{
			mIsAdjustToDirection = false;
			
			if (mArduino && mArduino->IsInitlized())
				mArduino->Run(Arduino::SDT_FORWARD, 75);
		}
	}

	if (mIsUseFakeForce)
	{
		mFakeFoceTimer += elpasedSeconds;
		if (mFakeFoceTimer > 0.1f)
		{
			_UpdateVirtualRobot(mFakeFoceTimer);

			//AVector moveDir = mPosition - mLastPostion;
			//mLastPostion = mPosition;
			//float moveLength = moveDir.Length();
			//float moveSpeed = moveLength / mFakeFoceTimer;

			//AVector force = mFakeForce;
			//float forceLength = force.Normalize();
			//float forcePerc = forceLength / 10.0f;
			//if (forcePerc > 1.0f)
			//	forcePerc = 1.0f;
			//float power = forcePerc * 80.0f;

			//float dotVal = mDirection.Dot(force);
			//AVector crossVal = force.Cross(mDirection);
			//float degree = Mathf::ACos(dotVal);
			//Vector2f dir2d;
			//if (crossVal.Z() > 0.0f)
			//{
			//	dir2d = Vector2f(Mathf::Sin(degree), Mathf::Cos(degree));
			//}
			//else
			//{
			//	dir2d = Vector2f(-Mathf::Sin(degree), Mathf::Cos(degree));
			//}

			//_CalSpeed(dir2d, forcePerc);
			//mArduino->RunSpeed(0, mDragingLeftMoveSpeed);
			//mArduino->RunSpeed(1, mDragingRightMoveSpeed);

			//_MoveTypeCal(dir2d, power);
			//mArduino->Run(0, (Arduino::DirectionType)mDragingLeftMoveType, mDragingLeftMoveSpeed);
			//mArduino->Run(1, (Arduino::DirectionType)mDragingRightMoveType, mDragingRightMoveSpeed);

			////if (forceLength > 0.01f)
			//{
			//	float adjustValue0 = 0.7f;

			//	float dotVal = mDirection.Dot(force);
			//	AVector crossVal = force.Cross(mDirection);

			//	mFackVelocity = mDirection * moveSpeed;
			//	mFakeSpeed = moveSpeed;

			//	if (crossVal.Z() > 0.0f)
			//	{
			//		if (dotVal > adjustValue0)
			//		{
			//			float adjustDotValue = (dotVal - adjustValue0) / (1.0f - adjustValue0);

			//			// right
			//			mArduino->Run(0, Arduino::DT_FORWARD, power);
			//			mArduino->Run(1, Arduino::DT_FORWARD, power * adjustDotValue * adjustDotValue * adjustDotValue * adjustDotValue);
			//		}
			//		else
			//		{
			//			// right
			//			mArduino->Run(0, Arduino::DT_FORWARD, power * 0.5f);
			//			mArduino->Run(1, Arduino::DT_BACKWARD, power * 0.5);
			//		}
			//	}
			//	else
			//	{
			//		if (dotVal > adjustValue0)
			//		{
			//			float adjustDotValue = (dotVal - adjustValue0) / (1.0f - adjustValue0);

			//			// left
			//			mArduino->Run(0, Arduino::DT_FORWARD, power * adjustDotValue * adjustDotValue * adjustDotValue * adjustDotValue);
			//			mArduino->Run(1, Arduino::DT_FORWARD, power);
			//		}
			//		else
			//		{

			//			mArduino->Run(0, Arduino::DT_BACKWARD, power * 0.5);
			//			mArduino->Run(1, Arduino::DT_FORWARD, power * 0.5);
			//		}
			//	}
			//}
			////else
			//{
			//	//mArduino->Stop();
			//}

			mFakeFoceTimer = 0.0f;
		}
	}

	int mapSize = mRobotMapData->MapStruct.MapSize;
	int resolution = mRobotMapData->MapStruct.MapResolution;
	std::vector<unsigned char> map = mRobotMapData->Map2D;

	if (mIsMapDataChanged && mIsInitSlamMap)
	{
		int mapAllSize = mapSize * mapSize;
		int robotindex = 0;
		int x = 0;
		int y = 0;
		int sx = 0;
		int sy = 0;
		char *dst = mTextureMap->GetData(0);
		int width = mTextureMap->GetWidth();
		for (int i = 0; i < mapAllSize; i++)
		{
			x = (i + width) % width;
			y = ((width - 1) - i / width);
			sx = (int)((float)x);
			sy = (int)((float)y);

			unsigned char *pixel = (unsigned char*)dst + y * width * 4 + x * 4;

			*(pixel + 0) = 0;	// b
			*(pixel + 1) = 0;	// g
			*(pixel + 2) = 0;	// r
			*(pixel + 3) = 255;

			bool isHasObst = false;
			int mapVal = 200;
			if (!map.empty())
			{
				mapVal = map[i];

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

			int drawVaL = mRobotMapData->LineDrawMapData2D[i];
			if (0 != drawVaL)
			{
				*(pixel + 0) = 0;
				*(pixel + 1) = 0;
				*(pixel + 2) = drawVaL;
				*(pixel + 3) = 255;
			}
		}

		//_LargerMapObst(mTextureMapSmaller);

		if (mTextureMap && mapSize > 0)
			Renderer::UpdateAll(mTextureMap, 0);

		//_RefreshVoxelSection(mRobotMapData->Map2D, resolution);

		mIsMapDataChanged = false;
	}
}
//----------------------------------------------------------------------------
void Robot::_CheckPathUpdateing(float appSeconds, float elapsedSeconds)
{
	mPathUpdateTiming += elapsedSeconds;

	if (mPathUpdateTiming > 0.2f)
	{
		if (mCurPathPlan && mArduino->IsInitlized())
		{
			if (mCurPathPlan->CheckForEnd())
			{
				mArduino->Run(Arduino::SDT_NONE, 0.0f);
				PX2_LOG_INFO("Ended");

				mCurPathPlan = 0;
			}
			else
			{
				APoint curPos = mCurPathPlan->GetCurrentNodePosition();

				AVector toDir = curPos - mPosition;
				toDir.Normalize();

				AdjustToDirection(toDir);

				mCurPathPlan->CheckForNextNode(mPosition);
			}
		}

		mPathUpdateTiming = 0.0f;
	}
}
//----------------------------------------------------------------------------
void Robot::FakeGoForce(const AVector &force)
{
	mFakeForce = force;
	mIsUseFakeForce = true;
}
//----------------------------------------------------------------------------
float Robot::GetSpeed() const
{
	return mFakeSpeed;
}
//----------------------------------------------------------------------------
AVector Robot::GetVelocity() const
{
	return mFackVelocity;
}
//----------------------------------------------------------------------------
void Robot::AdjustToDirection(const AVector &dir)
{
	mIsAdjustToDirection = true;
	mAdjustToDirection = dir;
}
//----------------------------------------------------------------------------
Float3 Robot::_FromString(const std::string &str)
{
	StringTokenizer stkCamPos(str, ",");
	float x = StringHelp::StringToFloat(stkCamPos[0]);
	float y = StringHelp::StringToFloat(stkCamPos[1]);
	float z = StringHelp::StringToFloat(stkCamPos[2]);

	return Float3(x, y, z);
}
//----------------------------------------------------------------------------
HMatrix Robot::_MatFromString(const std::string &str)
{
	HMatrix mat;
	StringTokenizer stkMat(str, ",");

	for (int i = 0; i < 16; i++)
	{
		int row = (i + 4) % 4;
		int col = i/4;
		mat[row][col] = StringHelp::StringToFloat(stkMat[i]);
	}

	return mat;
}
//----------------------------------------------------------------------------
APoint Robot::_PtFromString(const std::string &str, int &key, bool &isBad)
{
	StringTokenizer stkCamPos(str, ",");
	float x = StringHelp::StringToFloat(stkCamPos[0]);
	float y = StringHelp::StringToFloat(stkCamPos[1]);
	float z = StringHelp::StringToFloat(stkCamPos[2]);
	isBad = std::string("0") == stkCamPos[3];
	key = StringHelp::StringToInt(stkCamPos[4]);

	return APoint(x, y, z);
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
void Robot::_RefreshVoxelSection(std::vector<Slam3DPoint> &points,
	int mtlType)
{
	PX2_UNUSED(mtlType);

	if (!mVoxelSection)
		return;

	for (int i = 0; i < (int)points.size(); i++)
	{
		Slam3DPoint &sp = points[i];
		if (sp.IsBad)
			continue;

		APoint targetPos = _ChangePoint(sp.Pos);
		targetPos.X() *= 10.0f;
		targetPos.Y() *= 10.0f;
		targetPos.Z() *= 10.0f;
		if (targetPos.Z() < 0.2f)
			continue;

#if defined PX2_USE_VOXEL
		mVoxelSection->SetBlock(targetPos, mtlType);
#endif
	}
}
//----------------------------------------------------------------------------
void Robot::SetOffset(const AVector &offset)
{
	mOffset = offset;
}
//----------------------------------------------------------------------------
void Robot::SetCurSlam3DTransformLost(bool lost)
{
	mIsSlamLost3D = lost;

	if (mLiDar)
	{
		mLiDar->SetCurSlam3DTransformLost(lost);
	}
}
//----------------------------------------------------------------------------
bool Robot::IsCurSlam3DTransformLost() const
{
	return mIsSlamLost3D;
}
//----------------------------------------------------------------------------
void Robot::SetCurSlam3DCameraMatrix(HMatrix &mat)
{
	if (mIsSlamLost3D)
		return;

	HMatrix matRot;
	matRot.MakeRotation(AVector::UNIT_X, Mathf::DEG_TO_RAD * -90.0f);
	HMatrix matrix = matRot * mat;

	Scene *scene = PX2_PROJ.GetScene();
	if (scene)
	{
		APoint pos = APoint(mat[0][3], mat[1][3], mat[2][3]);
		APoint toPos = _ChangePoint(pos);
		toPos.X() *= 10.0f;
		toPos.Y() *= 10.0f;
		toPos.Z() *= 10.0f;
		toPos.Z() += 1.0f;

		AVector right;
		AVector dir;
		AVector up;
		matrix.GetColumn(0, right);
		matrix.GetColumn(1, dir);
		matrix.GetColumn(2, up);

		AVector lastright = right;
		AVector lastdir =  up;
		AVector lastup = -dir;

		mCameraPosition = toPos;
		mCameraDirection = lastdir;
		mCameraUp = lastup;
		mCameraRight = lastright;
		mCameraMatrix = HMatrix(mCameraRight, mCameraDirection, mCameraUp,
			mCameraPosition, true);

		mCameraPosition = mCameraPosition - mOffset;
		mPosition = mCameraPosition;

		mRight = mCameraRight;
		mRight.Z() = 0.0f;
		mRight.Normalize();
		mDirection = AVector::UNIT_Z.Cross(mRight);
		mDirection.Z() = 0.0f;
		mDirection.Normalize();
		mUp = AVector::UNIT_Z;
		mMatrix = HMatrix(mRight, mDirection, mUp, mPosition, true);

		if (mLiDar)
		{
			mLiDar->SetCurTransform(mMatrix);
		}
	}
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
		_RecreateMapTex(mapSize, mapSize / 2);
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
		mRobotMapData->Map2D = map;
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
void Robot::_RefreshVoxelSection(std::vector<unsigned char> &map,
	float reso)
{
	if (map.empty())
		return;

	int robotindex = 0;
	int x = 0;
	int y = 0;
	int width = mTextureMap->GetWidth();
	for (int i = 0; i < width; i++)
	{
		x = i % width;
		y = ((width - 1) - i / width);

		APoint pos((x - mRobotMapX)*reso, (y-mRobotMapY)*reso, 0.0f);

		int mapVal = map[i];

		if (mapVal == 100)
		{
			// robot
			robotindex = i;
		}
		else if (mapVal == 10)
		{
			// none
		}
		else if (mapVal == 200)
		{
			// space can go
		}
		else
		{
			if (0 == mapVal)
			{
#if defined PX2_USE_VOXEL
				// obst
				if (mVoxelSection)
					mVoxelSection->SetBlock(pos, 1);
#endif
			}
		}
	}
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
void Robot::_CalSpeed(const Vector2f &dir, float power)
{
	float absX = Mathf::FAbs(dir.X());
	if (absX < 0.1)
	{
		if (dir.X() == 0)
		{
			mDragingLeftMoveSpeed += 20;
			mDragingRightMoveSpeed += 20;
		}	}

		else if (dir.X() < 0)
		{
			mDragingLeftMoveSpeed += 20;
			mDragingRightMoveSpeed += 30;
		}
		else if (dir.X() > 0)
		{
			mDragingLeftMoveSpeed += 30;
			mDragingRightMoveSpeed += 20;
		}
	else
	{
		if (dir.X() < 0)
		{
			mDragingLeftMoveSpeed -= 20;
		}
		else if (dir.X() > 0)
		{
			mDragingRightMoveSpeed -= 20;
		}
	}

	if (mDragingLeftMoveSpeed > 80)
		mDragingLeftMoveSpeed = 80;

	if (mDragingLeftMoveSpeed < -80)
		mDragingLeftMoveSpeed = -80;

	if (mDragingRightMoveSpeed > 80)
		mDragingRightMoveSpeed = 80;

	if (mDragingRightMoveSpeed < -80)
		mDragingRightMoveSpeed = -80;
}
//----------------------------------------------------------------------------
void Robot::_MoveTypeCal(const Vector2f &dir, float strength)
{
	const Vector2f dragDir = dir;
	float dragingStrength = strength;
	float absX = Mathf::FAbs(dragDir.X());
	float signX = Mathf::Sign(dragDir.X());
	float absY = Mathf::FAbs(dragDir.Y());
	float signY = Mathf::Sign(dragDir.Y());
	float param = 1.0f;

	if (0.0f == absX && 0.0f == absY)
	{
		mDragingLeftMoveType = 0;
		mDragingLeftMoveSpeed = 0.0f;
		mDragingRightMoveType = 0;
		mDragingRightMoveSpeed = 0.0f;
	}
	else
	{
		if (absY > absX)
		{
			if (signY > 0.0f)
			{
				mDragingLeftMoveType = 1;
				mDragingRightMoveType = 1;
				if (signX < 0)
				{
					param = (45.0f - Mathf::ATan((float)absX / (float)absY) * Mathf::RAD_TO_DEG) / 45.0f;
					mDragingLeftMoveSpeed = dragingStrength * Lerp<float, float>(0, 1, param);
					mDragingRightMoveSpeed = dragingStrength;
				}
				else if (signX > 0)
				{
					param = (45.0f - Mathf::ATan((float)absX / (float)absY) * Mathf::RAD_TO_DEG) / 45.0f;
					mDragingLeftMoveSpeed = dragingStrength;
					mDragingRightMoveSpeed = dragingStrength  * Lerp<float, float>(0, 1, param);
				}
			}
			else if (signY < 0.0f)
			{
				mDragingLeftMoveType = 2;
				mDragingRightMoveType = 2;

				float param = 1.0f;
				if (signX < 0)
				{
					param = (45.0f - Mathf::ATan((float)absX / (float)absY) * Mathf::RAD_TO_DEG) / 45.0f;
					mDragingLeftMoveSpeed = dragingStrength;
					mDragingRightMoveSpeed = dragingStrength * Lerp<float, float>(0, 1, param);
				}
				else if (signX > 0)
				{
					param = (45.0f - Mathf::ATan((float)absX / (float)absY) * Mathf::RAD_TO_DEG) / 45.0f;
					mDragingLeftMoveSpeed = dragingStrength  * Lerp<float, float>(0, 1, param);
					mDragingRightMoveSpeed = dragingStrength;
				}
			}
		}
		else if (absY < absX)
		{
			if (signX > 0.0f)
			{
				mDragingLeftMoveType = 1;
				mDragingRightMoveType = 2;

				if (signY > 0.0f)
				{
					param = (45.0f - Mathf::ATan((float)absY / (float)absX) * Mathf::RAD_TO_DEG) / 45.0f;
					mDragingLeftMoveSpeed = dragingStrength;
					mDragingRightMoveSpeed = dragingStrength  * Lerp<float, float>(0, 1, param);
				}
				else if (signY < 0.0f)
				{
					param = (45.0f - Mathf::ATan((float)absY / (float)absX) * Mathf::RAD_TO_DEG) / 45.0f;
					mDragingLeftMoveSpeed = dragingStrength * Lerp<float, float>(0, 1, param);
					mDragingRightMoveSpeed = dragingStrength;
				}
			}
			else if (signX < 0.0f)
			{
				mDragingLeftMoveType = 2;
				mDragingRightMoveType = 1;

				if (signY > 0.0f)
				{
					param = (45.0f - Mathf::ATan((float)absY / (float)absX) * Mathf::RAD_TO_DEG) / 45.0f;
					mDragingLeftMoveSpeed = dragingStrength * Lerp<float, float>(0, 1, param);
					mDragingRightMoveSpeed = dragingStrength;
				}
				else if (signY < 0.0f)
				{
					param = (45.0f - Mathf::ATan((float)absY / (float)absX) * Mathf::RAD_TO_DEG) / 45.0f;
					mDragingLeftMoveSpeed = dragingStrength;
					mDragingRightMoveSpeed = dragingStrength * Lerp<float, float>(0, 1, param);
				}
			}
		}
	}
}
//----------------------------------------------------------------------------
static float rad = 0.0f;
static float leftSpeed = 0.0f;
static float rightSpeed = 0.0f;
static bool isDoRot = false;
static bool isDoRotShortGo = false;
static AVector lastNeedForce;
static float lastForceTimer = 0.0f;
static float rotRightDirTimer = 0.0f;
void Robot::_UpdateVirtualRobot(float elaplseSeconds)
{
	mFakeForce.Normalize();
	float dirVal = mFakeForce.Dot(mDirection);
	AVector forceA = mFakeForce * 0.2f;
	float allForce = 0.2f;
	float allSpdFront = 0.2f * dirVal;
	float radForce = Mathf::ACos(dirVal);
	float sinVal = Mathf::Sin(radForce);
	float cosVal = Mathf::Cos(radForce);
	float allSpdHor = 0.2f * sinVal;

	if (isDoRot)
	{
		if (isDoRotShortGo)
		{
			rotRightDirTimer += elaplseSeconds;
			if (rotRightDirTimer > 0.5f)
			{
				isDoRot = false;
				rotRightDirTimer = 0.0f;
			}
		}
		else
		{
			float dotVal1 = mFakeForce.Dot(mDirection);
			if (dotVal1 >= 0.8f)
			{
				isDoRotShortGo = true;
				leftSpeed = 0.2f;
				rightSpeed = 0.2f;
				rotRightDirTimer = 0.0f;
			}
		}
	}
	else
	{
		//if (dirVal <= -0.9f)
		//{
		//	lastNeedForce = mFakeForce;
		//	isDoRot = true;
		//}

		AVector cross = mFakeForce.Cross(mDirection);

		float leftSpeedA = 0.0f;
		float rightSpeedA = 0.0f;
		if (cross.Z() > 0.0f)
		{
			if (dirVal >= 0.0f)
			{
				// go right
				rightSpeedA = (allForce - allSpdHor);
				leftSpeedA = rightSpeedA + allSpdHor;
			}
			else
			{
				rightSpeedA = -(allForce - allSpdHor);
				leftSpeedA = 0.2f;
			}

			if (isDoRot)
			{
				leftSpeed = 0.2f;
				rightSpeed = -0.2f;
			}
		}
		else
		{
			if (dirVal >= 0.0f)
			{
				// go left
				leftSpeedA = (allForce - allSpdHor);
				rightSpeedA = leftSpeedA + allSpdHor;
			}
			else
			{
				leftSpeedA = -(allForce - allSpdHor);
				rightSpeedA = 0.2f;
			}

			if (isDoRot)
			{
				leftSpeed = -0.2f;
				rightSpeed = 0.2f;
			}
		}

		if (isDoRot)
		{
		}
		else
		{
			leftSpeed = leftSpeedA;
			rightSpeed = rightSpeedA;
		}
	}

	float width = 1;
	float rotSpeed = rightSpeed - leftSpeed;
	float rotDist = rotSpeed * elaplseSeconds;
	float rotRad = (rotDist / (width*Mathf::PI) ) * Mathf::TWO_PI;
	rad += rotRad;

	float spd = (leftSpeed + rightSpeed) * 0.5f;

	mDirection = AVector(-Mathf::Sin(rad), Mathf::Cos(rad), 0.0f);
	mDirection.Normalize();

	mFakeSpeed = spd;
	mFackVelocity = mDirection * mFakeSpeed;
	
	mPosition += mFackVelocity * elaplseSeconds;
}
//----------------------------------------------------------------------------
void Robot::GoTarget(const APoint &targetPos)
{
	mIsGoPathPlan = true;
	mGoTargetPos = targetPos;
	mPathUpdateTiming = 0.0f;

	mCurPathPlan = mPathGraph->FindPath(mPosition, mGoTargetPos);
	if (mCurPathPlan)
	{
		PathingNodeList list = mCurPathPlan->m_path;
		int numPoints = list.size();

		auto it = list.begin();
		for (; it != list.end(); it++)
		{
			PathingNode *node = *it;
			SetLineValueAtPos(node->GetPos(), 0.1f, 200.0f);
		}

		mCurPathPlan->ResetPath();
	}
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