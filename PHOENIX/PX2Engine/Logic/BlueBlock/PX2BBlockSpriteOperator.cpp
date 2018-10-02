// PX2BSpriteOperator.cpp

#include "PX2BBlockSprite.hpp"
#include "PX2BBlockSystem.hpp"
#include "PX2BBlockEvent.hpp"
#include "PX2Arduino.hpp"
#include "PX2StringHelp.hpp"
#include "PX2ScriptController.hpp"
#include "PX2UIProgressBar.hpp"
#include "PX2Log.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
void BBlockSprite::setPostion(float posX, float posY)
{
	SetAnchorHor(0.0f, 0.0f);
	SetAnchorVer(0.0f, 0.0f);
	SetAnchorParamHor(posX, posX);
	SetAnchorParamVer(posY, posY);
}
//----------------------------------------------------------------------------
void BBlockSprite::setAnchorHor(float valA, float valB)
{
	SetAnchorHor(valA, valB);
}
//----------------------------------------------------------------------------
void BBlockSprite::setAnchorParamHor(float valA, float valB)
{
	SetAnchorParamHor(valA, valB);
}
//----------------------------------------------------------------------------
void BBlockSprite::setAnchorVer(float valA, float valB)
{
	SetAnchorVer(valA, valB);
}
//----------------------------------------------------------------------------
void BBlockSprite::setAnchorParamVer(float valA, float valB)
{
	SetAnchorParamVer(valA, valB);
}
//----------------------------------------------------------------------------
void BBlockSprite::setPivot(float pivotX, float pivotY)
{
	SetPivot(pivotX, pivotY);
}
//----------------------------------------------------------------------------
void BBlockSprite::setSize(float size)
{
	SetSize(size, size);
}
//----------------------------------------------------------------------------
void BBlockSprite::setSize1(float size)
{
	UIRound *round = DynamicCast<UIRound>(mFrameObject);
	if (round)
	{
		round->GetButton()->SetSize(size, size);
	}
	UISlider *slider = DynamicCast<UISlider>(mFrameObject);
	if (slider)
	{
		slider->SetSliderLength(size);
	}
}
//----------------------------------------------------------------------------
void BBlockSprite::setSizeWidthHeight(float width, float height)
{
	SetSize(width, height);
}
//----------------------------------------------------------------------------
void BBlockSprite::setLayout(
	float horA, float horB, float horParamA, float horParamB,
	float verA, float verB, float verParamA, float verParamB,
	float pivotX, float pivotY, float width, float height)
{
	SetAnchorHor(horA, horB);
	SetAnchorParamHor(horParamA, horParamB);
	SetAnchorVer(verA, verB);
	SetAnchorParamVer(verParamA, verParamB);
	SetPivot(pivotX, pivotY);
	SetSize(width, height);
}
//----------------------------------------------------------------------------
void BBlockSprite::setRotateXYZ(float x, float y, float z)
{
	mRotate = APoint(x, y, z);

	LocalTransform.SetRotate(mRotate.X()*Mathf::DEG_TO_RAD,
		mRotate.Y()*Mathf::DEG_TO_RAD, mRotate.Z()*Mathf::DEG_TO_RAD);
}
//----------------------------------------------------------------------------
void BBlockSprite::setRotateX(float degree)
{
	mRotate.X() = degree;

	LocalTransform.SetRotate(mRotate.X()*Mathf::DEG_TO_RAD,
		mRotate.Y()*Mathf::DEG_TO_RAD, mRotate.Z()*Mathf::DEG_TO_RAD);
}
//----------------------------------------------------------------------------
void BBlockSprite::setRotateY(float degree)
{
	mRotate.Y() = degree;

	LocalTransform.SetRotate(mRotate.X()*Mathf::DEG_TO_RAD,
		mRotate.Y()*Mathf::DEG_TO_RAD, mRotate.Z()*Mathf::DEG_TO_RAD);
}
//----------------------------------------------------------------------------
void BBlockSprite::setRotateZ(float degree)
{
	mRotate.Z() = degree;

	LocalTransform.SetRotate(mRotate.X()*Mathf::DEG_TO_RAD,
		mRotate.Y()*Mathf::DEG_TO_RAD, mRotate.Z()*Mathf::DEG_TO_RAD);
}
//----------------------------------------------------------------------------
float BBlockSprite::getRotateX() const
{
	return mRotate.X();
}
//----------------------------------------------------------------------------
float BBlockSprite::getRotateY() const
{
	return mRotate.Y();
}
//----------------------------------------------------------------------------
float BBlockSprite::getRotateZ() const
{
	return mRotate.Z();
}
//----------------------------------------------------------------------------
void BBlockSprite::setScale(float scale)
{
	mScale = APoint(scale, scale, scale);

	LocalTransform.SetScale(mScale);
}
//----------------------------------------------------------------------------
float BBlockSprite::getScale() const
{
	return mScale.X();
}
//----------------------------------------------------------------------------
void BBlockSprite::setScaleXZ(float scaleX, float scaleZ)
{
	mScale = APoint(scaleX, mScale.Y(), scaleZ);
	LocalTransform.SetScale(mScale);
}
//----------------------------------------------------------------------------
void BBlockSprite::setScaleX(float val)
{
	mScale.X() = val;
	LocalTransform.SetScale(mScale);
}
//----------------------------------------------------------------------------
void BBlockSprite::setScaleZ(float val)
{
	mScale.Z() = val;
	LocalTransform.SetScale(mScale);
}
//----------------------------------------------------------------------------
float BBlockSprite::getScaleX() const
{
	return mScale.X();
}
//----------------------------------------------------------------------------
float BBlockSprite::getScaleZ() const
{
	return mScale.Z();
}
//----------------------------------------------------------------------------
void BBlockSprite::move(float moveX, float moveY)
{
	SetAnchorHor(0.0f, 0.0f);
	SetAnchorVer(0.0f, 0.0f);

	Float2 paramHor = GetAnchorParamHor();
	paramHor[0] += moveX;
	Float2 paramVer = GetAnchorParamVer();
	paramVer[1] += moveY;

	SetAnchorParamHor(paramHor[0], paramHor[1]);
	SetAnchorParamVer(paramVer[0], paramVer[1]);
}
//----------------------------------------------------------------------------
void BBlockSprite::addRotate(float rotateDegree)
{
	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotZ = 0.0f;
	LocalTransform.GetRotate(rotX, rotY, rotZ);
	rotZ += rotateDegree * Mathf::DEG_TO_RAD;

	LocalTransform.SetRotate(rotX, rotY, rotZ);
}
//----------------------------------------------------------------------------
void BBlockSprite::addScale(float scale)
{
	mRotate.X() += scale;
	mRotate.Y() += scale;
	mRotate.Z() += scale;
}
//----------------------------------------------------------------------------
void BBlockSprite::setLayer(int layer)
{
	if (0 <= layer && layer <= 10)
	{
		mLayerIndex = layer;
		LocalTransform.SetTranslateY(layer*-5.0f);
	}
}
//----------------------------------------------------------------------------
int BBlockSprite::getLayer() const
{
	return mLayerIndex;
}
//----------------------------------------------------------------------------
void BBlockSprite::setName(const std::string &name)
{
	SetName(name);
}
//----------------------------------------------------------------------------
const std::string &BBlockSprite::getName() const
{
	return GetName();
}
//----------------------------------------------------------------------------
void BBlockSprite::setFixUpdateFPS(int fps)
{
	mFixUpdateFPS = fps;
	PX2_LOG_INFO("setFixUpdateFPS %d", mFixUpdateFPS);

	ScriptController *sc = GetController<ScriptController>();
	if (sc)
	{
		sc->SetNumFixUpdatePerSeconds(fps);

		PX2_LOG_INFO("SetNumFixUpdatePerSeconds %d", mFixUpdateFPS);
	}
}
//----------------------------------------------------------------------------
int BBlockSprite::getFixUpdateFPS() const
{
	return mFixUpdateFPS;
}
//----------------------------------------------------------------------------
void BBlockSprite::attachChild(BBlockSprite *sprite)
{
	if (!sprite)
		return;

	AttachChild(sprite);
}
//----------------------------------------------------------------------------
void BBlockSprite::detachChild(BBlockSprite *sprite)
{
	if (!sprite)
		return;

	DetachChild(sprite);
}
//----------------------------------------------------------------------------
void BBlockSprite::detachChildByName(const std::string &name)
{
	Movable *mov = DynamicCast<Movable>(GetChildByName(name));
	if (mov)
	{
		DetachChild(mov);
	}
}
//----------------------------------------------------------------------------
void BBlockSprite::show(bool show)
{
	Show(show);
}
//----------------------------------------------------------------------------
void BBlockSprite::setColor(int r, int g, int b)
{
	UIButton *but = DynamicCast<UIButton>(mFrameObject);
	if (but)
	{
		but->SetStateColor(UIButtonBase::BS_NORMAL, Float3::MakeColor(r, g, b));
		but->SetStateColor(UIButtonBase::BS_HOVERED, Float3::MakeColor(r, g, b));
		but->SetStateColor(UIButtonBase::BS_PRESSED, Float3::MakeColor(r, g, b));
		but->SetStateBrightness(UIButtonBase::BS_NORMAL, 1.0f);
		but->SetStateBrightness(UIButtonBase::BS_HOVERED, 1.0f);
		but->SetStateBrightness(UIButtonBase::BS_PRESSED, 1.2f);
	}

	UIProgressBar *progBar = DynamicCast<UIProgressBar>(mFrameObject);
	if (progBar)
	{
		progBar->GetProgressPicBox()->SetColor(Float3::MakeColor(r, g, b));
	}

	UIRound *round = DynamicCast<UIRound>(mFrameObject);
	if (round)
	{
		round->GetButton()->SetStateColor(UIButtonBase::BS_NORMAL, Float3::MakeColor(r, g, b));
		round->GetButton()->SetStateColor(UIButtonBase::BS_HOVERED, Float3::MakeColor(r, g, b));
		round->GetButton()->SetStateColor(UIButtonBase::BS_PRESSED, Float3::MakeColor(r, g, b));
		round->GetButton()->SetStateBrightness(UIButtonBase::BS_NORMAL, 1.0f);
		round->GetButton()->SetStateBrightness(UIButtonBase::BS_HOVERED, 1.0f);
		round->GetButton()->SetStateBrightness(UIButtonBase::BS_PRESSED, 1.2f);
	}

	UIFText *fText = DynamicCast<UIFText>(mFrameObject);
	if (fText)
	{
		fText->GetText()->SetFontColor(Float3::MakeColor(r, g, b));
	}
}
//----------------------------------------------------------------------------
void BBlockSprite::setAlpha(float a)
{
	UIButton *but = DynamicCast<UIButton>(mFrameObject);
	if (but)
	{
		but->SetAlpha(a);
	}
}
//----------------------------------------------------------------------------
bool BBlockSprite::isShow() const
{
	return IsShow();
}
//----------------------------------------------------------------------------
void BBlockSprite::setText(const std::string &str)
{
	if (!mFrameObject)
		return;

	if (ST_BUTTON == mSpriteType || ST_EDITBOX == mSpriteType ||
		ST_TEXT == mSpriteType || ST_SLIDER == mSpriteType)
	{
		UIButton *but = DynamicCast<UIButton>(mFrameObject);
		UIFText *fText = DynamicCast<UIFText>(mFrameObject);
		UIEditBox *editBox = DynamicCast<UIEditBox>(mFrameObject);
		UISlider *slider = DynamicCast<UISlider>(mFrameObject);
		if (but)
		{
			UIText *text = but->GetText();
			if (!text)
			{
				UIFText *fText = but->CreateAddText(str);
				fText->GetText()->SetFont("Data/BlueBlock/fonts/font.ttf");
			}
			else
			{
				text->SetText(str);
			}
		}
		else if (fText)
		{
			fText->GetText()->SetText(str);
		}
		else if (editBox)
		{
			editBox->SetText(str);
		}
		else if (slider)
		{
			UIFText *fText = DynamicCast<UIFText>(slider->GetObjectByName("UIFText"));
			if (!fText)
			{
				fText = but->CreateAddText(str);
				fText->GetText()->SetFont("Data/BlueBlock/fonts/font.ttf");
			}
			else
			{
				fText->GetText()->SetText(str);
			}
		}
	}
}
//----------------------------------------------------------------------------
void BBlockSprite::setTextFontSize(int size)
{
	UIButton *but = DynamicCast<UIButton>(mFrameObject);
	if (but)
	{
		UIFText *fText = but->GetFText();
		if (fText)
		{
			fText->GetText()->SetFontSize(size);
		}
	}
	UIFText *fText = DynamicCast<UIFText>(mFrameObject);
	if (fText)
	{
		fText->GetText()->SetFontSize(size);
	}
}
//----------------------------------------------------------------------------
std::string BBlockSprite::getText()
{
	if (!mFrameObject)
		return "";

	UIButton *but = DynamicCast<UIButton>(mFrameObject);
	UIFText *fText = DynamicCast<UIFText>(mFrameObject);
	UIEditBox *editBox = DynamicCast<UIEditBox>(mFrameObject);

	if (but)
	{
		UIText *text = but->GetText();
		if (text)
		{
			std::string textStr = text->GetText();
			return  textStr;
		}
	}
	else if (fText)
	{
		return fText->GetText()->GetText();
	}
	else if (editBox)
	{
		return editBox->GetText();
	}

	return "";
}
//----------------------------------------------------------------------------
void BBlockSprite::setValue(float val)
{
	mValue = val;

	UIProgressBar *pb = DynamicCast<UIProgressBar>(mFrameObject);
	if (pb)
	{
		pb->SetProgress(val);
	}
	UISlider *sd = DynamicCast<UISlider>(mFrameObject);
	if (sd)
	{
		sd->SetPercent(val);
	}
}
//----------------------------------------------------------------------------
float BBlockSprite::getValue() const
{
	return mValue;
}
//----------------------------------------------------------------------------
float BBlockSprite::getDragingDirX() const
{
	if (!mFrameObject)
		return 0.0f;

	UIRound *round = DynamicCast<UIRound>(mFrameObject);
	if (!round) return 0.0f;

	return round->GetDraggingDir().X();
}
//----------------------------------------------------------------------------
float BBlockSprite::getDragingDirY() const
{
	if (!mFrameObject)
		return 0.0f;

	UIRound *round = DynamicCast<UIRound>(mFrameObject);
	if (!round) return 0.0f;

	return round->GetDraggingDir().Y();
}
//----------------------------------------------------------------------------
int BBlockSprite::getDragingDirSimple() const
{
	if (!mFrameObject)
		return 0;

	UIRound *round = DynamicCast<UIRound>(mFrameObject);
	if (!round) return 0;

	return round->GetDragingDirSimple();
}
//----------------------------------------------------------------------------
float BBlockSprite::getDragingPercent() const
{
	if (!mFrameObject)
		return 0.0f;

	UIRound *round = DynamicCast<UIRound>(mFrameObject);
	if (!round) return 0.0f;

	return round->GetDraggingPercent();
}
//----------------------------------------------------------------------------
int BBlockSprite::getDragingLeftMoveType() const
{
	UIRound *round = DynamicCast<UIRound>(mFrameObject);
	if (!round)
		return round->GetDragingLeftMoveType();
	
	return 0;
}
//----------------------------------------------------------------------------
float BBlockSprite::getDragingLeftMoveSpeed() const
{
	UIRound *round = DynamicCast<UIRound>(mFrameObject);
	if (!round)
		return round->GetDragingLeftMoveSpeed();

	return 0.0f;
}
//----------------------------------------------------------------------------
int BBlockSprite::getDragingRightMoveType() const
{
	UIRound *round = DynamicCast<UIRound>(mFrameObject);
	if (!round)
		return round->GetDragingRightMoveType();

	return 0;
}
//----------------------------------------------------------------------------
float BBlockSprite::getDragingRightMoveSpeed() const
{
	UIRound *round = DynamicCast<UIRound>(mFrameObject);
	if (!round)
		return round->GetDragingRightMoveSpeed();

	return 0.0f;
}
//----------------------------------------------------------------------------
void BBlockSprite::setSliderPercent(float perc)
{
	if (!mFrameObject)
		return;

	UISlider *slider = DynamicCast<UISlider>(mFrameObject);
	if (!slider) return;

	return slider->SetPercent(perc);
}
//----------------------------------------------------------------------------
void BBlockSprite::setSlider100(int val)
{
	if (!mFrameObject)
		return;

	UISlider *slider = DynamicCast<UISlider>(mFrameObject);
	if (!slider) return;

	return slider->SetPercent((float)val/100.0f);
}
//----------------------------------------------------------------------------
void BBlockSprite::setSlider180(int val)
{
	if (!mFrameObject)
		return;

	UISlider *slider = DynamicCast<UISlider>(mFrameObject);
	if (!slider) return;

	return slider->SetPercent((float)val / 180.0f);
}
//----------------------------------------------------------------------------
float BBlockSprite::getSliderPercent() const
{
	if (!mFrameObject)
		return 0.0f;

	UISlider *slider = DynamicCast<UISlider>(mFrameObject);
	if (!slider) return 0.0f;

	return slider->GetPercent();
}
//----------------------------------------------------------------------------
int BBlockSprite::getSlider100() const
{
	if (!mFrameObject)
		return 0;

	UISlider *slider = DynamicCast<UISlider>(mFrameObject);
	if (!slider) return 0;

	return (int)(slider->GetPercent()*100.0f);
}
//----------------------------------------------------------------------------
int BBlockSprite::getSlider180() const
{
	if (!mFrameObject)
		return 0;

	UISlider *slider = DynamicCast<UISlider>(mFrameObject);
	if (!slider) return 0;

	return (int)(slider->GetPercent()*180.0f);
}
//----------------------------------------------------------------------------
int BBlockSprite::getSlider360() const
{
	if (!mFrameObject)
		return 0;

	UISlider *slider = DynamicCast<UISlider>(mFrameObject);
	if (!slider) return 0;

	return (int)(slider->GetPercent()*360.0f);
}
//----------------------------------------------------------------------------
void BBlockSprite::addChooseString(const std::string &str)
{
	if (!mFrameObject)
		return;

	UIComboBox *combo = DynamicCast<UIComboBox>(mFrameObject);
	if (combo)
	{
		combo->AddChooseStr(str);
	}
}
//----------------------------------------------------------------------------
void BBlockSprite::chooseString(const std::string &str)
{
	if (!mFrameObject)
		return;

	UIComboBox *combo = DynamicCast<UIComboBox>(mFrameObject);
	if (combo)
	{
		combo->ChooseStr(str);
	}
}
//----------------------------------------------------------------------------
void BBlockSprite::chooseIndex(int index)
{
	if (!mFrameObject)
		return;

	UIComboBox *combo = DynamicCast<UIComboBox>(mFrameObject);
	if (combo)
	{
		combo->Choose(index);
	}
}
//----------------------------------------------------------------------------
std::string BBlockSprite::getChooseString()
{
	if (!mFrameObject)
		return "";

	UIComboBox *combo = DynamicCast<UIComboBox>(mFrameObject);
	if (combo)
	{
		return combo->GetChooseStr();
	}

	return "";
}
//----------------------------------------------------------------------------
int BBlockSprite::getChooseIndex()
{
	if (!mFrameObject)
		return 0;

	UIComboBox *combo = DynamicCast<UIComboBox>(mFrameObject);
	if (combo)
	{
		return combo->GetChoose();
	}

	return 0;
}
//----------------------------------------------------------------------------
void BBlockSprite::setURL(const std::string &url)
{
	UIWebFrame *webFrame = DynamicCast<UIWebFrame>(mFrameObject);
	if (webFrame)
	{
		webFrame->LoadURL(url);
		webFrame->SetScalesPageToFit(true);
	}
}
//----------------------------------------------------------------------------
void BBlockSprite::_UICallback(UIFrame *frame, UICallType type)
{
	UIButton *but = DynamicCast<UIButton>(frame);
	UIRound *round = DynamicCast<UIRound>(frame);
	UISlider *sd = DynamicCast<UISlider>(frame);
	if (but)
	{
		PX2BBLOCK_SYS.EventObjectName = GetName();
		PX2BBLOCK_SYS.EventDataFloat = 0.0f;

		if (UICT_PRESSED == type)
		{
			Event *ent = PX2_CREATEEVENTEX(BBlockEventS, UIButtonPressed);
			PX2_EW.BroadcastingLocalEvent(ent);
		}
		else if (UICT_RELEASED == type)
		{
			Event *ent = PX2_CREATEEVENTEX(BBlockEventS, UIButtonReleased);
			PX2_EW.BroadcastingLocalEvent(ent);
		}
		else if (UICT_RELEASED_NOTPICK == type)
		{
			Event *ent = PX2_CREATEEVENTEX(BBlockEventS, UIButtonReleasedNotPick);
			PX2_EW.BroadcastingLocalEvent(ent);
		}
	}
	else if (round)
	{
		if (UICT_ROUND_DRAG == type || UICT_ROUND_RELEASED || UICT_ROUND_PRESSED)
		{
			int curDragSimple = round->GetDragingDirSimple();
			if (curDragSimple != mRoundCurDragingDirSimple)
			{
				mRoundCurDragingDirSimple = curDragSimple;

				PX2BBLOCK_SYS.EventObjectName = GetName();
				PX2BBLOCK_SYS.EventDataFloat = (float)mRoundCurDragingDirSimple;

				Event *ent = PX2_CREATEEVENTEX(BBlockEventS, UIRoundDragChanged);
				PX2_EW.BroadcastingLocalEvent(ent);
			}
		}
	}
	else if (sd)
	{
		PX2BBLOCK_SYS.EventObjectName = GetName();
		PX2BBLOCK_SYS.EventDataFloat = sd->GetPercent();

		Event *ent = PX2_CREATEEVENTEX(BBlockEventS, UISliderChanged);
		PX2_EW.BroadcastingLocalEvent(ent);
	}
}
//----------------------------------------------------------------------------