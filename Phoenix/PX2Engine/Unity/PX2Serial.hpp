// PX2Serial.hpp

#ifndef PX2SERIAL_HPP1
#define PX2SERIAL_HPP1

#include "PX2UnityPre.hpp"
#include "PX2Runnable.hpp"
#include "PX2Thread.hpp"
#include "PX2Eventt.hpp"
#include "PX2Semaphore.hpp"
#ifdef WIN32
#include <windows.h>
#endif

namespace PX2
{

	class PX2_ENGINE_ITEM Serial : public Runnable
	{
#ifdef WIN32
	private:
		HANDLE hcom;
		DWORD mask;
		COMMTIMEOUTS ctmo;
		OVERLAPPED o;
		COMMPROP cmp;
#endif

	public:
		Serial();
		~Serial();

		char flag_opened;
		char comport[16];
		int baudrate;

		bool Init(const std::string &comport_in, int baudrate);
		bool Close();

		void StartThread(bool isUseEventt=true);
		void EndThread();

		void Clear();
		
		int Send(const char *buf_ptr, int size);
		int Receive(char *buf_ptr, int size);

		int Send(const std::string &buffer);
		int Receive(std::string &buffer);

		void SendWithCallback(const std::string &buffer);

		virtual void Run();

	protected:
		ThreadPtr mThread;
		bool mIsUseEventt;
		Eventt mEnt;
		Eventt mEntWaitCallback;
		bool mIsThreadRunning;
	};

}

#endif