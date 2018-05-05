// PX2UIBBlockPanels.cpp

#include "PX2UIBBlockPanels.hpp"
#include "PX2LogicES.hpp"
#include "PX2BBlockEvents.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2UIBBlockPanelCont.hpp"
#include "PX2UIBBlockPanelMusic.hpp"
#include "PX2BBManager.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, UIBBlockPanels);
PX2_IMPLEMENT_STREAM(UIBBlockPanels);
PX2_IMPLEMENT_FACTORY(UIBBlockPanels);

//----------------------------------------------------------------------------
UIBBlockPanels::UIBBlockPanels()
{
	BUIBlocksPanelCont *panel = new0 BUIBlocksPanelCont();
	mBlocksPanel["Ctrl"] = panel;
	AttachChild(panel);
	panel->LocalTransform.SetTranslateY(-1.0f);
	panel->SetAnchorHor(0.0f, 1.0f);
	panel->SetAnchorVer(0.0f, 1.0f);
	panel->SetCatalogue("Ctrl");
	panel->SetName("Ctrl");
	panel->Show(false);

	panel = new0 BUIBlocksPanelCont();
	mBlocksPanel["Test"] = panel;
	AttachChild(panel);
	panel->LocalTransform.SetTranslateY(-1.0f);
	panel->SetAnchorHor(0.0f, 1.0f);
	panel->SetAnchorVer(0.0f, 1.0f);
	panel->SetCatalogue("Test");
	panel->SetName("Test");
	panel->Show(false);

	panel = new0 BUIBlocksPanelCont();
	mBlocksPanel["Math"] = panel;
	AttachChild(panel);
	panel->LocalTransform.SetTranslateY(-1.0f);
	panel->SetAnchorHor(0.0f, 1.0f);
	panel->SetAnchorVer(0.0f, 1.0f);
	panel->SetCatalogue("Math");
	panel->SetName("Math");
	panel->Show(false);

	// param
	UITabFramePtr tabFrameParam = new0 UITabFrame();

	BUIBlocksPanelCont *frameParam = new0 BUIBlocksPanelCont("Param");
	frameParam->SetCatalogue("Param");
	tabFrameParam->AddTab("Param", PX2_LM_APP.GetValue("Function"), frameParam);
	BBlock::_SetFont(tabFrameParam->GetTabButton("Param")->GetText());

	BUIBlocksPanelCont *frameParamCreated = new0 BUIBlocksPanelCont("ParamCreated");
	frameParamCreated->SetCatalogue("ParamCreated");
	tabFrameParam->AddTab("ParamCreated", PX2_LM_APP.GetValue("Param"), frameParamCreated);
	tabFrameParam->SetActiveTab("Param");
	BBlock::_SetFont(tabFrameParam->GetTabButton("ParamCreated")->GetText());

	mBlocksPanel["Param"] = tabFrameParam;
	AttachChild(tabFrameParam);
	tabFrameParam->SetAnchorHor(0.0f, 1.0f);
	tabFrameParam->SetAnchorVer(0.0f, 1.0f);
	tabFrameParam->SetTabBarHeight(40.0f);
	tabFrameParam->SetTabHeight(40.0f);
	tabFrameParam->SetName("Param");
	tabFrameParam->Show(false);

	panel = new0 BUIBlocksPanelCont();
	mBlocksPanel["Event"] = panel;
	AttachChild(panel);
	panel->LocalTransform.SetTranslateY(-1.0f);
	panel->SetAnchorHor(0.0f, 1.0f);
	panel->SetAnchorVer(0.0f, 1.0f);
	panel->SetCatalogue("Event");
	panel->SetName("Event");
	panel->Show(false);

	// Func
	panel = new0 BUIBlocksPanelCont();
	mBlocksPanel["Func"] = panel;
	AttachChild(panel);
	panel->LocalTransform.SetTranslateY(-1.0f);
	panel->SetAnchorHor(0.0f, 1.0f);
	panel->SetAnchorVer(0.0f, 1.0f);
	panel->SetCatalogue("Func");
	panel->SetName("Func");
	panel->Show(false);

	// System
	panel = new0 BUIBlocksPanelCont();
	mBlocksPanel["System"] = panel;
	AttachChild(panel);
	panel->LocalTransform.SetTranslateY(-1.0f);
	panel->SetAnchorHor(0.0f, 1.0f);
	panel->SetAnchorVer(0.0f, 1.0f);
	panel->SetCatalogue("System");
	panel->SetName("System");
	panel->Show(false);

	// 扩展
	panel = new0 BUIBlocksPanelCont();
	mBlocksPanel["Extend"] = panel;
	AttachChild(panel);
	panel->LocalTransform.SetTranslateY(-1.0f);
	panel->SetAnchorHor(0.0f, 1.0f);
	panel->SetAnchorVer(0.0f, 1.0f);
	panel->SetCatalogue("Extend");
	panel->SetName("Extend");
	panel->Show(false);

	SetWidth(300.0f);
	SetWidget(true);

	SetChildNotPickRecursion(false);
	ComeInEventWorld();

	ShowPanel("Ctrl");
}
//----------------------------------------------------------------------------
UIBBlockPanels::~UIBBlockPanels()
{
}
//----------------------------------------------------------------------------
void UIBBlockPanels::OnEvent(Event *ent)
{
	if (BBlockES::IsEqual(ent, BBlockES::ShowBlockCata))
	{
		std::string cataname = ent->GetData<std::string>();
		if (!cataname.empty())
			ShowPanel(cataname);
	}
}
//----------------------------------------------------------------------------
void UIBBlockPanels::ShowPanel(const std::string &panelName)
{
	auto it = mBlocksPanel.begin();
	for (; it != mBlocksPanel.end(); it++)
	{
		if (panelName == it->second->GetName())
		{
			it->second->Show(true);
		}
		else
		{
			it->second->Show(false);
		}
	}
}
//----------------------------------------------------------------------------
void UIBBlockPanels::OnSizeNodeNotPicked(const CanvasInputData &inputData)
{
	if (UIPT_RELEASED == inputData.PickType)
	{
		bool isSideCata = PX2_BBM.IsSideCata();
		if (isSideCata)
		{
			PX2_BBM.ShowBlockCata("");
		}
	}

	UIFrame::OnSizeNodeNotPicked(inputData);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
UIBBlockPanels::UIBBlockPanels(LoadConstructor value) :
UIFrame(value)
{
}
//----------------------------------------------------------------------------
void UIBBlockPanels::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(UIBBlockPanels, source);
}
//----------------------------------------------------------------------------
void UIBBlockPanels::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void UIBBlockPanels::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool UIBBlockPanels::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void UIBBlockPanels::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(UIBBlockPanels, target);
}
//----------------------------------------------------------------------------
int UIBBlockPanels::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------