// EasyPRRecvObject.hpp

#ifndef EASYPRRECVOBJECT_HPP
#define EASYPRRECVOBJECT_HPP

#include "ProjectPre.hpp"
#include "PX2SmartPointer.hpp"

namespace PX2
{

	class UIVlc;

	class EasyPRRecvObject
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
	};

	typedef Pointer0<EasyPRRecvObject> EasyPRRecvObjectPtr;

}

#endif