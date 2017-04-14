// GeneralDll.cpp

#include "PX2PluginManager.hpp"
#include "GeneralPlugin.hpp"
#include "PX2InitTerm.hpp"

namespace PX2
{

	//Plugin *plugin = 0;

	extern "C" void GENERAL_DLL_ITEM DLLLoadPlugin(void)
	{
		//plugin = new GeneralPlugin();
		//PluginManager::GetSingleton().InstallPlugin(plugin);
	}

	extern "C" void GENERAL_DLL_ITEM DLLUnloadPlugin(void)
	{
		//PluginManager::GetSingleton().UninstallPlugin(plugin);
	}
}