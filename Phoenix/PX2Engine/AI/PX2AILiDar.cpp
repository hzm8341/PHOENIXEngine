// PX2AILiDar.cpp

#include "PX2AILiDar.hpp"
#include "C3iroboticsLidar.h"
#include "PX2Log.hpp"
#include "PX2LidarSerialConnection.hpp"
#include "PX2Renderer.hpp"
#include "PX2Rover.hpp"
#include "Position.hpp"
#include "algorithms.hpp"
using namespace PX2;
using namespace everest::hwdrivers;

//----------------------------------------------------------------------------
static const int MAP_SIZE_PIXELS = 800;
static const double MAP_SIZE_METERS = 40;
//----------------------------------------------------------------------------
#define DEG2RAD(x) ((x)*M_PI/180.0f)
//----------------------------------------------------------------------------
int _Coords2index(double x, double y)
{
	return y * MAP_SIZE_PIXELS + x;
}
int _MM2pix(double mm)
{
	return (int)(mm / (MAP_SIZE_METERS * 1000. / MAP_SIZE_PIXELS));
}
//----------------------------------------------------------------------------
LiDar::LiDar():
mDeviceConnectin(0),
mLiDar(0)
{
	mLiDar = new everest::hwdrivers::C3iroboticsLidar();

	Texture::Format format = Texture::TF_A8R8G8B8;
	int width = 256;
	int height = 256;
	mTexture = new0 Texture2D(format, width, height, 1);

	char *pDest = mTexture->GetData(0);
	int offsetDst = 0;

	for (int row = 0; row < width; ++row)
	{
		for (int col = 0; col < height; ++col)
		{
			pDest[offsetDst + 0] = 0; // b
			pDest[offsetDst + 1] = 0; // g 
			pDest[offsetDst + 2] = 0; // r
			pDest[offsetDst + 3] = 255;

			offsetDst += 4;
		}
	}

	mPicBox = new0 UIFPicBox();
	mPicBox->GetUIPicBox()->SetTexture(mTexture);
	mPicBox->GetUIPicBox()->GetMaterialInstance()
		->GetMaterial()->GetPixelShader(0, 0)->SetFilter(0, Shader::SF_NEAREST);

	mCurPosPic = new0 UIFPicBox();
	mPicBox->AttachChild(mCurPosPic);
	mCurPosPic->LocalTransform.SetTranslateY(-2.0f);
	mCurPosPic->SetAnchorHor(0.0f, 0.0f);
	mCurPosPic->SetAnchorVer(0.0f, 0.0f);
	mCurPosPic->SetSize(16, 16);

	mRover = new0 Rover();
	mMapData = new1<unsigned char>(MAP_SIZE_PIXELS * MAP_SIZE_PIXELS);

	MinesURG04LX laser;
	mSlam = (SinglePositionSLAM*)(new0 RMHC_SLAM(laser, MAP_SIZE_PIXELS,
		MAP_SIZE_METERS, 9999));
}
//----------------------------------------------------------------------------
LiDar::~LiDar()
{
	if (mLiDar)
	{
		delete(mLiDar);
		mLiDar = 0;
	}

	if (mDeviceConnectin)
	{
		delete(mDeviceConnectin);
		mDeviceConnectin = 0;
	}

	if (mRover)
	{
		delete0(mRover);
		mRover = 0;
	}

	if (mMapData)
	{
		delete1(mMapData);
	}
	mMapData = 0;

	if (mSlam)
	{
		delete0(mSlam);
		mSlam = 0;
	}
}
//----------------------------------------------------------------------------
LiDar *LiDar::New()
{
	return new0 LiDar();
}
//----------------------------------------------------------------------------	
bool LiDar::Open(const std::string &port, int baud)
{
	if (mLiDar)
	{
		if (mDeviceConnectin)
		{
			mDeviceConnectin->close();
			delete(mDeviceConnectin);
		}

		SerialConnection *cnt = new SerialConnection();
		cnt->SetParam(port, baud);
		mDeviceConnectin = cnt;
		if (mDeviceConnectin->openSimple())
		{
			if (mDeviceConnectin)
				return mLiDar->initilize(mDeviceConnectin);
		}
	}

	return false;
}
//----------------------------------------------------------------------------
bool LiDar::IsOpened() const
{
	if (mDeviceConnectin)
	{
		return CDeviceConnection::STATUS_OPEN == mDeviceConnectin->getStatus();
	}

	return false;
}
//----------------------------------------------------------------------------
void LiDar::Close()
{
	if (mDeviceConnectin)
	{
		mDeviceConnectin->close();
		delete(mDeviceConnectin);
		mDeviceConnectin = 0;
	}
}
Position curPos;
//----------------------------------------------------------------------------
void LiDar::Update(float appSeconds, float elapsedSeconds)
{
	PX2_UNUSED(elapsedSeconds);

	if (!mLiDar || !mDeviceConnectin)
		return;

	if (CDeviceConnection::STATUS_OPEN != mDeviceConnectin->getStatus())
		return;

	//vector<double *> trajectory;

	bool isTexUpdate = false;

	TLidarGrabResult result = mLiDar->getScanData();
	switch (result)
	{
	case LIDAR_GRAB_ING:
	{
		break;
	}
	case LIDAR_GRAB_SUCESS:
	{
		TLidarScan lidar_scan = mLiDar->getLidarScan();
		size_t lidar_scan_size = lidar_scan.getSize();

		mLiDarData.resize(lidar_scan_size);
		RslidarDataComplete one_lidar_data;
		for (size_t i = 0; i < lidar_scan_size; i++)
		{
			one_lidar_data.signal = (uint8_t)lidar_scan.signal[i];
			one_lidar_data.angle = lidar_scan.angle[i];
			one_lidar_data.distance = lidar_scan.distance[i];
			mLiDarData[i] = one_lidar_data;
		}

		if (mSlam)
		{
			int *lidarData = new int [SCAN_SIZE];
			memset(lidarData, 0, SCAN_SIZE);

			for (size_t i = 0; i < lidar_scan_size; i++)
			{
				RslidarDataComplete &data = mLiDarData[i];
				float angle = data.angle;
				float dist = data.distance;
				if (angle > 360.0f) angle = 360.0f;
				int iIndex = (int)((angle / 360.0f) * SCAN_SIZE);
				if (iIndex >= SCAN_SIZE) iIndex = SCAN_SIZE - 1;
				if (iIndex < 0) iIndex = 0;
				lidarData[iIndex] = (int)(dist * 5000);
			}

			mSlam->update(lidarData);
			delete [] lidarData;

			curPos = mSlam->getpos();
		}

		isTexUpdate = true;

		break;
	}
	case LIDAR_GRAB_ERRO:
	{
		break;
	}
	case LIDAR_GRAB_ELSE:
	{
		PX2_LOG_INFO("[Main] LIDAR_GRAB_ELSE!\n");
		break;
	}
	}

	// update map
	if (mSlam)
	{
		memset(mMapData, 0, MAP_SIZE_PIXELS * MAP_SIZE_PIXELS);
		mSlam->getmap(mMapData);

		int x = _MM2pix(curPos.x_mm);
		int y = _MM2pix(curPos.y_mm);
		//curPoses.insert(std::pair<int, int>(x, y));
	}

	if (isTexUpdate)
	{
		int texWidth = mTexture->GetWidth();
		int texHeight = mTexture->GetHeight();
		char* pDest = mTexture->GetData(0);

		// clear
		int offsetDst = 0;
		for (int row = 0; row < texWidth; ++row)
		{
			for (int col = 0; col < texHeight; ++col)
			{
				pDest[offsetDst + 0] = 0; // b
				pDest[offsetDst + 1] = 0; // g 
				pDest[offsetDst + 2] = 0; // r
				pDest[offsetDst + 3] = 255;
				offsetDst += 4;
			}
		}

		//for (auto it = curPoses.begin(); it != curPoses.end(); it++)
		//{
		//	std::pair<int, int> px = *it;
		//	mMapData[_Coords2index(px.first, px.second)] = 50;
		//}

		int x = _MM2pix(curPos.x_mm);
		int y = _MM2pix(curPos.y_mm);
		float xPos = (float)x / MAP_SIZE_PIXELS;
		float yPos = (float)y / MAP_SIZE_PIXELS;
		mCurPosPic->SetAnchorHor(xPos, xPos);
		mCurPosPic->SetAnchorVer(yPos, yPos);

		for (int i = 0; i < MAP_SIZE_PIXELS; i++)
		{
			for (int j = 0; j < MAP_SIZE_PIXELS; j++)
			{
				unsigned char val = mMapData[_Coords2index(j, i)];

				float u = (float)j / (float)(MAP_SIZE_PIXELS - 1);
				float v = (float)i / (float)(MAP_SIZE_PIXELS - 1);

				int posU = texWidth * u;
				if (posU < 0) posU = 0;
				if (posU > texWidth-1) posU = texWidth-1;

				int posV = texHeight * v;
				if (posV < 0) posV = 0;
				if (posV > texHeight-1) posV = texHeight-1;

				int destPos = (posV * texWidth + posU) * 4;
				pDest[destPos + 0] = 0; // b
				pDest[destPos + 1] = 0; // g 
				pDest[destPos + 2] = val; // r
				pDest[destPos + 3] = 255;

			}
		}

		Renderer::UpdateAll(mTexture, 0);
	}
	/*

	// update cur tex
	if (isTexUpdate)
	{
		int texWidth = mTexture->GetWidth();
		int texHeight = mTexture->GetHeight();
		char* pDest = mTexture->GetData(0);

		// clear
		int offsetDst = 0;
		for (int row = 0; row < texWidth; ++row)
		{
			for (int col = 0; col < texHeight; ++col)
			{
				pDest[offsetDst + 0] = 0; // b
				pDest[offsetDst + 1] = 0; // g 
				pDest[offsetDst + 2] = 0; // r
				pDest[offsetDst + 3] = 255;
				offsetDst += 4;
			}
		}

		// update
		float maxDist = 6.0f;
		for (int i = 0; i < (int)mLiDarData.size(); i++)
		{
			RslidarDataComplete lidarData = mLiDarData[i];

			int signal = lidarData.signal;
			float angle = lidarData.angle;
			float distance = lidarData.distance;

			float rad = angle * Mathf::DEG_TO_RAD;
			float offsetX = Mathf::Cos(rad) * distance / maxDist;
			float offsetY = Mathf::Sin(rad) * distance / maxDist;
			float u = 0.5f + 0.5f * offsetX;
			float v = 0.5f + 0.5f * offsetY;
			int posU = texWidth * u;
			if (posU < 0) posU = 0;
			if (posU > texWidth) posU = texWidth;

			int posV = texHeight * v;
			if (posV < 0) posV = 0;
			if (posV > texHeight) posV = texHeight;

			int destPos = (posV * texWidth + posU)*4;
			pDest[destPos + 0] = 0; // b
			pDest[destPos + 1] = 0; // g 
			pDest[destPos + 2] = 255; // r
			pDest[destPos + 3] = 255;
		}

		Renderer::UpdateAll(mTexture, 0);
	}
	*/
}
//----------------------------------------------------------------------------
UIFPicBox *LiDar::GetUIFPicBox()
{
	return mPicBox;
}
//----------------------------------------------------------------------------