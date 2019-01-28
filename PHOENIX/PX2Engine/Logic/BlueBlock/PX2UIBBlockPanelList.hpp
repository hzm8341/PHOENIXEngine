// PX2UIBBlockPanelList.hpp

#ifndef PX2UIBBLOCKPANELLIST_HPP
#define PX2UIBBLOCKPANELLIST_HPP

#include "PX2BBlockPre.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UIButton.hpp"
#include "PX2UITree.hpp"
#include "PX2UICollapsePanel.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM UIBBlockPanelList : public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_NEW(UIBBlockPanelList);
		PX2_DECLARE_STREAM(UIBBlockPanelList);

	public:
		UIBBlockPanelList();
		virtual ~UIBBlockPanelList();

		void SetCatalogue(const std::string &cata);		
		void ShowCata(const std::string &cata, bool show);

		virtual void OnEvent(Event *ent);

	protected:
		void _UpdateObjectFunctionsSystem();
		void _UpdateObjectFunctionsSystemClass();
		void _UpdateObjectFunctionsClass(const std::string &calssName);
		void _UpdateObjectFunctionsPanelTag(UICollapseItem *item,
			FunObject *funObj, const std::string &tag);
		bool _IsHasCata(FString cata);
		void _AddCataFun(FString cata, FString funname);

		std::string mCatalogue;
		UICollapsePanelPtr mCollapsePanel;
		std::vector<FString> mCatas;
		std::map<FString, std::vector<FString> > mCataFunnames;
	};

	PX2_REGISTER_STREAM(UIBBlockPanelList);
	typedef Pointer0<UIBBlockPanelList> UIBBlockPanelListPtr;

}

#endif