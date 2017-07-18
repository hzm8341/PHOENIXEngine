// SCAPlugin.hpp

#ifndef BLUEBLOCKPLUGIN_HPP
#define BLUEBLOCKPLUGIN_HPP

#include "PX2Plugin.hpp"
#include "SCA_Pre.hpp"

namespace PX2
{

	class SCA_DLL_ITEM SCAPlugin : public Plugin
	{
	public:
		SCAPlugin();
		virtual ~SCAPlugin();

		virtual void OnInstall();
		virtual void OnUninstall();
		virtual void OnUpdate();

	private:
		static Plugin *sPlugin;
	};

}
#endif