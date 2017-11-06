// PX2Serial.hpp

#ifndef PX2SERIAL_HPP
#define PX2SERIAL_HPP

#include "PX2UnityPre.hpp"
#include "PX2Runnable.hpp"
#include "PX2Thread.hpp"
#include "PX2Eventt.hpp"
#include "PX2Semaphore.hpp"

#if defined(LINUX)
#include <termios.h>
#elif defined(MACOSX)
#include <termios.h>
#elif defined(WIN32) || defined(_WIN32)
#include <windows.h>
#endif

namespace PX2
{

	typedef void(*SerialReceiveCallback) (std::string recvVal);

	class PX2_ENGINE_ITEM Serial : public Runnable
	{
	public:
		Serial();
		virtual ~Serial();

		void Update(float elapsedSeconds);

		// Return a list of all serial ports
		std::vector<std::string> GetPortList();

		int Open(const std::string &comport_in, int baudrate);

		// 0 success, non0:error
		int Open(const std::string& portName);
		std::string GetPortName();
		void Close();
		bool IsOpened() const;

		int SetBaudrate(int baud);
		int SetBaudrate(const std::string& baud_str);

		// Read from the serial port.  Returns only the bytes that are
		// already received, up to count.  This always returns without delay,
		// returning 0 if nothing has been received
		int Read(void *ptr, int count);

		// Write to the serial port.  This blocks until the data is
		// sent (or in a buffer to be sent).  All bytes are written,
		// unless there is some sort of error.
		int Write(const void *ptr, int len);

		int Write(const std::string &buffer);
		int Read(std::string &buffer);

		// Wait up to msec for data to become available for reading.
		// return 0 if timeout, or non-zero if one or more bytes are
		// received and can be read.  -1 if an error occurs
		int InputWait(int msec);

		void InputDiscard();
		int SetControl(int dtr, int rts);
		void OutputFlush();

		std::string GetErroMessage();

		// thread
		void StartThread();
		void EndThread();
		virtual void Run();

		void ClearRecvCallbacks();
		bool IsHasReceiveCallback(SerialReceiveCallback callBack);
		void AddReceiveCallback(SerialReceiveCallback callBack);
		void RemoveReceiveCallback(SerialReceiveCallback callback);

	private:
		void _ProcessRevBuf(std::string &recvBuf);
		void _OnCmd(const std::string &cmd);

		bool mIsPortOpen;
		std::string port_name;
		int baud_rate;
		std::string error_msg;

		ThreadPtr mThread;
		bool mIsThreadRunning;
		Mutex mMutex;
		std::string mRecingBuf;

		std::string mRecvStr;
		std::string mCmdStr;
		std::vector<SerialReceiveCallback> mCallbacks;

	private:
#if defined(LINUX) || defined(MACOSX)
		int port_fd;
		struct termios settings_orig;
		struct termios settings;
#elif defined(WIN32) || defined(_WIN32)
		HANDLE port_handle;
		COMMCONFIG port_cfg_orig;
		COMMCONFIG port_cfg;
#endif
	};

}

#endif