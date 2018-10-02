// PX2EU_StatusBar.cpp

#include "PX2EU_StatusBar.hpp"
#include "PX2UISkinManager.hpp"
#include "PX2RenderWindow.hpp"
#include "PX2StringHelp.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, EU_StatusBar);
PX2_IMPLEMENT_STREAM(EU_StatusBar);
PX2_IMPLEMENT_FACTORY(EU_StatusBar);

//----------------------------------------------------------------------------
EU_StatusBar::EU_StatusBar()
{
	SetName("EU_StatusBar");

	CreateAddBackgroundPicBox(true, PX2_UISM.Color_StatusBar);
	SetSize(0.0f, PX2_UISM.Size_StatusBar);

	SetAnchorHor(Float2(0.0f, 1.0f));
	SetAnchorVer(Float2(0.0f, 0.0f));
	SetPivot(0.5f, 0.0f);

	ComeInEventWorld();

	mCursorPosText = new0 UIFText();
	AttachChild(mCursorPosText);
	mCursorPosText->LocalTransform.SetTranslateY(-1.0f);
	mCursorPosText->GetText()->SetFontColor(Float3::WHITE);
	mCursorPosText->SetAnchorHor(0.0f, 0.0f);
	mCursorPosText->SetPivot(0.0f, 0.5f);
	mCursorPosText->GetText()->SetAligns(TEXTALIGN_LEFT | TEXTALIGN_VCENTER);
	mCursorPosText->SetAnchorVer(0.0f, 1.0f);
	mCursorPosText->SetSize(300.0f, 0.0);
	mCursorPosText->GetText()->SetFontScale(0.7f);
}
//----------------------------------------------------------------------------
EU_StatusBar::~EU_StatusBar()
{
}
//----------------------------------------------------------------------------
void EU_StatusBar::UpdateWorldData(double applicationTime,
	double elapsedTime)
{
	UIFrame::UpdateWorldData(applicationTime, elapsedTime);

	_UpdateCursorPos();
}
//----------------------------------------------------------------------------
void EU_StatusBar::_UpdateCursorPos()
{
	Float2 cursorPos = RenderWindow::GetCurCursorPos();

	mCursorPosText->GetText()->SetText("Cursor:" +
		StringHelp::IntToString((int)cursorPos.X()) + " " +
		StringHelp::IntToString((int)cursorPos.Y()));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EU_StatusBar::EU_StatusBar(LoadConstructor value) :
UIFrame(value)
{
}
//----------------------------------------------------------------------------
void EU_StatusBar::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(EU_StatusBar, source);
}
//----------------------------------------------------------------------------
void EU_StatusBar::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void EU_StatusBar::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool EU_StatusBar::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EU_StatusBar::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(EU_StatusBar, target);
}
//----------------------------------------------------------------------------
int EU_StatusBar::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------