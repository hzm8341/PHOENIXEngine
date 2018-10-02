// PX2UIBBlockPanelBlockCont.hpp

#ifndef PX2UIBBLOCKPANELBLOCKCONT_HPP
#define PX2UIBBLOCKPANELBLOCKCONT_HPP

#include "PX2BBlockPre.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UIBBlockPanelBlock.hpp"
#include "PX2UITabFrame.hpp"
#include "PX2UIBBlockCreateVariableFrame.hpp"
#include "PX2UIBBlockPanelList.hpp"
#include "PX2Canvas.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM BUIBlocksPanelCont : public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_NEW(BUIBlocksPanelCont);
		PX2_DECLARE_STREAM(BUIBlocksPanelCont);

	public:
		BUIBlocksPanelCont(const std::string &tag = "");
		virtual ~BUIBlocksPanelCont();

		void SetCatalogue(const std::string &cata);

		virtual void OnEvent(Event *ent);

	protected:
		virtual void UpdateWorldData(double applicationTime, double elapsedTime);
		void _SliderCallback(UIFrame *frame, UICallType type);
		void _ButCallback(UIFrame *frame, UICallType type);
		void _UpdateContentPos();

		std::string mTag;
		std::string mCata;

		UIFramePtr mToolFrame;
		CanvasPtr mContentCanvas;
		UIFramePtr mContentBlocks;
		UIBBlockPanelListPtr mContentList;

		BUIBlockPanelBlockPtr mBlocksPanel;
		UISliderPtr mSlider;
		float mSliderWidth;
		bool mIsUpdateSliderVisible;
		bool mIsUpdateContentPos;

		// tool param
		UIButtonPtr mButCreateParam;
		UIButtonPtr mButDeleteParam;
		BUICreateVariableFramePtr mCreateParamFrame;
	};

	PX2_REGISTER_STREAM(BUIBlocksPanelCont);
	typedef Pointer0<BUIBlocksPanelCont> BUIBlocksPanelContainerPtr;

}

#endif