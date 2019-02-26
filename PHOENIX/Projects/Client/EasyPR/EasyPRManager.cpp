// EasyPRManager.cpp

#include "EasyPRManager.hpp"
#include "PX2UDPServer.hpp"
#include "easypr.h"
#include "easypr/util/switch.hpp"
#include "PX2Application.hpp"
#include "PX2ScopedCS.hpp"
using namespace PX2;

void _EasyPRUDPServerRecvCallback(UDPServer *sever,
	SocketAddress &address, const std::string &buf, int length)
{
	StringTokenizer stk(buf, " ");

	std::string cmd;
	std::string param0;
	std::string param1;

	if (stk.Count() > 0)
		cmd = stk[0];
	if (stk.Count() > 1)
		param0 = stk[1];
	if (stk.Count() > 2)
		param1 = stk[2];

	std::string ip = address.GetHost().ToString();

	if ("aa" == cmd)
	{
		std::string paramName = param0;

	}
}
void _EasyPRVedioServerRecvCallback(UDPServer *sever,
	SocketAddress &address, const std::string &buf, int length)
{
}
//----------------------------------------------------------------------------
EasyPRManager::EasyPRManager() :
	mUDPServer(0)
{
	mUsingBuffer = 0;
	mPushingBuffer = 0;
}
//----------------------------------------------------------------------------
EasyPRManager::~EasyPRManager()
{
}
//----------------------------------------------------------------------------
bool EasyPRManager::Initlize()
{
	IPAddress ipAddr = PX2_APP.GetLocalAddressWith10_172_192();
	SocketAddress udpAddr(ipAddr, 9808);

	mIsDoStop = false;
	mUDPServer = new0 UDPServer(udpAddr);
	mUDPServer->AddRecvCallback(_EasyPRUDPServerRecvCallback);
	mUDPServer->Start();

	UIFrame *frame = PX2_PROJ.GetUI();	
	UIVlc *frameVLC = new0 UIVlc();
	mVLC0 = frameVLC;
	frame->AttachChild(frameVLC);
	frameVLC->SetAnchorHor(0.0f, 0.5f);
	frameVLC->SetAnchorVer(0.0f, 1.0f);

	UIVlc *frameVLC1 = new0 UIVlc();
	frame->AttachChild(frameVLC1);
	mVLC1 = frameVLC1;
	frameVLC1->SetAnchorHor(0.5f, 1.0f);
	frameVLC1->SetAnchorVer(0.0f, 1.0f);

	mUsingBuffer = &mBuffer0;
	mPushingBuffer = &mBuffer1;

	SetURL0("192.168.31.204:554");
	SetURl1("192.168.31.203:554");

	mRecognizeThread = new0 Thread();
	mRecognizeThread->Start(*this);
	mIsDoStop = false;

	return true;
}
//----------------------------------------------------------------------------
void EasyPRManager::SetURL0(const std::string &url0)
{
	std::string url = std::string("rtsp://") + url0 + 
		"/user=admin_password=tlJwpbo6_channel=1_stream=0.sdp?real_stream";
	mVLC0->StartVLC(url);
}
//----------------------------------------------------------------------------
void EasyPRManager::SetURl1(const std::string &url1)
{
	std::string url = std::string("rtsp://") + url1 +
		"/user=admin_password=tlJwpbo6_channel=1_stream=0.sdp?real_stream";
	mVLC1->StartVLC(url);
}
//----------------------------------------------------------------------------
//nH,nW为BYTE*类型图像的高和宽,nFlag为通道数
bool EasyPRManager::_ByteToMat(char* pImg, int nH, int nW, Mat& outImg)
{
	int nByte = nH * nW * 4;
	int nType = CV_8UC4;
	outImg = Mat::zeros(nH, nW, nType);
	memcpy(outImg.data, pImg, nByte);
	return true;
}
//----------------------------------------------------------------------------
void EasyPRManager::Recognize(const std::string &filename)
{
	Mat src = imread(filename);
	_Recognize(src);
}
//----------------------------------------------------------------------------
void EasyPRManager::_Recognize(const Mat &mat)
{
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
			cout << "plateRecognize: " << plateVec[j].getPlateStr() 
				<< "  score:" << plateVec[j].getPlateScore() <<endl;
		}
	}

	if (result != 0) cout << "result:" << result << endl;
}
//----------------------------------------------------------------------------
bool EasyPRManager::Ternimate()
{
	mIsDoStop = true;

	if (mUDPServer)
	{
		mUDPServer = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
void EasyPRManager::Run()
{
	while (!mIsDoStop)
	{
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
}
//----------------------------------------------------------------------------
void EasyPRManager::Update(float appSeconds, float elapsedSeconds)
{
	const std::vector<char> &lastBuffer =
		mVLC0->GetVLCMemObj()->GetLastBuffer();
	mBufferWidth = mVLC0->GetVLCMemObj()->GetMediaWidth();
	mBufferHeight = mVLC0->GetVLCMemObj()->GetMediaHeight();
	*mPushingBuffer = lastBuffer;

	if (mUDPServer)
	{
		mUDPServer->Update(elapsedSeconds);
	}

	{
		ScopedCS cs(&mRecogMutex);
		std::vector<char> *tempBuf = mPushingBuffer;
		mPushingBuffer = mUsingBuffer;
		mUsingBuffer = tempBuf;
	}
}
//----------------------------------------------------------------------------
