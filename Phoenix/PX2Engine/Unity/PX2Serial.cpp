// PX2Serial2.cpp

#include "PX2Serial.hpp"
#include "PX2ScopedCS.hpp"
#include "PX2StringHelp.hpp"
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
#endif

PX2_IMPLEMENT_EVENT(SerialES);

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
int Serial::Open(const std::string &port, int baudrate)
{
	Close();

#if defined (_WIN32) || defined(WIN32) || defined(__LINUX__)
	mSerial = new serial::Serial(port, baudrate);
	if (mSerial->isOpen())
	{
		Event *ent = PX2_CREATEEVENTEX(SerialES, Open);
		PX2_EW.BroadcastingLocalEvent(ent);
		return 0;
	}
#endif

	Event *ent = PX2_CREATEEVENTEX(SerialES, OpenFailed);
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
		PX2_EW.BroadcastingLocalEvent(ent);
	}
#endif
}
//---------------------------------------------------------------------------
void Serial::Update(float elapsedSeconds)
{
	PX2_UNUSED(elapsedSeconds);

#if defined (_WIN32) || defined(WIN32) || defined(__LINUX__)
	int numAvailable = mSerial->available();
	if (numAvailable > 0)
	{
		std::string readVal = mSerial->read(numAvailable);
		mRecingBuf.append(readVal);
	}
#endif

	if (mRecingBuf.size() > 0)
	{
		mRecvStr += mRecingBuf;
		_ProcessRevBuf(mRecvStr);
		mRecingBuf.clear();
	}
}
//---------------------------------------------------------------------------
void Serial::_ProcessRevBuf(std::string &recvBuf)
{
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
			if (!mCmdStr.empty())
			{
				_OnCmd(mCmdStr);
				mCmdStr.clear();
			}

			std::string subStr = recvBuf.substr(index + 1, recvBuf.length() - (index + 1));
			recvBuf = subStr;
			return;
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
	for (int i = 0; i < (int)mCallbacks.size(); i++)
	{
		if (mCallbacks[i])
			mCallbacks[i](cmd);
	}
}
//----------------------------------------------------------------------------
void Serial::ClearRecvCallbacks()
{
	mCallbacks.clear();
}
//----------------------------------------------------------------------------
bool Serial::IsHasReceiveCallback(SerialReceiveCallback callBack)
{
	for (int i = 0; i < (int)mCallbacks.size(); i++)
	{
		if (callBack == mCallbacks[i])
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void Serial::AddReceiveCallback(SerialReceiveCallback callBack)
{
	if (IsHasReceiveCallback(callBack))
		return;

	mCallbacks.push_back(callBack);
}
//----------------------------------------------------------------------------
void Serial::RemoveReceiveCallback(SerialReceiveCallback callback)
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
void Serial::StartThread()
{
	//EndThread();

	//mIsThreadRunning = true;

	//mThread = new0 Thread("SerailThread2");
	//mThread->Start(*this);
}
//---------------------------------------------------------------------------
void Serial::EndThread()
{
	//if (mThread)
	//{
	//	mIsThreadRunning = false;

	//	mThread->Join();
	//	mThread = 0;
	//}
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
		return mSerial->write((const uint8_t *)buf_ptr, size);
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

#if defined(LINUX)
	// This is ugly guessing, but Linux doesn't seem to provide anything else.
	// If there really is an API to discover serial devices on Linux, please
	// email paul@pjrc.com with the info.  Please?
	// The really BAD aspect is all ports get DTR raised briefly, because linux
	// has no way to open the port without raising DTR, and there isn't any way
	// to tell if the device file really represents hardware without opening it.
	// maybe sysfs or udev provides a useful API??
	DIR *dir;
	struct dirent *f;
	struct stat st;
	unsigned int i, len[NUM_DEVNAMES];
	char s[512];
	int fd, bits;
	termios mytios;

	dir = opendir("/dev/");
	if (dir == NULL) return list;
	for (i = 0; i < NUM_DEVNAMES; i++) len[i] = strlen(devnames[i]);
	// Read all the filenames from the /dev directory...
	while ((f = readdir(dir)) != NULL) {
		// ignore everything that doesn't begin with "tty"
		if (strncmp(f->d_name, "tty", 3)) continue;
		// ignore anything that's not a known serial device name
		for (i = 0; i < NUM_DEVNAMES; i++) {
			if (!strncmp(f->d_name + 3, devnames[i], len[i])) break;
		}
		if (i >= NUM_DEVNAMES) continue;
		snprintf(s, sizeof(s), "/dev/%s", f->d_name);
		// check if it's a character type device (almost certainly is)
		if (stat(s, &st) != 0 || !(st.st_mode & S_IFCHR)) continue;
		// now see if we can open the file - if the device file is
		// populating /dev but doesn't actually represent a loaded
		// driver, this is where we will detect it.
		fd = open(s, O_RDONLY | O_NOCTTY | O_NONBLOCK);
		if (fd < 0) {
			// if permission denied, give benefit of the doubt
			// (otherwise the port will be invisible to the user
			// and we won't have a to alert them to the permssion
			// problem)
			if (errno == EACCES) list.Add(s);
			// any other error, assume it's not a real device
			continue;
		}
		// does it respond to termios requests? (probably will since
		// the name began with tty).  Some devices where a single
		// driver exports multiple names will open but this is where
		// we can really tell if they work with real hardare.
		if (tcgetattr(fd, &mytios) != 0) {
			close(fd);
			continue;
		}
		// does it respond to reading the control signals?  If it's
		// some sort of non-serial terminal (eg, pseudo terminals)
		// this is where we will detect it's not really a serial port
		if (ioctl(fd, TIOCMGET, &bits) < 0) {
			close(fd);
			continue;
		}
		// it passed all the tests, it's a serial port, or some sort
		// of "terminal" that looks exactly like a real serial port!
		close(fd);
		// unfortunately, Linux always raises DTR when open is called.
		// not nice!  Every serial port is going to get DTR raised
		// and then lowered.  I wish there were a way to prevent this,
		// but it seems impossible.
		list.Add(s);
	}
	closedir(dir);
#elif defined(MACOSX)
	// adapted from SerialPortSample.c, by Apple
	// http://developer.apple.com/samplecode/SerialPortSample/listing2.html
	// and also testserial.c, by Keyspan
	// http://www.keyspan.com/downloads-files/developer/macosx/KesypanTestSerial.c
	// www.rxtx.org, src/SerialImp.c seems to be based on Keyspan's testserial.c
	// neither keyspan nor rxtx properly release memory allocated.
	// more documentation at:
	// http://developer.apple.com/documentation/DeviceDrivers/Conceptual/WorkingWSerial/WWSerial_SerialDevs/chapter_2_section_6.html
	mach_port_t masterPort;
	CFMutableDictionaryRef classesToMatch;
	io_iterator_t serialPortIterator;
	if (IOMasterPort(NULL, &masterPort) != KERN_SUCCESS) return list;
	// a usb-serial adaptor is usually considered a "modem",
	// especially when it implements the CDC class spec
	classesToMatch = IOServiceMatching(kIOSerialBSDServiceValue);
	if (!classesToMatch) return list;
	CFDictionarySetValue(classesToMatch, CFSTR(kIOSerialBSDTypeKey),
		CFSTR(kIOSerialBSDModemType));
	if (IOServiceGetMatchingServices(masterPort, classesToMatch,
		&serialPortIterator) != KERN_SUCCESS) return list;
	macos_ports(&serialPortIterator, list);
	IOObjectRelease(serialPortIterator);
	// but it might be considered a "rs232 port", so repeat this
	// search for rs232 ports
	classesToMatch = IOServiceMatching(kIOSerialBSDServiceValue);
	if (!classesToMatch) return list;
	CFDictionarySetValue(classesToMatch, CFSTR(kIOSerialBSDTypeKey),
		CFSTR(kIOSerialBSDRS232Type));
	if (IOServiceGetMatchingServices(masterPort, classesToMatch,
		&serialPortIterator) != KERN_SUCCESS) return list;
	macos_ports(&serialPortIterator, list);
	IOObjectRelease(serialPortIterator);
#elif defined(WIN32) || defined(_WIN32)
	// http://msdn.microsoft.com/en-us/library/aa365461(VS.85).aspx
	// page with 7 ways - not all of them work!
	// http://www.naughter.com/enumser.html
	// may be possible to just query the windows registary
	// http://it.gps678.com/2/ca9c8631868fdd65.html
	// search in HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM
	// Vista has some special new way, vista-only
	// http://msdn2.microsoft.com/en-us/library/aa814070(VS.85).aspx
	char *buffer, *p;
	//DWORD size = QUERYDOSDEVICE_BUFFER_SIZE;
	DWORD ret;

	buffer = (char *)malloc(QUERYDOSDEVICE_BUFFER_SIZE);
	if (buffer == NULL) return list;
	memset(buffer, 0, QUERYDOSDEVICE_BUFFER_SIZE);
	ret = QueryDosDeviceA(NULL, buffer, QUERYDOSDEVICE_BUFFER_SIZE);
	if (ret)
	{
		printf("Detect Serial using QueryDosDeviceA: ");
		for (p = buffer; *p; p += strlen(p) + 1)
		{
			printf(":  %s", p);
			if (strncmp(p, "COM", 3))
				continue;

			list.push_back(std::string(p));
		}
	}
	else
	{
		char buf[1024];
		win32_err(buf);
		printf("QueryDosDeviceA failed, error \"%s\"\n", buf);
		printf("Detect Serial using brute force GetDefaultCommConfig probing: ");
		for (int i = 1; i <= 32; i++)
		{
			printf("try  %s", buf);
			COMMCONFIG cfg;
			DWORD len;
			snprintf(buf, sizeof(buf), "COM%d", i);
			if (GetDefaultCommConfig(buf, &cfg, &len))
			{
				std::string name = "COM" + StringHelp::IntToString(i);
				list.push_back(name);
				printf(":  %s", buf);
			}
		}
	}
	free(buffer);
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
void Serial::Run()
{
	//if (!mSerial)
	//	return;

	//while (mIsThreadRunning)
	//{
		//int numAvailable = mSerial->available();
		//if (numAvailable > 0)
		//{
		//	std::string readVal = mSerial->read(numAvailable);

		//	ScopedCS cs(&mMutex);
		//	mRecingBuf.append(readVal);
		//}
	//}
}
//---------------------------------------------------------------------------