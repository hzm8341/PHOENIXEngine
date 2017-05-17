// PX2EU_ConsoleFrame.cpp

#include "PX2EU_ConsoleFrame.hpp"
#include "PX2UISkinManager.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2StringTokenizer.hpp"
#include "PX2Application.hpp"
#include "PX2EngineServer.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
ConsoleLogHandler::ConsoleLogHandler():
LogHandler(LT_INFO | LT_ERROR | LT_USER)
{
}
//----------------------------------------------------------------------------
ConsoleLogHandler::~ConsoleLogHandler()
{
}
//----------------------------------------------------------------------------
void ConsoleLogHandler::Handle(const LogBuffer *logBuffer,
	const char *timeStamp)
{
	EU_ConcoleFrame *euFrame = EU_ConcoleFrame::GetSingletonPtr();
	if (euFrame)
	{
		euFrame->Handle(logBuffer, timeStamp);
	}
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
PX2_IMPLEMENT_RTTI(PX2, UIFrame, EU_ConcoleFrame);
PX2_IMPLEMENT_STREAM(EU_ConcoleFrame);
PX2_IMPLEMENT_FACTORY(EU_ConcoleFrame);
//----------------------------------------------------------------------------
EU_ConcoleFrame::EU_ConcoleFrame()
{
	mToolFrame = new0 UIFrame();
	AttachChild(mToolFrame);
	mToolFrame->LocalTransform.SetTranslateY(-1.0f);
	UIPicBox *picBox = mToolFrame->CreateAddBackgroundPicBox();
	picBox->SetColor(PX2_UISM.Color_ToolBar);
	mToolFrame->SetAnchorHor(0.0f, 1.0f);
	mToolFrame->SetAnchorVer(1.0f, 1.0f);
	mToolFrame->SetPivot(0.5f, 1.0f);
	mToolFrame->SetSize(0.0f, PX2_UISM.Size_ToolBar);

	UIFText *text = new0 UIFText();
	mToolFrame->AttachChild(text);
	text->LocalTransform.SetTranslateY(-1.0);
	text->SetAnchorHor(0.0f, 1.0f);
	text->SetAnchorVer(0.0f, 1.0f);
	text->SetAnchorParamHor(20.0f, 0.0f);
	text->GetText()->SetText(PX2_LM_EDITOR.GetValue("Console"));
	text->GetText()->SetFontColor(Float3::WHITE);
	text->GetText()->SetFontScale(0.7f);
	text->GetText()->SetDrawStyle(FD_SHADOW);
	text->GetText()->SetAligns(TEXTALIGN_LEFT | TEXTALIGN_VCENTER);

	float butSendWidth = 50.0f;
	mEditBox = new0 UIEditBox();
	AttachChild(mEditBox);
	mEditBox->LocalTransform.SetTranslateY(-5.0f);
	mEditBox->SetAnchorHor(0.0f, 1.0f);
	mEditBox->SetAnchorParamHor(0.0f, -butSendWidth);
	mEditBox->SetAnchorVer(1.0f, 1.0f);
	mEditBox->SetAnchorParamVer(-PX2_UISM.Size_ToolBar, 0.0f);
	mEditBox->SetPivot(0.5f, 1.0f);
	mEditBox->GetInputText()->SetFontScale(0.8f);
	mEditBox->SetSize(0.0f, PX2_UISM.Size_SearchBar);

	UIButton *butSend = new0 UIButton();
	AttachChild(butSend);
	butSend->SetName("ButSend");
	butSend->LocalTransform.SetTranslateY(-5.0f);
	butSend->SetSize(butSendWidth, PX2_UISM.Size_SearchBar);
	butSend->SetAnchorHor(1.0f, 1.0f);
	butSend->SetAnchorVer(1.0f, 1.0f);
	butSend->SetAnchorParamVer(-PX2_UISM.Size_ToolBar, 0.0f);
	butSend->SetPivot(1.0f, 1.0f);
	butSend->CreateAddText("Send");
	butSend->SetMemUICallback(this,
		(UIFrame::MemUICallback)(&EU_ConcoleFrame::_UIConsoleCallback));

	mList = new0 UIList();
	AttachChild(mList);
	mList->SetAnchorHor(0.0f, 1.0f);
	mList->SetAnchorVer(0.0f, 1.0f);
	mList->SetAnchorParamVer(0.0f, -PX2_UISM.Size_ToolBar - PX2_UISM.Size_SearchBar);

	mLogHandler = new0 ConsoleLogHandler();
	Logger::GetSingleton().AddHandler(mLogHandler);
}
//----------------------------------------------------------------------------
EU_ConcoleFrame::~EU_ConcoleFrame()
{
	Logger::GetSingleton().RemoveHandler(mLogHandler);
}
//----------------------------------------------------------------------------
void EU_ConcoleFrame::_UIConsoleCallback(UIFrame *frame, UICallType type)
{
	UIButton *but = DynamicCast<UIButton>(frame);
	const std::string &name = frame->GetName();
	if (UICT_RELEASED == type)
	{
		if ("ButSend" == name)
		{
			const std::string &textEditBox = mEditBox->GetText();
			_ProcessCmdStr(textEditBox);
		}
	}
	else if (UICT_EDITBOX_ENTER == type)
	{
		const std::string &textEditBox = mEditBox->GetText();
		_ProcessCmdStr(textEditBox);
	}
}
//----------------------------------------------------------------------------
void EU_ConcoleFrame::_ProcessCmdStr(const std::string &cmdStr)
{
	StringTokenizer stk(cmdStr, " ");
	std::string strCmd;
	std::string strParam0;
	std::string strParam1;

	EngineServer *ssc = PX2_APP.GetEngineServer();
	
	int stkCount = stk.Count();
	if (stkCount > 0)
		strCmd = stk[0];
	if (stkCount > 1)
		strParam0 = stk[1];
	if (stkCount > 2)
		strParam1 = stk[2];

	if ("net_send" == strCmd)
	{
		ssc->BroadCastString(strParam0);
	}
	else if ("push" == strCmd)
	{
		std::string projName = strParam0;
		ssc->BroadCastPushProject(projName);
	}
}
//----------------------------------------------------------------------------
void EU_ConcoleFrame::Handle(const LogBuffer *logBuffer,
	const char *timeStamp)
{
	std::string timeStampStr(timeStamp);
	std::string logStr = timeStampStr + std::string((char*)logBuffer->Buffer);

	int level = logBuffer->Level;

	Float3 color;
	if (PX2::LT_INFO == level)
	{
		color = Float3(240, 240, 240);
	}
	else if (PX2::LT_ERROR == level)
	{
		color = Float3::RED;
	}
	else if (PX2::LT_USER == level)
	{
		color = Float3::GREEN;
	}

	UIItem *item = mList->AddItem(logStr);
	item->GetFText()->GetText()->SetFontColor(color);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EU_ConcoleFrame::EU_ConcoleFrame(LoadConstructor value) :
UIFrame(value)
{
}
//----------------------------------------------------------------------------
void EU_ConcoleFrame::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(EU_ConcoleFrame, source);
}
//----------------------------------------------------------------------------
void EU_ConcoleFrame::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void EU_ConcoleFrame::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool EU_ConcoleFrame::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EU_ConcoleFrame::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(EU_ConcoleFrame, target);
}
//----------------------------------------------------------------------------
int EU_ConcoleFrame::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------