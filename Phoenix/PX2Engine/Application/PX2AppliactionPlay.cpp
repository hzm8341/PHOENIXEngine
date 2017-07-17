// PX2AppliactionPlay.cpp

#include "PX2Application.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2ProjectEvent.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
void Application::Play(PlayType type)
{
	if (mPlayType == type) 
		return;

	std::string dirScirpt = "scripts";
	if (BM_APP == mBoostMode)
		dirScirpt = "/scripts";
	else if (BM_SERVER == mBoostMode)
		dirScirpt = "/scripts_server";

	if (PT_PLAY == type)
	{
		PX2_LOG_INFO("Begin PT_PLAY");

		std::string callFilenameLua = "Data/" + mProjectName + dirScirpt 
			+ "/lua/play.lua";

		PX2_LOG_INFO("Begin PT_PLAY CallFileFunction %s", callFilenameLua.c_str());

		PX2_SC_LUA->CallFileFunction(callFilenameLua.c_str(), "preplay");

		PX2_LOG_INFO("Begin PT_PLAY SetPlayType");

		PX2_GR.SetPlayType((GraphicsRoot::PlayType)type);
		mPlayType = type;

		PX2_LOG_INFO("Begin PT_PLAY broadcast event");

		Event *entPlay = PX2_CREATEEVENTEX(ProjectES, Play);
		PX2_EW.BroadcastingLocalEvent(entPlay);

		PX2_LOG_INFO("Begin PT_PLAY call script");

		PX2_SC_LUA->CallFileFunction(callFilenameLua.c_str(), "play");

		PX2_LOG_INFO("End PT_PLAY");
	}
	else if (PT_NONE == type)
	{
		PX2_LOG_INFO("Begin PT_NONE");

		std::string callFilename = "Data/" + mProjectName + dirScirpt + 
			"/lua/stop.lua";
		PX2_SC_LUA->CallFileFunction(callFilename.c_str(), "prestop");

		PX2_TimerM.ClearTimers();

		PX2_GR.SetPlayType((GraphicsRoot::PlayType)type);
		mPlayType = type;

		Event *entPlay = PX2_CREATEEVENTEX(ProjectES, Stop);
		PX2_EW.BroadcastingLocalEvent(entPlay);

		PX2_SC_LUA->CallFileFunction(callFilename.c_str(), "stop");

		PX2_LOG_INFO("End PT_NONE");
	}
}
//----------------------------------------------------------------------------