// BlueBlockPlugin.hpp

#ifndef BLUEBLOCKPLUGIN_HPP
#define BLUEBLOCKPLUGIN_HPP

#include "PX2Plugin.hpp"
#include "PX2BBlockPre.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM BlueBlockPlugin : public Plugin
	{
	public:
		BlueBlockPlugin();
		virtual ~BlueBlockPlugin();

		virtual void OnInstall();
		virtual void OnUninstall();
		virtual void OnUpdate();

	private:
		static Plugin *sPlugin;
	};

}
#endif