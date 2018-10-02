// PX2EU_ContentFrame.cpp

#include "PX2EU_ContentFrame.hpp"
#include "PX2UISkinManager.hpp"
#include "PX2UIComboBox.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2EU_WebFrame.hpp"
#include "PX2EU_StageFrame.hpp"
#include "PX2StringHelp.hpp"
#include "PX2EditorEventType.hpp"
#include "PX2LogicES.hpp"
#include <iostream>
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, EU_ContentFrame);
PX2_IMPLEMENT_STREAM(EU_ContentFrame);
PX2_IMPLEMENT_FACTORY(EU_ContentFrame);

//----------------------------------------------------------------------------
EU_ContentFrame::EU_ContentFrame()
{
	mTheNode = 0;

	ComeInEventWorld();
}
//----------------------------------------------------------------------------
void EU_ContentFrame::SetActive(bool act)
{
	UIFrame::SetActivate(act);
}
//----------------------------------------------------------------------------
EU_ContentFrame::~EU_ContentFrame()
{
}
//----------------------------------------------------------------------------
void EU_ContentFrame::OnEvent(Event *ent)
{
	if (EditorEventSpace::IsEqual(ent, EditorEventSpace::Copy))
	{
		if (IsActivated())
		{
			UIWebFrame *frame = DynamicCast<UIWebFrame>(mTheNode);
			if (frame)
			{
				frame->Copy();
			}
		}
	}
	else if (EditorEventSpace::IsEqual(ent, EditorEventSpace::Paste))
	{
		if (IsActivated())
		{
			UIWebFrame *frame = DynamicCast<UIWebFrame>(mTheNode);
			if (frame)
			{
				frame->Paste();
			}
		}
	}
	else if (EditorEventSpace::IsEqual(ent, EditorEventSpace::Undo))
	{
		if (IsActivated())
		{
			UIWebFrame *frame = DynamicCast<UIWebFrame>(mTheNode);
			if (frame)
			{
				frame->Undo();
			}
		}
	}
	else if (EditorEventSpace::IsEqual(ent, EditorEventSpace::Redo))
	{
		if (IsActivated())
		{
			UIWebFrame *frame = DynamicCast<UIWebFrame>(mTheNode);
			if (frame)
			{
				frame->ReDo();
			}
		}
	}
	else if (LogicES::IsEqual(ent, LogicES::RefreshGeneratedScript))
	{
		const std::string &name = GetName();
		if ("CodeView" == name)
		{
			std::string dataStr = ent->GetDataStr0();
			SetContString(dataStr);
		}
	}
}
//----------------------------------------------------------------------------
void EU_ContentFrame::SetContString(const std::string &str)
{
	mContentType = EU_ContentFrame::CT_STRING;
	mContentFilename = "";

	EU_WebFrame *webFrame = new0 EU_WebFrame();

	std::string htmlContent;

	std::string htmlExt = "index_lua.html";
	std::string htmlPath = "DataNIRVANAwx/codemirror/demo/";

	htmlPath += htmlExt;

	if (PX2_RM.LoadBuffer(htmlPath, htmlContent))
	{
		PX2_RM.ClearRes(htmlPath);

		std::string findKey = "PhoenixContent";
		auto pos = htmlContent.find("PhoenixContent");
		if (pos != htmlContent.npos)
		{
			htmlContent.replace(pos, findKey.length(), str);

			bool ret = FileIO::Save("DataNIRVANAwx/codemirror/demo/indexTemp.html", false, (int)htmlContent.length(),
				htmlContent.c_str());
			PX2_UNUSED(ret);
		}

		webFrame->LoadURL("file:///DataNIRVANAwx/codemirror/demo/indexTemp.html");
	}

	webFrame->SetUpdateToTex(true);
	mTheNode = webFrame;

	if (mTheNode)
	{
		AttachChild(mTheNode);
		mTheNode->SetAnchorHor(0.0, 1.0);
		mTheNode->SetAnchorVer(0.0, 1.0);

		Update(0.0f, 0.0f);
	}
}
//----------------------------------------------------------------------------
void EU_ContentFrame::SetContAcceptKeyboardInput(bool accept)
{
	UIWebFrame *webFrame = DynamicCast<UIWebFrame>(mTheNode);
	if (webFrame)
	{
		webFrame->SetAcceptKeyboardInput(accept);
	}
}
//----------------------------------------------------------------------------
void EU_ContentFrame::SetCont(ContentType type, const std::string &filename)
{
	mContentType = type;
	mContentFilename = filename;

	std::string outPath;
	std::string extStr;
	StringHelp::SplitFilename(filename, outPath, extStr);

	if (CT_TEXT == type)
	{
		std::string str;
		if (PX2_RM.LoadBuffer(filename, str))
		{
			PX2_RM.ClearRes(filename);

			EU_WebFrame *webFrame = new0 EU_WebFrame();

			std::string htmlContent;

			std::string htmlExt = "index_lua.html";
			std::string htmlPath = "DataNIRVANAwx/codemirror/demo/";

			if ("txt" == extStr)
				htmlExt = "index_txt.html";
			else if ("lua" == extStr)
				htmlExt = "index_lua.html";
			else if ("xml" == extStr)
				htmlExt = "index_xml.html";

			htmlPath += htmlExt;

			if (PX2_RM.LoadBuffer(htmlPath, htmlContent))
			{
				std::string findKey = "PhoenixContent";
				auto pos = htmlContent.find("PhoenixContent");
				if (pos != htmlContent.npos)
				{
					htmlContent.replace(pos, findKey.length(), str);

					bool ret = FileIO::Save("DataNIRVANAwx/codemirror/demo/indexTemp.html", true, (int)htmlContent.length(),
						htmlContent.c_str());
					PX2_UNUSED(ret);
				}

				webFrame->LoadURL("file:///DataNIRVANAwx/codemirror/demo/indexTemp.html");
			}

			webFrame->SetUpdateToTex(true);
			mTheNode = webFrame;
		}
	}
	else if (CT_PREVIEW == type)
	{
		EU_CanvasPreView *stageFrame = new0 EU_CanvasPreView();
		stageFrame->SetFilename(filename);
		mTheNode = stageFrame;
	}

	if (mTheNode)
	{
		AttachChild(mTheNode);
		mTheNode->SetAnchorHor(0.0, 1.0);
		mTheNode->SetAnchorVer(0.0, 1.0);

		Update(0.0f, 0.0f);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EU_ContentFrame::EU_ContentFrame(LoadConstructor value) :
UIFrame(value)
{
}
//----------------------------------------------------------------------------
void EU_ContentFrame::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(EU_ContentFrame, source);
}
//----------------------------------------------------------------------------
void EU_ContentFrame::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void EU_ContentFrame::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool EU_ContentFrame::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EU_ContentFrame::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(EU_ContentFrame, target);
}
//----------------------------------------------------------------------------
int EU_ContentFrame::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------