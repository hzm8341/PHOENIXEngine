// PX2AppliactionPlay.cpp

#include "PX2Application.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2BPManager.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
void Application::Play(PlayType type)
{
	if (mPlayType == type) return;

	if (PT_PLAY == type)
	{
		std::string callFilenameLua = "Data/" + mProjectName + "/scripts/lua/start.lua";
		PX2_SC_LUA->CallFileFunction(callFilenameLua.c_str(), "prestart");

		PX2_GR.SetPlayType((GraphicsRoot::PlayType)type);
		mPlayType = type;

		Event *entPlay = PX2_CREATEEVENTEX(ProjectES, Play);
		PX2_EW.BroadcastingLocalEvent(entPlay);

		PX2_SC_LUA->CallFileFunction(callFilenameLua.c_str(), "start");
	}
	else if (PT_NONE == type)
	{
		PX2_GR.SetPlayType((GraphicsRoot::PlayType)type);
		mPlayType = type;

		Event *entPlay = PX2_CREATEEVENTEX(ProjectES, Stop);
		PX2_EW.BroadcastingLocalEvent(entPlay);
	}
}
//----------------------------------------------------------------------------