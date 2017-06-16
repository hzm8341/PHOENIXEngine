// PX2N_ProjTree.hpp

#ifndef PX2N_PROJTREE_HPP
#define PX2N_PROJTREE_HPP

#include "PX2N_Pre.hpp"
#include "PX2EventHandler.hpp"
#include "PX2N_ProjTreeItem.hpp"
#include "PX2N_ProjTreeDef.hpp"
#include "PX2EditParams.hpp"

namespace NA
{

	class ProjTree : public wxTreeCtrl, public PX2::EventHandler
	{
		DECLARE_DYNAMIC_CLASS(ProjTree)

	public:
		ProjTree();
		ProjTree(wxWindow *parent);
		virtual ~ProjTree();

		void ShowHelpNode(bool showHelpNode);
		bool IsShowHelpNode() const;

		void SetTreeLevel(ProjTreeLevel level);
		ProjTreeLevel GetTreeLevel() const;
		void SetSelectItemLevel(ProjTreeLevel level);

		ProjTreeItem *GetItem(wxTreeItemId id);
		ProjTreeItem *GetItem(PX2::Object *obj);

		virtual void OnEvent(PX2::Event *event);

		void OnRightDown(wxMouseEvent& e);
		void OnRightUp(wxMouseEvent& e);
		void OnItemActivated(wxTreeEvent& event);
		void OnSelChanged(wxTreeEvent& event);
		void OnSelChanging(wxTreeEvent& event);
		void OnSelDelete(wxTreeEvent& event);

		void ExpandSelect();
		void CollapseSelect();

	public_internal:
		std::map<std::string, int> Icons;

	protected:
		DECLARE_EVENT_TABLE()

		void _RefreshProject();
		void _ClearProject();

		void _RefreshScene();
		void _ClearScene();

		void _RefreshUI();
		void _ClearUI();

		void _TravelRefreshChild(ProjTreeItem *item, PX2::Movable *mov);

		int _GetIconID(PX2::Object *obj);
		void _AddObject(PX2::Object *obj);
		void _RemoveObject(PX2::Object *obj);

		bool mIsShowHelpNode;
		ProjTreeLevel mTreeLevel;

		wxImageList *mImageList;

		ProjTreeItem *mItemProj;
		ProjTreeItem *mItemScene;

		ProjTreeItem *mItemUI;

		// edit menu
	public:
		wxMenu *CreateEditMenu();
		void PopUpRightMenu(int x, int y);

		wxMenu *AddSubMenuItem(wxMenu *menu, const std::string &title);
		wxMenuItem *AddMenuItem(wxMenu *menu,
			const std::string &title,
			const std::string &script,
			const std::string &scriptParam,
			const std::string &tag = "");
		void AddSeparater(wxMenu *menu);

		wxMenu *mEditMenu;
		std::map<std::string, wxMenu*> mMenuMap_Edit;
	};

}

#endif