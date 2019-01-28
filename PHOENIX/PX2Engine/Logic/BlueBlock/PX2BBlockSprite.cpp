// PX2BBlockSprite.cpp

#include "PX2BBlockSprite.hpp"
#include "PX2UIWebFrame.hpp"
#include "PX2BBlockSystem.hpp"
#include "PX2BBManager.hpp"
#include "PX2BBlockEvents.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2UIProgressBar.hpp"
#include "PX2Log.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, BBlockSprite);
PX2_IMPLEMENT_STREAM(BBlockSprite);
PX2_IMPLEMENT_FACTORY(BBlockSprite);

//----------------------------------------------------------------------------
BBlockSprite::BBlockSprite(SpriteType st) :
mLayerIndex(0),
mSpriteType(st),
mIsDragable(false),
mIsDoPickFrameObject(true),
mRoundCurDragingDirSimple(0),
mHorLayOutType(HLOT_CENTER),
mVerLayoutType(VLOT_CENTER),
mHorLayoutParam(0.0f),
mVerLayoutParam(0.0f),
mFixUpdateFPS(30),
mValue(0.0f)
{
	mScriptCtrl = new0 BBlockScriptGenController();
	AttachController(mScriptCtrl);

	std::string name = "BBlockSprite";
	if (ST_FRAME == mSpriteType)
	{
		name = "SFrame";
	}
	else if (ST_PICBOX == mSpriteType)
	{
		UIFPicBox *picBox = new0 UIFPicBox();
		mFrameObject = picBox;
		AttachChild(picBox);
		picBox->LocalTransform.SetTranslateY(-1.0f);
		picBox->SetAnchorHor(0.0f, 1.0f);
		picBox->SetAnchorVer(0.0f, 1.0f);
		picBox->GetUIPicBox()->SetTexture("Data/BlueBlock/images/ui/picbox.png");

		name = "SPicBox";
	}
	else if (ST_BUTTON == mSpriteType)
	{
		UIButton *but = new0 UIButton();
		mFrameObject = but;
		AttachChild(but);
		but->LocalTransform.SetTranslateY(-1.0f);
		but->SetAnchorHor(0.0f, 1.0f);
		but->SetAnchorVer(0.0f, 1.0f);
		but->SetStateColorDefaultWhite();
		but->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture("Data/BlueBlock/images/ui/button.png");

		SetSize(200.0f, 60.0f);

		name = "SButton";
	}
	else if (ST_TEXT == mSpriteType)
	{
		UIFText *text = new0 UIFText();
		mFrameObject = text;
		AttachChild(text);
		text->GetText()->SetAligns(TEXTALIGN_HCENTER | TEXTALIGN_VCENTER);
		text->GetText()->SetFont("Data/BlueBlock/fonts/font.ttf");
		text->LocalTransform.SetTranslateY(-1.0f);
		text->SetAnchorHor(0.0f, 1.0f);
		text->SetAnchorVer(0.0f, 1.0f);

		SetSize(100.0f, 40.0f);

		name = "SText";
	}
	else if (ST_EDITBOX == mSpriteType)
	{
		UIEditBox *editBox = new0 UIEditBox();
		AttachChild(editBox);
		mFrameObject = editBox;
		editBox->LocalTransform.SetTranslateY(-1.0f);
		editBox->SetAnchorHor(0.0f, 1.0f);
		editBox->SetAnchorVer(0.0f, 1.0f);
		editBox->GetBackPicBox()->GetUIPicBox()->SetTexture("Data/BlueBlock/images/ui/editbox.png");

		name = "SEditBox";
	}
	else if (ST_COMBOXBOX == mSpriteType)
	{
		UIComboBox *comboBox = new0 UIComboBox();
		AttachChild(comboBox);
		comboBox->GetChooseList()->SetTextAlignLeftPos(0.0f);
		mFrameObject = comboBox;
		comboBox->LocalTransform.SetTranslateY(-1.0f);
		comboBox->SetAnchorHor(0.0f, 1.0f);
		comboBox->SetAnchorVer(0.0f, 1.0f);

		SetSize(100.0, 30.0f);

		name = "SComboBox";
	}
	else if (ST_PROGRESS == mSpriteType)
	{
		UIProgressBar *pb = new0 UIProgressBar();
		AttachChild(pb);
		mFrameObject = pb;
		pb->LocalTransform.SetTranslateY(-1.0f);
		pb->SetAnchorHor(0.0f, 1.0f);
		pb->SetAnchorVer(0.0f, 1.0f);

		SetSize(200.0, 30.0f);

		name = "SProgress";
	}
	else if (ST_WEBVIEW == mSpriteType)
	{
		UIWebFrame *webFrame = new0 UIWebFrame();
		AttachChild(webFrame);
		mFrameObject = webFrame;
		SetSize(400.0f, 300.0f);
		webFrame->LocalTransform.SetTranslateY(-1.0f);
		webFrame->SetAnchorHor(0.0f, 1.0f);
		webFrame->SetAnchorVer(0.0f, 1.0f);
		webFrame->ShowNativeView(false);
		webFrame->SetUpdateToTex(true);
		webFrame->SetAcceptKeyboardInput(false);
		webFrame->LoadURL("http://www.phoenixcreate.org");

		SetChildPickOnlyInSizeRange(false);
		webFrame->SetChildPickOnlyInSizeRange(false);

		name = "SWebView";
	}
	else if (ST_ROUND == mSpriteType)
	{
		UIRound *round = new0 UIRound();
		AttachChild(round);
		mFrameObject = round;
		round->LocalTransform.SetTranslateY(-1.0f);
		round->SetAnchorHor(0.0f, 1.0f);
		round->SetAnchorVer(0.0f, 1.0f);
		SetChildPickOnlyInSizeRange(false);
		SetSize(200.0f, 200.0f);
		round->GetButton()->SetSize(80.0f, 80.0f);
		round->GetButton()->SetStateColorDefaultWhite();
		round->GetButton()->SetStateBrightness(UIButtonBase::BS_PRESSED, 1.2f);

		name = "SRound";
	}
	else if (ST_SLIDER == mSpriteType)
	{
		UISlider *slider = new0 UISlider();
		AttachChild(slider);
		mFrameObject = slider;
		slider->LocalTransform.SetTranslateY(-1.0f);
		slider->SetAnchorHor(0.0f, 1.0f);
		slider->SetAnchorVer(0.0f, 1.0f);
		slider->SetSliderLength(80.0f);

		UIFText *text = UIFText::New("UIFText");
		slider->AttachChild(text);
		text->SetAnchorHor(0.0f, 1.0f);
		text->SetAnchorVer(0.0f, 1.0f);
		text->GetText()->SetAligns(TEXTALIGN_HCENTER | TEXTALIGN_VCENTER);
		text->GetText()->SetText("Slider");

		DynamicCast<UIFText>(slider->GetObjectByName("UIFText"));

		SetChildPickOnlyInSizeRange(false);
		SetSize(400.0f, 60.0f);

		name = "Slider";
	}
	else if (ST_FRAMELIST == mSpriteType)
	{
		UIFrame *frame = new0 UIFrame();
		AttachChild(frame);
		mFrameObject = frame;
		frame->LocalTransform.SetTranslateY(-1.0f);
		frame->SetAnchorHor(0.0f, 1.0f);
		frame->SetAnchorVer(0.0f, 1.0f);

		name = "SFrameList";
	}
	else if (ST_ARDUINO == mSpriteType)
	{
		UIFPicBox *picBox = new0 UIFPicBox();
		mFrameObject = picBox;
		AttachChild(picBox);
		picBox->LocalTransform.SetTranslateY(-1.0f);
		picBox->SetAnchorHor(0.0f, 1.0f);
		picBox->SetAnchorVer(0.0f, 1.0f);
		picBox->GetUIPicBox()->SetTexture("Data/BlueBlock/images/ui/arduino.png");

		mScriptCtrl->GetLFile()->SetPlatformType(PT_ARDUINO);

		name = "Arduino";
	}
	else if (ST_PHOENIXFRAME == mSpriteType)
	{
		UIFPicBox *picBox = new0 UIFPicBox();
		mFrameObject = picBox;
		AttachChild(picBox);
		picBox->LocalTransform.SetTranslateY(-1.0f);
		picBox->SetAnchorHor(0.0f, 1.0f);
		picBox->SetAnchorVer(0.0f, 1.0f);
		picBox->GetUIPicBox()->SetTexture("Data/BlueBlock/images/ui/phoenixframe.png");

		SetSize(200.0f, 200.0f);

		name = "PhoenixFrame";
	}
	else if (ST_EAI == mSpriteType)
	{
		SetSize(200.0f, 200.0f);

		name = "EAIRobot";
	}

	setLayer(mLayerIndex);

	_SetFrameCallback();

	SetDoPickFrameObject(false);
	SetName(name);
	SetWidget(true);

	mRotate = APoint(0.0f, 0.0f, 0.0f);
	mScale = APoint::UNIT;

	ComeInEventWorld();

	RegistToScriptSystem();

	setFixUpdateFPS(10);
}
//----------------------------------------------------------------------------
BBlockSprite::~BBlockSprite()
{
	GoOutEventWorld();
}
//----------------------------------------------------------------------------
void BBlockSprite::_SetFrameCallback()
{
	if (ST_FRAME == mSpriteType)
	{
	}
	else if (ST_PICBOX == mSpriteType)
	{
	}
	else if (ST_TEXT == mSpriteType)
	{
	}
	else if (ST_BUTTON == mSpriteType)
	{
		UIButton *but = DynamicCast<UIButton>(mFrameObject);
		if (but)
		{
			but->SetMemUICallback(this,
				(UIFrame::MemUICallback)(&BBlockSprite::_UICallback));
		}
	}
	else if (ST_COMBOXBOX == mSpriteType)
	{
		UIComboBox *comboBox = DynamicCast<UIComboBox>(mFrameObject);
		if (comboBox)
		{
			comboBox->SetMemUICallback(this,
				(UIFrame::MemUICallback)(&BBlockSprite::_UICallback));
		}
	}
	else if (ST_WEBVIEW == mSpriteType)
	{
		UIWebFrame *webFrame = DynamicCast<UIWebFrame>(mFrameObject);
		SetChildPickOnlyInSizeRange(false);
		webFrame->SetChildPickOnlyInSizeRange(false);
	}
	else if (ST_ROUND == mSpriteType)
	{
		UIRound *round = DynamicCast<UIRound>(mFrameObject);
		if (round)
		{
			round->SetMemUICallback(this,
				(UIFrame::MemUICallback)(&BBlockSprite::_UICallback));
		}
	}
	else if (ST_SLIDER == mSpriteType)
	{
		UISlider *round = DynamicCast<UISlider>(mFrameObject);
		if (round)
		{
			round->SetMemUICallback(this,
				(UIFrame::MemUICallback)(&BBlockSprite::_UICallback));
		}
	}
	else if (ST_FRAMELIST == mSpriteType)
	{
	}
}
//----------------------------------------------------------------------------
BBlockSprite *BBlockSprite::New(SpriteType st)
{
	return new0 BBlockSprite(st);
}
//----------------------------------------------------------------------------
std::string BBlockSprite::GetSpriteTypeStr() const
{
	if (ST_FRAME == mSpriteType)
		return "ST_FRAME";
	else if (ST_PICBOX == mSpriteType)
		return "ST_PICBOX";
	else if (ST_BUTTON == mSpriteType)
		return "ST_BUTTON";
	else if (ST_TEXT == mSpriteType)
		return "ST_TEXT";
	else if (ST_EDITBOX == mSpriteType)
		return "ST_EDITBOX";
	else if (ST_COMBOXBOX == mSpriteType)
		return "ST_COMBOXBOX";
	else if (ST_WEBVIEW == mSpriteType)
		return "ST_WEBVIEW";
	else if (ST_ROUND == mSpriteType)
		return "ST_ROUND";
	else if (ST_SLIDER == mSpriteType)
		return "ST_SLIDER";
	else if (ST_FRAMELIST == mSpriteType)
		return "ST_FRAMELIST";
	else if (ST_ARDUINO == mSpriteType)
		return "ST_ARDUINO";
	else if (ST_PHOENIXFRAME == mSpriteType)
		return "ST_PHOENIXFRAME";

	return "";
}
//----------------------------------------------------------------------------
void BBlockSprite::SetHorLayOutType(HorLayOutType type)
{
	mHorLayOutType = type;

	if (HLOT_LEFT == mHorLayOutType)
	{
		SetAnchorHor(0.0, 0.0);
	}
	else if (HLOT_RIGHT == mHorLayOutType)
	{
		SetAnchorHor(1.0f, 1.0f);
	}
	else if (HLOT_CENTER == mHorLayOutType)
	{
		SetAnchorHor(0.5f, 0.5f);
	}
	else if (HLOT_STRATCH == mHorLayOutType)
	{
		SetAnchorHor(0.0f, 1.0f);
	}
}
//----------------------------------------------------------------------------
BBlockSprite::HorLayOutType BBlockSprite::GetHorLayOutType() const
{
	return mHorLayOutType;
}
//----------------------------------------------------------------------------
void BBlockSprite::SetLayoutParamHor(float param0)
{
	mHorLayoutParam = param0;
	SetAnchorParamHor(param0, param0);
}
//----------------------------------------------------------------------------
float BBlockSprite::GetLayoutParamHor() const
{
	return mHorLayoutParam;
}
//----------------------------------------------------------------------------
void BBlockSprite::SetVerLayoutType(VerLayoutType type)
{
	mVerLayoutType = type;

	if (VLOT_BOTTOM == mVerLayoutType)
	{
		SetAnchorVer(0.0, 0.0);
	}
	else if (VLOT_TOP == mVerLayoutType)
	{
		SetAnchorVer(1.0f, 1.0f);
	}
	else if (VLOT_CENTER == mVerLayoutType)
	{
		SetAnchorVer(0.5f, 0.5f);
	}
	else if (VLOT_STRATCH == mVerLayoutType)
	{
		SetAnchorVer(0.0f, 1.0f);
	}
}
//----------------------------------------------------------------------------
BBlockSprite::VerLayoutType BBlockSprite::GetVerLayoutType() const
{
	return mVerLayoutType;
}
//----------------------------------------------------------------------------
void BBlockSprite::SetLayoutParamVer(float param0)
{
	mVerLayoutParam = param0;
	SetAnchorParamVer(param0, param0);
}
//----------------------------------------------------------------------------
float BBlockSprite::GetLayoutParamVer() const
{
	return mVerLayoutParam;
}
//----------------------------------------------------------------------------
void BBlockSprite::SetName(const std::string &name)
{
	UIFrame::SetName(name);

	if (mScriptCtrl)
	{
		std::string ctrlName = "BBlockScriptGenController_" + name;
		mScriptCtrl->SetName(ctrlName);
	}
}
//----------------------------------------------------------------------------
void BBlockSprite::Enable(bool enable)
{
	UIFrame::Enable(enable);

	if (mScriptCtrl)
	{
		mScriptCtrl->Enable(enable);
	}
}
//----------------------------------------------------------------------------
void BBlockSprite::SetDragable(bool dragable)
{
	mIsDragable = dragable;
}
//----------------------------------------------------------------------------
void BBlockSprite::SetDoPickFrameObject(bool pick)
{
	mIsDoPickFrameObject = pick;

	if (mFrameObject)
	{
		mFrameObject->SetDoPick(pick);
	}
}
//----------------------------------------------------------------------------
void BBlockSprite::SetLookImage(const std::string &image, bool isUse9Grid)
{
	if (ST_PICBOX == mSpriteType)
	{
		UIFPicBox *picBox = DynamicCast<UIFPicBox>(mFrameObject);
		if (picBox)
		{
			picBox->GetUIPicBox()->SetTexture(image);
			if (isUse9Grid)
				picBox->GetUIPicBox()->SetPicBoxType(UIPicBox::PBT_NINE);
			else
				picBox->GetUIPicBox()->SetPicBoxType(UIPicBox::PBT_NORMAL);
		}
	}
	else if (ST_BUTTON == mSpriteType)
	{
		UIButton *but = DynamicCast<UIButton>(mFrameObject);
		if (but)
		{
			but->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture(image);
			if (isUse9Grid)
				but->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetPicBoxType(
				UIPicBox::PBT_NINE);
			else
				but->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetPicBoxType(
				UIPicBox::PBT_NORMAL);
		}
	}
	else if (ST_ROUND == mSpriteType)
	{
		UIRound *round = DynamicCast<UIRound>(mFrameObject);
		if (round)
		{
			round->GetBack()->GetUIPicBox()->SetTexture(image);
			if (isUse9Grid)
				round->GetBack()->GetUIPicBox()->SetPicBoxType(
				UIPicBox::PBT_NINE);
			else
				round->GetBack()->GetUIPicBox()->SetPicBoxType(
				UIPicBox::PBT_NORMAL);
		}
	}
	else if (ST_PROGRESS == mSpriteType)
	{
		UIProgressBar *pb = DynamicCast<UIProgressBar>(mFrameObject);
		if (pb)
		{
			pb->GetBackPicBox()->GetUIPicBox()->SetTexture(image);
		}
	}
	else if (ST_SLIDER == mSpriteType)
	{
		UISlider *sd = DynamicCast<UISlider>(mFrameObject);
		if (sd)
		{
			sd->GetFPicBoxBack()->GetUIPicBox()->SetPicBoxType(
				UIPicBox::PBT_NINE);
			sd->GetFPicBoxBack()->GetUIPicBox()->SetTexCornerSize(12.0f, 12.0f,
				12.0f, 12.0f);
			sd->GetFPicBoxBack()->GetUIPicBox()->SetTexture(image);
		}
	}
}
//----------------------------------------------------------------------------
void BBlockSprite::SetLookImage1(const std::string &image, bool isUse9Grid)
{
	if (ST_BUTTON == mSpriteType)
	{
		UIButton *but = DynamicCast<UIButton>(mFrameObject);
		if (but)
		{
			if (!image.empty())
			{
				but->SetButType(UIButtonBase::BT_PICBOXSWAP);

				UIPicBox *picNormal = but->GetPicBoxAtState(UIButtonBase::BS_NORMAL);

				but->GetPicBoxAtState(UIButtonBase::BS_PRESSED)->SetTexture(image);
				if (isUse9Grid)
					but->GetPicBoxAtState(UIButtonBase::BS_PRESSED)->SetPicBoxType(
					UIPicBox::PBT_NINE);
				else
					but->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetPicBoxType(
					UIPicBox::PBT_NORMAL);

				UIPicBox *picHoveredCopy = DynamicCast<UIPicBox>(picNormal->Copy(""));
				but->SetPicBox(UIButtonBase::BS_HOVERED, picHoveredCopy);
			}
			else
			{
				but->SetButType(UIButtonBase::BT_COLOR);
			}
		}
	}
	else if (ST_ROUND == mSpriteType)
	{
		UIRound *round = DynamicCast<UIRound>(mFrameObject);
		if (round)
		{
			round->GetButton()->GetPicBoxAtState(UIButtonBase::BS_NORMAL)
				->SetTexture(image);
			round->GetButton()->GetPicBoxAtState(UIButtonBase::BS_HOVERED)
				->SetTexture(image);
			round->GetButton()->GetPicBoxAtState(UIButtonBase::BS_PRESSED)
				->SetTexture(image);

			if (isUse9Grid)
			{
				round->GetButton()->GetPicBoxAtState(UIButtonBase::BS_NORMAL)
					->SetPicBoxType(UIPicBox::PBT_NINE);
				round->GetButton()->GetPicBoxAtState(UIButtonBase::BS_HOVERED)
					->SetPicBoxType(UIPicBox::PBT_NINE);
				round->GetButton()->GetPicBoxAtState(UIButtonBase::BS_PRESSED)
					->SetPicBoxType(UIPicBox::PBT_NINE);
			}
			else
			{
				round->GetButton()->GetPicBoxAtState(UIButtonBase::BS_NORMAL)
					->SetPicBoxType(UIPicBox::PBT_NORMAL);
				round->GetButton()->GetPicBoxAtState(UIButtonBase::BS_HOVERED)
					->SetPicBoxType(UIPicBox::PBT_NORMAL);
				round->GetButton()->GetPicBoxAtState(UIButtonBase::BS_PRESSED)
					->SetPicBoxType(UIPicBox::PBT_NORMAL);
			}
			round->AutoMakeSizeFixable();
		}
	}
	else if (ST_PROGRESS == mSpriteType)
	{
		UIProgressBar *pb = DynamicCast<UIProgressBar>(mFrameObject);
		if (pb)
		{
			pb->GetProgressPicBox()->GetUIPicBox()->SetTexture(image);
		}
	}
	else if (ST_SLIDER == mSpriteType)
	{
		UISlider *sd = DynamicCast<UISlider>(mFrameObject);
		if (sd)
		{
			if (isUse9Grid)
			{
				sd->GetButSlider()->GetPicBoxAtState(
					UIButtonBase::BS_NORMAL)->SetPicBoxType(UIPicBox::PBT_NINE);
			}
			else
			{
				sd->GetButSlider()->GetPicBoxAtState(
					UIButtonBase::BS_NORMAL)->SetPicBoxType(UIPicBox::PBT_NORMAL);
			}

			sd->GetButSlider()->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture(image);
			sd->GetButSlider()->AutoMakeSizeFixable();
		}
	}
}
//----------------------------------------------------------------------------
void BBlockSprite::AutoMakeSizeFixable()
{
	UIFrame *frame = mFrameObject;
	if (frame)
	{
		frame->AutoMakeSizeFixable();
	}
}
//----------------------------------------------------------------------------
void BBlockSprite::OnEvent(Event *ent)
{
	if (BBlockES::IsEqual(ent, BBlockES::Run))
	{
		bool isRun = ent->GetData<bool>();
		SetDoPickFrameObject(isRun);
	}
	else if (BBlockES::IsEqual(ent, BBlockES::PlayCamOK))
	{
		if (ST_WEBVIEW == mSpriteType)
		{
			std::string path = ent->GetData<std::string>();
			std::string pathAll = "http://" + path + ":8080/javascript_simple.html";

			PX2_LOG_INFO("play cam ok:%s", pathAll.c_str());
			setURL(pathAll);
		}
	}
}
//----------------------------------------------------------------------------
void BBlockSprite::UpdateWorldData(double applicationTime, double elapsedTime)
{
	UIFrame::UpdateWorldData(applicationTime, elapsedTime);

	if (mIsPlayingLook)
	{
		if (mLooks.empty())
			return;

		mLookPlayedTime += (float)elapsedTime;
		int numLooks = (int)mLooks.size();
		int index = (int)(mLookPlayedTime / mPlayLookSpeed);
		index = index%numLooks;
		SetCurLookIndex(index);
	}
}
//----------------------------------------------------------------------------
void BBlockSprite::OnWidgetPicked(const CanvasInputData &inputData)
{
	UIFrame::OnWidgetPicked(inputData);

	if (CanvasPickType::UIPT_PRESSED == inputData.PickType)
	{
		bool isRunning = PX2BBLOCK_SYS.IsRunning();
		if (!isRunning)
		{
			PX2_BBM.SetSelectSprite(this);
		}
	}
}
//----------------------------------------------------------------------------
void BBlockSprite::OnSizeNodeNotPicked(const CanvasInputData &inputData)
{
	UIFrame::OnSizeNodeNotPicked(inputData);

	if (CanvasPickType::UIPT_PRESSED == inputData.PickType)
	{
		BBlockSprite *selectSprite = PX2_BBM.GetSelectSprite();
		if (selectSprite == this)
		{
			PX2_BBM.SetSelectSprite(0);
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
BBlockSprite::BBlockSprite(LoadConstructor value) :
UIFrame(value),
mFixUpdateFPS(30),
mIsDragable(false),
mIsDoPickFrameObject(true),
mRoundCurDragingDirSimple(0),
mHorLayOutType(HLOT_CENTER),
mVerLayoutType(VLOT_CENTER),
mHorLayoutParam(0.0f),
mVerLayoutParam(0.0f),
mValue(0.0f)
{
}
//----------------------------------------------------------------------------
void BBlockSprite::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadEnum(mSpriteType);
	source.ReadPointer(mScriptCtrl);
	source.ReadPointer(mFrameObject);

	source.Read(mLayerIndex);
	source.ReadAggregate(mRotate);
	source.ReadAggregate(mScale);

	int numLooks = 0;
	source.Read(numLooks);
	mLooks.resize(numLooks);
	for (int i = 0; i < numLooks; i++)
	{
		if (mLooks[i])
			source.ResolveLink(mLooks[i]);
	}

	PX2_END_DEBUG_STREAM_LOAD(BBlockSprite, source);
}
//----------------------------------------------------------------------------
void BBlockSprite::Link(InStream& source)
{
	UIFrame::Link(source);

	if (mScriptCtrl)
		source.ResolveLink(mScriptCtrl);

	if (mFrameObject)
		source.ResolveLink(mFrameObject);
}
//----------------------------------------------------------------------------
void BBlockSprite::PostLink()
{
	UIFrame::PostLink();

	if (mScriptCtrl)
		mScriptCtrl->PostLink();

	if (mFrameObject)
		mFrameObject->PostLink();

	setLayer(mLayerIndex);

	RegistToScriptSystem();

	_SetFrameCallback();

	ComeInEventWorld();
}
//----------------------------------------------------------------------------
bool BBlockSprite::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		if (mScriptCtrl)
			target.Register(mScriptCtrl);

		if (mFrameObject)
			target.Register(mFrameObject);

		int numLooks = (int)mLooks.size();
		for (int i = 0; i < numLooks; i++)
		{
			target.Register(mLooks[i]);
		}

		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void BBlockSprite::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	target.WriteEnum(mSpriteType);
	target.WritePointer(mScriptCtrl);
	target.WritePointer(mFrameObject);

	target.Write(mLayerIndex);
	target.WriteAggregate(mRotate);
	target.WriteAggregate(mScale);

	int numLooks = (int)mLooks.size();
	target.Write(numLooks);
	for (int i = 0; i < numLooks; i++)
	{
		target.WritePointer(mLooks[i]);
	}

	PX2_END_DEBUG_STREAM_SAVE(BBlockSprite, target);
}
//----------------------------------------------------------------------------
int BBlockSprite::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	size += PX2_ENUMSIZE(mSpriteType);
	size += PX2_POINTERSIZE(mScriptCtrl);
	size += PX2_POINTERSIZE(mFrameObject);

	size += sizeof(mLayerIndex);
	size += sizeof(mRotate);
	size += sizeof(mScale);

	int numLooks = (int)mLooks.size();
	size += sizeof(numLooks);
	if (numLooks > 0)
	{
		size += numLooks * PX2_POINTERSIZE(mLooks[0]);
	}

	return size;
}
//----------------------------------------------------------------------------