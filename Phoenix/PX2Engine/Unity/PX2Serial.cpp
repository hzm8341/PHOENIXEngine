// PX2Serial.cpp

#include "PX2Serial.hpp"
#include "PX2Log.hpp"
#include "PX2ScopedCS.hpp"
#include "PX2Assert.hpp"
#include "PX2System.hpp"
using namespace PX2;

#if defined(__LINUX__)
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int fd, res;
struct termios oldtio, newtio;
#endif

//---------------------------------------------------------------------------
Serial::Serial() :
flag_opened(0),
baudrate(9600),
mIsThreadRunning(false),
mIsUseEventt(false)
{
#ifdef WIN32
	hcom = 0;
	mask = 0;
#endif
}
//---------------------------------------------------------------------------
Serial::~Serial()
{
	EndThread();
}
//---------------------------------------------------------------------------
bool Serial::Init(const std::string &comport_in, int baudrate)
{
	bool flag = false;

#ifdef WIN32
	flag = true;

	DCB dcb1;

	sprintf(comport, comport_in.c_str());

	if (1 == flag_opened)
		this->Close();

	hcom = CreateFile(comport,
		GENERIC_READ | GENERIC_WRITE,	// 读写
		0,								// 独占
		NULL,
		OPEN_EXISTING, 
		NULL,							// 同步
		NULL);

	// 获得当前串口配置信息
	GetCommState(hcom, &dcb1);

	dcb1.BaudRate = baudrate;

	dcb1.fParity = 1;//0
	dcb1.Parity = NOPARITY;//for AI_Motor
	//dcb1.Parity=EVENPARITY;
	dcb1.StopBits = ONESTOPBIT;//for AI_Motor
	dcb1.ByteSize = 8;//for AI Motor
	dcb1.fNull = FALSE;//
	//dcb1.EvtChar=STX;
	flag = (TRUE==SetCommState(hcom, &dcb1));

	if (flag == true)
	{
		GetCommMask(hcom, &mask);
		//mask=EV_RXCHAR|EV_RXFLAG;
		mask = EV_RXCHAR;
		flag = (TRUE == SetCommMask(hcom, mask));
	}

	if (flag == true)
	{
		GetCommTimeouts(hcom, &ctmo);
		ctmo.ReadIntervalTimeout = 1000;//0;//30;//SICKLMS偱偼6ms
		ctmo.ReadTotalTimeoutMultiplier = 5000;//=1;//0928
		//ctmo.ReadTotalTimeoutConstant=1000;//=6;//0928

		flag = (TRUE == SetCommTimeouts(hcom, &ctmo));
	}

	// 清空缓冲区，为读写串口做准备
	PurgeComm(hcom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR |
		PURGE_RXCLEAR);
	flag_opened = 1;

#endif


#if defined(__LINUX__)
	flag = true;

	fd = open(comport_in.c_str(), O_RDWR | O_NOCTTY ); 
	//fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
	if (fd < 0) 
	{
		perror(comport_in.c_str());
		PX2_LOG_ERROR("init() error. %s is not opend. fd=%d", comport_in.c_str(), fd);

		flag = false;
	}

	if (flag)
	{
		flag_opened = 1;
		PX2_LOG_INFO("init() com opened flag %d", flag_opened);

		tcgetattr(fd, &oldtio);

		bzero(&newtio, sizeof(newtio));

		tcflag_t baud;
		if (baudrate == 9600) baud = B9600;
		if (baudrate == 38400) baud = B38400;
		if (baudrate == 57600) baud = B57600;

		//newtio.c_cflag = baud | CRTSCTS | CS8 | CLOCAL | CREAD;
		newtio.c_cflag = baud | IGNPAR | CS8 | CLOCAL | CREAD;
		newtio.c_iflag = IGNPAR;
		newtio.c_oflag = 0;

		/* set input mode (non-canonical, no echo,...) */
		newtio.c_lflag = 0;

		tcsetattr(fd, TCSAFLUSH, &newtio);
	}

#endif

	return(flag);
}
//---------------------------------------------------------------------------
void Serial::Clear()
{
#ifdef WIN32
	PurgeComm(hcom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR |
		PURGE_RXCLEAR);
#endif

#if defined(__LINUX__)
	tcflush(fd, TCIFLUSH);
#endif

}
//---------------------------------------------------------------------------
bool Serial::Close()
{
	if (flag_opened != 1)
		return false;
	flag_opened = 0;

#ifdef WIN32
	return (TRUE == CloseHandle(hcom));
#endif

#if defined(__LINUX__)
	::close(fd);
	return true;
#endif
}
//---------------------------------------------------------------------------
void Serial::StartThread(bool isUseEventt)
{
	EndThread();

	mIsUseEventt = isUseEventt;
	mIsThreadRunning = true;

	mThread = new0 Thread("SerailThread");
	mThread->Start(*this);
}
//---------------------------------------------------------------------------
void Serial::EndThread()
{
	if (mThread)
	{
		mIsThreadRunning = false;
		
		if (mIsUseEventt)
		{
			mEnt.Set();
		}

		mThread->Join();
		mThread = 0;
	}
}
//---------------------------------------------------------------------------
int Serial::Receive(char *buf_ptr, int size)
{
	unsigned long byte, event;
	byte = 0;
	bool flag = false;

#ifdef WIN32
	while (!flag)
	{
		WaitCommEvent(hcom, &event, NULL);
		if (event | EV_RXCHAR)
		{
			if (ReadFile(hcom, buf_ptr, size, &byte, NULL))
				flag = true;
			break;
		}
		byte = 0;
	}
#endif

#if defined(__LINUX__)
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &newtio);
	byte = read(fd, buf_ptr, size);
#endif

	return byte;
}
//---------------------------------------------------------------------------
int Serial::Send(const char *buf_ptr, int size)
{
	unsigned long byte;
	if (flag_opened != 1)
	{
		PX2_LOG_ERROR("send() error. port Not opend");
		PX2_LOG_ERROR("flag_opened=%d", flag_opened);//debug
		return -1;
	}

#ifdef WIN32
	if (WriteFile(hcom, buf_ptr, size, &byte, NULL))
	{
		return byte;
	}
	else return -1;
#endif

#if defined(__LINUX__)
	byte = write(fd, buf_ptr, size);
	if (byte == 0)
	{
		PX2_LOG_ERROR("write error byte 0");
		return -1;
	}

	PX2_LOG_INFO("write byte=%d",byte);

	return (byte);
#endif

}
//---------------------------------------------------------------------------
int Serial::Send(const std::string &buffer)
{
	return Send(buffer.c_str(), (int)buffer.size());
}
//---------------------------------------------------------------------------
int Serial::Receive(std::string &buffer)
{
	return Receive((char*)buffer.c_str(), (int)buffer.size());
}
//---------------------------------------------------------------------------
void Serial::SendWithCallback(const std::string &buffer)
{
	Send(buffer);
	mEnt.Set();
	mEntWaitCallback.Wait(1000);
	System::SleepSeconds(1.0f);
}
//---------------------------------------------------------------------------
void Serial::Run()
{
	while (mIsThreadRunning)
	{
		if (mIsUseEventt)
			mEnt.Wait();

		if (!mIsThreadRunning)
			break;

		// recv
		std::string buf;
		int recvedBytes = Receive(buf);
		if (recvedBytes > 0)
		{
			if (mIsUseEventt)
				mEntWaitCallback.Set();

			if (!buf.empty())
			{
				PX2_LOG_INFO("Serial Recv %d", buf.c_str());
			}
		}
	}
}
//---------------------------------------------------------------------------
