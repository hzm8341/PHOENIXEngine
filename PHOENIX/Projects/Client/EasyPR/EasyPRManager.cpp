// EasyPRManager.cpp

#include "EasyPRManager.hpp"
#include "PX2UDPServer.hpp"
#include "easypr.h"
#include "easypr/util/switch.hpp"
#include "PX2Application.hpp"
#include "PX2ScopedCS.hpp"
#include "PX2Arduino.hpp"
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
//----------------------------------------------------------------------------
void _AppCmdCallback(
	const std::string &cmd,
	const std::string &paramStr,
	const std::string &paramStr1,
	const std::string &paramStr2)
{
	Arduino *arduino = EasyPRM.GetArduino();
	DistTest *dist = EasyPRM.mDistTest;

	if ("startvedio" == cmd)
	{
		EasyPRM.SetURL0("192.168.31.204:554");
		EasyPRM.SetURl1("192.168.31.203:554");
	}
	else if ("showpic" == cmd)
	{
		if ("true" == paramStr)
		{
			EasyPRM.mVLC0->ShowPic(true);
			EasyPRM.mVLC1->ShowPic(true);
		}
		else if ("false" == paramStr)
		{
			EasyPRM.mVLC0->ShowPic(false);
			EasyPRM.mVLC1->ShowPic(false);
		}
	}
	else if ("arduino" == cmd)
	{
		if ("connect" == paramStr)
		{
			if (arduino->Initlize(Arduino::M_SERIAL, paramStr1))
			{
				PX2_LOG_INFO("Connect suc");
			}
			else
			{
				PX2_LOG_INFO("Connect failed");
			}
		}
		else if ("tcp" == paramStr)
		{
			int port = StringHelp::StringToInt(paramStr2);
			if (arduino->InitlizeESPSocketTCP_Connector(paramStr1, port))
			{

			}
		}
	}
	else if ("rcinit" == cmd)
	{
		arduino->RCInit(Arduino::P_11);
	}
	else if ("rcsend" == cmd)
	{
		long val = StringHelp::StringToLong(paramStr);
		arduino->RCSend(val);
	}
	else if ("digitWrite" == cmd)
	{
		int val = StringHelp::StringToInt(paramStr);
		arduino->DigitalWrite(Arduino::P_13, val==1?true:false);
	}
	else if ("getdist" == cmd)
	{
		int port = StringHelp::StringToInt(paramStr1);
		dist->SendToGetData(paramStr, port);
	}
	else if ("dist" == cmd)
	{
		dist->InitlizeSerial();
	}
}
//----------------------------------------------------------------------------
EasyPRManager::EasyPRManager() :
	mUDPServer(0)
{
	mArduino = new0 Arduino();
	mDistTest = new0 DistTest();

	mDoorState = DS_NONE;
}
//----------------------------------------------------------------------------
EasyPRManager::~EasyPRManager()
{
}
//----------------------------------------------------------------------------
void EasyPRManager::SetDoorState(DoorState state)
{
	mDoorState = state;

	if (DS_STOP == mDoorState)
	{
		mArduino->RCSend();
	}
	else if (DS_OPENING == mDoorState)
	{
		mArduino->RCSend();
	}
	else if (DS_CLOSEING == mDoorState)
	{
		mArduino->RCSend();
	}
}
//----------------------------------------------------------------------------
EasyPRManager::DoorState EasyPRManager::GetDoorState() const
{
	return mDoorState;
}
//----------------------------------------------------------------------------
int EasyPRManager::GetCurDist() const
{
	return mCurDist;
}
//----------------------------------------------------------------------------
float EasyPRManager::GetCurDistFloat() const
{
	return (float)(mCurDist * 0.01f);
}
//----------------------------------------------------------------------------
void EasyPRManager::_SetCurDist(int dist)
{
	mCurDist = dist;
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

	mEasyPRObject0 = new0 EasyPRRecvObject(mVLC0);
	mEasyPRObject1 = new0 EasyPRRecvObject(mVLC1);

	mRecognizeThread = new0 Thread();
	mRecognizeThread->Start(*this);
	mIsDoStop = false;

	PX2_APP.AddAppCmdCallback(_AppCmdCallback);

	//mDistTest->InitlizeSerial();

	mDistTest->InitlizeUDP();

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

	if (mArduino)
	{
		delete0(mArduino);
		mArduino = 0;
	}

	mVLC0 = 0;
	mVLC1 = 0;

	mEasyPRObject0 = 0;
	mEasyPRObject1 = 0;

	mDistTest->Ternimate();
	mDistTest = 0;

	return true;
}
//----------------------------------------------------------------------------
Arduino *EasyPRManager::GetArduino()
{
	return mArduino;
}
//----------------------------------------------------------------------------
void EasyPRManager::Run()
{
	while (!mIsDoStop)
	{
		mEasyPRObject0->UpdateRecognize();
		mEasyPRObject1->UpdateRecognize();
	}
}
//----------------------------------------------------------------------------
void EasyPRManager::Update(float appSeconds, float elapsedSeconds)
{
	if (mArduino)
	{
		mArduino->Update(elapsedSeconds);
	}

	if (mUDPServer)
	{
		mUDPServer->Update(elapsedSeconds);
	}

	mEasyPRObject0->Update();
	mEasyPRObject1->Update();

	if (mDistTest)
	{
		mDistTest->Update(elapsedSeconds);
	}
}
//----------------------------------------------------------------------------
