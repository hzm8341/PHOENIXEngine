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

		enum DistType
		{
			DT_LIDAR,
			DT_ULTR,
			DT_MAX_TYPE
		};

		void SetDistType(DistType type);
		DistType GetDistType() const;

		void InitlizeSerial_Lidar();

		void InitlizeUDP();
		
		void Ternimate();

		void Update(float elpasedSeconds);

		virtual void Run();

		void SendToGetData(const std::string &ip, int port);
		void SetDist(int dist);
		std::string ProcessRecvStr(std::string &recvStr, int &length);

	private:
		Serial mSerialDist;
		ThreadPtr mThreadDist;
		bool mIsTestRun;
		DistType mDistType;

		UDPServer *mUDPServer;
		int mDist;

	public:
		void SetRecognizeNormal(int normal);
		int GetRecognizeNormal() const;

		bool IsDoRecognize() const;

	private:
		void _CheckDist(float elapsedSeconds);

		int mRecognizeNormal;
		bool mIsDoCheckingDist;
		float mCheckDistTime;
		bool mIsActivateRecoginze;
	};
	typedef Pointer0<DistTest> DistTestPtr;

}

#endif