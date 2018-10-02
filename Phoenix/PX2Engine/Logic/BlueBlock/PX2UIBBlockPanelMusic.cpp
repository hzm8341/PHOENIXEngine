// UIBBlockPanelMusic.cpp

#include "PX2UIBBlockPanelMusic.hpp"
#include "PX2UIButton.hpp"
#include "PX2LanguageManager.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, UIBBlockPanelMusic);
PX2_IMPLEMENT_STREAM(UIBBlockPanelMusic);
PX2_IMPLEMENT_FACTORY(UIBBlockPanelMusic);

//----------------------------------------------------------------------------
UIBBlockPanelMusic::UIBBlockPanelMusic()
{
	ComeInEventWorld();

	float butHeight = 40.0f;
	float butSpace = 10.0f;

	// param
	mButCreateParam = new0 UIButton();
	AttachChild(mButCreateParam);
	mButCreateParam->SetName("ButCreateParam");
	mButCreateParam->SetSize(0.0f, butHeight);
	mButCreateParam->SetAnchorHor(0.0f, 1.0f);
	mButCreateParam->SetAnchorParamHor(10.0f, -10.0f);
	mButCreateParam->SetAnchorVer(1.0f, 1.0f);
	mButCreateParam->SetAnchorParamVer(-butHeight*0.5f - butSpace, -butHeight*0.5f - butSpace);
	mButCreateParam->CreateAddText(PX2_LM_APP.GetValue("AddMusic"));
	mButCreateParam->GetText()->SetFontColor(Float3::WHITE);
	mButCreateParam->SetMemUICallback(this,
		(UIFrame::MemUICallback)(&UIBBlockPanelMusic::_UIButCallback));

	SetAnchorHor(0.0f, 1.0f);
	SetAnchorVer(0.0f, 1.0f);
}
//----------------------------------------------------------------------------
UIBBlockPanelMusic::~UIBBlockPanelMusic()
{
}
//----------------------------------------------------------------------------
void UIBBlockPanelMusic::_UIButCallback(UIFrame *frame, UICallType type)
{
	PX2_UNUSED(frame);
	PX2_UNUSED(type);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
UIBBlockPanelMusic::UIBBlockPanelMusic(LoadConstructor value) :
UIFrame(value)
{
}
//----------------------------------------------------------------------------
void UIBBlockPanelMusic::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(UIBBlockPanelMusic, source);
}
//----------------------------------------------------------------------------
void UIBBlockPanelMusic::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void UIBBlockPanelMusic::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool UIBBlockPanelMusic::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void UIBBlockPanelMusic::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(UIBBlockPanelMusic, target);
}
//----------------------------------------------------------------------------
int UIBBlockPanelMusic::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------