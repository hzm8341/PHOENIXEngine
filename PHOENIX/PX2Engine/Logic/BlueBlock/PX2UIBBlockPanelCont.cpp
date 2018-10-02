// PX2UIBBlockPanelBlockCont.cpp

#include "PX2UIBBlockPanelCont.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2EngineCanvas.hpp"
#include "PX2BBManager.hpp"
#include "PX2LogicManager.hpp"
#include "PX2LogicES.hpp"
#include "PX2BBlockEvents.hpp"
#include "PX2Math.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, BUIBlocksPanelCont);
PX2_IMPLEMENT_STREAM(BUIBlocksPanelCont);
PX2_IMPLEMENT_FACTORY(BUIBlocksPanelCont);

//----------------------------------------------------------------------------
BUIBlocksPanelCont::BUIBlocksPanelCont(const std::string &tag) :
mTag(tag)
{
	SetChildPickOnlyInSizeRange(true);
	SetOnlyShowUpdate(true);

	SetAnchorHor(0.0f, 1.0f);
	SetAnchorVer(0.0f, 1.0f);

	Float3 clearColor = Float3::MakeColor(97, 104, 117);
	Float4 clearColor4 = MathHelp::Float3ToFloat4(clearColor, 255.0f);

	mSliderWidth = 30.0f;
	mIsUpdateContentPos = true;
	mIsUpdateSliderVisible = true;
	float toolFrameHeight = 0.0f;

	mContentCanvas = new0 Canvas();
	AttachChild(mContentCanvas);
	mContentCanvas->LocalTransform.SetTranslateY(-1.0f);
	mContentCanvas->SetAnchorHor(0.0f, 1.0f);
	mContentCanvas->SetAnchorParamHor(0.0f, 0.0f);
	mContentCanvas->SetAnchorVer(0.0f, 1.0f);
	mContentCanvas->SetAnchorParamVer(0.0f, 0.0f);
	mContentCanvas->CreateUICameraNode();
	mContentCanvas->SetClearColor(clearColor4);

	mContentBlocks = new0 UIFrame();
	mContentCanvas->AttachChild(mContentBlocks);
	mContentBlocks->LocalTransform.SetTranslateY(-5.0f);
	mContentBlocks->SetAnchorHor(0.0f, 1.0f);
	mContentBlocks->SetAnchorVer(0.0f, 1.0f);

	mContentList = new0 UIBBlockPanelList();
	mContentCanvas->AttachChild(mContentList);
	mContentList->LocalTransform.SetTranslateY(-5.0f);
	mContentList->SetAnchorHor(0.0f, 1.0f);
	mContentList->SetAnchorVer(0.0f, 1.0f);

	if ("ParamCreated" == mTag)
	{
		toolFrameHeight = 40.0f;

		mContentCanvas->SetAnchorParamVer(0.0f, -toolFrameHeight);

		mToolFrame = new0 UIFrame();
		AttachChild(mToolFrame);
		mToolFrame->LocalTransform.SetTranslateY(-20.0f);
		mToolFrame->SetAnchorHor(0.0f, 1.0f);
		mToolFrame->SetAnchorVer(1.0f, 1.0f);
		mToolFrame->SetSize(0.0, toolFrameHeight);
		mToolFrame->SetPivot(0.5f, 1.0f);

		float butWidth = 150.0f;

		mButCreateParam = new0 UIButton();
		mToolFrame->AttachChild(mButCreateParam);
		mButCreateParam->LocalTransform.SetTranslateY(-1.0f);
		mButCreateParam->SetName("ButCreateParam");
		mButCreateParam->SetAnchorHor(0.0f, 0.0f);
		mButCreateParam->SetAnchorParamHor(0.0f, 0.0f);
		mButCreateParam->SetAnchorVer(0.0f, 1.0f);
		mButCreateParam->SetAnchorParamVer(1.0f, -1.0f);
		mButCreateParam->SetSize(butWidth, 0.0f);
		mButCreateParam->SetPivot(0.0f, 1.0f);
		mButCreateParam->CreateAddText(PX2_LM_APP.GetValue("AddParam"));
		mButCreateParam->GetText()->SetFontColor(Float3::WHITE);
		mButCreateParam->SetMemUICallback(this,
			(UIFrame::MemUICallback)(&BUIBlocksPanelCont::_ButCallback));
		BBlock::_SetFont(mButCreateParam->GetText());

		mButDeleteParam = new0 UIButton();
		mToolFrame->AttachChild(mButDeleteParam);
		mButDeleteParam->LocalTransform.SetTranslateY(-1.0f);
		mButDeleteParam->SetName("ButDeleteParam");
		mButDeleteParam->SetAnchorHor(0.0f, 0.0f);
		mButDeleteParam->SetAnchorParamHor(butWidth+1, butWidth+1);
		mButDeleteParam->SetAnchorVer(0.0f, 1.0f);
		mButDeleteParam->SetAnchorParamVer(1.0f, -1.0f);
		mButDeleteParam->SetSize(butWidth, 0.0);
		mButDeleteParam->SetPivot(0.0f, 1.0f);
		mButDeleteParam->CreateAddText(PX2_LM_APP.GetValue("DeleteParam"));
		mButDeleteParam->GetText()->SetFontColor(Float3::WHITE);
		mButDeleteParam->SetMemUICallback(this,
			(UIFrame::MemUICallback)(&BUIBlocksPanelCont::_ButCallback));
		BBlock::_SetFont(mButDeleteParam->GetText());

		mCreateParamFrame = new0 BUICreateVariableFrame();
		AttachChild(mCreateParamFrame);
		mCreateParamFrame->LocalTransform.SetTranslateY(-30.0f);
		mCreateParamFrame->SetAnchorHor(0.0f, 1.0f);
		mCreateParamFrame->SetAnchorVer(0.5f, 0.5f);
		mCreateParamFrame->SetSize(0.0f, 400.0f);
		mCreateParamFrame->Show(false);
	}

	mBlocksPanel = new0 BUIBlockPanelBlock();
	mContentBlocks->AttachChild(mBlocksPanel);
	mBlocksPanel->LocalTransform.SetTranslateY(-2.0f);
	mBlocksPanel->SetAnchorHor(0.0f, 1.0f);
	mBlocksPanel->SetAnchorParamHor(0.0f, -mSliderWidth);
	mBlocksPanel->SetAnchorVer(1.0f, 1.0f);
	mBlocksPanel->SetSize(0.0f, 400.0f);

	mSlider = new0 UISlider();
	mSlider->LocalTransform.SetTranslateY(-30.0f);
	mSlider->SetDirectionType(UISlider::DT_VERTICALITY);
	mSlider->EnableAnchorLayout(true);
	mSlider->SetAnchorHor(1.0f, 1.0f);
	mSlider->SetAnchorParamHor(-mSliderWidth*0.5f, -mSliderWidth*0.5f);
	mSlider->SetAnchorVer(0.0f, 1.0f);
	mSlider->SetSize(mSliderWidth, 0.0f);
	mSlider->SetPivot(0.5f, 0.5f);
	mContentBlocks->AttachChild(mSlider);
	mSlider->LocalTransform.SetTranslateY(-20.0f);
	mSlider->SetContentFrame(mBlocksPanel);
	mSlider->SetMemUICallback(this,
		(UIFrame::MemUICallback)(&BUIBlocksPanelCont::_SliderCallback));

	mSlider->GetButSlider()->SetStateBrightness(UIButtonBase::BS_NORMAL, 1.0f);
	mSlider->GetButSlider()->SetStateBrightness(UIButtonBase::BS_PRESSED, 1.2f);
	mSlider->GetButSlider()->SetStateColor(UIButtonBase::BS_NORMAL, Float3::MakeColor(232, 206, 93));
	mSlider->GetButSlider()->SetStateColor(UIButtonBase::BS_HOVERED, Float3::MakeColor(232, 206, 93));
	mSlider->GetButSlider()->SetStateColor(UIButtonBase::BS_PRESSED, Float3::MakeColor(232, 206, 93));

	SetName("BUIBlocksPanelCont");

	ComeInEventWorld();
}
//----------------------------------------------------------------------------
BUIBlocksPanelCont::~BUIBlocksPanelCont()
{
}
//----------------------------------------------------------------------------
void BUIBlocksPanelCont::UpdateWorldData(double applicationTime,
	double elapsedTime)
{
	UIFrame::UpdateWorldData(applicationTime, elapsedTime);

	if (mIsUpdateContentPos)
	{
		mIsUpdateContentPos = false;
		_UpdateContentPos();
	}
}
//----------------------------------------------------------------------------
void BUIBlocksPanelCont::_UpdateContentPos()
{
	float heightDist = mBlocksPanel->GetSize().Height - mContentBlocks->GetSize().Height;
	if (heightDist > 0.0f && heightDist < 99999.0f)
	{
		if (mSlider)
		{
			float downMove = heightDist * mSlider->GetPercent();
			mBlocksPanel->SetAnchorParamVer(downMove, 0.0f);
		}
	}
	else
	{
		mBlocksPanel->SetAnchorParamVer(0.0f, 0.0f);
	}
}
//----------------------------------------------------------------------------
void BUIBlocksPanelCont::_SliderCallback(UIFrame *frame, UICallType type)
{
	UISlider *slider = DynamicCast<UISlider>(frame);
	if (slider)
	{
		if (UICT_SLIDERCHANGED == type)
		{
			mIsUpdateContentPos = true;
			mIsUpdateSliderVisible = true;
		}
	}
}
//----------------------------------------------------------------------------
void BUIBlocksPanelCont::_ButCallback(UIFrame *frame, UICallType type)
{
	const std::string &frameName = frame->GetName();

	if (UICT_RELEASED == type)
	{
		if ("ButCreateParam" == frameName)
		{
			mCreateParamFrame->Show(true);
		}
		else if ("ButDeleteParam" == frameName)
		{
			BBlock *bbBlock = PX2_BBM.GetSelectBBlockCata();
			if (bbBlock)
			{
				LBlock *lParam = bbBlock->GetLBlock();
				if (lParam)
				{
					const std::string &name = lParam->GetName();
					FunObject *funObj = PX2_LOGICM.GetParam(name);
					if (funObj)
					{
						Event *entCV = BBlockES::CreateEventX(BBlockES::DeleteVariable);
						entCV->SetData<FunObject*>(funObj);
						PX2_EW.BroadcastingLocalEvent(entCV);

						PX2_LOGICM.RemoveParam(name);
					}
				}
			}
		}
	}
}
//----------------------------------------------------------------------------
void BUIBlocksPanelCont::OnEvent(Event *ent)
{
	if (BBlockES::IsEqual(ent, BBlockES::RefreshBlockCata))
	{
		if ("ParamCreated" == mCata)
		{
			if (mBlocksPanel)
				mBlocksPanel->SetCatalogue(mCata);
		}
	}
}
//----------------------------------------------------------------------------
void BUIBlocksPanelCont::SetCatalogue(const std::string &cata)
{
	mCata = cata;

	if ("Func" == mCata || "System" == mCata || "Extend" == mCata)
	{
		mBlocksPanel->Show(false);
		mSlider->Show(false);

		mContentList->Show(true);
	}
	else
	{
		mBlocksPanel->Show(true);
		mSlider->Show(true);

		mContentList->Show(false);
	}

	if (mBlocksPanel)
		mBlocksPanel->SetCatalogue(cata);

	if (mContentList)
		mContentList->SetCatalogue(cata);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
BUIBlocksPanelCont::BUIBlocksPanelCont(LoadConstructor value) :
UIFrame(value)
{
}
//----------------------------------------------------------------------------
void BUIBlocksPanelCont::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(BUIBlocksPanelCont, source);
}
//----------------------------------------------------------------------------
void BUIBlocksPanelCont::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void BUIBlocksPanelCont::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool BUIBlocksPanelCont::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void BUIBlocksPanelCont::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(BUIBlocksPanelCont, target);
}
//----------------------------------------------------------------------------
int BUIBlocksPanelCont::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------