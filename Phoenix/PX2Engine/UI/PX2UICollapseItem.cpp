// PX2UICollapseItem.cpp

#include "PX2UICollapseItem.hpp"
#include "PX2UIButton.hpp"
#include "PX2UICollapsePanel.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
PX2_IMPLEMENT_RTTI(PX2, UIFrame, UICollapseItem);
PX2_IMPLEMENT_STREAM(UICollapseItem);
PX2_IMPLEMENT_FACTORY(UICollapseItem);
//----------------------------------------------------------------------------
UICollapseItem::UICollapseItem():
mIsExpand(true),
mExpandBarHeight(25.0f),
mContentHeight(100.0f),
mUICollapsePanel(0)
{
	SetName("UICollapseItem");

	SetAnchorHor(0.0f, 1.0f);
	SetAnchorVer(1.0f, 1.0f);
	SetPivot(0.5f, 1.0f);

	mExpandBut = new0 UIButton();
	AttachChild(mExpandBut);
	mExpandBut->SetName("ButCollpase");
	mExpandBut->LocalTransform.SetTranslateY(-2.0f);
	mExpandBut->SetAnchorHor(0.0f, 1.0f);
	mExpandBut->SetAnchorVer(1.0f, 1.0f);
	mExpandBut->SetAnchorParamHor(0.0f, -1.0f);
	mExpandBut->SetPivot(0.5f, 1.0f);
	mExpandBut->SetStateColor(UIButtonBase::BS_NORMAL, Float3::MakeColor(100, 100, 100));
	mExpandBut->SetSize(0.0f, mExpandBarHeight-1.0f);
	mExpandBut->CreateAddText("-");
	mExpandBut->SetMemUICallback(this,
		(UIFrame::MemUICallback)(&UICollapseItem::_ButCallback));
	mExpandBut->SetUserData("Item", this);

	mContentFrame = new0 UIFrame();
	AttachChild(mContentFrame);
	mContentFrame->SetName("FrameContent");
	mContentFrame->SetAnchorHor(0.0f, 1.0f);
	mContentFrame->SetAnchorVer(0.0f, 1.0f);
	mContentFrame->SetAnchorParamVer(0.0f, -mExpandBarHeight);
}
//----------------------------------------------------------------------------
UICollapseItem::~UICollapseItem()
{
}
//----------------------------------------------------------------------------
void UICollapseItem::SetName(const std::string &name)
{
	UIFrame::SetName(name);

	_UpdateButText();
}
//----------------------------------------------------------------------------
void UICollapseItem::SetCollapsedPanel(UICollapsePanel *panel)
{
	mUICollapsePanel = panel;
}
//----------------------------------------------------------------------------
void UICollapseItem::_ButCallback(UIFrame *frame, UICallType type)
{
	UIButton *button = DynamicCast<UIButton>(frame);
	if (button)
	{
		if (UICT_PRESSED == type)
		{
			UICollapseItem *item = button->GetUserData<UICollapseItem*>("Item");
			if (item)
			{
				item->Expand(!item->IsExpand());
				item->_UpdateButText();

			}
		}
	}
}
//----------------------------------------------------------------------------
void UICollapseItem::_UpdateButText()
{
	std::string name = GetName();

	if (IsExpand())
	{
		if (mExpandBut)
			mExpandBut->GetText()->SetText("-" + name);
	}
	else
	{
		if (mExpandBut)
			mExpandBut->GetText()->SetText("+" + name);
	}

	if (mExpandBut)
	{
		mExpandBut->GetFText()->SetAnchorParamHor(10.0f, 0.0f);
		mExpandBut->GetText()->SetAligns(TEXTALIGN_LEFT | TEXTALIGN_VCENTER);
	}
}
//----------------------------------------------------------------------------
void UICollapseItem::_MarkPanelRecal()
{
	if (mUICollapsePanel)
		mUICollapsePanel->_MarkCollpaseRecal();
}
//----------------------------------------------------------------------------
void UICollapseItem::Expand(bool expand)
{
	mIsExpand = expand;

	mContentFrame->Show(mIsExpand);

	if (mIsExpand)
	{
		SetHeight(mExpandBarHeight + mContentHeight);
	}
	else
	{
		SetHeight(mExpandBarHeight);
	}

	_UpdateButText();
	_MarkPanelRecal();
}
//----------------------------------------------------------------------------
bool UICollapseItem::IsExpand() const
{
	return mIsExpand;
}
//----------------------------------------------------------------------------
void UICollapseItem::SetExpandBarHeight(float height)
{
	mExpandBarHeight = height;

	if (mExpandBut)
		mExpandBut->SetSize(0.0f, mExpandBarHeight - 1.0f);

	if (mContentFrame)
		mContentFrame->SetAnchorParamVer(0.0f, -mExpandBarHeight);
}
//----------------------------------------------------------------------------
float UICollapseItem::GetExpandBarHeight() const
{
	return mExpandBarHeight;
}
//----------------------------------------------------------------------------
void UICollapseItem::SetContentHeight(float cntHeight)
{
	if (mContentFrame)
		mContentFrame->SetHeight(cntHeight);

	mContentHeight = cntHeight;
	SetHeight(mExpandBarHeight + mContentHeight);

	_MarkPanelRecal();
}
//----------------------------------------------------------------------------
float UICollapseItem::GetAllHeight() const
{
	if (mIsExpand)
		return mContentHeight + mExpandBarHeight;
	else
		return mExpandBarHeight;
}
//----------------------------------------------------------------------------
UIFrame *UICollapseItem::GetContentFrame()
{
	return mContentFrame;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Property
//----------------------------------------------------------------------------
void UICollapseItem::RegistProperties()
{
	UIFrame::RegistProperties();
	AddPropertyClass("UICollapseItem");
}
//----------------------------------------------------------------------------
void UICollapseItem::OnPropertyChanged(const PropertyObject &obj)
{
	UIFrame::OnPropertyChanged(obj);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
UICollapseItem::UICollapseItem(LoadConstructor value) :
UIFrame(value),
mUICollapsePanel(0)
{
}
//----------------------------------------------------------------------------
void UICollapseItem::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(UICollapseItem, source);
}
//----------------------------------------------------------------------------
void UICollapseItem::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void UICollapseItem::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool UICollapseItem::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void UICollapseItem::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(UICollapseItem, target);
}
//----------------------------------------------------------------------------
int UICollapseItem::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------