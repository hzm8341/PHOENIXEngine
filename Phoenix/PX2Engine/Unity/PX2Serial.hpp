// PX2Serial2.hpp

#ifndef PX2SERIAL2_HPP
#define PX2SERIAL2_HPP

#include "PX2UnityPre.hpp"
#include "PX2Runnable.hpp"
#include "PX2Thread.hpp"
#include "PX2EventSystem.hpp"

namespace serial
{
	class Serial;
}

namespace PX2
{

	PX2_DECLARE_EVENT_BEGIN(PX2_ENGINE_ITEM SerialES)
	PX2_EVENT(Open)
	PX2_EVENT(Close)
	PX2_EVENT(OpenFailed)
	PX2_DECLARE_EVENT_END(SerialES)

	typedef void(*SerialReceiveCallback) (std::string recvVal);

	class PX2_ENGINE_ITEM Serial : public Runnable
	{
	public:
		Serial();
		virtual ~Serial();

		int Open(const std::string &port, int baudrate);
		void Close();
		bool IsOpened() const;

		std::string GetPort() const;
		void Update(float elapsedSeconds);

		int Write(const char *buf_ptr, int size);
		int Read(char *buf_ptr, int size);

		int Write(const std::string &buffer);
		int Read(std::string &buffer);

		void StartThread();
		void EndThread();
		virtual void Run();

		std::vector<std::string> GetPortList();
		int GetNumPorts() const;
		std::string GetPort(int i) const;

		void ClearRecvCallbacks();
		bool IsHasReceiveCallback(SerialReceiveCallback callBack);
		void AddReceiveCallback(SerialReceiveCallback callBack);
		void RemoveReceiveCallback(SerialReceiveCallback callback);

	protected:
		void _ProcessRevBuf(std::string &recvBuf);
		void _OnCmd(const std::string &cmd);

		std::vector<SerialReceiveCallback> mCallbacks;

		ThreadPtr mThread;
		bool mIsThreadRunning;

		std::string mRecingBuf;

		std::string mRecvStr;
		std::string mCmdStr;

#if defined (_WIN32) || defined(WIN32) || defined(__LINUX__)
		serial::Serial *mSerial;
#endif
		std::vector<std::string> mPortList;
	};

}

#endif