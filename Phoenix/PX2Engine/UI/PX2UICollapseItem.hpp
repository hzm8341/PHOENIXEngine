// PX2UICollapseItem.hpp

#ifndef PX2UICOLLAPSEITEM_HPP
#define PX2UICOLLAPSEITEM_HPP

#include "PX2UIFrame.hpp"
#include "PX2UIButton.hpp"

namespace PX2
{

	class UICollapsePanel;

	class PX2_ENGINE_ITEM UICollapseItem : public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(UICollapseItem);

	public:
		UICollapseItem();
		virtual ~UICollapseItem();

		virtual void SetName(const std::string &name);

		void Expand(bool expand);
		bool IsExpand() const;

		void SetContentHeight(float cntHeight);
		float GetAllHeight() const;

		UIFrame *GetContentFrame();

	public_internal:
		void SetCollapsedPanel(UICollapsePanel *panel);
		void _UpdateButText();

	protected:
		void _ButCallback(UIFrame *frame, UICallType type);
		void _MarkPanelRecal();

		UICollapsePanel *mUICollapsePanel;
		bool mIsExpand;
		float mExpandButHeight;
		float mContentHeight;
		UIButtonPtr mExpandBut;
		UIFramePtr mContentFrame;
	};

	PX2_REGISTER_STREAM(UICollapseItem);
	typedef Pointer0<UICollapseItem> UICollapseItemPtr;

}

#endif