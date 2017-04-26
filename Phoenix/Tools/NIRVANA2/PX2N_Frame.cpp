// PX2N_Frame.cpp

#include "PX2N_Frame.hpp"
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
#include "PX2N_DlgCreateProject.hpp"
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
N_Frame::N_Frame(PX2::RenderWindow *uiWindow, wxWindow *parent, long style) :
wxFrame((wxFrame*)parent, -1, uiWindow->GetTitle(), wxPoint(0, 0),
wxSize((int)uiWindow->GetScreenSize().Width, 
(int)uiWindow->GetScreenSize().Height), style),
mRenderWindow(uiWindow)
{
	_Init();

	std::string name = uiWindow->GetName();
	std::string title = uiWindow->GetTitle();
	int width = (int)uiWindow->GetScreenSize().Width;
	int height = (int)uiWindow->GetScreenSize().Height;

	SetName(name);
	PX2_EW.ComeIn(this);

	mTimerID = PX2_EDIT_GETID;
	Connect(mTimerID, wxEVT_TIMER, wxTimerEventHandler(N_Frame::OnTimer));
	mTimer.SetOwner(this, mTimerID);
	mTimer.Start(25);

	SetFocus();

	mRenderView = new RenderView(uiWindow, this);

	if ("Main" != name)
	{
		Renderer *renderer = PX2_APP.CreateRenderer(name, 
			mRenderView->GetHandle(), 0, 0, width, height, 0);
		uiWindow->SetRenderer(renderer);
		uiWindow->SetScreenSize(Sizef((float)width, (float)height));
	}

	wxBoxSizer* bSizer69;
	bSizer69 = new wxBoxSizer(wxVERTICAL);
	bSizer69->Add(mRenderView, 1, wxEXPAND, 5);
	this->SetSizer(bSizer69);
	this->Layout();
}
//----------------------------------------------------------------------------
void N_Frame::_Init()
{
	mIsInitlized = false;
	mIsSized = false;
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

	mIsOpeningRes = false;
}
//----------------------------------------------------------------------------
RenderView *N_Frame::GerRenderView()
{
	return mRenderView;
}
//----------------------------------------------------------------------------
N_Frame::~N_Frame()
{
	PX2_EW.GoOut(this);

	if (mEditMenu)
	{
		delete mEditMenu;
		mEditMenu = 0;
	}
}
//----------------------------------------------------------------------------
void N_Frame::OnEvent(Event *event)
{
	std::string name = GetName();
	if ("Main" == name)
	{
		if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_Window))
		{
			mIsNWindow = true;
			mNUIWindow = event->GetData<RenderWindow*>();
		}
		else if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_AddMenu))
		{
			EED_AddMenu data = event->GetData<EED_AddMenu>();
			if (data.Where == GetName())
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
							AddMenuItem(menu, data.Title, data.Script, data.Tag);
						}
						else if (EED_AddMenu::IT_MAIN_ITEMSPARATER == data.TheItemType)
						{
							AddSeparater(menu);
						}
					}
				}
			}

			if (EED_AddMenu::IT_EDIT_MENU == data.TheItemType ||
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
								AddMenuItem(menu, data.Title, data.Script, data.Tag);
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

	if (wxID_OK == dlg.ShowModal())
	{
		std::string name = dlg.mProjName;
		int screenOriention = dlg.mScreenOrientation;
		int width = dlg.mProjWidth;
		int height = dlg.mProjHeight;

		std::string pathName = name + "/";

		bool isProjectFolderExist = PX2_RM.IsFileFloderExist("Data/" + pathName);
		if (isProjectFolderExist)
		{
			MessageBox(PX2_LM_EDITOR.V("Notice"), PX2_LM_EDITOR.V("TipCreateProject"), 0);
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
		wxT("Open project"),
		wxEmptyString,
		wxEmptyString,
		wxT("Project (*.px2proj)|*.px2proj"));

	dlg.CenterOnParent();

	if (dlg.ShowModal() == wxID_OK)
	{
		std::string path = dlg.GetPath();
		path = StringHelp::StandardiseFilename(path);
		PX2_APP.LoadProject(path);
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
		wxT("Open scene"),
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
			wxT("Save scene"),
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
		wxT("Save scene as"),
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

	int ret = wxMessageBox(PX2_LM_EDITOR.GetValue("Notice"), PX2_LM_EDITOR.GetValue("Notice"),
		wxYES_NO);
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
		PX2EU_MAN.PlayTip(PX2_LM_EDITOR.GetValue("Notice"),
			PX2_LM_EDITOR.GetValue("TipNotHasParent"));
		return;
	}

	wxFileDialog dlg(this,
		PX2_LM_EDITOR.GetValue("Import"),
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
		PX2EU_MAN.PlayTip(PX2_LM_EDITOR.GetValue("Notice"),
			PX2_LM_EDITOR.GetValue("TipNotSelectAObject"));
		return;
	}

	wxFileDialog dlg(this,
		PX2_LM_EDITOR.GetValue("Export"),
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
		PopUpRightMenu(mPopUpRightMenuPos.X(), mSize.GetHeight() -
			mPopUpRightMenuPos.Z());
	}
}
//----------------------------------------------------------------------------
void N_Frame::OnSize(wxSizeEvent& e)
{
	PX2_UNUSED(e);

	mSize = GetClientSize();
	if (mRenderView)
		mRenderView->SetSize(0, 0, mSize.x, mSize.y);

	mIsSized = true;
}
//----------------------------------------------------------------------------
RenderView *N_Frame::GetMainRenderView()
{
	return mRenderView;
}
//----------------------------------------------------------------------------