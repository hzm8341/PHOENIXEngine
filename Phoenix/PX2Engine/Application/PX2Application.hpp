// PX2Application.hpp

#ifndef PX2APPLICATION_HPP
#define PX2APPLICATION_HPP

#include "PX2Singleton_NeedNew.hpp"
#include "PX2Project.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2Bluetooth.hpp"
#include "PX2HardCamera.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2DynLibManager.hpp"
#include "PX2PluginManager.hpp"
#include "PX2FunObject.hpp"
#include "PX2IMEDispatcher.hpp"
#include "PX2InputManager.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2FontManager.hpp"
#include "PX2AddDeleteManager.hpp"
#include "PX2SelectionManager.hpp"
#include "PX2RedoUndo.hpp"
#include "PX2RUStateManager.hpp"
#include "PX2AccoutManager.hpp"
#include "PX2Project.hpp"
#include "PX2UIAuiManager.hpp"
#include "PX2UISkinManager.hpp"
#include "PX2SoundSystem.hpp"
#include "PX2Creater.hpp"
#include "PX2Singleton.hpp"
#include "PX2RendererInput.hpp"
#include "PX2TimerManager.hpp"
#include "PX2LogicManager.hpp"
#include "PX2EngineCanvas.hpp"
#include "PX2UISizeExtendControl.hpp"
#include "PX2AppBoostInfo.hpp"
#include "PX2GeneralServer.hpp"
#include "PX2GeneralClientConnector.hpp"
#include "PX2EngineServer.hpp"
#include "PX2EngineClientConnector.hpp"
#include "PX2UDPServer.hpp"
#include "PX2ApplicationUDPNetInfo.hpp"

namespace PX2
{

	class Arduino;
	class VoiceSDK;

	class PX2_ENGINE_ITEM Application : public Singleton<Application>, public EventHandler
	{
	public:
		Application();
		virtual ~Application();

		enum PlatformType
		{
			PLT_WINDOWS,
			PLT_LINUX,
			PLT_ANDROID,
			PLT_IOS,
			PLT_MAX_TYPE
		};
		PlatformType GetPlatformType() const;

		// pre init
	public:
		void SetPt_Data(void *data);
		void *GetPt_Data();
		void SetPt_Data1(void *data);
		void *GetPt_Data1();
		void SetPt_Data2(void *data);
		void *GetPt_Data2();
		void SetPt_Size(const Sizef &size);
		const Sizef &GetPt_Size() const;

	protected:
		void *mPt_Data;
		void *mPt_Data1;
		void *mPt_Data2;
		Sizef mPt_Size;

		// init term
	public:
		bool Initlize();
		void InitlizeDefaultEngineCanvas(Canvas *parentCanvas);
		Renderer *InitlizeRenderer();
		Renderer *CreateRenderer(const std::string &name, void *winHandle,
			void *ptDataLinuxWindow, void *ptDataLinuxVisual,
			int width, int height, int numMultisamples);
		RendererInput *GetRendererInput(const std::string &name);
		Renderer *GetRenderer(const std::string &name);

		const std::string &GetHostName() const;

		void SetInEditor(bool isInEditor);
		bool IsInEditor() const;

		void SetQuit(bool quit);
		bool IsQuit() const;

		EngineServer *GetEngineServer();
		EngineClientConnector *GetEngineClientConnector();

		UDPServer *CreateEngineUDPServerClient();
		UDPServer *GetEngineUDPServerClient();

		UDPServer *CreateEngineUDPServerEditor();
		UDPServer *GetEngineUDPServerEditor();

		GeneralServer *CreateGeneralServer(int port,
			int numMaxConnects, int numMaxMsgHandlers);
		GeneralServer *GetGeneralServer();
		GeneralClientConnector *CreateGeneralClientConnector();
		GeneralClientConnector *GetGeneralClientConnector();

		void WillEnterForeground(bool isFirstTime);
		void DidEnterBackground();

		bool Terminate();

	private:
		std::map<std::string, RendererInput *> mRendererInputMap;
		std::map<std::string, Renderer*> mRenderersMap;
		bool mIsInEditor;
		std::string mHostName;

		DynLibManager *mDynLibMan;
		PluginManager *mPluginMan;
		TimerManager *mTimerMan;
		EventWorld *mEventWorld;
		LanguageManager *mLanguageMan;
		ScriptManager *mScriptMan;
		Bluetooth *mBluetooth;
		HardCamera *mHardCamera;
		GraphicsRoot *mRoot;
		InputManager *mInputMan;
		IMEDispatcher *mIMEDisp;
		ResourceManager *mResMan;
		FontManager *mFontMan;
		SoundSystem *mSoundSys;
		AddDeleteManager *mADMan;
		SelectionManager *mSelectionMan;
		URDoManager *mURDoMan;
		URStateManager *mURStateMan;
		FunObjectManager *mFunObjectManager;
		AccoutManager *mAccoutManager;
		UIAuiManager *mUIAuiManager;
		UISkinManager *mUISkinManager;
		LogicManager *mLogicManager;
		Creater *mCreater;
		Arduino *mArduino;
		VoiceSDK *mVoiceSDK;

		EngineServerPtr mEngineServer;
		EngineClientConnectorPtr mEngineClient;
		UDPServerPtr mEngineUDPServerClient;
		UDPServerPtr mEngineDUPServerEditor;

		GeneralServerPtr mGeneralServer;
		GeneralClientConnectorPtr mGeneralClientConnector;

		bool mIsInBackground;
		bool mBeforeInBackgroundMusicEnable;
		bool mBeforeInBackgroundSoundEnable;

		bool mIsQuit;

		// Update
	public:
		void Update();
		float GetElapsedTime();

	private:
		double mAppTime;
		double mLastAppTime;
		double mElapsedTime;

		// screen adjust
	public:
		void SetScreenSize(const Sizef &screenSize);
		const Sizef &GetScreenSize() const;
	protected:
		Sizef mScreenSize;

		// boost
	public:
		enum BoostMode
		{
			BM_APP = 1,
			BM_SERVER = 2,
			BM_MAX_MODE
		};
		void SetBoostMode(BoostMode mode);
		BoostMode GetBoostMode() const;

		bool LoadBoost(const std::string &filename);

		const Sizef &GetBoostSize() const;
		const std::string &GetBoostProjectName() const;
		AppBoostInfo::PlayLogicMode GetPlayLogicMode() const;
		std::string GetPlayLogicModeStr() const;
		bool IsShowInfo() const;

		AppBoostInfo &GetBoostServerInfo();

		void SetBoostProjectName(const std::string &boostProjectName);
		void SetBoostSize(const Sizef &size);
		void SetBoostSize(float width, float height);
		void SetPlayLogicMode(AppBoostInfo::PlayLogicMode mode);
		void SetShowInfo(bool show);

		bool WriteBoost();

	protected:
		AppBoostInfo::PlayLogicMode _StrToPlayLogicMode(const std::string &str);

		BoostMode mBoostMode;
		AppBoostInfo mBoostInfo;
		AppBoostInfo mBoostServerInfo;

		// project
	public:
		void NewProject(const std::string &pathname,
			const std::string &projName, int so, int width, int height);
		bool LoadProject(const std::string &name);
		bool LoadProjectByPath(const std::string &pathname);
		bool SaveProject();
		bool SaveProjectAs(const std::string &pathname);
		void CloseProject();
		const std::string &GetProjectFilePath() const;

		void NewScene();
		bool LoadScene(const std::string &pathname);
		bool SaveScene(const std::string &pathname);
		bool SaveSceneAs(const std::string &pathname);
		void CloseScene();

		bool LoadUI(const std::string &pathname);
		void CloseUI();

		void GenerateProjectFileList(const std::string &projName);

		Canvas *GetEngineCanvas();

	protected:
		std::string _CalSavePath(const std::string &pathname);
		bool _SaveSceneInternal(const std::string &pathname);
		std::string GetProjDataFolderPath(const std::string &projName);
		std::string GetDllFileName(const std::string &projName);
		void _ProcessReWrite(const std::string &projName);
		void _ProcessXMLNode(XMLNode node);

		std::string mProjectName;
		std::string mProjectFilePath;
		std::string mSceneFilePath;
		std::string mUIFilePath;
		std::string mBPFilePath;

		EngineCanvasPtr mEngineCanvas;

	public_internal:
		Pointer0<Project> TheProject;

		// play
	public:
		enum PlayType
		{
			PT_NONE,
			PT_SIMULATE,
			PT_PLAY,
			PT_MAX_TYPE
		};
		void Play(PlayType type);
		PlayType GetPlayType() const;

	protected:
		PlayType mPlayType;

		// project tree menus
	public:
		void Menu_Clear();
		void Menu_AddSubItemCatalogue(
			const std::string &parentAllName,
			const std::string &name,
			const std::string &title);
		void Menu_AddItem(
			const std::string &parentAllName,
			const std::string &name,
			const std::string &title,
			const std::string &script);

		class MenuItem
		{
		public:
			MenuItem();
			~MenuItem();

			void Clear();

			enum Type
			{
				T_SUB,
				T_ITEM,
				T_MAX_TYPE
			};
			Type TheType;

			std::string AllName;

			std::string Name;
			std::string Title;
			std::string Script;

			MenuItem *GetMenuItem(const std::string &parentAllName);
			std::vector<Pointer0<MenuItem> > Items;
		};

		MenuItem *GetMenuItem();

	protected:
		Pointer0<MenuItem> mItem;

		// general editmenus
	public:
		void Menu_Main_AddMainItem(const std::string &name, const std::string &title);
		void Menu_Main_AddSubItem(const std::string &parentName, const std::string &name,
			const std::string &title);
		void Menu_Main_AddItem(const std::string &parentName, const std::string &name,
			const std::string &title, const std::string &script, const std::string &scriptParam="",
			const std::string &tag = "");
		void Menu_Main_AddItemSeparater(const std::string &parentName);

		void Menu_Edit_Begin(const std::string &whe, const std::string &name);
		void Menu_Edit_AddSubItem(const std::string &whe,
			const std::string &parentName, const std::string &name,
			const std::string &title);
		void Menu_Edit_AddItem(const std::string &whe,
			const std::string &parentName, const std::string &name,
			const std::string &title,
			const std::string &script,
			const std::string &scriptParam="",
			const std::string &tag="");
		void Menu_Edit_AddItemSeparater(const std::string &whe,
			const std::string &parentName);
		void Menu_Edit_EndPopUp(const std::string &whe,
			const APoint &pos); // x z

	public:
		RenderWindow *CreateUIWindow(RenderWindow *parent, const std::string &name,
			const std::string &title, const APoint &pos, const Sizef &size, bool isFloat);

		// Event
	public:
		virtual void OnEvent(Event *ent);
		void BroadcastGeneralString(const std::string &generalStr);

		// NetInfo
	public:
		UDPNetInfo *GetUDPNetInfo(const std::string &ip);
		bool AddUDPNetInfo(const std::string &ip, const std::string &name);
		int GetNumUDPNetInfo() const;
		UDPNetInfo *GetUDPNetInfo(int i);
		void ClearUDPNetInfo();

	protected:
		void _UpdateUDPNetInfos(float elapsedTime);

		std::vector<UDPNetInfoPtr> mUDPNetInfos;
	};
#include "PX2Application.inl"

#define  PX2_APP Application::GetSingleton()

}

#endif
