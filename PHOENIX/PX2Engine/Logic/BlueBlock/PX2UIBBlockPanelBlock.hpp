// PX2UIBBlockPanelBlock.hpp

#ifndef PX2UIBLOCKSPANELBLOCK_HPP
#define PX2UIBLOCKSPANELBLOCK_HPP

#include "PX2BBlockPre.hpp"
#include "PX2UIFrame.hpp"
#include "PX2BBlock.hpp"
#include "PX2UISlider.hpp"
#include "PX2UITree.hpp"

namespace PX2
{

	class BActor;

	class PX2_ENGINE_ITEM BUIBlockPanelBlock : public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_NEW(BUIBlockPanelBlock);
		PX2_DECLARE_STREAM(BUIBlockPanelBlock);

	public:
		BUIBlockPanelBlock();
		virtual ~BUIBlockPanelBlock();

		virtual void Show(bool show);

		void SetCatalogue(const std::string &cata);
		const std::string &GetCatalogue() const;

		virtual void OnEvent(Event *ent);

		void AddBBlock(BBlock *block);
		float _UpdateAligns(Object *obj);

		virtual void OnSizeChanged();

	protected:
		virtual void UpdateWorldData(double applicationTime, double elapsedTime);
		void _UpdateEvents();
		void _UpdateFunctions();
		void _UpdateCtrls();
		void _UpdateParams();
		void _UpdateOperators();
		void _AddParam(FunObject *funObject);
		void _RemoveParam(FunObject *funObject);
		bool _IsObjectHasTag(Object *obj, const std::string &tag);

		std::string mCatalogue;
		int mNumCurAddedItems;
		float mABlockWidth;
		float mSpaceHeight;
		int mNumWidth;
		std::vector<BBlockPtr> mBlocks;

		bool mIsNeedReAlign;
	};

	PX2_REGISTER_STREAM(BUIBlockPanelBlock);
	typedef Pointer0<BUIBlockPanelBlock> BUIBlockPanelBlockPtr;

}

#endif
