// SCAPlugin.cpp

#include "SCA_Plugin.hpp"
#include "PX2PluginManager.hpp"
#include "SCA_Manager.hpp"
#include "PX2Log.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Plugin *SCAPlugin::sPlugin = 0;
//----------------------------------------------------------------------------
SCAPlugin::SCAPlugin()
{
	mName = "SCAPlugin";
}
//----------------------------------------------------------------------------
SCAPlugin::~SCAPlugin()
{
}
//----------------------------------------------------------------------------
void SCAPlugin::OnInstall()
{
	PX2_LOG_INFO("SCAPlugin::OnInstall()");

	SCA_MAN.Initlize();
}
//----------------------------------------------------------------------------
void SCAPlugin::OnUninstall()
{
	PX2_LOG_INFO("SCAPlugin::OnUninstall()");

	SCA_MAN.Terminate();
}
//----------------------------------------------------------------------------
void SCAPlugin::OnUpdate()
{
}
//----------------------------------------------------------------------------