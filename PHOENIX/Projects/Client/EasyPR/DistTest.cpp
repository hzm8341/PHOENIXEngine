// DistTest.cpp

#include "DistTest.hpp"
#include "PX2System.hpp"
#include "PX2UDPServer.hpp"
#include "PX2Log.hpp"
#include "PX2StringHelp.hpp"
#include "EasyPRManager.hpp"
#include "PX2Log.hpp"
using namespace PX2;

std::string sRecvStr;
int sRecvStrLength = 0;
//----------------------------------------------------------------------------
void _DistTestCallback(Serial *ser, std::string recvVal, int length)
{
	DistTest *dstT = (DistTest*)
		(ser->GetUserDataPointer("DistTest"));
	if (dstT)
	{
		sRecvStr += recvVal;
		sRecvStrLength += length;

		sRecvStr = dstT->ProcessRecvStr(sRecvStr, sRecvStrLength);
	}
}
//----------------------------------------------------------------------------
DistTest::DistTest() :
	mIsTestRun(true)
{
	mDistType = DT_LIDAR;
	mDist = 0;
	mRecognizeNormal = 200.0f;
	mCheckDistTime = 0.0f;
	mIsDoCheckingDist = false;
}
//----------------------------------------------------------------------------
DistTest::~DistTest()
{
}
//----------------------------------------------------------------------------
void DistTest::SetDistType(DistType type)
{
	mDistType = type;
}
//----------------------------------------------------------------------------
DistTest::DistType DistTest::GetDistType() const
{
	return mDistType;
}
//----------------------------------------------------------------------------
void DistTest::InitlizeSerial_Lidar()
{
	mIsTestRun = true;

	mThreadDist = new0 Thread();
	mThreadDist->Start(*this);

	mSerialDist.Open("COM10", 115200);
	mSerialDist.SetDoProcessRecv(false);
	mSerialDist.SetUserDataPointer("DistTest", this);
	mSerialDist.AddCallback(_DistTestCallback);
}
//----------------------------------------------------------------------------
void _UDPServerRecvCallback(UDPServer *sever,
	SocketAddress &address, const std::string &buf, int length)
{
	DistTest *distTest = sever->GetUserData<DistTest*>("DistTest");
	if (distTest)
	{
		std::string recvStr = buf;
		int dist = StringHelp::StringToInt(buf);
		distTest->SetDist(dist);
	}
}
//----------------------------------------------------------------------------
void DistTest::InitlizeUDP()
{
	mUDPServer = new0 UDPServer();
	mUDPServer->SetUserData("DistTest", this);
	mUDPServer->AddRecvCallback(_UDPServerRecvCallback);
	mUDPServer->Start();
}
//----------------------------------------------------------------------------
void DistTest::SendToGetData(const std::string &ip, int port)
{
	std::string strData = "startdata";
	SocketAddress skAddr(ip, (int16_t)port);
	mUDPServer->GetSocket().SendTo(strData.c_str(), strData.length(), skAddr);
}
//----------------------------------------------------------------------------
void DistTest::SetDist(int dist)
{
	mDist = dist;

	DistTest::DistType dstType = GetDistType();
	if (dstType == DistTest::DT_LIDAR)
	{
		EasyPRM._SetCurDist(dist);
	}
	else if (dstType == DistTest::DT_ULTR)
	{
		//PX2_LOG_INFO("Dist %d", dist);
	}
}
//----------------------------------------------------------------------------
void DistTest::Ternimate()
{
	mIsTestRun = false;
	System::SleepSeconds(0.5f);
	if (mThreadDist)
	{
		mThreadDist->Join();
		mThreadDist = 0;
	}
}
//----------------------------------------------------------------------------
std::string DistTest::ProcessRecvStr(std::string &recvBuf, int &length)
{
	int leftRecvLength = length;

	unsigned char cmdArray[10];

	int comIndex = 0;
	int cmdSize = 0;
	int lowDist = 0;
	int highDist = 0;
	bool isNewCMD = false;

	int processLength = 0;
	for (int index = 0; index < (int)recvBuf.length(); index++)
	{
		unsigned char chara = recvBuf[index];
		if (89 == chara)
		{
			comIndex++;
		}

		if (isNewCMD)
		{
			cmdArray[cmdSize] = chara;
			cmdSize += 1;

			if (cmdSize == 7)
			{                                                                                            
				lowDist = cmdArray[0];
				highDist = cmdArray[1];

				unsigned short allDist = highDist * 256 + lowDist;

				std::cout << lowDist<< " " << highDist << " " << allDist << std::endl;

				processLength = (index+1);

				comIndex = 0;
				isNewCMD = false;
			}
		}

		if (2 == comIndex)
		{
			isNewCMD = true;
			cmdSize = 0;
			comIndex = 0;
		}
	}

	length = length - processLength;
	std::string leftRecvBuf = recvBuf.substr(processLength, length);
	return leftRecvBuf;
}
//----------------------------------------------------------------------------
void DistTest::SetRecognizeNormal(int normal)
{
	mRecognizeNormal = normal;
}
//----------------------------------------------------------------------------
int DistTest::GetRecognizeNormal() const
{
	return mRecognizeNormal;
}
//----------------------------------------------------------------------------
bool DistTest::IsDoRecognize() const
{
	return mIsActivateRecoginze;
}
//----------------------------------------------------------------------------
void DistTest::Update(float elpasedSeconds)
{
	if (mUDPServer)
	{
		mUDPServer->Update(elpasedSeconds);
	}

	_CheckDist(elpasedSeconds);
}
//----------------------------------------------------------------------------
void DistTest::_CheckDist(float elapsedSeconds)
{
	if (mDist < mRecognizeNormal)
	{
		mIsDoCheckingDist = true;
	}
	else
	{
		mIsDoCheckingDist = false;
	}

	if (mIsDoCheckingDist)
	{
		mCheckDistTime += elapsedSeconds;
	}
	else
	{
		mCheckDistTime -= elapsedSeconds;
	}

	if (mCheckDistTime > 2.0f)
	{
		mCheckDistTime = 2.0f;
	}
	if (mCheckDistTime < 0.0f)
	{
		mCheckDistTime = 0.0f;
	}

	if (mCheckDistTime >= 1.5f)
	{
		mIsActivateRecoginze = true;
	}
	else
	{
		mIsActivateRecoginze = false;
	}
}
//----------------------------------------------------------------------------
void DistTest::Run()
{
	while (mIsTestRun)
	{
		if (mSerialDist.IsOpened())
			mSerialDist.Update();
	}
}
//----------------------------------------------------------------------------