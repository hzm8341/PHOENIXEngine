// PX2N_ResTree.cpp

#include "PX2N_ResTree.hpp"
#include "PX2Project.hpp"
#include "PX2Edit.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditorEventType.hpp"
#include "PX2Selection.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2EditEventType.hpp"
#include "PX2N_Define.hpp"
#include "PX2SelectionManager.hpp"
#include "PX2EditorEventType.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2N_Man.hpp"
#include "PX2ScriptManager.hpp"

using namespace NA;
using namespace PX2;

static int sID_RESTREE = PX2_EDIT_GETID;

IMPLEMENT_DYNAMIC_CLASS(ResTree, wxTreeCtrl)
BEGIN_EVENT_TABLE(ResTree, wxTreeCtrl)
EVT_TREE_SEL_CHANGED(sID_RESTREE, ResTree::OnSelChanged)
EVT_TREE_ITEM_ACTIVATED(sID_RESTREE, ResTree::OnItemActivated)
EVT_RIGHT_DOWN(ResTree::OnRightDown)
EVT_RIGHT_UP(ResTree::OnRightUp)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
ResTree::ResTree(wxWindow *parent, bool isUseOnlyDir) :
wxTreeCtrl(parent, sID_RESTREE, wxDefaultPosition, wxDefaultSize,
wxTR_DEFAULT_STYLE | wxTR_FULL_ROW_HIGHLIGHT | wxTR_NO_LINES | wxNO_BORDER),
mEditMenu(0),
mIsUseOnlyDir(isUseOnlyDir)
{
	mImageList = new wxImageList(16, 16);
	int imageFolder = mImageList->Add(wxIcon(wxT("DataNIRVANAwx/images/icons/res/folder.png"), wxBITMAP_TYPE_PNG));
	//int imageImage = mImageList->Add(wxIcon(wxT("DataNIRVANAwx/images/icons/res/image.png"), wxBITMAP_TYPE_PNG));
	//int imageObject = mImageList->Add(wxIcon(wxT("DataNIRVANAwx/images/icons/res/object.png"), wxBITMAP_TYPE_PNG));
	//int imageCSV = mImageList->Add(wxIcon(wxT("DataNIRVANAwx/images/icons/res/csv.png"), wxBITMAP_TYPE_PNG));
	//int imageLua = mImageList->Add(wxIcon(wxT("DataNIRVANAwx/images/icons/res/lua.png"), wxBITMAP_TYPE_PNG));
	SetImageList(mImageList);

	Icons["folder"] = imageFolder;
	//Icons["image"] = imageImage;
	//Icons["px2obj"] = imageObject;
	//Icons["csv"] = imageCSV;
	//Icons["lua"] = imageLua;

	ResRefresh();
	CloudRefresh();

	PX2_EW.ComeIn(this);

	SetBackgroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Background));
	SetForegroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Foreground));
}
//----------------------------------------------------------------------------
ResTree::ResTree()
{
}
//----------------------------------------------------------------------------
ResTree::~ResTree()
{
	EventWorld *ew = EventWorld::GetSingletonPtr();
	if (ew)
		PX2_EW.GoOut(this);

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
void ResTree::OnRightDown(wxMouseEvent& e)
{
	PX2_UNUSED(e);
}
//-----------------------------------------------------------------------------
void ResTree::OnRightUp(wxMouseEvent& e)
{
	wxPoint mousePos = e.GetPosition();

	if (mEditMenu)
	{
		delete mEditMenu;
		mEditMenu = 0;
	}

	mEditMenu = new wxMenu();
	NirMan::GetSingleton().SetCurMenu(mEditMenu);

	PX2_SC_LUA->CallString("n_CreateResMenu()");

	if (mEditMenu) PopupMenu(mEditMenu, mousePos.x, mousePos.y);
}
//-----------------------------------------------------------------------------
void ResTree::OnItemActivated(wxTreeEvent& event)
{
	PX2_UNUSED(event);
}
//-----------------------------------------------------------------------------
void ResTree::OnSelChanged(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();

	ResTreeItem *item = GetItem(id);
	if (!item) return;

	if (mIsUseOnlyDir)
	{
		PX2_EDIT.SetSelectPath_ChildFilenames(item->GetChildFilenamesList());
		PX2_EDIT.SetSelectPath_ChildPaths(item->GetChildPathsList());

		std::string pathName = item->GetPathName();
		PX2_EDIT.ChangeSelectResDir(pathName, Edit::CDT_TREE_REFRESH);

		SelectResData srd;
		srd.ResPathname = pathName;
		PX2_EDIT.SetSelectedResource(srd);
	}
	else
	{
		if (item->IsTexPackElement())
		{
			std::string eleName = item->GetName();
			std::string pathName = item->GetPathName();

			const TexPackElement &ele = PX2_RM.GetTexPackElement(pathName, eleName);
			if (ele.IsValid())
			{
				ObjectPtr obj = PX2_RM.BlockLoad(ele.ImagePathFull);

				SelectResData data(SelectResData::RT_TEXPACKELEMENT);
				data.ResPathname = pathName;
				data.EleName = eleName;
				data.TheObject = obj;
				PX2_EDIT.SetSelectedResource(data);
				PX2_EDIT.SetPreViewObject(obj);
			}

			return;
		}

		std::string resPath = item->GetPathName();
		if (resPath.find(".wav") != std::string::npos ||
			resPath.find(".WAV") != std::string::npos ||
			resPath.find(".ogg") != std::string::npos ||
			resPath.find(".OGG") != std::string::npos ||
			resPath.find(".mp3") != std::string::npos ||
			resPath.find(".MP3") != std::string::npos)
		{
			SelectResData data;
			data.ResPathname = resPath;
			PX2_EDIT.SetSelectedResource(data);
		}
		else if (resPath.find(".xml") != std::string::npos || resPath.find(".XML") != std::string::npos)
		{
			SelectResData data;
			data.ResPathname = resPath;
			PX2_EDIT.SetSelectedResource(data);
		}
		else if (resPath.find(".lua") != std::string::npos)
		{
			SelectResData data;
			data.ResPathname = resPath;

			PX2_EDIT.SetSelectedResource(data);
		}
		else if (resPath.find(".px2logic") != std::string::npos)
		{
			SelectResData data;
			data.ResPathname = resPath;

			PX2_EDIT.SetSelectedResource(data);
		}
		else if (resPath.find(".") != std::string::npos)
		{
			SelectResData data;
			data.ResPathname = resPath;

			PX2::ObjectPtr object = ResourceManager::GetSingleton().BlockLoad(
				resPath.c_str());
			data.TheObject = object;

			PX2_EDIT.SetSelectedResource(data);
			PX2_EDIT.SetPreViewObject(object);
		}
	}
}
//-----------------------------------------------------------------------------
ResTreeItem *ResTree::GetItem(wxTreeItemId id)
{
	if (id == mRootData->GetItemID())
		return mRootData;

	return mRootData->GetChildItem(id);
}
//----------------------------------------------------------------------------
ResTreeItem *ResTree::GetItem(const std::string &resPath)
{
	return mRootData->GetChildItem(resPath);
}
//----------------------------------------------------------------------------
ResTreeItem *ResTree::GetTreeRootItem()
{
	return mRootData;
}
//----------------------------------------------------------------------------
void ResTree::UpdateOnPath(const std::string &pathName)
{
	std::string name;
	std::string compareStr = "Data/";
	if (pathName == compareStr)
	{
		name = "Data";
	}
	else
	{
		name = pathName.substr(compareStr.length(),
			pathName.length() - compareStr.length() - 1);
	}

	mRootData = new0 ResTreeItem(this, name, pathName);
	mRootData->RootBuild(mIsUseOnlyDir);

	SelectItem(mRootData->GetItemID());
}
//----------------------------------------------------------------------------
void ResTree::ResRefresh()
{
	UpdateOnPath("Data/");

	SelectItem(mRootData->GetItemID());
}
//----------------------------------------------------------------------------
void ResTree::ResClear()
{
	PX2_RM.Clear();
}
//----------------------------------------------------------------------------
void ResTree::CloudRefresh()
{
	mRootCloud = new0 ResTreeItem(this, "Cloud", "");
	mRootCloud->CloudBuild(true);
}
//----------------------------------------------------------------------------
void ResTree::OnEvent(PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::RefreshRes))
	{
		ResRefresh();
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::UpRes))
	{
		wxTreeItemId select = GetSelection();
		ResTreeItem *item = GetItem(select);
		if (item)
		{
			ResTreeItem *parentItem = (item->GetParent());
			if (parentItem)
			{
				SelectItem(parentItem->GetItemID());
			}
		}
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::DownRes))
	{

	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::ChangeResDir))
	{
		Edit::ChangeDirType type = event->GetData<Edit::ChangeDirType>();
		if (Edit::CDT_GRID_REFRESH == type)
		{
			const std::string &selectedResDir = PX2_EDIT.GetSelectedResDir();
			if (!selectedResDir.empty())
			{
				ResTreeItem *item = GetItem(selectedResDir);
				if (item)
				{
					SelectItem(item->GetItemID());
					Expand(item->GetItemID());
				}
			}
		}
	}
}
//----------------------------------------------------------------------------