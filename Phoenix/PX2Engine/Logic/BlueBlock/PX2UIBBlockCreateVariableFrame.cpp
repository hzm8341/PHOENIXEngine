// PX2UIBBlockCreateVariableFrame.cpp

#include "PX2UIBBlockCreateVariableFrame.hpp"
#include "PX2UIButton.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2UIEditBox.hpp"
#include "PX2LogicManager.hpp"
#include "PX2LogicES.hpp"
#include "PX2BBlockEvents.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, BUICreateVariableFrame);
PX2_IMPLEMENT_STREAM(BUICreateVariableFrame);
PX2_IMPLEMENT_FACTORY(BUICreateVariableFrame);

//----------------------------------------------------------------------------
BUICreateVariableFrame::BUICreateVariableFrame()
{
	CreateAddBackgroundPicBox(true);

	UIButton *butClose = new0 UIButton();
	AttachChild(butClose);
	butClose->SetSize(60.0f, 60.0f);
	butClose->SetName("ButClose");
	butClose->LocalTransform.SetTranslateY(-1.0f);
	butClose->SetAnchorHor(1.0f, 1.0f);
	butClose->SetAnchorVer(1.0f, 1.0f);
	butClose->SetPivot(1.0f, 1.0f);
	butClose->CreateAddText(PX2_LM_APP.GetValue("Close"));
	butClose->GetText()->SetFontColor(Float3::WHITE);
	butClose->SetMemUICallback(this,
		(UIFrame::MemUICallback)(&BUICreateVariableFrame::_ButCallback));

	UIFText *fText = new0 UIFText();
	AttachChild(fText);
	fText->LocalTransform.SetTranslateY(-1.0f);
	fText->SetAnchorHor(0.0f, 1.0f);
	fText->SetAnchorVer(1.0f, 1.0f);
	fText->SetAnchorParamVer(-40.0f, -40.0f);
	fText->GetText()->SetText(PX2_LM_APP.GetValue("InputVariableName"));

	mComboParamType = new0 UIComboBox();
	AttachChild(mComboParamType);
	mComboParamType->GetChooseList()->SetTextAlignLeftPos(0.0f);
	mComboParamType->GetSelectButton()->SetStateColor(UIButtonBase::BS_NORMAL, Float3::MakeColor(200, 200, 200));
	mComboParamType->GetSelectButton()->SetStateColor(UIButtonBase::BS_HOVERED, Float3::MakeColor(200, 200, 200));
	mComboParamType->GetSelectButton()->SetStateColor(UIButtonBase::BS_PRESSED, Float3::MakeColor(250, 250, 250));
	mComboParamType->LocalTransform.SetTranslateY(-1.0f);
	mComboParamType->SetAnchorHor(0.0f, 1.0f);
	mComboParamType->SetAnchorVer(1.0f, 1.0f);
	mComboParamType->SetAnchorParamVer(-100.0f, -100.0f);
	mComboParamType->AddChooseStr("int");
	mComboParamType->AddChooseStr("float");
	mComboParamType->AddChooseStr("char");
	mComboParamType->AddChooseStr("string");
	mComboParamType->AddChooseStr("bool");
	mComboParamType->Choose(0);
	mComboParamType->SetChooseListHeightSameWithChooses();
	mComboParamType->SetMemUICallback(this,
		(UIFrame::MemUICallback)(&BUICreateVariableFrame::_ButCallback));

	mEditBoxVariable = new0 UIEditBox();
	AttachChild(mEditBoxVariable);
	mEditBoxVariable->GetBackPicBox()->SetColor(Float3::MakeColor(200, 200, 200));
	mEditBoxVariable->LocalTransform.SetTranslateY(-1.0f);
	mEditBoxVariable->SetAnchorHor(0.0f, 1.0f);
	mEditBoxVariable->SetAnchorParamHor(50.0f, -50.0f);
	mEditBoxVariable->SetAnchorVer(0.5f, 0.5f);

	UIButton *butOK = new0 UIButton();
	AttachChild(butOK);
	butOK->SetName("ButOK");
	butOK->LocalTransform.SetTranslateY(-1.0f);
	butOK->SetSize(180.0f, 60.0f);
	butOK->SetAnchorHor(0.5f, 0.5f);
	butOK->SetAnchorParamHor(-120.0f, -120.0f);
	butOK->SetAnchorVer(0.0f, 0.0f);
	butOK->SetAnchorParamVer(60.0f, 60.0f);
	butOK->CreateAddText(PX2_LM_APP.GetValue("OK"));
	butOK->GetText()->SetFontColor(Float3::WHITE);
	butOK->SetMemUICallback(this,
		(UIFrame::MemUICallback)(&BUICreateVariableFrame::_ButCallback));

	UIButton *butCancel = new0 UIButton();
	AttachChild(butCancel);
	butCancel->SetName("ButCancel");
	butCancel->LocalTransform.SetTranslateY(-1.0f);
	butCancel->SetSize(180.0f, 60.0f);
	butCancel->SetAnchorHor(0.5f, 0.5f);
	butCancel->SetAnchorParamHor(120.0f, 120.0f);
	butCancel->SetAnchorVer(0.0f, 0.0f);
	butCancel->SetAnchorParamVer(60.0f, 60.0f);
	butCancel->CreateAddText(PX2_LM_APP.GetValue("Cancel"));
	butCancel->GetText()->SetFontColor(Float3::WHITE);
	butCancel->SetMemUICallback(this,
		(UIFrame::MemUICallback)(&BUICreateVariableFrame::_ButCallback));
}
//----------------------------------------------------------------------------
BUICreateVariableFrame::~BUICreateVariableFrame()
{
}
//----------------------------------------------------------------------------
void BUICreateVariableFrame::_ButCallback(UIFrame *frame, UICallType type)
{
	const std::string &frameName = frame->GetName();
	UIButton *but = DynamicCast<UIButton>(frame);
	PX2_UNUSED(but);

	if (UICT_RELEASED == type)
	{
		if ("ButOK" == frameName)
		{
			const std::string &text = mEditBoxVariable->GetText();
			if (!text.empty())
			{
				FunObject *funObj = PX2_LOGICM.GetParam(text);
				if (!funObj)
				{
					PX2_LOGICM.BeginAddParam(text, FunObject::PT_VARIABLE);
					std::string chooseStr = mComboParamType->GetChooseStr();
					if ("int" == chooseStr)
					{
						PX2_LOGICM.AddInputInt("val", 0);
					}
					else if ("float" == chooseStr)
					{
						PX2_LOGICM.AddInputFloat("val", 0.0f);
					}
					else if ("char" == chooseStr)
					{
						PX2_LOGICM.AddInputChar("val", 65);
					}
					else if ("string" == chooseStr)
					{
						PX2_LOGICM.AddInputString("val", "");
					}
					else if ("bool" == chooseStr)
					{
						PX2_LOGICM.AddInputBool("val", "");
					}
					PX2_LOGICM.EndAddFun_Param("ParamCreated");

					funObj = PX2_LOGICM.GetParam(text);

					if (funObj)
					{
						Show(false);

						Event *entCV = BBlockES::CreateEventX(BBlockES::CreateVariable);
						entCV->SetData<FunObject*>(funObj);
						PX2_EW.BroadcastingLocalEvent(entCV);

						Event *ent = BBlockES::CreateEventX(BBlockES::ShowCreateVaiableFrame);
						ent->SetData<bool>(false);
						PX2_EW.BroadcastingLocalEvent(ent);
					}
				}
			}
		}
		else if ("ButCancel" == frameName)
		{
			Show(false);

			Event *ent = BBlockES::CreateEventX(BBlockES::ShowCreateVaiableFrame);
			ent->SetData<bool>(false);
			PX2_EW.BroadcastingLocalEvent(ent);
		}
		else if ("ButClose" == frameName)
		{
			Show(false);

			Event *ent = BBlockES::CreateEventX(BBlockES::ShowCreateVaiableFrame);
			ent->SetData<bool>(false);
			PX2_EW.BroadcastingLocalEvent(ent);
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
BUICreateVariableFrame::BUICreateVariableFrame(LoadConstructor value) :
UIFrame(value)
{
}
//----------------------------------------------------------------------------
void BUICreateVariableFrame::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(BUICreateVariableFrame, source);
}
//----------------------------------------------------------------------------
void BUICreateVariableFrame::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void BUICreateVariableFrame::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool BUICreateVariableFrame::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void BUICreateVariableFrame::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(BUICreateVariableFrame, target);
}
//----------------------------------------------------------------------------
int BUICreateVariableFrame::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------