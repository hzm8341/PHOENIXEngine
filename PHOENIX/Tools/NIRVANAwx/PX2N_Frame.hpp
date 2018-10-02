// PX2N_Frame.hpp

#ifndef PX2N_FRAME_HPP
#define PX2N_FRAME_HPP

#include "PX2N_Pre.hpp"
#include "PX2N_GeneralWindow.hpp"
#include "PX2N_RenderView.hpp"
#include "PX2N_Define.hpp"
#include "PX2RenderWindow.hpp"
#include "PX2wxAui.hpp"

namespace NA
{

	class InspView;
	class ProjView;
	class ResView;
	class LogView;
	class TextView;
	class ConnectView;

	class N_Frame : public wxFrame, public PX2::EventHandler
	{
	public:
		N_Frame(PX2::RenderWindow *uiWindow, wxWindow *parent, long style = wxDEFAULT_FRAME_STYLE);
		virtual ~N_Frame();

		void CreateRenderView(bool isCreateToolBar);
		RenderView *GerRenderView();
		void SetTableSelect(bool select);

		void OnTimer(wxTimerEvent& e);
		void OnSize(wxSizeEvent& e);

		static N_Frame *MainFrame;

	protected:
		void _Init();

		// operators
	public:
		void DoNewProject();
		void DoOpenProject();
		void DoSaveProject();
		void DoCloseProject();
		void DoNewScene();
		void DoOpenScene();
		void DoSaveScene();
		void DoSaveSceneAs();
		void DoCloseScene();

		void DoExit();

		void OnImport();
		void OnExport();

	protected:
		bool mIsNewProject;
		bool mIsOpenProject;
		bool mIsSaveProject;
		bool mIsCloseProject;
		bool mIsNewScene;
		bool mIsOpenScene;
		bool mIsSaveScene;
		bool mIsSaveSceneAs;
		bool mIsCloseScene;
		bool mIsExit;
		bool mIsDoImport;
		bool mIsDoExport;
		bool mIsNWindow;

		wxAuiToolBar *mRenderViewBar;
		PX2::RenderWindow *mNUIWindow;
		bool mIsTableSelect;

		// main emnu
	public:
		wxMenu *AddMainMenuItem(const std::string &title);

		wxMenu *AddSubMenuItem(wxMenu *menu, const std::string &title);
		wxMenuItem *AddMenuItem(wxMenu *menu,
			const std::string &title,
			const std::string &script,
			const std::string &param,
			const std::string &tag = "");
		void AddSeparater(wxMenu *menu);

		void EnableMenusTag(const std::string &tag, bool enable);

		std::map<int, std::string> mIDScripts;
		std::map<int, std::string> mIDScriptParams;

		void OnCommondItem(wxCommandEvent &e);
		void OnChooseItem(wxCommandEvent &e);

	protected:
		void _CreateMenu();

		wxMenuBar *mMainMenuBar;
		std::map<std::string, wxMenu*> mMenuMap;
		std::map<std::string, std::vector<wxMenuItem*> > mTagMenuItems;

		// edit menu
	public:
		wxMenu *CreateEditMenu();
		void PopUpRightMenu(int x, int y);

	protected:
		void _EnableMenus(const std::vector<std::string> &tags, bool enable);

		wxMenu *mEditMenu;
		std::map<std::string, wxMenu*> mMenuMap_Edit;
		std::map<std::string, std::vector<wxMenuItem*> > mTagMenuItems_Edit;

		PX2::APoint mPopUpRightMenuPos;
		bool mIsPopUpRightMenu;

		// tool bar
	public:
		void AddTool(wxAuiToolBar *toolBar, const std::string &icon, const std::string &script,
			const std::string &helpStr = "", int type = 0);
		void AddToolChoose(wxAuiToolBar *toolBar, const std::string &script,
			const std::string &choose0, const std::string &choose1 = "",
			const std::string &choose2 = "", const std::string &choose3 = "",
			const std::string &choose4 = "");
		void AddToolSeparater(wxAuiToolBar *toolBar);
		void AddToolStretch(wxAuiToolBar *toolBar);

		// event
	public:
		virtual void OnEvent(PX2::Event *event);

	protected:
		void OnResCopyResPath(const std::string &text);

		// renderview
	public:
		RenderView *GetMainRenderView();

	protected:
		PX2::RenderWindow *mRenderWindow;
		RenderView *mRenderView;

	protected:
		DECLARE_EVENT_TABLE()

		wxTimer mTimer;
		bool mIsInitlized;
		int mTimerID;

		bool mIsOpeningRes;
		std::string mOpeningResFilename;

		// PopUp Window
	public:
		N_Frame *CreatePopUpWindow(PX2::RenderWindow *uiWindow);

		std::map<std::string, N_Frame*> mChildFrameMap;

		// general
	public:
		int MessageBox(const std::string &caption, const std::string &content,
			int type);

		// aui
	public:
		void InitlizeAUI();
		void InitMainFrameItems();

	protected:
		PX2wxAuiNotebook *_CreateView(wxWindow *window0,
			const std::string &paneName, const std::string &panelCaption,
			wxAuiPaneInfo &paneInfo, bool isTopStyle);
		PX2wxAuiNotebook *_CreateView(std::vector<WindowObj> &objs,
			const std::string &panelName,
			const std::string &panelCaption,
			wxAuiPaneInfo &paneInfo, bool isTopStyle);

		void _CreateMainToolBar();

		void _CreateViews();
		void _CreateViewStages(bool isTopStyle);
		void _CreateViewProjRes(bool isTopStyle);
		void _CreateViewInspConsole(bool isTopStyle);
		void _CreateViewTimeLine(bool isTopStyle);
		void _CreateStatusBar();
		void _UpdateStatusBarText();

		std::string mPerspConfigName;
		wxAuiManager *mAuiManager;
		PX2wxAuiToolBar *mAuiBarMain;
		wxStaticText *mStatusBarText;
		std::map<std::string, WindowObj> mWindowObjs;
		std::map<wxWindow*, wxAuiNotebook*> mBookMap;

		N_Frame *mStageView;
		N_Frame *mLogicView;
		N_Frame *mSimuView;
		ProjView *mProjView;
		InspView *mInspView;
		TextView *mTextView;
		ResView *mResView;
		LogView *mLogView;
		ConnectView *mConnectView;
		N_Frame *mTimeLineView;

		// timeline
	public:
		void TimeLine_SelectCtrl_InValue();
		void TimeLine_SelectCtrl_OutValue();
	};

}

#endif