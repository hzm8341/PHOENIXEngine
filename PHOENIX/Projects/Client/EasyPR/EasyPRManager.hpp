#ifndef EASYPRMANAGER_HPP
#define EASYPRMANAGER_HPP

#include "PX2Singleton_NeedNew.hpp"
#include "ProjectPre.hpp"
#include "PX2UIVlc.hpp"
#include "PX2Thread.hpp"
#include "PX2Runnable.hpp"
#include "EasyPRRecvObject.hpp"
#include "PX2Serial.hpp"
#include "DistTest.hpp"

namespace cv
{
	class Mat;
}

namespace PX2
{

	class UDPServer;
	class Arduino;
	class GeneralClientConnector;

	class PROJECT_DLL_ITEM EasyPRManager : public Singleton<EasyPRManager>, public Runnable, public EventHandler
	{
	public:
		EasyPRManager();
		virtual ~EasyPRManager();

		bool Initlize();
		bool Ternimate();

		Arduino *GetArduino();

		void SetURL0(const std::string &url0);
		void SetURl1(const std::string &url1);

		virtual void Update(float appSeconds, float elapsedSeconds);

		virtual void Run();

		virtual void OnEvent(Event *event);

	public:		
		UIVLCPtr mVLC0;
		UIVLCPtr mVLC1;

	private:
		UDPServer *mUDPServer;
		ThreadPtr mRecognizeThread;

		bool mIsDoStop;
		EasyPRRecvObjectPtr mEasyPRObject0;
		EasyPRRecvObjectPtr mEasyPRObject1;
		Arduino *mArduino;

	public:
		enum DoorState
		{
			DS_NONE,
			DS_STOP,
			DS_OPENING,
			DS_CLOSEING,
			DS_MAX_TYPE
		};
		void SetDoorState(DoorState state);
		DoorState GetDoorState() const;

		void SetDoorToDist(float dist);
		bool IsAutoAdjustingDoor() const;

		void SetDoorToPercent(float perc);
		void SetClosedDist(float dist);
		void SetOpenedDist(float dist);

		int GetCurDist() const;
		float GetCurDistFloat() const;
		void _SetCurDist(int dist);

		DistTestPtr mDistTest;
		int mCurDist;
		float mCurDistFloat;
		float mToDist;
		
		DoorState mDoorState;
		bool mIsAutoAdjustingDoor;

		float mAllClosedDist;
		float mAllOpenedDist;

	public:
		void SendScreenStr(const std::string &screen);

		GeneralClientConnector *mGeneralClientConnector;
	};

#define EasyPRM EasyPRManager::GetSingleton()

}

#endif