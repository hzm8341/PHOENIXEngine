// PX2N_ProjTree.cpp

#include "PX2N_ProjTree.hpp"
#include "PX2N_Define.hpp"
#include "PX2Project.hpp"
#include "PX2Edit.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditEventData.hpp"
#include "PX2Selection.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2EditDefine.hpp"
#include "PX2EffectableController.hpp"
#include "PX2Edit.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2SelectionManager.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2GraphicsEventType.hpp"
#include "PX2EditorEventType.hpp"
#include "PX2GraphicsEventData.hpp"
#include "PX2N_Man.hpp"
#include "PX2N_Frame.hpp"
using namespace NA;
using namespace PX2;

static int sID_PROJVIEW = PX2_EDIT_GETID;

IMPLEMENT_DYNAMIC_CLASS(NA::ProjTree, wxTreeCtrl)
BEGIN_EVENT_TABLE(ProjTree, wxTreeCtrl)
EVT_TREE_ITEM_ACTIVATED(sID_PROJVIEW, ProjTree::OnItemActivated)
EVT_TREE_SEL_CHANGED(sID_PROJVIEW, ProjTree::OnSelChanged)
EVT_TREE_SEL_CHANGING(sID_PROJVIEW, ProjTree::OnSelChanging)
EVT_TREE_DELETE_ITEM(sID_PROJVIEW, ProjTree::OnSelDelete)
EVT_RIGHT_DOWN(ProjTree::OnRightDown)
EVT_RIGHT_UP(ProjTree::OnRightUp)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
ProjTree::ProjTree()
{
}
//----------------------------------------------------------------------------
ProjTree::ProjTree(wxWindow *parent) :
wxTreeCtrl(parent, sID_PROJVIEW, wxDefaultPosition, wxDefaultSize,
wxTR_DEFAULT_STYLE | wxTR_FULL_ROW_HIGHLIGHT | wxTR_NO_LINES | wxNO_BORDER),
mIsShowHelpNode(false),
mTreeLevel(PTL_CHILDREN),
mImageList(0),
mItemProj(0),
mItemScene(0),
mItemUI(0),
mEditMenu(0)
{
	SetBackgroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Background));
	SetForegroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Foreground));

	PX2_EW.ComeIn(this);

	mImageList = new wxImageList(16, 16);

	int imageProject = mImageList->Add(wxIcon(wxT("DataNIRVANAwx/images/icons/project/project.png"), wxBITMAP_TYPE_PNG));
	int imageScene = mImageList->Add(wxIcon(wxT("DataNIRVANAwx/images/icons/project/scene1.png"), wxBITMAP_TYPE_PNG));
	int imageUI = mImageList->Add(wxIcon(wxT("DataNIRVANAwx/images/icons/project/ui.png"), wxBITMAP_TYPE_PNG));
	int imageLogic = mImageList->Add(wxIcon(wxT("DataNIRVANAwx/images/icons/project/logic.png"), wxBITMAP_TYPE_PNG));

	int imageObject = mImageList->Add(wxIcon(wxT("DataNIRVANAwx/images/icons/project/object.png"), wxBITMAP_TYPE_PNG));
	int imageCamera = mImageList->Add(wxIcon(wxT("DataNIRVANAwx/images/icons/project/camera.png"), wxBITMAP_TYPE_PNG));
	int imageTerrain = mImageList->Add(wxIcon(wxT("DataNIRVANAwx/images/icons/project/terrain.png"), wxBITMAP_TYPE_PNG));
	int imageEffect = mImageList->Add(wxIcon(wxT("DataNIRVANAwx/images/icons/project/effect.png"), wxBITMAP_TYPE_PNG));
	int imageControl = mImageList->Add(wxIcon(wxT("DataNIRVANAwx/images/icons/project/control.png"), wxBITMAP_TYPE_PNG));
	int imageMesh = mImageList->Add(wxIcon(wxT("DataNIRVANAwx/images/icons/project/mesh.png"), wxBITMAP_TYPE_PNG));

	SetImageList(mImageList);

	Icons["proj"] = imageProject;
	Icons["scene"] = imageScene;
	Icons["ui"] = imageUI;
	Icons["logic"] = imageLogic;
	Icons["camera"] = imageCamera;
	Icons["terrain"] = imageTerrain;
	Icons["object"] = imageObject;
	Icons["effect"] = imageEffect;
	Icons["control"] = imageControl;
	Icons["mesh"] = imageMesh;

	SetName("ProjectTree");
}
//----------------------------------------------------------------------------
ProjTree::~ProjTree()
{
	UnselectAll();

	_ClearProject();

	if (mEditMenu)
	{
		delete mEditMenu;
		mEditMenu = 0;
	}

	if (mImageList)
	{
		delete mImageList;
		mImageList = 0;
	}
}
//-----------------------------------------------------------------------------
void ProjTree::ShowHelpNode(bool showHelpNode)
{
	mIsShowHelpNode = showHelpNode;
}
//-----------------------------------------------------------------------------
bool ProjTree::IsShowHelpNode() const
{
	return mIsShowHelpNode;
}
//-----------------------------------------------------------------------------
void ProjTree::SetTreeLevel(ProjTreeLevel level)
{
	if (!mItemProj) return;

	mItemProj->SetTreeLevel(level, mIsShowHelpNode);	
	mItemScene->SetTreeLevel(level, mIsShowHelpNode);

	mItemUI->SetTreeLevel(level, mIsShowHelpNode);

	mTreeLevel = level;
}
//-----------------------------------------------------------------------------
ProjTreeLevel ProjTree::GetTreeLevel() const
{
	return mTreeLevel;
}
//-----------------------------------------------------------------------------
void ProjTree::SetSelectItemLevel(ProjTreeLevel level)
{
	wxTreeItemId selectID = GetSelection();
	ProjTreeItem *item = GetItem(selectID);
	if (item)
	{
		item->SetTreeLevel(level, mIsShowHelpNode);
		SelectItem(item->GetItemID());
	}
}
//-----------------------------------------------------------------------------
ProjTreeItem *ProjTree::GetItem(wxTreeItemId id)
{
	if (!mItemProj) return 0;

	return mItemProj->GetItem(id);
}
//-----------------------------------------------------------------------------
ProjTreeItem *ProjTree::GetItem(PX2::Object *obj)
{
	if (!mItemProj) return 0;

	return mItemProj->GetItem(obj);
}
//----------------------------------------------------------------------------
void ProjTree::_RefreshProject()
{
	Project *proj = Project::GetSingletonPtr();
	if (!proj) return;

	wxTreeItemId projectID = AddRoot(proj->GetName(), 0);
	mItemProj = new ProjTreeItem(this, projectID, ProjTreeItem::IT_CATALOG, 
		Icons["proj"], "Project");
	mItemProj->SetObject(proj);

	SelectItem(projectID);

	// scene
	mItemScene = new ProjTreeItem(this, mItemProj,
		ProjTreeItem::IT_CATALOG, Icons["scene"], 0, mTreeLevel, mIsShowHelpNode, "Scene");
	mItemProj->mChildItems.push_back(mItemScene);

	// ui
	mItemUI = new ProjTreeItem(this, mItemProj,
		ProjTreeItem::IT_CATALOG, Icons["ui"], 0, mTreeLevel, mIsShowHelpNode, "UI");
	mItemProj->mChildItems.push_back(mItemUI);

	Expand(mItemProj->GetItemID());
}
//----------------------------------------------------------------------------
void ProjTree::_ClearProject()
{
	if (mItemProj)
	{
		mItemProj->ClearChildren();
		mItemProj->SetObject(0);

		mItemScene = 0;
		mItemUI = 0;

		delete(mItemProj);
		mItemProj = 0;
	}
}
//----------------------------------------------------------------------------
void ProjTree::_RefreshScene()
{
	Scene *scene = 0;
	Project *proj = Project::GetSingletonPtr();
	if (proj)
	{
		scene = proj->GetScene();
	}
	if (!scene) return;

	mItemScene->SetObject(scene);
	mItemScene->SetName(scene->GetName());
	_TravelRefreshChild(mItemScene, scene);

	Expand(mItemScene->GetItemID());
}
//----------------------------------------------------------------------------
void ProjTree::_ClearScene()
{
	if (mItemScene)
	{
		mItemScene->ClearChildren();
		mItemScene->SetObject(0);
		mItemScene->SetName("NoScene");
	}
}
//----------------------------------------------------------------------------
void ProjTree::_RefreshUI()
{
	UI *ui = 0;
	Project *proj = Project::GetSingletonPtr();
	if (proj)
	{
		ui = proj->GetUI();
	}
	if (!ui) return;

	mItemUI->SetObject(ui);
	mItemUI->SetName(ui->GetName());
	_TravelRefreshChild(mItemUI, ui);

	if (mItemUI)
		Expand(mItemUI->GetItemID());
}
//----------------------------------------------------------------------------
void ProjTree::_ClearUI()
{
	if (mItemUI)
	{
		mItemUI->ClearChildren();
	}
}
//----------------------------------------------------------------------------
void ProjTree::_TravelRefreshChild(ProjTreeItem *item, Movable *mov)
{
	Node *node = DynamicCast<Node>(mov);
	if (node)
	{
		for (int i = 0; i < node->GetNumChildren(); i++)
		{
			Movable *movChild = node->GetChild(i);
			if (movChild)
			{
				ProjTreeLevel treeLevel = mTreeLevel;
				NA::ProjTreeItem *itemAdd = item->AddChild(movChild, _GetIconID(movChild), treeLevel, mIsShowHelpNode);
				_TravelRefreshChild(itemAdd, movChild);
			}
		}
	}
}
//----------------------------------------------------------------------------
int ProjTree::_GetIconID(PX2::Object *obj)
{
	CameraNode *camNode = DynamicCast<CameraNode>(obj);
	Terrain *ter = DynamicCast<Terrain>(obj);
	Effectable *ef = DynamicCast<Effectable>(obj);
	Controller *ctrl = DynamicCast<Controller>(obj);
	TriMesh *mesh = DynamicCast<TriMesh>(obj);

	if (camNode)
		return Icons["camera"];
	else if (ter)
		return Icons["terrain"];
	else if (ef)
		return Icons["effect"];
	else if (ctrl)
		return Icons["control"];
	else if (mesh)
		return Icons["mesh"];

	return Icons["object"];
}
//----------------------------------------------------------------------------
void ProjTree::_AddObject(Object *obj)
{
	Movable *move = DynamicCast<Movable>(obj);
	EffectModule *eftModule = DynamicCast<EffectModule>(obj);

	if (move)
	{
		Node *parNode = DynamicCast<Node>(move->GetParent());
		ProjTreeItem *item = GetItem(parNode);

		if (parNode && item)
		{
			ProjTreeLevel treeLevel = mTreeLevel;
			NA::ProjTreeItem *itemAdd = item->AddChild(move, _GetIconID(move), treeLevel, mIsShowHelpNode);
			Expand(item->GetItemID());

			_TravelRefreshChild(itemAdd, move);
		}
	}
	else if (eftModule)
	{
		EffectableController *eftableCtrl = DynamicCast<EffectableController>(
			eftModule->GetEffectableController());
		ProjTreeItem *item = GetItem(eftableCtrl);
		if (eftableCtrl && item)
		{
			item->AddChild(eftModule, _GetIconID(move), mTreeLevel, mIsShowHelpNode);
			Expand(item->GetItemID());
		}
	}
}
//-----------------------------------------------------------------------------
void ProjTree::OnRightDown(wxMouseEvent& e)
{
	PX2_UNUSED(e);
}
//-----------------------------------------------------------------------------
void ProjTree::OnRightUp(wxMouseEvent& e)
{
	wxPoint mousePos = e.GetPosition();

	APoint pos;
	pos.X() = mousePos.x;
	pos.Z() = mousePos.y;
	PX2EU_MAN.CreateEditMenu("ProjectTree", pos, EU_Manager::EMT_PROJTREE);
}
//----------------------------------------------------------------------------
void ProjTree::OnItemActivated(wxTreeEvent& event)
{
	PX2_UNUSED(event);
	PX2_EDIT.FocusOnSelection();
}
//----------------------------------------------------------------------------
void ProjTree::OnSelChanged(wxTreeEvent& event)
{
	Project *proj = Project::GetSingletonPtr();
	if (!proj) return;

	wxTreeItemId id = event.GetItem();

	ProjTreeItem *item = GetItem(id);
	if (item)
	{
		Object *obj = item->GetObject();
		if (obj)
		{
			PX2_SELECTM_E->Clear();
			PX2_SELECTM_E->AddObject(obj);
		}
		else
		{
			PX2_SELECTM_E->Clear();
		}
	}
}
//----------------------------------------------------------------------------
void ProjTree::OnSelChanging(wxTreeEvent& event)
{
	PX2_UNUSED(event);
}
//----------------------------------------------------------------------------
void ProjTree::OnSelDelete(wxTreeEvent& event)
{
	PX2_UNUSED(event);
}
//----------------------------------------------------------------------------
void ProjTree::ExpandSelect()
{
	wxTreeItemId selectID = GetSelection();
	ProjTreeItem *item = GetItem(selectID);
	if (item)
	{
		ExpandAllChildren(selectID);
	}
}
//----------------------------------------------------------------------------
void ProjTree::CollapseSelect()
{
	wxTreeItemId selectID = GetSelection();
	ProjTreeItem *item = GetItem(selectID);
	if (item)
	{
		Collapse(selectID);
	}
}
//----------------------------------------------------------------------------
void ProjTree::OnEvent(Event *event)
{
	if (ProjectES::IsEqual(event, ProjectES::NewProject) ||
		ProjectES::IsEqual(event, ProjectES::LoadedProject))
	{
		_RefreshProject();
	}
	else if (ProjectES::IsEqual(event, ProjectES::CloseProject))
	{
		_ClearProject();
	}
	else if (ProjectES::IsEqual(event, ProjectES::NewScene))
	{
		_RefreshScene();
	}
	else if (ProjectES::IsEqual(event, ProjectES::CloseScene))
	{
		_ClearScene();
	}
	else if (ProjectES::IsEqual(event, ProjectES::NewUI))
	{
		_RefreshUI();
	}
	else if (ProjectES::IsEqual(event, ProjectES::CloseUI))
	{
		_ClearUI();
	}
	else if (GraphicsES::IsEqual(event, GraphicsES::AddObject))
	{
		AddObjectData data = event->GetData<AddObjectData>();
		_AddObject(data.Obj);
	}
	else if (GraphicsES::IsEqual(event, GraphicsES::RemoveObject))
	{
		Object *object = event->GetData<Object*>();
		_RemoveObject(object);
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::SetProjectTreeLevel))
	{
		int level = event->GetData<int>();
		SetSelectItemLevel((ProjTreeLevel)level);
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_ObjectNameChanged))
	{
		Object *obj = event->GetData<Object*>();
		ProjTreeItem *item = GetItem(obj);
		if (item) item->SetName(obj->GetName());
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::FindActorInProjectTree))
	{
		Object *obj = PX2_SELECTM_E->GetFirstObject();
		ProjTreeItem *item = GetItem(obj);
		if (item)
		{
			SelectItem(item->GetItemID());
			SetFocus();
		}
	}
	else if (EditES::IsEqual(event, EditES::N_AddMenu))
	{
		std::string name = GetName();

		EED_AddMenu data = event->GetData<EED_AddMenu>();
		if (data.Where == name)
		{
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
						PopUpRightMenu(data.PopUpPos.X(), data.PopUpPos.Z());
					}
				}
			}
		}
	}
}
//----------------------------------------------------------------------------
void ProjTree::_RemoveObject(PX2::Object *obj)
{
	ProjTreeItem *item = GetItem(obj);
	if (item)
	{
		ProjTreeItem *parItem = item->GetParent();
		if (parItem)
		{
			parItem->RemoveChild(obj);
		}
	}
}
//----------------------------------------------------------------------------
wxMenu *ProjTree::CreateEditMenu()
{
	if (mEditMenu)
	{
		delete mEditMenu;
		mEditMenu = 0;
	}
	mMenuMap_Edit.clear();

	mEditMenu = new wxMenu();

	return mEditMenu;
}
//----------------------------------------------------------------------------
wxMenu *ProjTree::AddSubMenuItem(wxMenu *menu, const std::string &title)
{
	wxMenu *subMenu = new wxMenu();
	menu->AppendSubMenu(subMenu, title);

	return subMenu;
}
//----------------------------------------------------------------------------
wxMenuItem *ProjTree::AddMenuItem(wxMenu *menu,
	const std::string &title,
	const std::string &script,
	const std::string &scriptParam,
	const std::string &tag)
{
	PX2_UNUSED(tag);

	int id = PX2_EDIT_GETID;
	wxMenuItem *item = new wxMenuItem(menu, id, title);
	menu->Append(item);

	N_Frame::MainFrame->Connect(id, wxEVT_MENU,
		wxCommandEventHandler(N_Frame::OnCommondItem));

	N_Frame::MainFrame->mIDScripts[id] = script;
	if (!scriptParam.empty())
		N_Frame::MainFrame->mIDScriptParams[id] = scriptParam;

	return item;
}
//----------------------------------------------------------------------------
void ProjTree::AddSeparater(wxMenu *menu)
{
	wxMenuItem *item = new wxMenuItem(menu, wxID_SEPARATOR);
	menu->Append(item);
}
//----------------------------------------------------------------------------
void ProjTree::PopUpRightMenu(int x, int y)
{
	if (mEditMenu)
	{
		PopupMenu(mEditMenu, x, y);
	}
}
//----------------------------------------------------------------------------