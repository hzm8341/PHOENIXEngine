// EasyPRRecvObject.cpp

#include "EasyPRRecvObject.hpp"
#include "easypr.h"
#include "easypr/util/switch.hpp"
#include "PX2ScopedCS.hpp"
#include "EasyPRManager.hpp"
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
void EasyPRRecvObject::Update()
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
void EasyPRRecvObject::UpdateRecognize()
{
	std::vector<char> toUseBuffer;
	{
		ScopedCS cs(&mRecogMutex);
		toUseBuffer = *mUsingBuffer;
	}

	if (toUseBuffer.size() > 0)
	{
		Mat mat;
		EasyPRM._ByteToMat((char*)&(toUseBuffer)[0], mBufferHeight,
			mBufferWidth, mat);
		cvtColor(mat, mat, CV_RGBA2RGB);

		EasyPRM._Recognize(mat);
	}
}
//----------------------------------------------------------------------------