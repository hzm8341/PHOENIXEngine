// PX2EU_SimuFrame.cpp

#include "PX2EU_SimuFrame.hpp"
#include "PX2UISkinManager.hpp"
#include "PX2UIComboBox.hpp"
#include "PX2Edit.hpp"
#include "PX2EU_Manager.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, EU_SimuFrame);
PX2_IMPLEMENT_STREAM(EU_SimuFrame);
PX2_IMPLEMENT_FACTORY(EU_SimuFrame);

//----------------------------------------------------------------------------
void _SimuComboBoxCallback(UIFrame *frame, UICallType type)
{
	UIComboBox *comboBox = DynamicCast<UIComboBox>(frame);
	if (comboBox)
	{
		const std::string &name = comboBox->GetName();
		std::string chooseStr = comboBox->GetChooseStr();

		if (UICT_COMBOBOX_CHOOSED == type)
		{
			if ("RenderView" == name)
			{
				if ("ViewProj" == chooseStr)
				{
					PX2_EDIT.SetSimuRenderViewMode(Edit::SRVM_PROJ);
				}
				else if ("ViewFull" == chooseStr)
				{
					PX2_EDIT.SetSimuRenderViewMode(Edit::SRVM_FULL);
				}
			}

		}
	}
}
//----------------------------------------------------------------------------
EU_SimuFrame::EU_SimuFrame()
{
	mToolFrame = new0 UIFrame();
	mToolFrame->SetChildPickOnlyInSizeRange(false);
	AttachChild(mToolFrame);
	mToolFrame->LocalTransform.SetTranslateY(-1.0f);
	UIPicBox *picBox = mToolFrame->CreateAddBackgroundPicBox();
	picBox->SetColor(PX2_UISM.Color_ToolBar);
	mToolFrame->SetAnchorHor(0.0f, 1.0f);
	mToolFrame->SetAnchorVer(1.0f, 1.0f);
	mToolFrame->SetPivot(0.5f, 1.0f);
	mToolFrame->SetSize(Sizef(0.0f, PX2_UISM.Size_ToolBar));

	Sizef butSize = Sizef(PX2_UISM.Size_ToolBarBut, PX2_UISM.Size_ToolBarBut);
	Sizef spliterSize = Sizef(4.0f, PX2_UISM.Size_ToolBar - 2);

	float comboWidth = 100.0f;

	float addButPos = 0.0f;
	addButPos += (spliterSize.Width / 2.0f + comboWidth / 2.0f);

	UIComboBox *renderViewComboBox = new0 UIComboBox();
	mToolFrame->AttachChild(renderViewComboBox);
	renderViewComboBox->LocalTransform.SetTranslateY(-1.0f);
	renderViewComboBox->SetAnchorHor(0.0f, 0.0f);
	renderViewComboBox->SetAnchorVer(0.5f, 0.5f);
	renderViewComboBox->SetAnchorParamHor(addButPos, 0.0f);
	renderViewComboBox->SetSize(Sizef(comboWidth, butSize.Height));
	renderViewComboBox->SetName("RenderView");
	renderViewComboBox->AddChooseStr("ViewProj");
	renderViewComboBox->AddChooseStr("ViewFull");
	renderViewComboBox->SetChooseListHeightSameWithChooses();
	renderViewComboBox->SetTextColor(Float3::MakeColor(220, 220, 220));
	renderViewComboBox->GetSelectButton()->GetText()->SetFontScale(0.65f);
	renderViewComboBox->Choose(0);
	renderViewComboBox->AddUICallback(_SimuComboBoxCallback);

	mCanvasStageSimu = new0 EU_CanvasStageSimu();
	mCanvasStageSimu->LocalTransform.SetTranslateY(-1.0f);
	AttachChild(mCanvasStageSimu);
	mCanvasStageSimu->SetAnchorHor(0.0f, 1.0f);
	mCanvasStageSimu->SetAnchorVer(0.0f, 1.0f);
	mCanvasStageSimu->SetAnchorParamVer(0.0f, -PX2_UISM.Size_ToolBar);

	SetActivateSelfCtrled(false);
}
//----------------------------------------------------------------------------
EU_SimuFrame::~EU_SimuFrame()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EU_SimuFrame::EU_SimuFrame(LoadConstructor value) :
UIFrame(value)
{
}
//----------------------------------------------------------------------------
void EU_SimuFrame::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(EU_SimuFrame, source);
}
//----------------------------------------------------------------------------
void EU_SimuFrame::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void EU_SimuFrame::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool EU_SimuFrame::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EU_SimuFrame::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(EU_SimuFrame, target);
}
//----------------------------------------------------------------------------
int EU_SimuFrame::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------