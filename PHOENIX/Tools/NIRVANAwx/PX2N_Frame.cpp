// PX2N_Frame.cpp

#include "PX2N_Frame.hpp"
#include "PX2N_DlgCreateProject.hpp"
#include "PX2Edit.hpp"
#include "PX2Application.hpp"
#include "PX2InputManager.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditEventData.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2GraphicsEventType.hpp"
#include "PX2EditorEventType.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditorEventData.hpp"
using namespace NA;
using namespace PX2;

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#include "shellapi.h "
#endif

BEGIN_EVENT_TABLE(N_Frame, wxFrame)
EVT_SIZE(N_Frame::OnSize)
END_EVENT_TABLE();

//----------------------------------------------------------------------------
N_Frame *N_Frame::MainFrame = 0;
//----------------------------------------------------------------------------
N_Frame::N_Frame(PX2::RenderWindow *uiWindow, wxWindow *parent, long style) :
wxFrame(parent, wxID_ANY, "N_Frame", wxDefaultPosition, wxDefaultSize, 
style),
mRenderWindow(uiWindow)
{
	_Init();

	PX2_EW.ComeIn(this);

	if (uiWindow)
	{
		std::string name = uiWindow->GetName();
		std::string title = uiWindow->GetTitle();
		int width = (int)uiWindow->GetScreenSize().Width;
		int height = (int)uiWindow->GetScreenSize().Height;

		SetName(name);
		SetTitle(uiWindow->GetTitle());
		SetSize(width, height);
	}
	else
	{
		MainFrame = this;
	}

	mTimerID = PX2_EDIT_GETID;
	Connect(mTimerID, wxEVT_TIMER, wxTimerEventHandler(N_Frame::OnTimer));
	mTimer.SetOwner(this, mTimerID);
	mTimer.Start(25);

	SetFocus();
	// wx
	mPerspConfigName = "NIRVANAwx.layout.1.0.xml";
}
//----------------------------------------------------------------------------
void N_Frame::_Init()
{
	SetName("N_Frame");
	mIsInitlized = false;
	mRenderView = 0;
	mMainMenuBar = 0;
	mIsExit = false;
	mIsNewProject = false;
	mIsOpenProject = false;
	mIsSaveProject = false;
	mIsCloseProject = false;
	mIsNewScene = false;
	mIsOpenScene = false;
	mIsSaveScene = false;
	mIsSaveSceneAs = false;
	mIsCloseScene = false;
	mIsPopUpRightMenu = false;
	mIsDoImport = false;
	mIsDoExport = false;
	mEditMenu = 0;
	mIsNWindow = false;

	mRenderViewBar = 0;
	mNUIWindow = 0;
	mIsTableSelect = false;

	mIsOpeningRes = false;

	mAuiManager = 0;
}
//----------------------------------------------------------------------------
void N_Frame::CreateRenderView(bool isCreateToolBar)
{
	mRenderView = new RenderView(mRenderWindow, this);
	if (mRenderWindow)
	{
		std::string name = mRenderWindow->GetName();
		std::string title = mRenderWindow->GetTitle();
		int width = (int)mRenderWindow->GetScreenSize().Width;
		int height = (int)mRenderWindow->GetScreenSize().Height;

		mRenderView->SetName(name);
		Renderer *renderer = PX2_APP.CreateRenderer(name,
			mRenderView->GetHandle(), 0, 0, width, height, 0);
		mRenderWindow->SetRenderer(renderer);
		mRenderWindow->SetScreenSize(Sizef((float)width, (float)height));
		if ("Main" == name)
			Renderer::SetDefaultRenderer(renderer);
	}

	if (isCreateToolBar)
	{
		PX2wxAuiToolBar *renderViewToolBar = new PX2wxAuiToolBar(this, wxID_ANY,
			wxDefaultPosition, wxDefaultSize,
			wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_HORIZONTAL);
		renderViewToolBar->SetArtProvider(new PX2wxAuiToolBarArt(1));
		renderViewToolBar->SetSize(wxSize(-1, 24));

		renderViewToolBar->Realize();
		mRenderViewBar = renderViewToolBar;

		wxBoxSizer* bSizer54;
		bSizer54 = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer* bSizer55;
		bSizer55 = new wxBoxSizer(wxVERTICAL);
		bSizer55->Add(mRenderViewBar, 0, wxEXPAND, 0);
		bSizer54->Add(bSizer55, 0, wxEXPAND, 0);
		wxBoxSizer* bSizer57;
		bSizer57 = new wxBoxSizer(wxVERTICAL);

		bSizer57->Add(mRenderView, 1, wxEXPAND | wxTOP, 0);

		bSizer54->Add(bSizer57, 1, wxEXPAND, 0);

		SetSizer(bSizer54);
		Layout();
	}
	else
	{
		wxBoxSizer* bSizer69;
		bSizer69 = new wxBoxSizer(wxVERTICAL);
		bSizer69->Add(mRenderView, 1, wxEXPAND, 5);
		this->SetSizer(bSizer69);
		this->Layout();
	}
}
//----------------------------------------------------------------------------
RenderView *N_Frame::GerRenderView()
{
	return mRenderView;
}
//----------------------------------------------------------------------------
N_Frame::~N_Frame()
{
	EventWorld *ew = EventWorld::GetSingletonPtr();
	if (ew)
		PX2_EW.GoOut(this);

	if (mEditMenu)
	{
		delete mEditMenu;
		mEditMenu = 0;
	}

	if (mAuiManager)
	{
		wxString strPerspective = mAuiManager->SavePerspective();
		wxFileOutputStream os(mPerspConfigName);
		wxFileConfig config;
		config.Write("Perspective", strPerspective);
		config.Save(os);
		os.Close();

		mAuiManager->UnInit();
		delete mAuiManager;
	}
}
//----------------------------------------------------------------------------
void N_Frame::SetTableSelect(bool select)
{
	mIsTableSelect = select;

	if (mRenderView)
	{
		mRenderView->Show(mIsTableSelect);
	}
}
//----------------------------------------------------------------------------
void N_Frame::OnEvent(Event *event)
{
	std::string name = GetName();
	if ("Main" == name)
	{
		if (EditES::IsEqual(event, EditES::N_Window))
		{
			mIsNWindow = true;
			mNUIWindow = event->GetData<RenderWindow*>();
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_NewProject))
		{
			mIsNewProject = true;
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_OpenProject))
		{
			mIsOpenProject = true;
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_SaveProject))
		{
			mIsSaveProject = true;
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_CloseProject))
		{
			mIsCloseProject = true;
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_NewScene))
		{
			mIsNewScene = true;
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_OpenScene))
		{
			mIsOpenScene = true;
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_SaveScene))
		{
			mIsSaveScene = true;
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_SaveSceneAs))
		{
			mIsSaveSceneAs = true;
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_CloseScene))
		{
			mIsCloseScene = true;
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_Exit))
		{
			mIsExit = true;
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_PlayTip))
		{
			EED_Tip tipData = event->GetData<EED_Tip>();			
			MessageBox(tipData.Title, tipData.Content, 0);
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::OpenRes))
		{
			std::string pathFilename = event->GetData<std::string>();

			mIsOpeningRes = true;
			mOpeningResFilename = pathFilename;
		}
		else if (ProjectES::IsEqual(event, ProjectES::NewProject))
		{
			EnableMenusTag("Edit", true);

			EnableMenusTag("Proj_Save", true);
			EnableMenusTag("Proj_Close", true);

			EnableMenusTag("Proj_Scene_NewScene", true);
			EnableMenusTag("Proj_Scene_Open", true);
			EnableMenusTag("Proj_Scene_Save", false);
			EnableMenusTag("Proj_Scene_SaveAs", false);
			EnableMenusTag("Proj_Scene_Close", false);
		}
		else if (ProjectES::IsEqual(event, ProjectES::LoadedProject))
		{
			EnableMenusTag("Edit", true);

			EnableMenusTag("Proj_Save", true);
			EnableMenusTag("Proj_Close", true);

			EnableMenusTag("Proj_Scene_NewScene", true);
			EnableMenusTag("Proj_Scene_Open", true);
			EnableMenusTag("Proj_Scene_Save", false);
			EnableMenusTag("Proj_Scene_SaveAs", false);
			EnableMenusTag("Proj_Scene_Close", false);
		}
		else if (ProjectES::IsEqual(event, ProjectES::CloseProject))
		{
			EnableMenusTag("Edit", false);

			EnableMenusTag("Proj_Save", false);
			EnableMenusTag("Proj_Close", true);

			EnableMenusTag("Proj_Scene_NewScene", false);
			EnableMenusTag("Proj_Scene_Open", false);
			EnableMenusTag("Proj_Scene_Save", false);
			EnableMenusTag("Proj_Scene_SaveAs", false);
			EnableMenusTag("Proj_Scene_Close", false);
		}
		else if (ProjectES::IsEqual(event, ProjectES::NewScene))
		{
			EnableMenusTag("Proj_Scene_NewScene", true);
			EnableMenusTag("Proj_Scene_Open", true);
			EnableMenusTag("Proj_Scene_Save", true);
			EnableMenusTag("Proj_Scene_SaveAs", true);
			EnableMenusTag("Proj_Scene_Close", true);
		}
		else if (ProjectES::IsEqual(event, ProjectES::CloseScene))
		{
			EnableMenusTag("Proj_Scene_NewScene", true);
			EnableMenusTag("Proj_Scene_Open", true);
			EnableMenusTag("Proj_Scene_Save", false);
			EnableMenusTag("Proj_Scene_SaveAs", false);
			EnableMenusTag("Proj_Scene_Close", false);
		}
		else if (ProjectES::IsEqual(event, ProjectES::Play))
		{
			std::vector<std::string> menuItems;
			menuItems.push_back("Proj_NewProject");
			menuItems.push_back("Proj_Open");
			menuItems.push_back("Proj_Save");
			menuItems.push_back("Proj_Close");
			menuItems.push_back("Proj_Scene_NewScene");
			menuItems.push_back("Proj_Scene_Open");
			menuItems.push_back("Proj_Scene_Save");
			menuItems.push_back("Proj_Scene_SaveAs");
			menuItems.push_back("Proj_Scene_Close");
			_EnableMenus(menuItems, false);
		}
		else if (ProjectES::IsEqual(event, ProjectES::Stop))
		{
			std::vector<std::string> menuItems;
			menuItems.push_back("Proj_NewProject");
			menuItems.push_back("Proj_Open");
			menuItems.push_back("Proj_Save");
			menuItems.push_back("Proj_Close");
			menuItems.push_back("Proj_Scene_NewScene");
			menuItems.push_back("Proj_Scene_Open");
			menuItems.push_back("Proj_Scene_Save");
			menuItems.push_back("Proj_Scene_SaveAs");
			menuItems.push_back("Proj_Scene_Close");

			_EnableMenus(menuItems, true);
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_Import))
		{
			mIsDoImport = true;
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_Export))
		{
			mIsDoExport = true;
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::SetCopyText))
		{
			const std::string &cpText = PX2_EDIT.GetCopyText();
			OnResCopyResPath(cpText);
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::TimeLine_SetInValue))
		{
			TimeLine_SelectCtrl_InValue();
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::TimeLine_SetOutValue))
		{
			TimeLine_SelectCtrl_OutValue();
		}
	}
	if (GraphicsES::IsEqual(event, GraphicsES::WindowMaxSize))
	{
		RenderWindow *rw = event->GetData<RenderWindow*>();
		if (rw == mRenderWindow)
		{
			Maximize(mRenderWindow->IsMaxSize());
		}
	}
	else if (GraphicsES::IsEqual(event, GraphicsES::WindowShow))
	{
		RenderWindow *rw = event->GetData<RenderWindow*>();
		if (rw == mRenderWindow)
		{
			Show(true);
		}
	}
	else if (GraphicsES::IsEqual(event, GraphicsES::WindowHide))
	{
		RenderWindow *rw = event->GetData<RenderWindow*>();
		if (rw == mRenderWindow)
		{
			Show(false);
		}
	}
	else if (GraphicsES::IsEqual(event, GraphicsES::WindowSetPosition))
	{
		RenderWindow *rw = event->GetData<RenderWindow*>();
		if (rw == mRenderWindow && !rw->IsMain())
		{
			RenderWindow *parentRW = rw->GetParentRenderWindow();
			const Sizef &wsize = parentRW->GetScreenSize();

			const APoint &pos = rw->GetPosition();
			wxPoint pt;
			pt.x = pos.X();
			pt.y = wsize.Height - pos.Z();
			SetPosition(pt);
		}
	}
	else if (GraphicsES::IsEqual(event, GraphicsES::WindowSetCursorType))
	{
		RenderWindow::CursorType ct = RenderWindow::GetCursorType();
		
		wxStockCursor wxCursorType = (wxStockCursor)ct;
		SetCursor(wxCursor(wxCursorType));
	}
	else if (EditES::IsEqual(event, EditES::N_AddMenu))
	{
		EED_AddMenu data = event->GetData<EED_AddMenu>();
		if (data.Where == name)
		{
			if (EED_AddMenu::IT_MAIN_MENU == data.TheItemType)
			{
				if (0 == mMainMenuBar)
				{
					_CreateMenu();
				}

				wxMenu *menu = AddMainMenuItem(data.Title);
				mMenuMap[data.Name] = menu;
			}
			else if (EED_AddMenu::IT_MAIN_SUBMENU == data.TheItemType ||
				EED_AddMenu::IT_MAIN_ITEM == data.TheItemType ||
				EED_AddMenu::IT_MAIN_ITEMSPARATER == data.TheItemType)
			{
				std::map<std::string, wxMenu*>::iterator it =
					mMenuMap.find(data.ParentName);
				if (it != mMenuMap.end())
				{
					wxMenu *menu = it->second;

					if (EED_AddMenu::IT_MAIN_SUBMENU == data.TheItemType)
					{
						wxMenu *subMenu = AddSubMenuItem(menu, data.Title);
						mMenuMap[data.ParentName + data.Name] = subMenu;
					}
					else if (EED_AddMenu::IT_MAIN_ITEM == data.TheItemType)
					{
						AddMenuItem(menu, data.Title, data.Script, data.ScriptParam, data.Tag);
					}
					else if (EED_AddMenu::IT_MAIN_ITEMSPARATER == data.TheItemType)
					{
						AddSeparater(menu);
					}
				}
			}
			else if (EED_AddMenu::IT_EDIT_MENU == data.TheItemType ||
				EED_AddMenu::IT_EDIT_SUBMENU == data.TheItemType ||
				EED_AddMenu::IT_EDIT_ITEM == data.TheItemType ||
				EED_AddMenu::IT_EDIT_ITEMSPARATER == data.TheItemType ||
				EED_AddMenu::IT_EDIT_POPUP == data.TheItemType)
			{
				if (EED_AddMenu::IT_EDIT_MENU == data.TheItemType)
				{
					wxMenu *menu = CreateEditMenu();
					mMenuMap_Edit[data.Name] = menu;
				}
				else
				{
					std::map<std::string, wxMenu*>::iterator it =
						mMenuMap_Edit.find(data.ParentName);
					if (it != mMenuMap_Edit.end())
					{
						wxMenu *menu = it->second;

						if (EED_AddMenu::IT_EDIT_SUBMENU == data.TheItemType)
						{
							if (menu)
							{
								wxMenu *subMenu = AddSubMenuItem(menu, data.Title);
								mMenuMap_Edit[data.ParentName + data.Name] = subMenu;
							}
						}
						else if (EED_AddMenu::IT_EDIT_ITEM == data.TheItemType)
						{
							if (menu)
							{
								AddMenuItem(menu, data.Title, data.Script, data.ScriptParam, data.Tag);
							}
						}
						else if (EED_AddMenu::IT_EDIT_ITEMSPARATER == data.TheItemType)
						{
							if (menu)
							{
								AddSeparater(menu);
							}
						}
					}

					if (EED_AddMenu::IT_EDIT_POPUP == data.TheItemType)
					{
						mPopUpRightMenuPos = data.PopUpPos;
						mIsPopUpRightMenu = true;
					}
				}
			}
		}
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_AddTool))
	{
		AddToolBarData data = event->GetData<AddToolBarData>();
		std::string name = GetName();
		wxAuiToolBar *toolBar = mRenderViewBar;
		if ("Main" == name)
			toolBar = mAuiBarMain;

		if (toolBar && data.Where == name)
		{
			if (AddToolBarData::T_TOOL == data.TheType)
			{
				AddTool(toolBar, data.Icon, data.Script, data.HelpStr, data.DataType);
			}
			else if (AddToolBarData::T_CHOOSE == data.TheType)
			{
				std::string chooseStr0;
				std::string chooseStr1;
				std::string chooseStr2;
				std::string chooseStr3;
				std::string chooseStr4;
				if (data.Chooses.size() > 0)
					chooseStr0 = data.Chooses[0];
				if (data.Chooses.size() > 0)
					chooseStr1 = data.Chooses[1];
				if (data.Chooses.size() > 0)
					chooseStr2 = data.Chooses[2];
				if (data.Chooses.size() > 0)
					chooseStr3 = data.Chooses[3];
				if (data.Chooses.size() > 0)
					chooseStr4 = data.Chooses[4];

				AddToolChoose(toolBar, chooseStr0, chooseStr1,
					chooseStr2, chooseStr3, chooseStr4);
			}
			else if (AddToolBarData::T_SPEARATER == data.TheType)
			{
				AddToolSeparater(toolBar);
			}
			else if (AddToolBarData::T_STRETCH == data.TheType)
			{
				AddToolStretch(toolBar);
			}
		}
	}
}
//----------------------------------------------------------------------------
void N_Frame::OnResCopyResPath(const std::string &text)
{
	wxTextDataObject *data = new wxTextDataObject(text);
	wxTheClipboard->SetData(data);
	wxTheClipboard->Close();
}
//----------------------------------------------------------------------------
void _CreateScriptFile(const std::string &pathName, const std::string &subDir,
	const std::string &scFileName, const std::string &defFunName)
{
	std::string scriptPath = "Data/" + pathName + subDir + scFileName;
	std::ofstream outputFile;
	outputFile.open(scriptPath.c_str());

	std::string outBaseName;
	std::string outExt;
	StringHelp::SplitBaseFilename(scFileName, outBaseName, outExt);
	
	std::string noteStr = "-- ";
	if ("lua" == outExt)
		noteStr = "-- ";
	else if ("as" == outExt)
		noteStr = "// ";

	std::string scriptStart;
	scriptStart += noteStr + scFileName;
	outputFile << scriptStart << std::endl << std::endl;
	
	std::string scriptContent;
	if ("lua" == outExt)
	{
		scriptContent += "function pre" + defFunName + "() \n";
		scriptContent += "end\n";

		scriptContent += "function " + defFunName + "() \n";
		scriptContent += "end";
	}
	outputFile << scriptContent;

	outputFile.close();
}
//----------------------------------------------------------------------------
void N_Frame::DoNewProject()
{
	mIsNewProject = false;

	DlgCreateProject dlg(this);
	int showModal = dlg.ShowModal();
	if (wxID_OK == showModal)
	{
		std::string name = dlg.mProjName;
		int screenOriention = dlg.mScreenOrientation;
		int width = dlg.mProjWidth;
		int height = dlg.mProjHeight;

		std::string pathName = name + "/";

		bool isProjectFolderExist = PX2_RM.IsFileFloderExist("Data/" + pathName);
		if (isProjectFolderExist)
		{
			MessageBox(PX2_LM_EDITOR.V("n_Notice"), PX2_LM_EDITOR.V("n_TipCreateProject"), 0);
			return;
		}
		else
		{
			PX2_APP.CloseProject();

			PX2_RM.CreateFloder("Data/", pathName);
			PX2_RM.CreateFloder("Data/", pathName + "images/");
			PX2_RM.CreateFloder("Data/", pathName + "models/");
			PX2_RM.CreateFloder("Data/", pathName + "scenes/");
			PX2_RM.CreateFloder("Data/", pathName + "scripts/");
			PX2_RM.CreateFloder("Data/", pathName + "scripts/lua/");
			PX2_RM.CreateFloder("Data/", pathName + "scripts/lua/editor/");
			PX2_RM.CreateFloder("Data/", pathName + "scripts_server/");
			PX2_RM.CreateFloder("Data/", pathName + "scripts_server/lua/");
			PX2_RM.CreateFloder("Data/", pathName + "scripts_server/lua/editor/");

			_CreateScriptFile(pathName, "scripts/lua/", "play.lua", "play");
			_CreateScriptFile(pathName, "scripts/lua/", "stop.lua", "stop");
			_CreateScriptFile(pathName, "scripts/lua/editor/", "editor.lua", "editorplay");

			_CreateScriptFile(pathName, "scripts_server/lua/", "play.lua", "play");
			_CreateScriptFile(pathName, "scripts_server/lua/", "stop.lua", "stop");
			_CreateScriptFile(pathName, "scripts_server/lua/editor/", "editor.lua", "editorstop");

			std::string path = "Data/" + pathName + name + ".px2proj";
			PX2_APP.NewProject(path, name, screenOriention, width,
				height);
		}
	}
}
//----------------------------------------------------------------------------
void N_Frame::DoOpenProject()
{
	mIsOpenProject = false;

	wxFileDialog dlg(this,
		PX2_LM_EDITOR.GetValue("n_OpenProject"),
		wxEmptyString,
		wxEmptyString,
		wxT("Project (*.px2proj)|*.px2proj"));

	dlg.CenterOnParent();

	if (dlg.ShowModal() == wxID_OK)
	{
		std::string path = dlg.GetPath();
		path = StringHelp::StandardiseFilename(path);
		PX2_APP.LoadProjectByPath(path);
	}
	else
	{
		dlg.Close();
	}
}
//----------------------------------------------------------------------------
void N_Frame::DoSaveProject()
{
	mIsSaveProject = false;

	Project *proj = Project::GetSingletonPtr();
	if (proj)
	{
		if (proj->GetScene())
		{
			DoSaveScene();
		}
	}

	PX2_APP.SaveProject();
}
//----------------------------------------------------------------------------
void N_Frame::DoCloseProject()
{
	mIsCloseProject = false;

	PX2_APP.CloseProject();
}
//----------------------------------------------------------------------------
void N_Frame::DoNewScene()
{
	mIsNewScene = false;
	PX2_APP.NewScene();
}
//----------------------------------------------------------------------------
void N_Frame::DoOpenScene()
{
	mIsOpenScene = false;

	wxFileDialog dlg(this,
		PX2_LM_EDITOR.GetValue("n_OpenScene"),
		wxEmptyString,
		wxEmptyString,
		wxT("scene (*.px2obj)|*.px2obj"));

	dlg.CenterOnParent();

	if (wxID_OK == dlg.ShowModal())
	{
		std::string strPath = dlg.GetPath();
		PX2_APP.LoadScene(strPath);
	}
}
//----------------------------------------------------------------------------
void N_Frame::DoSaveScene()
{
	mIsSaveScene = false;

	std::string path;
	if (Project::GetSingletonPtr())
		path = Project::GetSingleton().GetSceneFilename();

	if (!path.empty())
	{
		PX2_APP.SaveScene(path.c_str());
	}
	else
	{
		wxFileDialog dlg(this,
			PX2_LM_EDITOR.GetValue("n_SaveScene"),
			wxEmptyString,
			wxEmptyString,
			wxT("scene (*.px2obj)|*.px2obj"),
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

		dlg.CenterOnParent();

		if (wxID_OK == dlg.ShowModal())
		{
			std::string strPath = dlg.GetPath();
			PX2_APP.SaveScene(strPath);
		}
	}
}
//----------------------------------------------------------------------------
void N_Frame::DoSaveSceneAs()
{
	mIsSaveSceneAs = false;

	wxFileDialog dlg(this,
		PX2_LM_EDITOR.GetValue("n_SaveSceneAs"),
		wxEmptyString,
		wxEmptyString,
		wxT("scene (*.px2obj)|*.px2obj"),
		wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	dlg.CenterOnParent();

	if (dlg.ShowModal() == wxID_OK)
	{
		std::string strPath = dlg.GetPath();
		PX2_APP.SaveSceneAs(strPath);
	}
}
//----------------------------------------------------------------------------
void N_Frame::DoCloseScene()
{
	mIsCloseScene = false;

	PX2_APP.CloseScene();
}
//----------------------------------------------------------------------------
void N_Frame::DoExit()
{
	mIsExit = false;

	int ret = wxMessageBox(PX2_LM_EDITOR.GetValue("n_Tip0"),
		PX2_LM_EDITOR.GetValue("n_Notice"), wxYES_NO);
	if (wxYES == ret)
	{
		wxExit();
	}
}
//----------------------------------------------------------------------------
void N_Frame::OnImport()
{
	int numObjs = PX2_SELECTM_E->GetNumObjects();
	if (1 != numObjs)
	{
		PX2EU_MAN.PlayTip(PX2_LM_EDITOR.GetValue("n_Notice"),
			PX2_LM_EDITOR.GetValue("n_TipCreateProject"));
		return;
	}

	wxFileDialog dlg(this,
		PX2_LM_EDITOR.GetValue("n_Import"),
		wxEmptyString,
		wxEmptyString,
		wxT("object (*.px2obj)|*.px2obj|model (*.PX2OBJ)|*.PX2OBJ"));

	dlg.CenterOnParent();

	if (dlg.ShowModal() == wxID_OK)
	{
		PX2_EDIT.Import(dlg.GetPath());
	}
}
//----------------------------------------------------------------------------
void N_Frame::OnExport()
{
	int numObjs = PX2_SELECTM_E->GetNumObjects();
	Object *obj = PX2_SELECTM_E->GetFirstObject();
	if (1 != numObjs)
	{
		PX2EU_MAN.PlayTip(PX2_LM_EDITOR.GetValue("n_Notice"),
			PX2_LM_EDITOR.GetValue("n_TipNotSelectAObject"));
		return;
	}

	wxFileDialog dlg(this,
		PX2_LM_EDITOR.GetValue("n_Export"),
		wxT("Data/"),
		wxEmptyString,
		wxT("object (*.px2obj)|*.px2obj|model (*.PX2OBJ)|*.PX2OBJ"),
		wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	dlg.CenterOnParent();

	if (dlg.ShowModal() == wxID_OK)
	{
		PX2_EDIT.Export(obj, dlg.GetPath());
	}
}
//----------------------------------------------------------------------------
void N_Frame::OnSize(wxSizeEvent& e)
{
	e.Skip();
}
//----------------------------------------------------------------------------
void N_Frame::OnTimer(wxTimerEvent& e)
{
	PX2_UNUSED(e);

	std::string name = GetName();
	if ("Main" == name)
	{
		if (mIsNewProject)
		{
			DoNewProject();
			DoSaveProject();
		}
		if (mIsOpenProject)
		{
			DoOpenProject();
		}
		if (mIsSaveProject)
		{
			DoSaveProject();
		}
		if (mIsCloseProject)
		{
			DoCloseProject();
		}
		if (mIsNewScene)
		{
			DoNewScene();
		}
		if (mIsOpenScene)
		{
			DoOpenScene();
		}
		if (mIsSaveScene)
		{
			DoSaveScene();
		}
		if (mIsSaveSceneAs)
		{
			DoSaveSceneAs();
		}
		if (mIsCloseScene)
		{
			DoCloseScene();
		}
		if (mIsExit)
		{
			DoExit();
		}
		if (mIsNWindow)
		{
			mIsNWindow = false;
			CreatePopUpWindow(mNUIWindow);
		}
		if (mIsOpeningRes)
		{
			mIsOpeningRes = false;

#if defined(_WIN32) || defined(WIN32)
			WCHAR wszPath[MAX_PATH];
			GetCurrentDirectoryW(sizeof(wszPath), wszPath);
			std::wstring fullPath = wszPath + std::wstring(_T("\\")) + mOpeningResFilename;

			ShellExecute(0, _T("open"), fullPath.c_str(), 0, 0, SW_SHOW);
#endif
		}
	}

	if (mIsDoImport)
	{
		mIsDoImport = false;

		OnImport();
	}

	if (mIsDoExport)
	{
		mIsDoExport = false;

		OnExport();
	}

	if (mIsPopUpRightMenu && mEditMenu)
	{
		wxSize sz = GetClientSize();
		PopUpRightMenu(mPopUpRightMenuPos.X(), sz.GetHeight() -
			mPopUpRightMenuPos.Z());
	}
}
//----------------------------------------------------------------------------
RenderView *N_Frame::GetMainRenderView()
{
	return mRenderView;
}
//----------------------------------------------------------------------------