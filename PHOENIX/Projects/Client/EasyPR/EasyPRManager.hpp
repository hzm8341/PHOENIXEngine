#ifndef EASYPRMANAGER_HPP
#define EASYPRMANAGER_HPP

#include "PX2Singleton_NeedNew.hpp"
#include "ProjectPre.hpp"
#include "PX2UIVlc.hpp"
#include "PX2Thread.hpp"
#include "PX2Runnable.hpp"

namespace cv
{
	class Mat;
}

namespace PX2
{

	class UDPServer;

	class EasyPRManager : public Singleton<EasyPRManager>, public Runnable
	{
	public:
		EasyPRManager();
		virtual ~EasyPRManager();

		bool Initlize();
		bool Ternimate();

		void SetURL0(const std::string &url0);
		void SetURl1(const std::string &url1);

		virtual void Update(float appSeconds, float elapsedSeconds);

		virtual void Run();

		void Recognize(const std::string &filename);

	private:
		bool _ByteToMat(char* pImg, int nH, int nW, cv::Mat& outImg);
		void _Recognize(const cv::Mat &mat);

		UDPServer *mUDPServer;
		UIVLCPtr mVLC0;
		UIVLCPtr mVLC1;
		ThreadPtr mRecognizeThread;
		Mutex mRecogMutex;
		bool mIsDoStop;
		std::vector<char> mBuffer0;
		std::vector<char> mBuffer1;
		std::vector<char> *mUsingBuffer;
		std::vector<char> *mPushingBuffer;
		int mBufferWidth;
		int mBufferHeight;
	};

}

#endif