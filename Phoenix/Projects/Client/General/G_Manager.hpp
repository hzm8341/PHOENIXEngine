// G_Manage.hpp

#ifndef G_MANAGER_HPP
#define G_MANAGER_HPP

#include "General_Pre.hpp"
#include "PX2EventHandler.hpp"
#include "PX2Singleton.hpp"

namespace PX2
{

	class GENERAL_DLL_ITEM G_Man : public EventHandler
	{
	public:
		PX2_SINGLETION(G_Man);

	public:
		void Initlize();
		void Terminate();
		void Update();

		virtual void OnEvent(Event *event);

	protected:
		void _Play();
		void _Stop();

		bool mIsPlaying;
	};

#define GENERAL_MAN G_Man::GetSingleton()

}

#endif