// EasyPRRecvObject.hpp

#ifndef EASYPRRECVOBJECT_HPP
#define EASYPRRECVOBJECT_HPP

#include "ProjectPre.hpp"
#include "PX2SmartPointer.hpp"

namespace cv
{
	class Mat;
}

namespace PX2
{

	class UIVlc;

	class PROJECT_DLL_ITEM EasyPRRecvObject
	{
	public:
		EasyPRRecvObject(UIVlc *vlc);
		~EasyPRRecvObject();

		void Update();
		void UpdateRecognize();

		Mutex mRecogMutex;

		UIVlc *TheVLC;
		std::vector<char> mBuffer0;
		std::vector<char> mBuffer1;
		std::vector<char> *mUsingBuffer;
		std::vector<char> *mPushingBuffer;
		int mBufferWidth;
		int mBufferHeight;

	private:
		bool _ByteToMat(char* pImg, int nH, int nW, cv::Mat& outImg);
		void Recognize(const std::string &filename);
		void _Recognize(const cv::Mat &mat);

		std::map<std::string, int> mResultStrs;

		Mutex mResultMutex;
		std::string mResultStr;
	};

	typedef Pointer0<EasyPRRecvObject> EasyPRRecvObjectPtr;

}

#endif