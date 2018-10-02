// PX2Serial2.cpp

#include "PX2Serial.hpp"
#include "PX2ScopedCS.hpp"
#include "PX2StringHelp.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2Log.hpp"
using namespace PX2;

#if defined (_WIN32) || defined(WIN32)
#include "serial.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#if _MSC_VER
#define snprintf _snprintf
#endif

#define win32_err(s) FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, \
			GetLastError(), 0, (s), sizeof(s), NULL)
#define QUERYDOSDEVICE_BUFFER_SIZE 262144

#elif defined (__LINUX__)
#include "serial.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#endif

PX2_IMPLEMENT_EVENT(SerialES);

//---------------------------------------------------------------------------
Serial *Serial::msDefaultSerial = 0;
//---------------------------------------------------------------------------
Serial::Serial() 
{
#if defined (_WIN32) || defined(WIN32) || defined(__LINUX__)
	mSerial = 0;
#endif
}
//---------------------------------------------------------------------------
Serial::~Serial()
{
	Close();
}
//---------------------------------------------------------------------------
void Serial::SetDefaultSerial(Serial *serial)
{
	msDefaultSerial = serial;
}
//---------------------------------------------------------------------------
Serial *Serial::GetDefaultSerial()
{
	return msDefaultSerial;
}
//---------------------------------------------------------------------------
Serial *Serial::New()
{
	return new0 Serial();
}
//---------------------------------------------------------------------------
void Serial::Delete(Serial *serial)
{
	delete0(serial);
}
//---------------------------------------------------------------------------
int Serial::Open(const std::string &port, int baudrate)
{
	Close();

#if defined (_WIN32) || defined(WIN32) || defined(__LINUX__)
	mSerial = new serial::Serial(port, baudrate);

	if (mSerial->isOpen())
	{
		mSerialPortName = port;

		// linux system at least needs 2 seconds, then you can send your first msg
		Event *ent = PX2_CREATEEVENTEX(SerialES, Open);
		ent->SetDataStr0(port);
		ent->SetTimeDelay(3.0f);
		PX2_EW.BroadcastingLocalEvent(ent);

		return 0;
	}
#endif

	Event *ent = PX2_CREATEEVENTEX(SerialES, OpenFailed);
	ent->SetDataStr0(port);
	PX2_EW.BroadcastingLocalEvent(ent);

	return -1;
}
//---------------------------------------------------------------------------
bool Serial::IsOpened() const
{
#if defined (_WIN32) || defined(WIN32) || defined(__LINUX__)
	if (mSerial)
		return mSerial->isOpen();
#endif

	return false;
}
//---------------------------------------------------------------------------
void Serial::Close()
{
#if defined (_WIN32) || defined(WIN32) || defined(__LINUX__)
	if (mSerial)
	{
		mSerial->close();

		delete(mSerial);
		mSerial = 0;

		Event *ent = PX2_CREATEEVENTEX(SerialES, Close);
		ent->SetDataStr0(mSerialPortName);
		PX2_EW.BroadcastingLocalEvent(ent);
	}
#endif
}
//---------------------------------------------------------------------------
void Serial::Update(float elapsedSeconds)
{
	PX2_UNUSED(elapsedSeconds);

#if defined (_WIN32) || defined(WIN32) || defined(__LINUX__)
	if (mSerial)
	{
		int numAvailable = mSerial->available();
		if (numAvailable > 0)
		{
			std::string readVal = mSerial->read(numAvailable);
			mRecvStr += readVal;
		}
	}
#endif

	if (mRecvStr.length() > 0)
	{
		std::string recvStr = mRecvStr;
		_ProcessRevBuf(mRecvStr);

		for (int i = 0; i < (int)mCallbacks.size(); i++)
		{
			if (mCallbacks[i])
				mCallbacks[i](mRecvStr);
		}

		if ((int)mScriptHandlers.size() > 0)
		{
			for (int i = 0; i < (int)mScriptHandlers.size(); i++)
			{
				const std::string &scriptStr = mScriptHandlers[i];
				if (!scriptStr.empty())
				{
					std::string strBuf = scriptStr + "(\"" + recvStr + "\")";
					PX2_SC_LUA->CallString(strBuf);
				}
			}
		}

		if ((int)mScriptHandlersHex.size() > 0)
		{
			std::string hexBuf = StringHelp::StrToHex(recvStr);
			for (int i = 0; i < (int)mScriptHandlersHex.size(); i++)
			{
				const std::string &scriptStrHex = mScriptHandlersHex[i];
				if (!scriptStrHex.empty())
				{
					std::string strBuf = scriptStrHex + "(\"" + hexBuf + "\")";
					PX2_SC_LUA->CallString(strBuf);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void Serial::_ProcessRevBuf(std::string &recvBuf)
{
	mCmdStr.clear();

	bool hasN = false;
	std::string cmdStr;
	int index = 0;
	for (index = 0; index < (int)recvBuf.size(); index++)
	{
		char chara = recvBuf[index];
		if ('\r' == chara)
		{
			continue;
		}
		else if ('\n' == chara)
		{
			hasN = true;
			if (!mCmdStr.empty())
			{
				_OnCmd(mCmdStr);
				mCmdStr.clear();
			}

			std::string subStr = recvBuf.substr(index + 1, recvBuf.size() - (index + 1));
			recvBuf = subStr;
			_ProcessRevBuf(recvBuf);
		}
		else
		{
			mCmdStr += chara;
		}
	}
}
//---------------------------------------------------------------------------
void Serial::_OnCmd(const std::string &cmd)
{
	for (int i = 0; i < (int)mCMDCallbacks.size(); i++)
	{
		if (mCMDCallbacks[i])
			mCMDCallbacks[i](cmd);
	}
}
//----------------------------------------------------------------------------
void Serial::ClearCMDCallbacks()
{
	mCMDCallbacks.clear();
}
//----------------------------------------------------------------------------
bool Serial::IsHasCMDCallback(SerialCMDCallback callBack)
{
	for (int i = 0; i < (int)mCMDCallbacks.size(); i++)
	{
		if (callBack == mCMDCallbacks[i])
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void Serial::AddCMDCallback(SerialCMDCallback callBack)
{
	if (IsHasCMDCallback(callBack))
		return;

	mCMDCallbacks.push_back(callBack);
}
//----------------------------------------------------------------------------
void Serial::RemoveCMDCallback(SerialCMDCallback callback)
{
	auto it = mCMDCallbacks.begin();
	for (; it != mCMDCallbacks.end();)
	{
		if (*it == callback)
		{
			it = mCMDCallbacks.erase(it);
		}
		else
		{
			it++;
		}
	}
}
//----------------------------------------------------------------------------
void Serial::ClearCallbacks()
{
	mCallbacks.clear();
}
//----------------------------------------------------------------------------
bool Serial::IsHasCallback(SerialCMDCallback callBack)
{
	for (int i = 0; i < (int)mCallbacks.size(); i++)
	{
		if (callBack == mCallbacks[i])
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void Serial::AddCallback(SerialCallback callBack)
{
	if (IsHasCallback(callBack))
		return;

	mCallbacks.push_back(callBack);
}
//----------------------------------------------------------------------------
void Serial::RemoveCallback(SerialCallback callback)
{
	auto it = mCallbacks.begin();
	for (; it != mCallbacks.end();)
	{
		if (*it == callback)
		{
			it = mCallbacks.erase(it);
		}
		else
		{
			it++;
		}
	}
}
//----------------------------------------------------------------------------
void Serial::ClearScirptHandlers()
{
	mScriptHandlers.clear();
}
//----------------------------------------------------------------------------
bool Serial::IsHasScriptHandler(const std::string &scriptHandler)
{
	for (int i = 0; i < (int)mScriptHandlers.size(); i++)
	{
		if (scriptHandler == mScriptHandlers[i])
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void Serial::AddScriptHandler(const std::string &scriptHandler)
{
	if (IsHasScriptHandler(scriptHandler))
		return;

	mScriptHandlers.push_back(scriptHandler);
}
//----------------------------------------------------------------------------
void Serial::RemoveScriptHandler(const std::string &scriptHandler)
{
	auto it = mScriptHandlers.begin();
	for (; it != mScriptHandlers.end();)
	{
		if (scriptHandler == (*it))
		{
			it = mScriptHandlers.erase(it);
		}
		else
		{
			it++;
		}
	}
}
//----------------------------------------------------------------------------
void Serial::ClearScriptHandlersHex()
{
	mScriptHandlersHex.clear();
}
//----------------------------------------------------------------------------
bool Serial::IsHasScriptHandlerHex(const std::string &scriptHandler)
{
	for (int i = 0; i < (int)mScriptHandlersHex.size(); i++)
	{
		if (scriptHandler == mScriptHandlersHex[i])
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void Serial::AddScriptHandlerHex(const std::string &scriptHandler)
{
	if (IsHasScriptHandlerHex(scriptHandler))
		return;

	mScriptHandlersHex.push_back(scriptHandler);
}
//----------------------------------------------------------------------------
void Serial::RemoveScriptHandlerHex(const std::string &scriptHandler)
{
	auto it = mScriptHandlersHex.begin();
	for (; it != mScriptHandlersHex.end();)
	{
		if (scriptHandler == (*it))
		{
			it = mScriptHandlersHex.erase(it);
		}
		else
		{
			it++;
		}
	}
}
//---------------------------------------------------------------------------
void Serial::OnAndroidUSBReceive(const char *buf, int size)
{
	mRecvStr = std::string(buf, size);
}
//---------------------------------------------------------------------------
std::string Serial::GetPort() const
{
#if defined (_WIN32) || defined(WIN32) || defined(__LINUX__)
	if (mSerial)
		return mSerial->getPort();
#endif

	return "";
}
//---------------------------------------------------------------------------
int Serial::Read(char *buf_ptr, int size)
{
#if defined (_WIN32) || defined(WIN32) || defined(__LINUX__)
	if (mSerial)
	{
		return mSerial->read((uint8_t*)buf_ptr, size);
	}
#endif

	return 0;
}
//---------------------------------------------------------------------------
int Serial::Write(const char *buf_ptr, int size)
{
#if defined (_WIN32) || defined(WIN32) || defined(__LINUX__)
	if (mSerial)
	{
		if (!mSerial->isOpen())
			return 0;
	}

	if (mSerial)
	{
		int writeVal = mSerial->write((const uint8_t *)buf_ptr, size);
		mSerial->flush();
		return writeVal;
	}
#endif

	return 0;
}
//---------------------------------------------------------------------------
int Serial::Write(const std::string &buffer)
{
	return Write(buffer.c_str(), (int)buffer.size());
}
//---------------------------------------------------------------------------
int Serial::Read(std::string &buffer)
{
	return Read((char*)buffer.c_str(), (int)buffer.size());
}
//---------------------------------------------------------------------------
std::vector<std::string> Serial::GetPortList()
{
	std::vector<std::string> list;

#if defined (_WIN32) || defined(WIN32) || defined(__LINUX__)
	std::vector<serial::PortInfo> ports = serial::list_ports();
	for (int i=0; i<(int)ports.size(); i++)
	{
		list.push_back(ports[i].port);
	}
#endif

	mPortList = list;

	return list;
}
//---------------------------------------------------------------------------
int Serial::GetNumPorts() const
{
	return (int)mPortList.size();
}
//---------------------------------------------------------------------------
std::string Serial::GetPort(int i) const
{
	if (0 <= i && i < (int)mPortList.size())
		return mPortList[i];

	return std::string("");
}
//---------------------------------------------------------------------------