// BlueBlockDll.cpp

#include "PX2PluginManager.hpp"
#include "BlueBlockPlugin.hpp"
#include "PX2InitTerm.hpp"

namespace PX2
{

	Plugin *plugin = 0;

	extern "C" void PX2_ENGINE_ITEM DLLLoadPlugin(void)
	{
		plugin = new BlueBlockPlugin();
		PluginManager::GetSingleton().InstallPlugin(plugin);
	}

	extern "C" void PX2_ENGINE_ITEM DLLUnloadPlugin(void)
	{
		PluginManager::GetSingleton().UninstallPlugin(plugin);
	}
}