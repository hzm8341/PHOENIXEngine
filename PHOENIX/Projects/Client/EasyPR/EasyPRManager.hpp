#ifndef EASYPRMANAGER_HPP
#define EASYPRMANAGER_HPP

#include "PX2Singleton_NeedNew.hpp"
#include "ProjectPre.hpp"
#include "PX2UIVlc.hpp"

namespace PX2
{

	class UDPServer;

	class EasyPRManager : public Singleton<EasyPRManager>
	{
	public:
		EasyPRManager();
		virtual ~EasyPRManager();

		bool Initlize();
		bool Ternimate();

		void SetURL0(const std::string &url0);
		void SetURl1(const std::string &url1);

		virtual void Update(float appSeconds, float elapsedSeconds);

		void Recognize(const std::string &filename);

	private:
		UDPServer *mUDPServer;
		UIVLCPtr mVLC0;
		UIVLCPtr mVLC1;
	};

}

#endif