// EasyPRManager.cpp

#include "EasyPRManager.hpp"
#include "PX2UDPServer.hpp"
#include "easypr.h"
#include "easypr/util/switch.hpp"
#include "PX2Application.hpp"
#include "PX2ScopedCS.hpp"
#include "PX2Arduino.hpp"
#include "PX2GeneralClientConnector.hpp"
#include "PX2GraphicsEventType.hpp"
using namespace PX2;

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
	else if ("dooropen" == cmd)
	{
		EasyPRM.SetDoorState(EasyPRManager::DS_OPENING);
	}
	else if ("doorclose" == cmd)
	{
		EasyPRM.SetDoorState(EasyPRManager::DS_CLOSEING);
	}
	else if ("doorstop" == cmd)
	{
		EasyPRM.SetDoorState(EasyPRManager::DS_STOP);
	}
	else if ("doorperc" == cmd)
	{
		float perc = StringHelp::StringToFloat(paramStr);
		EasyPRM.SetDoorToPercent(perc);
	}
	else if ("disconnectaiot" == cmd)
	{
		EasyPRM.mAIOTConnector->Disconnect();
	}
}
//----------------------------------------------------------------------------
EasyPRManager::EasyPRManager()
{
	mArduino = new0 Arduino();
	mDistTest = new0 DistTest();
	mDistTest->SetDistType(DistTest::DT_LIDAR);

	mDoorState = DS_STOP;
	mIsAutoAdjustingDoor = false;

	mAllClosedDist = 0.0f;
	mAllOpenedDist = 0.0f;

	mLEDScreenConnector = 0;
	mAIOTConnector = 0;
}
//----------------------------------------------------------------------------
EasyPRManager::~EasyPRManager()
{
}
//----------------------------------------------------------------------------
void EasyPRManager::SetDoorState(DoorState state)
{
	if (DS_STOP == state)
	{
		if (mArduino->IsInitlized())
		{
			mArduino->RCSend(1069360);
		}

		mDoorState = state;
	}
	else if (DS_OPENING == state)
	{
		if (DS_STOP != mDoorState)
		{
			SetDoorState(DS_STOP);

			PX2_GR.SendGeneralEvent("dooropening", 0.5f);
		}
		else
		{
			if (mArduino->IsInitlized())
			{
				mArduino->RCSend(1069504);
			}

			mDoorState = state;
		}
	}
	else if (DS_CLOSEING == state)
	{
		if (DS_STOP != mDoorState)
		{
			SetDoorState(DS_STOP);

			PX2_GR.SendGeneralEvent("doorcloseing", 0.5f);
		}
		else
		{
			if (mArduino->IsInitlized())
			{
				mArduino->RCSend(1069324);
			}

			mDoorState = state;
		}
	}
}
//----------------------------------------------------------------------------
void EasyPRManager::SetDoorToDist(float dist)
{
	mToDist = dist;
	mIsAutoAdjustingDoor = true;

	if (mCurDistFloat < mToDist)
	{
		SetDoorState(EasyPRManager::DS_OPENING);
	}
	else if (mCurDistFloat > mToDist)
	{
		SetDoorState(EasyPRManager::DS_CLOSEING);
	}
}
//----------------------------------------------------------------------------
bool EasyPRManager::IsAutoAdjustingDoor() const
{
	return mIsAutoAdjustingDoor;
}
//----------------------------------------------------------------------------
EasyPRManager::DoorState EasyPRManager::GetDoorState() const
{
	return mDoorState;
}
//----------------------------------------------------------------------------
void EasyPRManager::SetDoorToPercent(float perc)
{
	if (mAllClosedDist == mAllOpenedDist)
		return;

	if (perc < 0)
		perc = 0;

	if (perc > 1.0f)
		perc = 1.0f;

	float toDist = mAllClosedDist + (mAllOpenedDist - mAllClosedDist)*perc;
	SetDoorToDist(toDist);
}
//----------------------------------------------------------------------------
void EasyPRManager::SetClosedDist(float dist)
{
	mAllClosedDist = dist;
}
//----------------------------------------------------------------------------
void EasyPRManager::SetOpenedDist(float dist)
{
	mAllOpenedDist = dist;
}
//----------------------------------------------------------------------------
int EasyPRManager::GetCurDist() const
{
	return mCurDist;
}
//----------------------------------------------------------------------------
float EasyPRManager::GetCurDistFloat() const
{
	return mCurDistFloat;
}
//----------------------------------------------------------------------------
void EasyPRManager::_SetCurDist(int dist)
{
	mCurDist = dist;
	mCurDistFloat = mCurDist * 0.01f;

	float distFloat = EasyPRM.GetCurDistFloat();
	PX2_LOG_INFO("Recv:%.2f", distFloat);
}
//----------------------------------------------------------------------------
void EasyPRManager::SendScreenStr(const std::string &screen)
{
	if (screen == mLastSendStr)
	{
		return;
	}

	if (mLEDScreenConnector && mLEDScreenConnector->IsConnected())
	{
		std::string setStr = "text " + screen;
		mLEDScreenConnector->SendRawBuffer(setStr.c_str(), setStr.length());
	}
	else
	{
		PX2_LOG_INFO("LEDScreen Is not connected!");
	}

	mLastSendStr = screen;
}
//----------------------------------------------------------------------------
void EasyPRManager::SendAIOT(const std::string &content)
{
	if (mAIOTConnector && mAIOTConnector->IsConnected())
	{
		mAIOTConnector->SendRawBuffer(content.c_str(), content.length());
	}
	else
	{
		PX2_LOG_INFO("Is not connected!");
	}
}
//----------------------------------------------------------------------------
void _AIOTRecvCallback(ClientConnector *connector, const std::string &recvStr)
{
	PX2_LOG_INFO("Recv Str:%s", recvStr.c_str());
}
//----------------------------------------------------------------------------
bool EasyPRManager::Initlize()
{
	PX2_EW.ComeIn(this);

	IPAddress ipAddr = PX2_APP.GetLocalAddressWith10_172_192();
	SocketAddress udpAddr(ipAddr, 9808);

	mIsDoStop = false;

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

	mDistTest->InitlizeUDP();

	//mArduino->Initlize(Arduino::M_SERIAL, "COM6");
	System::SleepSeconds(2.0f);
	mArduino->Update(0.1f);
	mArduino->RCInit(Arduino::P_11);

	mDistTest->SendToGetData("192.168.31.163", 2333);

	mTestTimer = 0;

	SetClosedDist(0.11f);
	SetOpenedDist(6.8f);

	EasyPRM.SetURL0("192.168.31.204:554");
	//EasyPRM.SetURl1("192.168.31.203:554");

	mLEDScreenConnector = PX2_APP.CreateGetGeneralClientConnector(
		"EasyPR");
	mLEDScreenConnector->ConnectNB("127.0.0.1", 8000);

	mAIOTConnector = PX2_APP.CreateGetGeneralClientConnector(
		"AOIT");
	mAIOTConnector->ConnectB("127.0.0.1", 9800);
	mAIOTConnector->AddRecvCallback(_AIOTRecvCallback);

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
bool EasyPRManager::Ternimate()
{
	PX2_EW.GoOut(this);

	mIsDoStop = true;

	if (mArduino)
	{
		delete0(mArduino);
		mArduino = 0;
	}

	PX2_APP.ShutdownGeneralClientConnector("EasyPR");
	PX2_APP.ShutdownGeneralClientConnector("AOIT");

	mLEDScreenConnector = 0;
	mAIOTConnector = 0;

	System::SleepSeconds(1.0f);

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
void EasyPRManager::OnEvent(Event *event)
{
	if (GraphicsES::IsEqual(event, GraphicsES::GeneralString))
	{
		std::string dataStr = event->GetDataStr0();
		if ("dooropening" == dataStr)
		{
			SetDoorState(EasyPRManager::DS_OPENING);
		}
		else if ("doorcloseing" == dataStr)
		{
			SetDoorState(EasyPRManager::DS_CLOSEING);
		}
	}
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

	mEasyPRObject0->Update(elapsedSeconds);
	mEasyPRObject1->Update(elapsedSeconds);

	if (mDistTest)
	{
		mDistTest->Update(elapsedSeconds);
	}

	if (mIsAutoAdjustingDoor)
	{
		float dist = Mathf::FAbs(mToDist - mCurDistFloat);
		if (dist <= 0.15f)
		{
			SetDoorState(EasyPRManager::DS_STOP);

			mIsAutoAdjustingDoor = false;
		}
	}

	mTestTimer += elapsedSeconds;
	if (mTestTimer > 2.0f)
	{
		//SendAIOT("carnumber 34890341");

		mTestTimer = 0.0f;
	}
}
//----------------------------------------------------------------------------
