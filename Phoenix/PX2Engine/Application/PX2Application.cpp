// PX2Application.cpp

#include "PX2Application.hpp"
#include "PX2TimerManager.hpp"
#include "PX2GraphicsEventType.hpp"
#include "PX2EngineNetEvent.hpp"
#include "PX2Arduino.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Application::Application() :
mPt_Data(0),
mPt_Data1(0),
mPt_Data2(0),

mDynLibMan(0),
mPluginMan(0),
mTimerMan(0),
mEventWorld(0),
mLanguageMan(0),
mBluetooth(0),
mHardCamera(0),
mRoot(0),
mIMEDisp(0),
mInputMan(0),
mResMan(0),
mScriptMan(0),
mFontMan(0),
mSoundSys(0),
mADMan(0),
mSelectionMan(0),
mURDoMan(0),
mFunObjectManager(0),
mAccoutManager(0),
mUIAuiManager(0),
mUISkinManager(0),
mLogicManager(0),
mCreater(0),
mArduino(0),

mIsInBackground(false),
mBeforeInBackgroundMusicEnable(true),
mBeforeInBackgroundSoundEnable(true),
mIsQuit(false),

mBoostMode(BM_APP),
mPlayType(PT_NONE),

mAppTime(0),
mLastAppTime(0),
mElapsedTime(0)
{
}
//----------------------------------------------------------------------------
Application::~Application()
{
}
//----------------------------------------------------------------------------
void Application::SetPt_Data(void *data)
{
	mPt_Data = data;
}
//----------------------------------------------------------------------------
void *Application::GetPt_Data()
{
	return mPt_Data;
}
//----------------------------------------------------------------------------
void Application::SetPt_Data1(void *data)
{
	mPt_Data1 = data;
}
//----------------------------------------------------------------------------
void *Application::GetPt_Data1()
{
	return mPt_Data1;
}
//----------------------------------------------------------------------------
void Application::SetPt_Data2(void *data)
{
	mPt_Data2 = data;
}
//----------------------------------------------------------------------------
void *Application::GetPt_Data2()
{
	return mPt_Data2;
}
//----------------------------------------------------------------------------
void Application::SetPt_Size(const Sizef &size)
{
	mPt_Size = size;
}
//----------------------------------------------------------------------------
const Sizef &Application::GetPt_Size() const
{
	return mPt_Size;
}
//----------------------------------------------------------------------------
Application::PlatformType Application::GetPlatformType() const
{
#if defined (_WIN32) || defined(WIN32)
	return PLT_WINDOWS;
#elif defined (__LINUX__)
	return PLT_LINUX;
#elif defined (__ANDROID__)
	return PLT_ANDROID;
#else
	return PLT_IOS;
#endif
}
//----------------------------------------------------------------------------
float Application::GetElapsedTime()
{
	return (float)(mAppTime - mLastAppTime);
}
//----------------------------------------------------------------------------
void Application::Update()
{
	mAppTime = Time::GetTimeInSeconds();
	mElapsedTime = GetElapsedTime();
	mLastAppTime = mAppTime;
	if (mElapsedTime > 1.0f)
		mElapsedTime = 0.1f;

	Time::FrameElapsedSeconds = mElapsedTime;
	Time::FrameRunnedSeconds += mElapsedTime;

	Update((float)mAppTime, (float)mElapsedTime);
}
//----------------------------------------------------------------------------
void Application::Update(float appSeconds, float elapsedSeconds)
{
	// event
	if (mEventWorld)
		mEventWorld->Update((float)elapsedSeconds);

	// resource
	PX2_RM.Update(appSeconds, elapsedSeconds);

	// font
	PX2_FM.Update();

	if (mSoundSys)
		mSoundSys->Update(appSeconds, elapsedSeconds);

	// Plugin
	PX2_PLUGINMAN.Update();

	PX2_ADM.Update((float)elapsedSeconds);

	PX2_TIMERM.Update((float)appSeconds);

	// graph
	PX2_GR.Update(appSeconds, elapsedSeconds);

	if (mEngineServer)
		mEngineServer->Run((float)elapsedSeconds);

	if (mEngineClient)
		mEngineClient->Update((float)elapsedSeconds);

	if (mEngineUDPServerClient)
		mEngineUDPServerClient->Update((float)elapsedSeconds);

	if (mEngineDUPServerEditor)
		mEngineDUPServerEditor->Update((float)elapsedSeconds);

	if (mGeneralServer)
		mGeneralServer->Run((float)elapsedSeconds);

	if (mGeneralClientConnector)
		mGeneralClientConnector->Update((float)elapsedSeconds);

	if (mArduino)
		mArduino->Update((float)elapsedSeconds);

	PX2_BLUETOOTH.Update((float)elapsedSeconds);
	PX2_WIFI.Update((float)elapsedSeconds);

	_UpdateUDPNetInfos((float)elapsedSeconds);

	if (!mUpdateScriptCallbacks.empty())
	{
		std::string strAppSeconds = StringHelp::FloatToString(appSeconds);
		std::string strElapsedSeconds = StringHelp::FloatToString(elapsedSeconds);
		auto it = mUpdateScriptCallbacks.begin();
		for (; it != mUpdateScriptCallbacks.end(); it++)
		{
			std::string scriptCallback = *it;
			PX2_SC_LUA->CallString(scriptCallback + "(\"" + strAppSeconds +
				", " + strElapsedSeconds + "\")");
		}
	}

	if (mIsInBackground) return;

	PX2_GR.Draw();
}
//----------------------------------------------------------------------------
bool Application::IsHasUpdateScriptCallback(const std::string &callback)
{
	for (int i = 0; i < (int)mUpdateScriptCallbacks.size(); i++)
	{
		if (callback == mUpdateScriptCallbacks[i])
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
bool Application::AddUpdateScriptCallback(const std::string &callback)
{
	if (IsHasUpdateScriptCallback(callback))
		return false;

	mUpdateScriptCallbacks.push_back(callback);

	return true;
}
//----------------------------------------------------------------------------
bool Application::RemoveUpdateScriptCallback(const std::string &callback)
{
	auto it = mUpdateScriptCallbacks.begin();
	for (; it != mUpdateScriptCallbacks.end();)
	{
		if (callback == *it)
		{
			it = mUpdateScriptCallbacks.erase(it);
			return true;
		}
		else
		{
			it++;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
void Application::ClearUpdateScriptCallback()
{
	mUpdateScriptCallbacks.clear();
}
//----------------------------------------------------------------------------
void Application::OnEvent(Event *ent)
{
	if (EngineNetES::IsEqual(ent, EngineNetES::OnEngineServerBeConnected))
	{
		std::string ip = ent->GetDataStr1();
		UDPNetInfo *info = GetUDPNetInfo(ip);
		if (info)
		{
			info->IsConnected = true;
		}
	}
	else if (EngineNetES::IsEqual(ent, EngineNetES::OnEngineServerBeDisConnected))
	{
		std::string ip = ent->GetDataStr1();
		UDPNetInfo *info = GetUDPNetInfo(ip);
		if (info)
		{
			info->IsConnected = false;
		}
	}
}
//----------------------------------------------------------------------------
void Application::SendGeneralEvent(const std::string &eventDataStr0)
{
	Event *ent = PX2_CREATEEVENTEX(GraphicsES, GeneralString);
	ent->SetData<std::string>(eventDataStr0);
	ent->SetDataStr0(eventDataStr0);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Application::SendGeneralEvent(const std::string &eventDataStr0, 
	const std::string &eventDataStr1)
{
	Event *ent = PX2_CREATEEVENTEX(GraphicsES, GeneralString);
	ent->SetData<std::string>(eventDataStr0);
	ent->SetDataStr0(eventDataStr0);
	ent->SetDataStr1(eventDataStr1);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------