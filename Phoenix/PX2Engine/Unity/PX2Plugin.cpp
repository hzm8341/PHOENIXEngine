// PX2Plugin.cpp

#include "PX2Plugin.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
std::vector<PluginInitlizeFun> Plugin::msPluginInitlizeFuns;
//----------------------------------------------------------------------------
std::vector<PluginTernamateFun> Plugin::msPluginTernamateFuns;
//----------------------------------------------------------------------------
Plugin::Plugin() 
{
	mName = "Plugin";
}
//----------------------------------------------------------------------------
Plugin::~Plugin() 
{
}
//----------------------------------------------------------------------------
std::string Plugin::GetName()
{
	return mName;
}
//----------------------------------------------------------------------------
void Plugin::OnInstall()
{
}
//----------------------------------------------------------------------------
void Plugin::OnUninstall()
{
}
//----------------------------------------------------------------------------
void Plugin::OnUpdate()
{
}
//----------------------------------------------------------------------------
void Plugin::ExecuteInit()
{
	auto it = msPluginInitlizeFuns.begin();
	for (; it != msPluginInitlizeFuns.end(); it++)
	{
		PluginInitlizeFun fun = *it;
		(*fun)();
	}

	msPluginInitlizeFuns.clear();
}
//----------------------------------------------------------------------------
void Plugin::ExecuteTerm()
{
	auto it = msPluginTernamateFuns.begin();
	for (; it != msPluginTernamateFuns.end(); it++)
	{
		PluginTernamateFun fun = *it;
		(*fun)();
	}

	msPluginTernamateFuns.clear();
}
//----------------------------------------------------------------------------
void Plugin::RemoveInit(PluginInitlizeFun fun)
{
	auto it = msPluginInitlizeFuns.begin();
	for (; it != msPluginInitlizeFuns.end();)
	{
		if (*it == fun)
		{
			it = msPluginInitlizeFuns.erase(it);
		}
		else
		{
			it++;
		}
	}
}
//----------------------------------------------------------------------------
void Plugin::RemoveTerm(PluginTernamateFun fun)
{
	auto it = msPluginTernamateFuns.begin();
	for (; it != msPluginTernamateFuns.end();)
	{
		if (*it == fun)
		{
			it = msPluginTernamateFuns.erase(it);
		}
		else
		{
			it++;
		}
	}
}
//----------------------------------------------------------------------------