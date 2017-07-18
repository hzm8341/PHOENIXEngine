// SCA_Dll.cpp

#include "PX2PluginManager.hpp"
#include "SCA_Plugin.hpp"
#include "PX2InitTerm.hpp"

namespace PX2
{

	Plugin *plugin = 0;

	extern "C" void SCA_DLL_ITEM DLLLoadPlugin(void)
	{
		plugin = new SCAPlugin();
		PluginManager::GetSingleton().InstallPlugin(plugin);
	}

	extern "C" void SCA_DLL_ITEM DLLUnloadPlugin(void)
	{
		PluginManager::GetSingleton().UninstallPlugin(plugin);
	}
}