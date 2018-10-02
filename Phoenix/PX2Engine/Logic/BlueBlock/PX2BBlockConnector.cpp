// PX2BBlockConnector.cpp

#include "PX2BBlockConnector.hpp"
#include "PX2BBlock.hpp"
#include "PX2BDefine.hpp"
#include "PX2Log.hpp"
#include "PX2BBManager.hpp"
#include "PX2BDefine.hpp"
#include "PX2LanguageManager.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, BBlockConnector);
PX2_IMPLEMENT_STREAM(BBlockConnector);
PX2_IMPLEMENT_FACTORY(BBlockConnector);

//----------------------------------------------------------------------------
BBlockConnector::BBlockConnector(LParam *lParam, ConnectorType type) :
mConnectorType(type),
mLParam(lParam)
{
	ComeInEventWorld();

	SetSize(BDefine::ParamHeight, BDefine::ParamHeight);

	SetSaveWriteIngore(true);
	SetChildPickOnlyInSizeRange(false);
	SetChildNotPickRecursion(false);

	mConnectRectFrame = new0 UIFrame();
	AttachChild(mConnectRectFrame);
	mConnectRectFrame->SetAnchorHor(0.0f, 1.0f);
	mConnectRectFrame->SetAnchorVer(0.0f, 1.0f);

	if (CT_NEXT == mConnectorType)
	{
		mConnectRectFrame->SetAnchorHor(0.0f, 1.0f);
		mConnectRectFrame->SetAnchorVer(1.0f, 1.0f);
		mConnectRectFrame->SetAnchorParamHor(-BDefine::BlockHeightMiddle, BDefine::BlockHeightMiddle);
		mConnectRectFrame->SetSize(0.0f, BDefine::BlockHeight *0.84f);

		SetAnchorHor(0.0f, 0.0f);
		SetAnchorVer(0.0f, 0.0f);
		SetAnchorParamHor(0.0f, 0.0f);
		SetAnchorParamVer(0.0f, 0.0f);

		SetPivot(0.0f, 1.0f);
	}
	else
	{
		if (CT_PARAM == mConnectorType)
		{
			mConnectRectFrame->SetAnchorHor(0.0f, 1.0f);
			mConnectRectFrame->SetAnchorParamHor(0.0f, 0.0f);
			mConnectRectFrame->SetAnchorVer(0.0f, 1.0f);
			mConnectRectFrame->SetAnchorParamVer(0.0f, 0.0f);
			mConnectRectFrame->SetSize(0.0f, 0.0f);

			mBackPic = new0 UIFPicBox();
			AttachChild(mBackPic);
			mBackPic->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/circle.png");
			mBackPic->SetAnchorHor(0.1f, 0.9f);
			mBackPic->SetAnchorParamHor(0.0f, 0.0f);
			mBackPic->SetAnchorVer(0.1f, 0.9f);
			mBackPic->SetAnchorParamVer(0.0f, 0.0f);

			SetPivot(0.0f, 0.5f);
		}
		else if (CT_BLOCK == mConnectorType)
		{
			SetPivot(0.0f, 1.0f);

			mConnectRectFrame->SetAnchorHor(0.0f, 1.0f);
			mConnectRectFrame->SetAnchorVer(1.0f, 1.0f);
			mConnectRectFrame->SetAnchorParamHor(-BDefine::BlockHeightMiddle, BDefine::BlockHeightMiddle);
			mConnectRectFrame->SetSize(0.0f, BDefine::BlockHeight *0.84f);
		}
	}

	if (CT_NEXT != mConnectorType)
	{
		mNameText = new0 UIFText();
		AttachChild(mNameText);
		mNameText->LocalTransform.SetTranslateY(-1.0f);
		mNameText->SetDoPick(false);
		BBlock::_SetFont(mNameText->GetText());
		mNameText->GetText()->SetFontScale(0.8f);
		mNameText->GetText()->SetFontColor(Float3::WHITE);

		std::string paramName = lParam->GetName();
		std::string paramNameValueText = PX2_LM_APP1.GetValueNoAssert(paramName);
		if (!paramNameValueText.empty())
			mNameText->GetText()->SetText(paramNameValueText);
		else
			mNameText->GetText()->SetText(paramName);
		mNameText->Update();

		float textWdith = mNameText->GetText()->GetTextWidth();
		mNameText->SetWidth(textWdith);
		mNameText->SetHeight(BDefine::ParamHeight);

		if (CT_PARAM == mConnectorType)
		{
			mNameText->SetPivot(0.0f, 0.5f);
			mNameText->SetAnchorHor(0.0f, 0.0f);
			mNameText->SetAnchorParamHor(-textWdith - BDefine::BlockTitleParamHorSpace,	0.0f);
			mNameText->SetAnchorVer(0.0f, 1.0f);
			mNameText->SetAnchorParamVer(0.0f, 0.0f);
			mNameText->GetText()->SetAligns(TEXTALIGN_RIGHT | TEXTALIGN_VCENTER);
		}
		else
		{
			mNameText->SetHeight(BDefine::BlockHeightMiddle);
			mNameText->SetPivot(0.0f, 0.0f);
			mNameText->SetAnchorHor(0.0f, 0.0f);
			mNameText->SetAnchorParamHor(2.0f, 2.0f);
			mNameText->SetAnchorVer(1.0f, 1.0f);
			mNameText->SetAnchorParamVer(0.0f, 0.0f);
			mNameText->GetText()->SetAligns(TEXTALIGN_LEFT | TEXTALIGN_VCENTER);
		}
	}

	mHitPicBox = new0 UIFPicBox();
	AttachChild(mHitPicBox);
	mHitPicBox->LocalTransform.SetTranslateY(-20.0f);
	if (CT_NEXT == mConnectorType || CT_BLOCK==mConnectorType)
	{
		mHitPicBox->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/param.png");
		mHitPicBox->SetAnchorHor(0.0f, 1.0f);
		mHitPicBox->SetAnchorVer(1.0f, 1.0f);
		mHitPicBox->SetSize(0.0f, 5.0f);
		mHitPicBox->SetPivot(0.5f, 1.0f);
	}
	else if (CT_PARAM == mConnectorType)
	{
		mHitPicBox->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/circle.png");
		mHitPicBox->SetAnchorHor(0.0f, 1.0f);
		mHitPicBox->SetAnchorVer(0.0f, 1.0f);
		mHitPicBox->SetPivot(0.5f, 0.5f);
	}
	mHitPicBox->Show(false);

	if (mConnectRectFrame)
	{
		mConnectRectFrame->LocalTransform.SetTranslateY(-4.0f);
		//auto picBox = mConnectRectFrame->CreateAddBackgroundPicBox();
		//picBox->UseAlphaBlend(true);
		//picBox->SetAlpha(0.3f);
	}
}
//----------------------------------------------------------------------------
BBlockConnector::~BBlockConnector()
{
}
//----------------------------------------------------------------------------
BBlockConnector::ConnectorType BBlockConnector::GetConnectorType() const
{
	return mConnectorType;
}
//----------------------------------------------------------------------------
int BBlockConnector::GetNumChildUIBlock()
{
	int numChildBlocks = 0;
	for (int i = 0; i < GetNumChildren(); i++)
	{
		MovablePtr mov = GetChild(i);
		BBlock *block = DynamicCast<BBlock>(mov);
		if (block)
		{
			numChildBlocks++;
		}
	}

	return numChildBlocks;
}
//----------------------------------------------------------------------------
UIFText *BBlockConnector::GetNameText()
{
	return mNameText;
}
//----------------------------------------------------------------------------
UIFrame *BBlockConnector::GetConnectRectFrame()
{
	return mConnectRectFrame;
}
//----------------------------------------------------------------------------
void BBlockConnector::ShowHitPicBox(bool show)
{
	if (mHitPicBox)
	{
		mHitPicBox->Show(show);
	}
}
//----------------------------------------------------------------------------
UIFPicBox *BBlockConnector::GetHitPicBox()
{
	return mHitPicBox;
}
//----------------------------------------------------------------------------
int BBlockConnector::AttachChild(Movable* child)
{
	int ret = UIFrame::AttachChild(child);

	BBlock *childBlock = DynamicCast<BBlock>(child);
	if (childBlock)
	{
		if (mBackPic)
			mBackPic->Show(false);

		if (mHitPicBox)
			mHitPicBox->Show(false);

		LBlock *lb = childBlock->GetLBlock();
		if (lb)
		{
			mLParam->SetLinkBlock(lb);
		}

		LBlock::BlockType bt = lb->GetBlockType();
		if ((LBlock::MT_FUNCTION_OUTPUT == bt && !lb->IsFunOutputConvertToGeneral() )||
			LBlock::MT_FUNCTION_OPERATOR == bt ||
			LBlock::MT_PARAM == bt)
		{
			childBlock->SetAnchorHor(0.0f, 0.0f);
			childBlock->SetAnchorVer(0.5f, 0.5f);
			childBlock->SetAnchorParamHor(0.0f, 0.0f);
			childBlock->SetAnchorParamVer(0.0f, 0.0f);
			childBlock->LocalTransform.SetTranslateY(-2.0f);
		}
		else
		{
			childBlock->SetAnchorHor(0.0f, 0.0f);
			childBlock->SetAnchorVer(1.0f, 1.0f);
			childBlock->SetAnchorParamHor(0.0f, 0.0f);
			childBlock->SetAnchorParamVer(0.0f, 0.0f);
			childBlock->LocalTransform.SetTranslateY(-2.0f);
		}
	}

	BBlock *parBlock = DynamicCast<BBlock>(GetParent());
	if (parBlock)
	{
		parBlock->_ReGenLayOut();
	}

	if (childBlock)
	{
		UICheckButton *checkUseThisPointer = childBlock->GetCheckButtonUseThisPointer();
		if (checkUseThisPointer)
		{
			checkUseThisPointer->Show(false);
		}

		PX2_BBM.SetNeedCompileScript(true);
	}

	return ret;
}
//----------------------------------------------------------------------------
BBlock* BBlockConnector::GetCurBlock()
{
	for (int i = 0; i < GetNumChildren(); i++)
	{
		BBlock *block = DynamicCast<BBlock>(GetChild(i));
		if (block)
			return block;
	}

	return 0;
}
//----------------------------------------------------------------------------
int BBlockConnector::DetachChild(Movable* child)
{
	BBlock *childBlock = DynamicCast<BBlock>(child);
	if (childBlock)
	{
		if (mBackPic)
			mBackPic->Show(true);

		LBlock *lb = childBlock->GetLBlock();
		if (lb)
		{
			mLParam->SetLinkBlock(0);
		}
	}

	int ret = UIFrame::DetachChild(child);

	BBlock *parBlock = DynamicCast<BBlock>(GetParent());
	if (parBlock)
	{
		parBlock->_ReGenLayOut();
	}

	if (childBlock)
	{
		UICheckButton *checkUseThisPointer = childBlock->GetCheckButtonUseThisPointer();
		if (checkUseThisPointer)
		{
			checkUseThisPointer->Show(true);
		}

		PX2_BBM.SetNeedCompileScript(true);
	}

	return ret;
}
//----------------------------------------------------------------------------
BBlockConnector::BBlockConnector()
{
}
//----------------------------------------------------------------------------
float BBlockConnector::GetBlockAllWidth()
{
	if (CT_PARAM == mConnectorType)
	{
		float width = 0.0f;
		int numBlocks = 0;
		for (int i = 0; i < GetNumChildren(); i++)
		{
			BBlock *block = DynamicCast<BBlock>(GetChild(i));
			if (block)
			{			
				width += block->GetWidth();
				numBlocks++;
			}
		}

		if (0 == numBlocks)
		{
			width = BDefine::ParamHeight;
		}

		return width;
	}
	else if (CT_BLOCK == mConnectorType)
	{
		float width = 0.0f;
		int numBlocks = 0;
		for (int i = 0; i < GetNumChildren(); i++)
		{
			BBlock *block = DynamicCast<BBlock>(GetChild(i));
			if (block)
			{
				width += block->GetWidth();
				numBlocks++;
			}
		}

		if (0 == numBlocks)
		{
			width = BDefine::ParamHeight;
		}

		return width;
	}

	return BDefine::ParamHeight;
}
//----------------------------------------------------------------------------
float BBlockConnector::GetBlockAllHeight(int *numChildBlocks)
{
	if (CT_PARAM == mConnectorType)
	{
		float height = 0.0f;
		int numBlocks = 0;
		for (int i = 0; i < GetNumChildren(); i++)
		{
			BBlock *block = DynamicCast<BBlock>(GetChild(i));
			if (block)
			{
				height += block->GetHeight();
				numBlocks++;
			}
		}

		assertion(0 == numBlocks || 1 == numBlocks, "");

		if (numChildBlocks)
			*numChildBlocks = numBlocks;
		if (0 == numBlocks)
		{
			height = BDefine::ParamHeight;
		}

		return height;
	}
	else if (CT_BLOCK == mConnectorType)
	{
		float height = 0.0f;
		int numBlocks = 0;
		for (int i = 0; i < GetNumChildren(); i++)
		{
			BBlock *block = DynamicCast<BBlock>(GetChild(i));
			if (block)
			{
				height += block->GetBlockHeightWithNext();
				numBlocks++;
			}
		}

		assertion(0 == numBlocks || 1 == numBlocks, "");

		if (numChildBlocks)
			*numChildBlocks = numBlocks;
		if (0 == numBlocks)
		{
			height = BDefine::ParamHeight;
		}

		return height;
	}
	else if (CT_NEXT == mConnectorType)
	{
		float height = 0.0f;
		for (int i = 0; i < GetNumChildren(); i++)
		{
			BBlock *block = DynamicCast<BBlock>(GetChild(i));
			if (block)
			{
				height += block->GetHeight();

				BBlockConnector *nextCnt = block->GetBlockConnectorByName("Next");
				if (nextCnt)
				{
					height += nextCnt->GetBlockAllHeight();
				}
			}
		}

		return height;
	}

	return BDefine::BlockHeight;
}
//----------------------------------------------------------------------------
LParam *BBlockConnector::GetLParam()
{
	return mLParam;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
BBlockConnector::BBlockConnector(LoadConstructor value) :
UIFrame(value)
{
}
//----------------------------------------------------------------------------
void BBlockConnector::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(BBlockConnector, source);
}
//----------------------------------------------------------------------------
void BBlockConnector::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void BBlockConnector::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool BBlockConnector::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void BBlockConnector::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(BBlockConnector, target);
}
//----------------------------------------------------------------------------
int BBlockConnector::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------