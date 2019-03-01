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

	class PROJECT_DLL_ITEM EasyPRManager : public Singleton<EasyPRManager>, public Runnable
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

		void Recognize(const std::string &filename);

	public:
		bool _ByteToMat(char* pImg, int nH, int nW, cv::Mat& outImg);
		void _Recognize(const cv::Mat &mat);
		
		UIVLCPtr mVLC0;
		UIVLCPtr mVLC1;

	private:
		UDPServer *mUDPServer;
		ThreadPtr mRecognizeThread;

		bool mIsDoStop;
		EasyPRRecvObjectPtr mEasyPRObject0;
		EasyPRRecvObjectPtr mEasyPRObject1;
		Arduino *mArduino;

		DistTestPtr mDistTest;
	};

#define EasyPRM EasyPRManager::GetSingleton()

}

#endif