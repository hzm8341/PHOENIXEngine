// DistTest.hpp

#ifndef DISTTEST_HPP
#define DISTTEST_HPP

#include "ProjectPre.hpp"
#include "PX2Thread.hpp"
#include "PX2Serial.hpp"
#include "PX2SmartPointer.hpp"

namespace PX2
{

	class UDPServer;

	class PROJECT_DLL_ITEM DistTest : public Runnable
	{
	public:
		DistTest();
		~DistTest();

		void InitlizeSerial_Lidar();
		void Ternimate();

		void Update(float elpasedSeconds);

		virtual void Run();

		std::string ProcessRecvStr(std::string &recvStr, int &length);

	private:
		Serial mSerialDist;
		ThreadPtr mThreadDist;
		bool mIsTestRun;

	public:
		void InitlizeUDP_Lidar();
		void SendToGetData(const std::string &ip, int port);

	private:
		UDPServer *mUDPServer;
	};
	typedef Pointer0<DistTest> DistTestPtr;

}

#endif