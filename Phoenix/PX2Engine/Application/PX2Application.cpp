// PX2Application.cpp

#include "PX2Application.hpp"
#include "PX2TimerManager.hpp"
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
mBPManager(0),
mCreater(0),
mEngineEventHandler(0),
mGeneralServer(0),

mIsInBackground(false),
mBeforeInBackgroundMusicEnable(true),
mBeforeInBackgroundSoundEnable(true),

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

	Time::FrameElapsedSeconds = mElapsedTime;
	Time::FrameRunnedSeconds += mElapsedTime;

	if (mIsInBackground) return;

	// event
	if (mEventWorld)
		mEventWorld->Update((float)mElapsedTime);

	// resource
	PX2_RM.Update(mAppTime, mElapsedTime);

	// font
	PX2_FM.Update();

	if (mSoundSys)
		mSoundSys->Update(mAppTime, mElapsedTime);

	// Plugin
	PX2_PLUGINMAN.Update();

	PX2_ADM.Update((float)mElapsedTime);

	PX2_TimerM.Update((float)mAppTime);

	// graph
	PX2_GR.Update(mAppTime, mElapsedTime);

	if (mGeneralServer)
		mGeneralServer->Run();

	if (mGeneralClientConnector)
		mGeneralClientConnector->Update((float)mElapsedTime);

	PX2_GR.Draw();
}
//----------------------------------------------------------------------------
void Application::Menu_Clear()
{
	mItem->Name = "ExtendMenu";
}
//----------------------------------------------------------------------------
void Application::Menu_AddSubItemCatalogue(
	const std::string &parentAllName,
	const std::string &name,
	const std::string &title)
{
	MenuItem *parentItem = 0;

	if (!parentAllName.empty())
	{
		parentItem = mItem->GetMenuItem(parentAllName);
	}
	else
	{
		parentItem = mItem;
	}

	if (parentItem)
	{
		MenuItem *menuItem = new0 MenuItem();
		menuItem->TheType = MenuItem::T_SUB;
		menuItem->Name = name;
		menuItem->Title = title;
		menuItem->AllName = parentItem->AllName + name;

		parentItem->Items.push_back(menuItem);
	}
}
//----------------------------------------------------------------------------
void Application::Menu_AddItem(
	const std::string &parentAllName,
	const std::string &name,
	const std::string &title,
	const std::string &script)
{
	MenuItem *parentItem = 0;

	if (!parentAllName.empty())
	{
		parentItem = mItem->GetMenuItem(parentAllName);
	}
	else
	{
		parentItem = mItem;
	}

	if (parentItem)
	{
		MenuItem *menuItem = new0 MenuItem();
		menuItem->TheType = MenuItem::T_ITEM;
		menuItem->Name = name;
		menuItem->Title = title;
		menuItem->Script = script;
		menuItem->AllName = parentItem->AllName + name;

		parentItem->Items.push_back(menuItem);
	}
}
//----------------------------------------------------------------------------
Application::MenuItem::MenuItem()
{
	TheType = T_ITEM;
}
//----------------------------------------------------------------------------
Application::MenuItem::~MenuItem()
{
}
//----------------------------------------------------------------------------
void Application::MenuItem::Clear()
{
	for (int i = 0; i < (int)Items.size(); i++)
	{
		MenuItem *item = Items[i];
		item->Clear();
	}

	Items.clear();
}
//----------------------------------------------------------------------------
Application::MenuItem *Application::MenuItem::GetMenuItem(
	const std::string &parentAllName)
{
	for (int i = 0; i < (int)Items.size(); i++)
	{
		MenuItem *item = Items[i];

		if (parentAllName == item->AllName)
			return item;

		MenuItem *subItem = item->GetMenuItem(parentAllName);
		if (subItem)
			return subItem;
	}

	return 0;
}
//----------------------------------------------------------------------------
Application::MenuItem *Application::GetMenuItem()
{
	return mItem;
}
//----------------------------------------------------------------------------