// DistTest.cpp

#include "DistTest.hpp"
#include "PX2System.hpp"
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
}
//----------------------------------------------------------------------------
DistTest::~DistTest()
{
}
//----------------------------------------------------------------------------
void DistTest::Initlize()
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
void DistTest::Ternimate()
{
	mIsTestRun = false;
	System::SleepSeconds(0.5f);
	mThreadDist->Join();
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

				std::cout << allDist << std::endl;

				processLength = (index+1);
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
void DistTest::Run()
{
	while (mIsTestRun)
	{
		if (mSerialDist.IsOpened())
			mSerialDist.Update();
	}
}
//----------------------------------------------------------------------------