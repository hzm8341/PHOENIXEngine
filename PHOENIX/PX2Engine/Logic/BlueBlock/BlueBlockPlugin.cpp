// BlueBlockPlugin.cpp

#include "BlueBlockPlugin.hpp"
#include "PX2PluginManager.hpp"
#include "PX2Log.hpp"
#include "PX2BBManager.hpp"
#include "PX2BBlueBlockToLua.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2LuaPlusContext.hpp"
#include "PX2LogicManager.hpp"
#include "PX2Project.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Plugin *BlueBlockPlugin::sPlugin = 0;
//----------------------------------------------------------------------------
BlueBlockPlugin::BlueBlockPlugin()
{
	mName = "BlueBlockPlugin";
}
//----------------------------------------------------------------------------
BlueBlockPlugin::~BlueBlockPlugin()
{
}
//----------------------------------------------------------------------------
void BlueBlockPlugin::OnInstall()
{
	PX2_LOG_INFO("BlueBlockPlugin::OnInstall()");

	//BBlock::InitializeFactory();
	//BBlockConnector::InitializeFactory();
	//BBlockScriptGenController::InitializeFactory();
	//BBlockSprite::InitializeFactory();

	PX2_LOGICM.AddPkgInfo("Data/BlueBlock/pkg/pkg.xml");

	LuaPlusContext *luaContext = (LuaPlusContext*)PX2_SC_LUA;
	tolua_BBlocks_open((lua_State*)luaContext->GetLuaState());

	BBManager *bbMan = BBManager::GetSingletonPtr();
	if (bbMan)
	{
		PX2_EW.GoOut(bbMan);
		delete0(bbMan);
		BBManager::Set(0);
	}
	bbMan = new0 BBManager();
	PX2_EW.ComeIn(bbMan);

	luaContext->SetUserTypePointer("PX2BBLOCK_SYS", "BBlockSystem",
		BBlockSystem::GetSingletonPtr());

	luaContext->SetUserTypePointer("PX2_BBM", "BBManager",
		BBManager::GetSingletonPtr());

	PX2_LOG_INFO("BlueBlockPlugin::OnInstalled()");
}
//----------------------------------------------------------------------------
void BlueBlockPlugin::OnUninstall()
{
	PX2_LOG_INFO("BlueBlockPlugin::OnUninstall()");

	PX2_LOGICM.SetSelectLogicObject(0);
	PX2_LOGICM.SetCurLogicObject(0);

	BBManager *bbMan = BBManager::GetSingletonPtr();
	if (bbMan)
	{
		delete0(bbMan);
		BBManager::Set(0);
	}

	PX2_LOG_INFO("BlueBlockPlugin::OnUninstalled()");
}
//----------------------------------------------------------------------------
void BlueBlockPlugin::OnUpdate()
{
	BBManager *bbMan = BBManager::GetSingletonPtr();
	if (bbMan)
	{
		bbMan->Update((float)Time::FrameElapsedSeconds);
	}
}
//----------------------------------------------------------------------------