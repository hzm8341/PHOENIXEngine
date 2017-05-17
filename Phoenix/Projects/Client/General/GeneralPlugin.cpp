// GeneralPlugin.cpp

#include "GeneralPlugin.hpp"
#include "PX2PluginManager.hpp"
#include "G_Manager.hpp"
#include "PX2Log.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Plugin *GeneralPlugin::sPlugin = 0;
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