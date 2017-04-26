// PX2ApplicationInitTerm.cpp

#include "PX2Application.hpp"
#include "PX2Assert.hpp"
#include "PX2RendererInput.hpp"
#include "PX2LocalDateTime.hpp"
#include "PX2PluginManager.hpp"
#include "PX2ToLua.hpp"
#include "PX2NetInitTerm.hpp"
#include "PX2LuaContext.hpp"
#include "PX2LuaPlusContext.hpp"
#include "PX2LuaScriptController.hpp"
#include "PX2EngineSceneCanvas.hpp"
#include "PX2EngineUICanvas.hpp"
#include "PX2ProjectEventController.hpp"
#include "PX2ServerInfoManager.hpp"
#include "PX2Bluetooth.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
bool Application::Initlize()
{
	time_t ti; time(&ti); srand((unsigned int)ti);

#ifdef PX2_USE_MEMORY
	Memory::Initialize();
#endif

	StringHelp::Initlize();
	FString::Initlize();

	Logger *logger = new0 Logger();

#if defined(_WIN32) || defined(WIN32) || defined(__LINUX__)
	logger->AddFileHandler("PX2Application_Log.txt",
	 LT_INFO | LT_ERROR | LT_USER);
#endif

#if defined (__LINUX__)
	logger->AddConsoleHandler(LT_INFO | LT_ERROR | LT_USER);
#endif

	logger->AddOutputWindowHandler(LT_INFO | LT_ERROR | LT_USER);
	logger->StartLogger();

	LocalDateTime time;
	int year1 = time.Year();
	int month1 = time.Month();
	int week1 = time.Week();
	int day1 = time.Day();
	int dayOfWeek1 = time.DayOfWeek();
	int dayOfYear1 = time.DayOfYear();
	int hour1 = time.Hour();
	int minute1 = time.Minute();
	int second1 = time.Second();
	int millisecond1 = time.Millisecond();
	int microsecond1 = time.Microsecond();
	PX2_LOG_INFO("Year:%d; Month:%d; Week:%d; Day:%d; DayOfWeek:%d; DayOfYear:%d; Hour:%d; Minute:%d; Second:%d; Millisecond:%d; Microsecond:%d",
		year1, month1, week1, day1, dayOfWeek1, dayOfYear1, hour1, minute1, 
		second1, millisecond1, microsecond1);

	InitializeNetwork();

	mDynLibMan = new0 DynLibManager();
	PX2_UNUSED(mDynLibMan);
	mPluginMan = new0 PluginManager();
	PX2_UNUSED(mPluginMan);

	mTimerMan = new0 TimerManager();

	mIMEDisp = new0 IMEDispatcher();

	mInputMan = new0 InputManager();

	mLanguageMan = new0 LanguageManager();
	mResMan = new0 ResourceManager();

	mEventWorld = new0 EventWorld();

	mScriptMan = new0 ScriptManager();
	mScriptMan->AddContext(new0 LuaPlusContext());

	mBluetooth = new0 Bluetooth();

	mRoot = new0 GraphicsRoot();
	mRoot->Initlize();

	mFontMan = new0 FontManager();
	mFontMan->Initlize();
	
	SoundSystemInitInfo info;
	mSoundSys = SoundSystem::Create(SoundSystem::ST_FMOD, info);

	mADMan = new0 AddDeleteManager();
	PX2_UNUSED(mADMan);

	mSelectionMan = new0 SelectionManager();
	PX2_UNUSED(mSelectionMan);

	mURDoMan = new0 URDoManager();
	PX2_UNUSED(mURDoMan);

	mURStateMan = new0 URStateManager();
	PX2_UNUSED(mURStateMan);

	mFunObjectManager = new0 FunObjectManager();
	mFunObjectManager->Initlize();

	mAccoutManager = new0 AccoutManager();

	mUIAuiManager = new0 UIAuiManager();

	mUISkinManager = new0 UISkinManager();

	mLogicManager = new0 LogicManager();
	mLogicManager->Initlize();

	mBPManager = new0 BPManager();

	mCreater = new0 Creater();

	mEngineEventHandler = new0 EngineEventHandler();
	PX2_EW.ComeIn(mEngineEventHandler);

	LuaPlusContext *luaContext = (LuaPlusContext*)PX2_SC_LUA;

	// Lua
	tolua_PX2_open((lua_State*)luaContext->GetLuaState());
	LuaPlus::LuaState *luaPlusState = luaContext->GetLuaPlusState();
	PX2_UNUSED(luaPlusState);
	LuaScriptController::RegisterScriptClass();

	PX2_SC_LUA->SetUserTypePointer("PX2_GR", "GraphicsRoot", GraphicsRoot::GetSingletonPtr());
	PX2_SC_LUA->SetUserTypePointer("PX2_APP", "Application", Application::GetSingletonPtr());
	PX2_SC_LUA->SetUserTypePointer("PX2_LM_EDITOR", "LanguagePackage", LanguageManager::GetSingletonPtr()->GetPackageEditor());
	PX2_SC_LUA->SetUserTypePointer("PX2_LM_APP", "LanguagePackage", LanguageManager::GetSingletonPtr()->GetPackageApp());
	PX2_SC_LUA->SetUserTypePointer("PX2_LM_APP1", "LanguagePackage", LanguageManager::GetSingletonPtr()->GetPackageApp1());
	PX2_SC_LUA->SetUserTypePointer("PX2_LOGGER", "Logger", Logger::GetSingletonPtr());
	PX2_SC_LUA->SetUserTypePointer("PX2_RM", "ResourceManager", PX2_SC_LUA);
	PX2_SC_LUA->SetUserTypePointer("PX2_SM", "ScriptManager", ScriptManager::GetSingletonPtr());
	PX2_SC_LUA->SetUserTypePointer("PX2_SC_LUA", "LuaContext", PX2_SC_LUA);
	PX2_SC_LUA->SetUserTypePointer("PX2_CREATER", "Creater", Creater::GetSingletonPtr());
	PX2_SC_LUA->SetUserTypePointer("PX2_SELECTM", "SelectionManager", SelectionManager::GetSingletonPtr());
	PX2_SC_LUA->SetUserTypePointer("PX2_SELECTM_D", "Selection", SelectionManager::GetSingleton().GetSelecton("Default"));
	PX2_SC_LUA->SetUserTypePointer("PX2_SELECTM_E", "Selection", SelectionManager::GetSingleton().GetSelecton("Editor"));
	PX2_SC_LUA->SetUserTypePointer("PX2_EEH", "EngineEventHandler", EngineEventHandler::GetSingletonPtr());
	PX2_SC_LUA->SetUserTypePointer("PX2_URDOM", "URDoManager", URDoManager::GetSingletonPtr());
	PX2_SC_LUA->SetUserTypePointer("PX2_LOGICM", "LogicManager", LogicManager::GetSingletonPtr());
	PX2_SC_LUA->SetUserTypePointer("PX2_BLUETOOTH", "Bluetooth", Bluetooth::GetSingletonPtr());
	PX2_SC_LUA->SetUserTypePointer("PX2_SS", "SoundSystem", SoundSystem::GetSingletonPtr());
	// end Lua

	Canvas *mainCanvas = new0 Canvas();
	mainCanvas->SetMain(true);
	mainCanvas->CreateUICameraNode();
	mainCanvas->EnableAnchorLayout(true);
	mainCanvas->SetAnchorHor(0.0f, 1.0f);
	mainCanvas->SetAnchorVer(0.0f, 1.0f);
	mainCanvas->ComeInEventWorld();
	mainCanvas->SetName("MainCanvas");

	mItem = new0 MenuItem();
	mItem->Name = "ExtendMenu";
	mItem->TheType = Application::MenuItem::T_SUB;

	RenderWindow *rw = PX2_GR.GetMainWindow();
	rw->SetMainCanvas(mainCanvas);

	PX2_SC_LUA->CallFile("Data/engine/scripts/lua/engine_start.lua");

	PX2_LOG_INFO("End Application::Initlize.");

	LoadBoost("Data/boost.xml");

	PX2_SC_LUA->CallFile("Data/boost.lua");

	return true;
}
//----------------------------------------------------------------------------
void Application::InitlizeDefaultEngineCanvas(Canvas *parentCanvas)
{
	mEngineCanvas = new0 EngineCanvas();
	parentCanvas->AttachChild(mEngineCanvas);
}
//----------------------------------------------------------------------------
Renderer * Application::InitlizeRenderer()
{
	Renderer *defRenderer = CreateRenderer("DefaultRenderer", mPt_Data,
		mPt_Data1, mPt_Data2, (int)mPt_Size.Width, (int)mPt_Size.Height, 0);
	Renderer::SetDefaultRenderer(defRenderer);
	PX2_GR.GetMainWindow()->SetRenderer(defRenderer);

	mScreenSize = mPt_Size;

	return defRenderer;
}
//----------------------------------------------------------------------------
Renderer *Application::CreateRenderer(const std::string &name, void *winHandle,
	void *ptDataLinuxWindow, void *ptDataLinuxVisual,
	int width, int height, int numMultisamples)
{
	RendererInput *rendererInput = 0;
	Renderer *renderer = Renderer::CreateRenderer(winHandle, ptDataLinuxWindow,
		ptDataLinuxVisual, width, height, numMultisamples, rendererInput);
	renderer->SetName(name);

	mRenderersMap[name] = renderer;
	mRendererInputMap[name] = rendererInput;

	return renderer;
}
//----------------------------------------------------------------------------
RendererInput *Application::GetRendererInput(const std::string &name)
{
	auto it = mRendererInputMap.find(name);
	if (it != mRendererInputMap.end())
	{
		return it->second;
	}

	return 0;
}
//----------------------------------------------------------------------------
Renderer *Application::GetRenderer(const std::string &name)
{
	auto it = mRenderersMap.find(name);
	if (it != mRenderersMap.end())
	{
		return it->second;
	}

	return 0;
}
//----------------------------------------------------------------------------
GeneralServer *Application::CreateGeneralServer(int port,
	int numMaxConnects, int numMaxMsgHandlers)
{
	if (mGeneralServer)
	{
		mGeneralServer->Shutdown();
		mGeneralServer = 0;
	}

	mGeneralServer = new0 GeneralServer(Server::ST_POLL, port, numMaxConnects,
		numMaxMsgHandlers);

	PX2_SC_LUA->SetUserTypePointer("PX2_GS", "GeneralServer",
		(GeneralServer*)mGeneralServer);

	return mGeneralServer;
}
//----------------------------------------------------------------------------
GeneralServer *Application::GetGeneralServer()
{
	return mGeneralServer;
}
//----------------------------------------------------------------------------
GeneralClientConnector *Application::CreateGeneralClientConnector()
{
	if (mGeneralClientConnector)
	{
		mGeneralClientConnector->Disconnect();
		mGeneralClientConnector = 0;
	}

	mGeneralClientConnector = new0 GeneralClientConnector();

	PX2_SC_LUA->SetUserTypePointer("PX2_GCC", "GeneralClientConnector",
		(GeneralClientConnector*)mGeneralClientConnector);

	return mGeneralClientConnector;
}
//----------------------------------------------------------------------------
GeneralClientConnector *Application::GetGeneralClientConnector()
{
	return mGeneralClientConnector;
}
//----------------------------------------------------------------------------
void Application::WillEnterForeground(bool isFirstTime)
{
	PX2_LOG_INFO("WillEnterForeground %s", isFirstTime ? "true":"false");
	PX2_LOG_INFO("IsInBackground %s", mIsInBackground ? "true" : "false");

	if (!mIsInBackground) return;

	if (isFirstTime)
	{
		PX2_FM.Initlize();
	}
	else
	{
		Renderer::GetDefaultRenderer()->OnRestoreDevice();

		PX2_FM.SetNeedUpdate();
	}

	mIsInBackground = false;
}
//----------------------------------------------------------------------------
void Application::DidEnterBackground()
{
	PX2_LOG_INFO("DidEnterBackground");

	Renderer::GetDefaultRenderer()->OnLostDevice();

	mIsInBackground = true;
}
//----------------------------------------------------------------------------
bool Application::Terminate()
{
	Play(Application::PT_NONE);
	CloseProject();

	Plugin::ExecuteTerm();

	PX2_PLUGINMAN.UnloadPlugins();

	PX2_SC_LUA->CallFile("Data/engine/scripts/lua/engine_end.lua");

	mItem = 0;

	mEngineCanvas = 0;

	PX2_EW.Shutdown(true);

	mScriptMan->TernimateAll();
	if (mScriptMan)
	{
		delete0(mScriptMan);
		ScriptManager::Set(0);
	}

	if (mEngineEventHandler)
	{
		delete0(mEngineEventHandler);
	}

	if (mGeneralServer)
	{
		mGeneralServer->Shutdown();
		mGeneralServer = 0;
	}

	if (mGeneralClientConnector)
	{
		mGeneralClientConnector->Disconnect();
		mGeneralClientConnector = 0;
	}

	if (mCreater)
	{
		delete0(mCreater);
		Creater::Set(0);
	}

	if (mBPManager)
	{
		delete0(mBPManager);
		BPManager::Set(0);
	}

	if (mLogicManager)
	{
		delete0(mLogicManager);
		LogicManager::Set(0);
	}

	if (mUISkinManager)
	{
		delete0(mUISkinManager);
		UISkinManager::Set(0);
	}

	if (mUIAuiManager)
	{
		delete0(mUIAuiManager);
		UIAuiManager::Set(0);
	}

	if (mSelectionMan)
	{
		mSelectionMan->Clear();
		delete0(mSelectionMan);
		SelectionManager::Set(0);
	}

	if (mURDoMan)
	{
		delete0(mURDoMan);
		URDoManager::Set(0);
	}

	PX2_SVRINFOMAN.Clear();

	if (mURStateMan)
	{
		delete0(mURStateMan);
		URStateManager::Set(0);
	}

	if (mADMan)
	{
		mADMan->Clear();
		delete0(mADMan);
		AddDeleteManager::Set(0);
	}

	if (mFunObjectManager)
	{
		mFunObjectManager->Terminate();
		delete0(mFunObjectManager);
		FunObjectManager::Set(0);
	}

	if (mSoundSys)
	{
		delete0(mSoundSys);
		SoundSystem::Set(0);
	}

	if (mAccoutManager)
	{
		delete0(mAccoutManager);
		AccoutManager::Set(0);
	}

	if (mFontMan)
	{
		delete0(mFontMan);
		FontManager::Set(0);
	}

	bool isInEditor = mRoot->IsInEditor();
	PX2_UNUSED(isInEditor);
	if (mRoot)
	{
		mRoot->Terminate();
		delete0(mRoot);
		GraphicsRoot::Set(0);
	}

	if (mInputMan)
	{
		delete0(mInputMan);
		mInputMan = 0;
	}

	if (mResMan)
	{
		mResMan->Clear();
		delete0(mResMan);		
		ResourceManager::Set(0);
	}

	if (mBluetooth)
	{
		delete0(mBluetooth);
		Bluetooth::Set(0);
	}

	if (mLanguageMan)
	{
		delete0(mLanguageMan);
		LanguageManager::Set(0);
	}

	if (mIMEDisp)
	{ // 需要在资源管理器之后释放
		delete0(mIMEDisp);
		IMEDispatcher::Set(0);
	}

	if (mEventWorld)
	{
		delete0(mEventWorld);
		EventWorld::Set(0);
	}

	if (mTimerMan)
	{
		delete0(mTimerMan);
		TimerManager::Set(0);
	}

	std::map<std::string, Renderer*>::iterator it = mRenderersMap.begin();
	for (; it != mRenderersMap.end(); it++)
	{
		Renderer *renderer = it->second;
		delete0(renderer);
	}
	Renderer::SetDefaultRenderer(0);
	mRenderersMap.clear();

	std::map<std::string, RendererInput*>::iterator itInput = mRendererInputMap.begin();
	for (; itInput != mRendererInputMap.end(); itInput++)
	{
		RendererInput *rendererInput = itInput->second;
		delete0(rendererInput);
	}
	mRendererInputMap.clear();

	PX2_PLUGINMAN.UnloadPlugins();
	if (mPluginMan)
	{
		delete0(mPluginMan);
		PluginManager::Set(0);
	}

	if (mDynLibMan)
	{
		delete0(mDynLibMan);
		DynLibManager::Set(0);
	}

	TerminateNetwork();

	PX2_LOG_INFO("Engine Terminate done.");
	Logger *logger = Logger::GetSingletonPtr();
	if (logger)
	{
		delete0(logger);
		Logger::Set(0);
	}

	FString::Ternimate();

#ifdef PX2_USE_MEMORY

	if (isInEditor)
	{
		Memory::Terminate("Editor_MemoryReport.txt", false);
	}
	else
	{
		Memory::Terminate("PX2Application_MemoryReport.txt", false);
	}

#endif

	return true;
}
//----------------------------------------------------------------------------
void Application::SetBoostMode(BoostMode mode)
{
	mBoostMode = mode;
}
//----------------------------------------------------------------------------
Application::BoostMode Application::GetBoostMode() const
{
	return mBoostMode;
}
//----------------------------------------------------------------------------
bool Application::LoadBoost(const std::string &filename)
{
	XMLData data;

	int bufferSize = 0;
	char *buffer = 0;
	ResourceManager::GetSingleton().LoadBuffer(filename, bufferSize, buffer);
	if (!buffer || bufferSize == 0) 
	{
		mBoostInfo.BoostSize = Sizef(1136.0f, 600.0f);
		return false;
	}

	if (data.LoadBuffer(buffer, bufferSize))
	{
		XMLNode rootNode = data.GetRootNode();
		XMLNode nodeChild = rootNode.IterateChild();
		while (!nodeChild.IsNull())
		{
			const std::string &name = nodeChild.GetName();
			if ("app" == name)
			{
				mBoostInfo.BoostSize.Width = data.GetNodeByPath("app.config.var").AttributeToFloat("width");
				mBoostInfo.BoostSize.Height = data.GetNodeByPath("app.config.var").AttributeToFloat("height");
				mBoostInfo.ProjectName = data.GetNodeByPath("app.play.var").AttributeToString("projectname");
				mBoostInfo.ThePlayLogicMode = _StrToPlayLogicMode(data.GetNodeByPath("app.play.var").AttributeToString("playlogicmode"));
				mBoostInfo.IsShowInfo = data.GetNodeByPath("app.play.var").AttributeToBool("isshowinfo");

				XMLNode nodePlugins = data.GetNodeByPath("app.plugins");
				XMLNode nodePlugin = nodePlugins.IterateChild();
				if (!nodePlugin.IsNull())
				{
					std::string name = nodePlugin.AttributeToString("name");
					mBoostInfo.Plugins.push_back(name);

					nodePlugin = nodePlugins.IterateChild(nodePlugin);
				}

				if (BM_APP == mBoostMode)
				{
					for (int i = 0; i < (int)mBoostInfo.Plugins.size(); i++)
					{
						const std::string &pluginName = mBoostInfo.Plugins[i];
						if (!pluginName.empty())
						{
							std::string path = "PluginsCommon/" + pluginName + "/" +
								GetDllFileName(pluginName);
							PX2_PLUGINMAN.Load(path);
						}
					}
				}
			}
			else if ("server" == name)
			{
				AppBoostInfo info;

				XMLNode nodePlay = nodeChild.GetChild("play");
				info.ProjectName = nodePlay.GetChild("var").AttributeToString("projectname");
				info.Port = nodePlay.GetChild("var").AttributeToInt("port");
				info.NumMaxConnection = nodePlay.GetChild("var").AttributeToInt("nummaxconnection");

				XMLNode nodePlugins = nodeChild.GetChild("plugins");
				XMLNode nodePlugin = nodePlugins.IterateChild();
				if (!nodePlugin.IsNull())
				{
					std::string name = nodePlugin.AttributeToString("name");
					info.Plugins.push_back(name);

					nodePlugin = nodePlugins.IterateChild(nodePlugin);
				}

				mBoostServerInfo = info;

				if (BM_SERVER == mBoostMode)
				{
					for (int i = 0; i < (int)mBoostServerInfo.Plugins.size(); i++)
					{
						const std::string &pluginName = mBoostServerInfo.Plugins[i];
						if (!pluginName.empty())
						{
							std::string path = "PluginsCommon/" + pluginName + "/" +
								GetDllFileName(pluginName);
							PX2_PLUGINMAN.Load(path);
						}
					}
				}
			}

			nodeChild = rootNode.IterateChild(nodeChild);
		}

		Plugin::ExecuteInit();

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
std::string Application::GetPlayLogicModeStr() const
{
	if (AppBoostInfo::PLM_SIMPLE == mBoostInfo.ThePlayLogicMode)
		return "simple";

	return "logic";
}
//----------------------------------------------------------------------------
AppBoostInfo::PlayLogicMode Application::_StrToPlayLogicMode(
	const std::string &str)
{
	if ("simple" == str)
		AppBoostInfo::PLM_SIMPLE;

	return AppBoostInfo::PLM_LOGIC;
}
//----------------------------------------------------------------------------
bool Application::IsShowInfo() const
{
	return mBoostInfo.IsShowInfo;
}
//----------------------------------------------------------------------------
void Application::SetBoostProjectName(const std::string &boostProjectName)
{
	mBoostInfo.ProjectName = boostProjectName;
}
//----------------------------------------------------------------------------
void Application::SetBoostSize(const Sizef &size)
{
	mBoostInfo.BoostSize = size;
}
//----------------------------------------------------------------------------
void Application::SetBoostSize(float width, float height)
{
	mBoostInfo.BoostSize.Width = width;
	mBoostInfo.BoostSize.Height = height;
}
//----------------------------------------------------------------------------
void Application::SetPlayLogicMode(AppBoostInfo::PlayLogicMode mode)
{
	mBoostInfo.ThePlayLogicMode = mode;
}
//----------------------------------------------------------------------------
void Application::SetShowInfo(bool show)
{
	mBoostInfo.IsShowInfo = show;
}
//----------------------------------------------------------------------------
bool Application::WriteBoost()
{
	XMLData data;

	data.Create();

	//XMLNode boostNode = data.NewChild("boost");
	//boostNode.SetAttributeString("name", "boost");

	//XMLNode configNode = boostNode.NewChild("config");

	//XMLNode varNode_config = configNode.NewChild("var");
	//varNode_config.SetAttributeInt("width", (int)mBoostSize.Width);
	//varNode_config.SetAttributeInt("height", (int)mBoostSize.Height);

	//XMLNode playNode = boostNode.NewChild("play");
	//XMLNode varNode_play = playNode.NewChild("var");
	//varNode_play.SetAttributeString("projectname", mBoostProjectName);
	//varNode_play.SetAttributeString("playlogicmode", GetPlayLogicModeStr());

	return data.SaveFile("Data/boost.xml");
}
//----------------------------------------------------------------------------
AppBoostInfo &Application::GetBoostServerInfo()
{
	return mBoostServerInfo;
}
//----------------------------------------------------------------------------
void Application::SetScreenSize(const Sizef &screenSize)
{
	PX2_LOG_INFO("Application::SetScreenSize Width:%.2f, Height:%.2f", 
		screenSize.Width, screenSize.Height);

	mScreenSize = screenSize;
	PX2_GR.GetMainWindow()->SetScreenSize(mScreenSize);
	PX2_INPUTMAN.GetDefaultListener()->SetViewSize(mScreenSize);
}
//----------------------------------------------------------------------------