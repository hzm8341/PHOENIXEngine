// GeneralPlugin.cpp

#include "GeneralPlugin.hpp"
#include "PX2PluginManager.hpp"
#include "G_Manager.hpp"
#include "PX2Log.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Plugin *GeneralPlugin::sPlugin = 0;
//----------------------------------------------------------------------------
PX2_IMPLEMENT_PLUGIN(GeneralPlugin);
//----------------------------------------------------------------------------
GeneralPlugin::GeneralPlugin()
{
	mName = "GeneralPlugin";
}
//----------------------------------------------------------------------------
GeneralPlugin::~GeneralPlugin()
{
}
//----------------------------------------------------------------------------
bool GeneralPlugin::PluginInitialize()
{
	sPlugin = new GeneralPlugin();
	PluginManager::GetSingleton().InstallPlugin(sPlugin);

	return true;
}
//----------------------------------------------------------------------------
bool GeneralPlugin::PluginTerminate()
{
	if (sPlugin)
	{
		PluginManager::GetSingleton().UninstallPlugin(sPlugin);
		sPlugin = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
void GeneralPlugin::OnInstall()
{
	PX2_LOG_INFO("GeneralPlugin::OnInstall()");

	GENERAL_MAN.Initlize();
}
//----------------------------------------------------------------------------
void GeneralPlugin::OnUninstall()
{
	PX2_LOG_INFO("GeneralPlugin::OnUninstall()");

	GENERAL_MAN.Terminate();
}
//----------------------------------------------------------------------------
void GeneralPlugin::OnUpdate()
{
}
//----------------------------------------------------------------------------