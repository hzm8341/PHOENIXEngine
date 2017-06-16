// PX2N_Frame_Aui.cpp

#include "PX2N_Frame.hpp"
#include "PX2N_RenderView.hpp"
#include "PX2N_ResView.hpp"
#include "PX2N_ProjView.hpp"
#include "PX2N_InspView.hpp"
#include "PX2N_LogView.hpp"
#include "PX2N_TextView.hpp"
#include "PX2N_CntView.hpp"
#include "PX2wxDockArt.hpp"
#include "PX2StringHelp.hpp"
#include "PX2SelectionManager.hpp"
#include "PX2Edit.hpp"
#include "PX2RenderWindow.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2EU_TimeLineFrame.hpp"
#include "PX2EU_StageFrame.hpp"
#include "PX2EU_SimuFrame.hpp"
#include "PX2EU_Manager.hpp"
using namespace PX2;
using namespace NA;

//-----------------------------------------------------------------------------
PX2wxAuiNotebook *N_Frame::_CreateView(wxWindow *window0,
	const std::string &paneName, const std::string &panelCaption,
	wxAuiPaneInfo &paneInfo, bool isTopStyle)
{
	WindowObj obj;
	obj.TheWindow = window0;
	obj.Name = paneName;
	obj.Caption = panelCaption;

	std::vector<WindowObj> winObjs;
	winObjs.push_back(obj);

	return _CreateView(winObjs, paneName, panelCaption, paneInfo, isTopStyle);
}
//-----------------------------------------------------------------------------
PX2wxAuiNotebook *N_Frame::_CreateView(std::vector<WindowObj> &objs,
	const std::string &panelName,
	const std::string &panelCaption,
	wxAuiPaneInfo &paneInfo, bool isTopStyle)
{
	PX2wxAuiNotebook* noteBook = new PX2wxAuiNotebook(this, isTopStyle);
	PX2wxAuiTabArt *tabArt = new PX2wxAuiTabArt(isTopStyle);
	noteBook->SetArtProvider(tabArt);
	long styleFlag = 0;
	if (isTopStyle)
	{
		styleFlag ^= wxAUI_NB_WINDOWLIST_BUTTON;
	}
	else
	{
		styleFlag ^= wxAUI_NB_BOTTOM;
	}

	styleFlag ^= wxAUI_NB_WINDOWLIST_BUTTON;
	styleFlag ^= wxAUI_NB_TAB_MOVE;
	styleFlag ^= wxAUI_NB_TAB_EXTERNAL_MOVE;
	styleFlag ^= wxAUI_NB_TAB_FIXED_WIDTH;
	styleFlag ^= wxAUI_NB_TAB_SPLIT;
	styleFlag ^= wxAUI_NB_SCROLL_BUTTONS;
	styleFlag ^= wxAUI_NB_CLOSE_BUTTON;

	noteBook->SetWindowStyleFlag(styleFlag);
	noteBook->SetTabCtrlHeight(24);

	noteBook->Freeze();

	wxBitmap bitMap = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));
	for (int i = 0; i < (int)objs.size(); i++)
	{
		WindowObj &obj = objs[i];

		noteBook->AddPage(obj.TheWindow, obj.Caption, false, bitMap);

		WindowObj winObj;
		winObj.Name = obj.Name;
		winObj.TheWindow = obj.TheWindow;
		winObj.NoteBook = noteBook;
		mWindowObjs[obj.Name] = winObj;

		obj.TheWindow->SetName(obj.Name);

		mBookMap[obj.TheWindow] = noteBook;
	}

	noteBook->UpdateTabsHeight();
	noteBook->Thaw();

	paneInfo.CloseButton(true).MaximizeButton(true).MinimizeButton(true)
		.PinButton(true).MinSize(200., 100).Name(panelName).
		Caption(panelCaption).CaptionVisible(!isTopStyle).Floatable(!isTopStyle);
	mAuiManager->AddPane(noteBook, paneInfo);

	noteBook->Refresh();

	return noteBook;
}
//-----------------------------------------------------------------------------
void N_Frame::InitlizeAUI()
{
	mAuiManager = new wxAuiManager(this, wxAUI_MGR_DEFAULT
		| wxAUI_MGR_TRANSPARENT_DRAG | wxAUI_MGR_ALLOW_ACTIVE_PANE);

	mAuiManager->SetArtProvider(new PX2wxDockArt());
	mAuiManager->GetArtProvider()->SetMetric(wxAUI_DOCKART_CAPTION_SIZE, 24);
	mAuiManager->GetArtProvider()->SetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE, 0);
	mAuiManager->GetArtProvider()->SetMetric(wxAUI_DOCKART_SASH_SIZE, 4);
	mAuiManager->GetArtProvider()->SetColor(wxAUI_DOCKART_BORDER_COLOUR, wxColour(10, 10, 10));
	mAuiManager->GetArtProvider()->SetColor(wxAUI_DOCKART_BACKGROUND_COLOUR, wxColour(10, 10, 10));

	_CreateMainToolBar();
	_CreateViews();

	wxFileInputStream is(mPerspConfigName);
	if (is.IsOk())
	{
		wxFileConfig config(is);
		wxString strPerspective;
		if (config.Read(wxString("Perspective"), &strPerspective))
		{
			mAuiManager->LoadPerspective(strPerspective);
		}
	}

	mAuiManager->Update();
}
//-----------------------------------------------------------------------------
void N_Frame::InitMainFrameItems()
{
	std::vector<std::string> menuItems;
	menuItems.push_back("Proj_NewProject");
	menuItems.push_back("Proj_Save");
	menuItems.push_back("Proj_Close");
	menuItems.push_back("Proj_Scene_NewScene");
	menuItems.push_back("Proj_Scene_Open");
	menuItems.push_back("Proj_Scene_Save");
	menuItems.push_back("Proj_Scene_SaveAs");
	menuItems.push_back("Proj_Scene_Close");

	EnableMenusTag("Edit", false);

	_EnableMenus(menuItems, false);
}
//-----------------------------------------------------------------------------
void N_Frame::_CreateMainToolBar()
{
	mAuiBarMain = new PX2wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_HORIZONTAL);
	if (mAuiBarMain)
	{
		mAuiBarMain->SetArtProvider(new PX2wxAuiToolBarArt(2));

		mAuiBarMain->Realize();

		mAuiManager->AddPane(mAuiBarMain, wxAuiPaneInfo().
			Name(wxT("maintoolbar")).
			ToolbarPane().Gripper(true).Top().Dockable(false).PaneBorder(true).
			MinSize(200, 24).MaxSize(200, 24).Top().Resizable(false).CaptionVisible(false).
			BottomDockable(false).LeftDockable(false).RightDockable(false).Floatable(false));
	}
}
//-----------------------------------------------------------------------------
void N_Frame::_CreateViews()
{
	_CreateViewStages(true);
	_CreateViewProjRes(false);
	_CreateViewInspConsole(false);
	_CreateViewTimeLine(false);
	_CreateStatusBar();
}
//-----------------------------------------------------------------------------
void N_Frame::_CreateViewStages(bool isTopStyle)
{
	std::vector<WindowObj> windowObjs;

	RenderWindow *renderWindowMain = PX2_GR.GetMainWindow();
	mStageView = new N_Frame(renderWindowMain, this, 0);
	mStageView->SetName("STAGE");
	mStageView->CreateRenderView(false);
	renderWindowMain->SetWindowHandle(mStageView->GerRenderView()->GetHandle());

	EU_StageFrame *stageFrame = new0 EU_StageFrame();
	stageFrame->LocalTransform.SetTranslateY(-1.0f);
	stageFrame->SetAnchorHor(0.0f, 1.0f);
	stageFrame->SetAnchorVer(0.0f, 1.0f);
	renderWindowMain->GetMainCanvas()->AttachChild(stageFrame);
	renderWindowMain->GetMainCanvas()->SetClearColor(Float4::MakeColor(68, 180, 221, 255));

	WindowObj obj0;
	obj0.Name = "STAGE";
	obj0.Caption = PX2_LM_EDITOR.GetValue("n_Stage");
	obj0.TheWindow = mStageView;
	windowObjs.push_back(obj0);

	RenderWindow *rwLogic = new0 RenderWindow();
	rwLogic->SetName("LOGIC");
	PX2_GR.AddRenderWindow("LOGIC", rwLogic);
	rwLogic->SetScreenSize(Sizef(1024.0f, 768.0f));
	Canvas *canvasLogic = new0 Canvas();
	rwLogic->SetMainCanvas(canvasLogic);
	canvasLogic->CreateUICameraNode();
	PX2EU_MAN.SetLogicCanvas(canvasLogic);
	mLogicView = new N_Frame(rwLogic, this, 0);
	mLogicView->CreateRenderView(false);
	WindowObj obj1;
	obj1.Name = "LOGIC";
	obj1.Caption = PX2_LM_EDITOR.GetValue("n_Logic");
	obj1.TheWindow = mLogicView;
	windowObjs.push_back(obj1);

	RenderWindow *rwSimu = new0 RenderWindow();
	rwSimu->SetName("SIMU");
	PX2_GR.AddRenderWindow("SIMU", rwSimu);
	rwSimu->SetScreenSize(Sizef(1024.0f, 768.0f));

	Canvas *canvasSimu = new0 Canvas();
	rwSimu->SetMainCanvas(canvasSimu);
	canvasSimu->CreateUICameraNode();
	EU_SimuFrame *simuFrame = new0 EU_SimuFrame();
	canvasSimu->AttachChild(simuFrame);
	simuFrame->SetAnchorHor(0.0f, 1.0f);
	simuFrame->SetAnchorVer(0.0f, 1.0f);

	mSimuView = new N_Frame(rwSimu, this, 0);
	mSimuView->CreateRenderView(false);
	WindowObj obj2;
	obj2.Name = "SIMU";
	obj2.Caption = PX2_LM_EDITOR.GetValue("n_Play");
	obj2.TheWindow = mSimuView;
	windowObjs.push_back(obj2);

	_CreateView(windowObjs, "STAGESIMUE", "STAGESIMUE",
		wxAuiPaneInfo().DefaultPane().Centre(), isTopStyle);
}
//-----------------------------------------------------------------------------
void N_Frame::_CreateViewProjRes(bool isTopStyle)
{
	std::vector<WindowObj> windowObjs;

	mResView = new ResView(this);
	WindowObj obj1;
	obj1.Name = "RES";
	obj1.Caption = PX2_LM_EDITOR.GetValue("n_Res");
	obj1.TheWindow = mResView;
	windowObjs.push_back(obj1);

	mProjView = new ProjView(this);
	WindowObj obj0;
	obj0.Name = "PROJECT";
	obj0.Caption = PX2_LM_EDITOR.GetValue("n_Project");
	obj0.TheWindow = mProjView;
	windowObjs.push_back(obj0);

	_CreateView(windowObjs, "PROJRES", "PROJRES",
		wxAuiPaneInfo().DefaultPane().Left(), isTopStyle);
}
//-----------------------------------------------------------------------------
void N_Frame::_CreateViewInspConsole(bool isTopStyle)
{
	std::vector<WindowObj> windowObjs;

	mInspView = new InspView(this);
	WindowObj objInsp;
	objInsp.Name = "INSPECTOR";
	objInsp.Caption = PX2_LM_EDITOR.GetValue("n_Inspector");
	objInsp.TheWindow = mInspView;
	windowObjs.push_back(objInsp);

	mLogView = new LogView(this);
	WindowObj objLog;
	objLog.Name = "LOG";
	objLog.Caption = PX2_LM_EDITOR.GetValue("n_Console");
	objLog.TheWindow = mLogView;
	windowObjs.push_back(objLog);

	mTextView = new TextView(this);
	WindowObj obj2;
	obj2.Name = "TEXT";
	obj2.Caption = PX2_LM_EDITOR.GetValue("n_Text");
	obj2.TheWindow = mTextView;
	windowObjs.push_back(obj2);

	mConnectView = new ConnectView(this);
	WindowObj obj3;
	obj3.Name = "CONNECT";
	obj3.Caption = PX2_LM_EDITOR.GetValue("n_Connect");
	obj3.TheWindow = mConnectView;
	windowObjs.push_back(obj3);

	_CreateView(windowObjs, "INSPECTORLOG", "INSPECTORLOG",
		wxAuiPaneInfo().DefaultPane().Right(), isTopStyle);
}
//-----------------------------------------------------------------------------
void N_Frame::_CreateViewTimeLine(bool isTopStyle)
{
	RenderWindow *rw = new0 RenderWindow();
	PX2_GR.AddRenderWindow("TimeLine", rw);
	rw->SetName("TimeLine");
	
	Canvas *canva = new0 Canvas();
	rw->SetMainCanvas(canva);
	canva->CreateUICameraNode();

	EU_TimeLineFrame *timeLineFrame = new0 EU_TimeLineFrame();
	canva->AttachChild(timeLineFrame);
	timeLineFrame->SetAnchorHor(0.0f, 1.0f);
	timeLineFrame->SetAnchorVer(0.0f, 1.0f);

	mTimeLineView = new N_Frame(rw, this, 0);
	mTimeLineView->CreateRenderView(false);

	_CreateView(mTimeLineView, "TIMELINE", PX2_LM_EDITOR.GetValue("n_TimeLine"),
		wxAuiPaneInfo().DefaultPane().Right(), isTopStyle);
}
//-----------------------------------------------------------------------------
void N_Frame::_CreateStatusBar()
{
	wxStatusBar *status = CreateStatusBar();
	status->SetBackgroundColour(wxColour(102, 33, 122));
	status->SetForegroundColour(wxColour(wxT("WHITE")));
	mStatusBarText = new wxStaticText(status, wxID_ANY,
		PX2_LM_EDITOR.GetValue("n_Welcome"), wxPoint(20, 5), wxSize(1024, 24), 0);
	mStatusBarText->Show(true);

	_UpdateStatusBarText();
}
//----------------------------------------------------------------------------
void N_Frame::_UpdateStatusBarText()
{
	std::string str;
	
	str += PX2_LM_EDITOR.GetValue("n_Welcome") + " ";

	int numObj = PX2_SELECTM_E->GetNumObjects();
	if (0 == numObj)
	{
		str += "		CurSelObjNull";
	}
	else
	{
		Object *firObj = PX2_SELECTM_E->GetFirstObject();

		str += "		CurSelObj";
		str += " Num:" + StringHelp::IntToString(numObj);
		str += " " + std::string("Name") + ": " + firObj->GetName();
	}

	const SelectResData &resData = PX2_EDIT.GetSelectedResource();
	str  += "	CurSelRes" + resData.ResPathname;

	const APoint &pickPos = PX2_EDIT.GetPickPos();
	str += std::string("		PickingPos") + "(" +
		StringHelp::FloatToString(pickPos[0]) + ", " +
		StringHelp::FloatToString(pickPos[1]) + ", " +
		StringHelp::FloatToString(pickPos[2]) + ")";

	mStatusBarText->SetLabelText(str);
}
//-----------------------------------------------------------------------------