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

	if ("showpic" == cmd)
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
		EasyPRM.mRPConnector->Disconnect();
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
	mRPConnector = 0;
	mIsRPConnected = false;
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

	//float distFloat = EasyPRM.GetCurDistFloat();
	//PX2_LOG_INFO("Recv:%.2f", distFloat);
}
//----------------------------------------------------------------------------
GeneralClientConnector *EasyPRManager::GetLEDScreenConnector()
{
	return mLEDScreenConnector;
}
//----------------------------------------------------------------------------
GeneralClientConnector *EasyPRManager::GetRPConnector()
{
	return mRPConnector;
}
//----------------------------------------------------------------------------
GeneralClientConnector *EasyPRManager::GetNodeConnector()
{
	return mNodeConnector;
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
	if (mRPConnector && mRPConnector->IsConnected())
	{
		mRPConnector->SendRawBuffer(content.c_str(), content.length());
	}
	else
	{
		PX2_LOG_INFO("Is not connected!");
	}
}
//----------------------------------------------------------------------------
void _RPRecvCallback(ClientConnector *connector, const std::string &recvStr)
{
	EasyPRManager *mgr = connector->GetUserData<EasyPRManager*>(
		"EasyPRManager");
	if (mgr)
	{

	}
}
//----------------------------------------------------------------------------
void _NodeRecvCallback(ClientConnector *connector, const std::string &recvStr)
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

	PX2_APP.AddAppCmdCallback(_AppCmdCallback);

	// udpdist
	mDistTest->InitlizeUDP();
	mDistTest->SendToGetData("192.168.31.193", 2333);

	// opendoor
	mArduino->Initlize(Arduino::M_SERIAL, "COM6");
	System::SleepSeconds(2.0f);
	mArduino->Update(0.1f);
	mArduino->RCInit(Arduino::P_11);

	mTestTimer = 0;

	SetClosedDist(0.11f);
	SetOpenedDist(6.8f);

	mLEDScreenConnector = PX2_APP.CreateGetGeneralClientConnector(
		"LEDScreen");
	mIsLEDScreenConnected = false;
	mLEDScreenConnector->ConnectNB("127.0.0.1", 8000);

	mRPConnector = PX2_APP.CreateGetGeneralClientConnector("RP");
	mRPConnector->AddRecvCallback(_RPRecvCallback);
	mIsRPConnected = false;
	mRPConnector->SetUserData("EasyPRManager", this);
	mRPConnector->ConnectNB("127.0.0.1", 9800);

	mNodeConnector = PX2_APP.CreateGetGeneralClientConnector("Node");
	mNodeConnector->AddRecvCallback(_NodeRecvCallback);
	mIsNodeConnected = false;
	mNodeConnector->SetUserData("EasyPRManager", this);
	mNodeConnector->ConnectNB("127.0.0.1", 9801);

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

	PX2_APP.ShutdownGeneralClientConnector("LEDScreen");
	PX2_APP.ShutdownGeneralClientConnector("AOIT");

	mLEDScreenConnector = 0;
	mRPConnector = 0;

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
		if (mEasyPRObject0)
			mEasyPRObject0->UpdateRecognize();

		if (mEasyPRObject1)
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

	if (mEasyPRObject0)
		mEasyPRObject0->Update(elapsedSeconds);

	if (mEasyPRObject1)
		mEasyPRObject1->Update(elapsedSeconds);

	if (mDistTest)
	{
		mDistTest->Update(elapsedSeconds);
	}

	if (!mIsLEDScreenConnected && mLEDScreenConnector &&
		mLEDScreenConnector->IsConnected())
	{
		PX2_LOG_INFO("LEDScreenConnected connected!");

		mIsLEDScreenConnected = true;
	}

	if (!mIsRPConnected && mRPConnector && mRPConnector->IsConnected())
	{
		PX2_LOG_INFO("RPConnector connected!");

		mIsRPConnected = true;
	}

	if (!mIsNodeConnected && mNodeConnector && mNodeConnector->IsConnected())
	{
		PX2_LOG_INFO("NodeConnector connected!");

		mIsNodeConnected = true;
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
