// SCA_Manage.hpp

#ifndef SCA_MANAGER_HPP
#define SCA_MANAGER_HPP

#include "SCA_Pre.hpp"
#include "PX2EventHandler.hpp"
#include "PX2Singleton.hpp"
#include "PX2HTTPServer.hpp"

namespace PX2
{

	class SCA_DLL_ITEM SCA_Man : public EventHandler
	{
	public:
		PX2_SINGLETION(SCA_Man);

	public:
		void Initlize();
		void Terminate();
		void Update();

		virtual void OnEvent(Event *event);

	protected:
		void _Play();
		void _Stop();

		bool mIsPlaying;
		HTTPServerPtr mHttpServer;
	};

#define SCA_MAN SCA_Man::GetSingleton()

}

#endif