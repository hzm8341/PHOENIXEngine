// EasyPRRecvObject.cpp

#include "EasyPRRecvObject.hpp"
#include "easypr.h"
#include "easypr/util/switch.hpp"
#include "PX2ScopedCS.hpp"
#include "EasyPRManager.hpp"
#include "PX2Log.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
EasyPRRecvObject::EasyPRRecvObject(UIVlc *vlc)
{
	TheVLC = vlc;

	mUsingBuffer = 0;
	mPushingBuffer = 0;
	mBufferWidth = 0;
	mBufferHeight = 0;

	mUsingBuffer = &mBuffer0;
	mPushingBuffer = &mBuffer1;
}
//----------------------------------------------------------------------------
EasyPRRecvObject::~EasyPRRecvObject()
{
}
//----------------------------------------------------------------------------
void EasyPRRecvObject::Update(float elapsedSeconds)
{
	const std::vector<char> &lastBuffer =
		TheVLC->GetVLCMemObj()->GetLastBuffer();
	mBufferWidth = TheVLC->GetVLCMemObj()->GetMediaWidth();
	mBufferHeight = TheVLC->GetVLCMemObj()->GetMediaHeight();
	*mPushingBuffer = lastBuffer;

	{
		ScopedCS cs(&mRecogMutex);
		std::vector<char> *tempBuf = mPushingBuffer;
		mPushingBuffer = mUsingBuffer;
		mUsingBuffer = tempBuf;
	}
}
//----------------------------------------------------------------------------
void EasyPRRecvObject::BeginRecognize()
{ 
	ScopedCS cs(&mResultMutex);
	mResultStrs.clear();
	mIsBeginRecognize = true;
}
//----------------------------------------------------------------------------
void EasyPRRecvObject::EndRecognize()
{
	std::string retStr;
	{
		ScopedCS cs(&mResultMutex);
		retStr = mResultStr;
		mIsBeginRecognize = false;
	}

	EasyPRM.SendScreenStr(retStr);
}
//----------------------------------------------------------------------------
void EasyPRRecvObject::UpdateRecognize()
{
	if (!mIsBeginRecognize)
		return;

	std::vector<char> toUseBuffer;
	{
		ScopedCS cs(&mRecogMutex);
		toUseBuffer = *mUsingBuffer;
	}

	if (toUseBuffer.size() > 0)
	{
		Mat mat;
		_ByteToMat((char*)&(toUseBuffer)[0], mBufferHeight,
			mBufferWidth, mat);
		cvtColor(mat, mat, CV_RGBA2RGB);

		_Recognize(mat);
	}
}
//----------------------------------------------------------------------------
//nH,nW为BYTE*类型图像的高和宽,nFlag为通道数
bool EasyPRRecvObject::_ByteToMat(char* pImg, int nH, int nW, Mat& outImg)
{
	int nByte = nH * nW * 4;
	int nType = CV_8UC4;
	outImg = Mat::zeros(nH, nW, nType);
	memcpy(outImg.data, pImg, nByte);
	return true;
}
//----------------------------------------------------------------------------
void EasyPRRecvObject::Recognize(const std::string &filename)
{
	Mat src = imread(filename);
	_Recognize(src);
}
//----------------------------------------------------------------------------
void EasyPRRecvObject::_Recognize(const Mat &mat)
{
	auto it = mResultStrs.begin();
	for (; it != mResultStrs.end(); it++)
	{
		it->second -= 0.1f;
	}

	easypr::CPlateRecognize pr;
	pr.setLifemode(true);
	pr.setDebug(false);
	pr.setMaxPlates(4);
	pr.setDetectType(easypr::PR_DETECT_CMSER);

	vector<easypr::CPlate> plateVec;
	int result = pr.plateRecognize(mat, plateVec);
	if (result == 0)
	{
		size_t num = plateVec.size();
		for (size_t j = 0; j < num; j++)
		{
			std::string regRet = plateVec[j].getPlateStr();
			double score = Mathf::FAbs(plateVec[j].getPlateScore());
			if (!regRet.empty())
			{
				mResultStrs[regRet] += score;
			}
		}
	}

	// remove not reg
	double maxCount = 0;
	std::string retStr;
	it = mResultStrs.begin();
	for (; it != mResultStrs.end(); it++)
	{
		if (it->second < 0)
		{
			it = mResultStrs.erase(it);
		}
		else
		{
			if (it->second > maxCount && it->second > 0.95f)
			{
				maxCount = it->second;
				retStr = it->first;
			}
		}
	}

	{
		ScopedCS cs(&mResultMutex);
		mResultStr = retStr;
	}
}
//----------------------------------------------------------------------------