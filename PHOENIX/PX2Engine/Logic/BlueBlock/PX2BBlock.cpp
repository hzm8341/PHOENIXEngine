// BBlock.cpp

#include "PX2BBlock.hpp"
#include "PX2BDefine.hpp"
#include "PX2TriangulateEC.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2VertexColor4Material.hpp"
#include "PX2Renderer.hpp"
#include "PX2SelectionManager.hpp"
#include "PX2BBManager.hpp"
#include "PX2Log.hpp"
#include "PX2Time.hpp"
#include "PX2LogicES.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2BBlockEvents.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
ConnectUIObj::ConnectUIObj()
{
}
//----------------------------------------------------------------------------
ConnectUIObj::~ConnectUIObj()
{
}
//----------------------------------------------------------------------------

PX2_IMPLEMENT_RTTI(PX2, UIFrame, BBlock);
PX2_IMPLEMENT_STREAM(BBlock);
PX2_IMPLEMENT_FACTORY(BBlock);
//----------------------------------------------------------------------------
BBlock::BBlock()
{
	SetName("BBlock");

	_Init();

	mBlockTextName = new0 UIFText();
	AttachChild(mBlockTextName);
	mBlockTextName->SetDoPick(false);
	mBlockTextName->LocalTransform.SetTranslateY(-5.0f);
	mBlockTextName->SetAnchorHor(0.0f, 1.0f);
	mBlockTextName->SetAnchorVer(1.0f, 1.0f);
	mBlockTextName->SetAnchorParamHor(0.0f, 0.0f);
	mBlockTextName->SetPivot(0.5f, 1.0f);
	mBlockTextName->SetHeight(BDefine::BlockHeight);
	mBlockTextName->GetText()->SetFontWidthHeight(18, 18);
	mBlockTextName->GetText()->SetRectUseage(UIText::RU_ALIGNS);
	mBlockTextName->GetText()->SetAligns(TEXTALIGN_LEFT | TEXTALIGN_VCENTER);
	mBlockTextName->GetText()->SetFontColor(Float3::WHITE);
	_SetFont(mBlockTextName->GetText());

	SetChildPickOnlyInSizeRange(false);
	SetChildNotPickRecursion(false);

	mBackPic0 = new0 UIFPicBox();
	mBackPic0->GetUIPicBox()->SetPicBoxType(UIPicBox::PBT_NINE);
	if (mIsDoSetTexture)
		mBackPic0->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/block.png");
	else
		mBackPic0->GetUIPicBox()->SetTexture("Data/engine/white.png");
	AttachChild(mBackPic0);
	mBackPic0->SetAnchorHor(0.0f, 1.0f);
	mBackPic0->SetAnchorVer(0.0f, 1.0f);
	mBackPic0->SetWidget(false);

	mBoardColor = Float4(0.96f, 0.96f, 0.96f, 1.0f);

	ComeInEventWorld();
}
//----------------------------------------------------------------------------
BBlock::~BBlock()
{
}
//----------------------------------------------------------------------------
void BBlock::_SetFont(UIText *text)
{
	text->SetFont("Data/BlueBlock/fonts/font.ttf");
	text->SetFontColor(Float3::WHITE);
	text->SetFontScale(0.85f);
}
//----------------------------------------------------------------------------
void BBlock::SetState(BBlock::BlockState state)
{
	mState = state;

	if (BS_NORMAL == mState)
	{
		SetBoardBrightness(1.0f);
	}
	else if (BS_PRESSED == mState)
	{
		SetBoardBrightness(0.6f);
	}
}
//----------------------------------------------------------------------------
BBlock *BBlock::CopyAll(EditState editState)
{
	return _CopyBlock(this, editState);
}
//----------------------------------------------------------------------------
BBlock *BBlock::_CopyBlock(BBlock *fromBlock, EditState editState)
{
	BBlock *copyBlock = DynamicCast<BBlock>(fromBlock->Copy(""));
	copyBlock->SetEditState(editState);
	copyBlock->SetBoardBrightness(1.0f);

	for (int i = 0; i < (int)fromBlock->mConnectors.size(); i++)
	{
		BBlockConnector *fromCtn = fromBlock->mConnectors[i];
		if (fromCtn)
		{
			const std::string &fromCtnName = fromCtn->GetName();
			BBlockConnector*ctn = copyBlock->GetBlockConnectorByName(fromCtnName);
			if (ctn)
			{
				for (int i = 0; i < fromCtn->GetNumChildren(); i++)
				{
					BBlock *block = DynamicCast<BBlock>(fromCtn->GetChild(i));
					if (block)
					{
						BBlock *newCtnBlock = _CopyBlock(block, editState);
						newCtnBlock->SetBoardBrightness(1.0f);
						ctn->AttachChild(newCtnBlock);
					}
				}
			}
		}
	}

	copyBlock->Update(Time::GetTimeInSeconds(), 0.0f);

	return copyBlock;
}
//----------------------------------------------------------------------------
BBlock::BlockState BBlock::GetState() const
{
	return mState;
}
//----------------------------------------------------------------------------
bool BBlock::IsAttachedToBlockConnector()
{
	BBlockConnector *ctn = DynamicCast<BBlockConnector>(GetParent());
	if (ctn)
		return true;

	return false;
}
//----------------------------------------------------------------------------
bool BBlock::IsCanBeDragingDetached()
{
	LBlock::ParamType pt = mBlock->GetParamType();
	if (pt != LBlock::PT_NONE)
	{
		// param
		Movable *mov = GetParent();
		BBlockConnector *parentBlockCnt = DynamicCast<BBlockConnector>(mov);
		if (parentBlockCnt)
			return false;
	}

	return true;
}
//----------------------------------------------------------------------------
void BBlock::OnPivotChanged()
{
	UIFrame::OnPivotChanged();
}
//----------------------------------------------------------------------------
void BBlock::SetDraging(bool draging)
{

}
//----------------------------------------------------------------------------
void BBlock::SetEditState(EditState state)
{
	mEditState = state;

	if (ES_EDITOR == state)
	{
		if (mParamEditBox)
		{
			mParamEditBox->Enable(true);
			mParamEditBox->SetDoPick(true);
		}

		if (mParamComboBox)
		{
			mParamComboBox->Enable(true);
			mParamComboBox->SetDoPick(true);
		}
	}
	else
	{
		if (mParamEditBox)
		{
			mParamEditBox->Enable(false);
			mParamEditBox->SetDoPick(false);
		}

		if (mParamComboBox)
		{
			mParamComboBox->Enable(false);
			mParamComboBox->SetDoPick(false);
		}
	}
}
//----------------------------------------------------------------------------
BBlock::EditState BBlock::GetEditState() const
{
	return mEditState;
}
//----------------------------------------------------------------------------
void BBlock::SetLBlock(LBlock *block)
{
	mBlock = block;

	if (mBlock)
	{
		std::string cateName = mBlock->GetFunObj().CateName;

		std::map<std::string, Float4>::iterator it = PX2_BBM.CateColors.find(cateName);
		if (it != PX2_BBM.CateColors.end())
		{
			SetBoardColor((*it).second);
		}
	}

	LBlock::BlockType mdt = block->GetBlockType();
	LBlock::CtrlType ct = block->GetCtrlType();

	if (LBlock::MT_CONTROL == mdt)
	{
		mBlockTextName->SetAnchorHor(0.0f, 1.0f);
		mBlockTextName->SetAnchorVer(1.0f, 1.0f);
		
		if (LBlock::CT_PROGRAM == ct || LBlock::CT_PROGRAMSTART == ct || LBlock::CT_PROGRAMFIXUPDATE == ct)
		{
			mBlockTextName->SetAnchorParamHor(BDefine::BlockTitleParamHor, 0.0f);
		}
		else
		{
			mBlockTextName->SetAnchorParamHor(BDefine::BlockTitleParamHor, 0.0f);
		}

		mBlockTextName->SetPivot(0.5f, 1.0f);
		mBlockTextName->SetHeight(BDefine::BlockHeight);
	}
	else if (LBlock::MT_EVENT==mdt)
	{
		mBlockTextName->SetAnchorHor(0.0f, 1.0f);
		mBlockTextName->SetAnchorVer(1.0f, 1.0f);
		mBlockTextName->SetAnchorParamHor(BDefine::BlockTitleParamHor, 0.0f);
		mBlockTextName->SetPivot(0.5f, 1.0f);
		mBlockTextName->SetHeight(BDefine::BlockHeight);
	}
	else if (LBlock::MT_PARAM == mdt)
	{
		mBlockTextName->SetAnchorHor(0.0f, 1.0f);
		mBlockTextName->SetAnchorVer(0.0f, 1.0f);
		mBlockTextName->SetAnchorParamHor(0.0f, 0.0f);

	}
	else
	{
		mBlockTextName->SetAnchorHor(0.0f, 1.0f);
		mBlockTextName->SetAnchorVer(0.0f, 1.0f);
		mBlockTextName->SetAnchorParamHor(BDefine::BlockTitleParamHor, 0.0f);
		mBlockTextName->SetAnchorParamVer(0.0f, 0.0f);
	}

	if (mdt == LBlock::MT_FUNCTION_GENERAL)
	{
		SetPivot(0.0f, 1.0f);

		SetShapeType(ST_FUN);

		std::vector<LParamPtr> &inputParans = block->GetInputParamsVec();
		for (int i = 0; i < (int)inputParans.size(); i++)
		{
			LParam *param = inputParans[i];
			const std::string &paramName = param->GetName();
			_DetachConnector(paramName);

			bool isAddConnector = true;
			if (FPT_POINTER_THIS == param->GetDataType() && !mBlock->IsUseThisPointer())
				isAddConnector = false;
			if (isAddConnector)
			{
				BBlockConnector *cnt = new0 BBlockConnector(param, BBlockConnector::CT_PARAM);
				AttachChild(cnt);
				cnt->SetName(param->GetName());
				cnt->LocalTransform.SetTranslateY(-2.0f);
				_AddConnector(cnt);
				cnt->SetAnchorHor(1.0f, 1.0f);
			}
		}		

		_DetachConnector("Next");
		BBlockConnector *cntNext = new0 BBlockConnector(block->GetLParamByName("Next"), BBlockConnector::CT_NEXT);
		AttachChild(cntNext);
		cntNext->SetName("Next");
		cntNext->LocalTransform.SetTranslateY(-2.0f);
		mConnectors.push_back(cntNext);
	}
	else if (mdt == LBlock::MT_FUNCTION_OUTPUT)
	{
		if (mBlock->IsFunOutputConvertToGeneral())
		{
			SetShapeType(ST_FUN);
			SetPivot(0.0f, 1.0f);
		}
		else
		{
			SetShapeType(ST_FUN_OUTPUT);
			SetPivot(0.0f, 0.5f);
		}

		std::vector<LParamPtr> &inputParans = block->GetInputParamsVec();
		for (int i = 0; i < (int)inputParans.size(); i++)
		{
			LParam *param = inputParans[i];
			const std::string &paramName = param->GetName();
			_DetachConnector(paramName);

			bool isAddConnector = true;
			if (FPT_POINTER_THIS == param->GetDataType() && !mBlock->IsUseThisPointer())
				isAddConnector = false;
			
			if (isAddConnector)
			{
				BBlockConnector *cnt = new0 BBlockConnector(param, BBlockConnector::CT_PARAM);
				AttachChild(cnt);
				cnt->SetName(param->GetName());
				cnt->LocalTransform.SetTranslateY(-2.0f);
				_AddConnector(cnt);
				cnt->SetAnchorHor(1.0f, 1.0f);
			}
		}

		_DetachConnector("Next");
		if (mBlock->IsFunOutputConvertToGeneral())
		{
			BBlockConnector *cntNext = new0 BBlockConnector(block->GetLParamByName("Next"), BBlockConnector::CT_NEXT);
			AttachChild(cntNext);
			cntNext->SetName("Next");
			cntNext->LocalTransform.SetTranslateY(-2.0f);
			mConnectors.push_back(cntNext);
		}
	}
	else if (mdt == LBlock::MT_PARAM)
	{
		SetPivot(0.0f, 0.5f);
		SetAnchorHor(0.0f, 0.0f);
		SetAnchorVer(0.5f, 0.5f);
		SetAnchorParamHor(0.0f, 0.0f);
		SetAnchorParamVer(0.0f, 0.0f);

		SetShapeType(ST_PARAM);

		LBlock::ParamType pt = mBlock->GetParamType();
		if (LBlock::PT_VALUE == pt)
		{
			FunObject funObj = mBlock->GetFunObj();

			std::vector<LParamPtr> &inputParams = block->GetInputParamsVec();
			if ((int)inputParams.size() > 0)
			{
				LParam *lParam = inputParams[0];
				mParamEditBox->SetText(lParam->GetValueScriptStr(false));
				mIsNeedUpdateWidth = true;
			}
		}
		else if (LBlock::PT_ENUM == pt)
		{
			FunObject funObj = mBlock->GetFunObj();
			const std::string &name = funObj.Name;

			std::vector<LParamPtr> &inputParams = block->GetInputParamsVec();
			for (int i = 0; i < (int)inputParams.size(); i++)
			{
				LParam *lParam = inputParams[i];
				const std::string &paramName = lParam->GetName();
				std::string useStr = paramName;
				const std::string &str = PX2_LM_APP1.GetValueNoAssert(paramName);
				if (!str.empty())
					useStr = str;

				UIItem *item = mParamComboBox->AddChooseStr(useStr);
				item->SetUserData("ParamName", paramName);
			}
			mParamComboBox->SetChooseListHeightSameWithChooses();
			if (mParamComboBox->GetChooseList()->GetHeight() > 200.0f)
				mParamComboBox->GetChooseList()->SetHeight(200.0f);

			mIsNeedUpdateWidth = true;

			std::string str;
			LParam *param = block->GetLParamByName("val");
			if (param)
				str = param->GetValueScriptStr(false);
			if (!str.empty())
			{
				auto it = str.find(".");
				str = str.substr(it+1, str.length() - it - 1);

				std::string useStr = str;
				const std::string &str = PX2_LM_APP1.GetValueNoAssert(useStr);
				if (!str.empty())
					useStr = str;
				mParamComboBox->ChooseStr(useStr);
			}
			else
			{
				mParamComboBox->Choose(0);
			}
		}
		else if (LBlock::PT_ENUMSTRING == pt)
		{
			FunObject funObj = mBlock->GetFunObj();
			const std::string &name = funObj.Name;
		
			std::vector<LParamPtr> &inputParams = block->GetInputParamsVec();
			for (int i = 0; i < (int)inputParams.size(); i++)
			{
				LParam *lParam = inputParams[i];
				const std::string &paramName = lParam->GetName();

				std::string useStr = paramName;
				const std::string &str = PX2_LM_APP1.GetValueNoAssert(paramName);
				if (!str.empty())
					useStr = str;

				UIItem *item = mParamComboBox->AddChooseStr(useStr);
				item->SetUserData("ParamName", paramName);
			}
			mParamComboBox->SetChooseListHeightSameWithChooses();
			if (mParamComboBox->GetChooseList()->GetHeight() > 200.0f)
				mParamComboBox->GetChooseList()->SetHeight(200.0f);

			mIsNeedUpdateWidth = true;

			std::string str;
			LParam *param = block->GetLParamByName("val");
			if (param)
				str = param->GetValueScriptStr(false);
			if (!str.empty())
			{
				std::string name0 = name + "::";
				str = str.substr(name0.length(), str.length() - name0.length());

				std::string useStr = str;
				const std::string &str = PX2_LM_APP1.GetValueNoAssert(useStr);
				if (!str.empty())
					useStr = str;
				mParamComboBox->ChooseStr(useStr);
			}
			else
			{
				mParamComboBox->Choose(0);
			}
		}
		else if (LBlock::PT_VARIABLESELECT == pt || LBlock::PT_VALUESELECT==pt)
		{
			FunObject funObj = mBlock->GetFunObj();

			std::vector<LParamPtr> &inputParams = block->GetInputParamsVec();
			for (int i = 0; i < (int)inputParams.size(); i++)
			{
				LParam *lParam = inputParams[i];
				const std::string &paramName = lParam->GetName();

				UIItem *item = mParamComboBox->AddChooseStr(paramName);
				item->SetUserData("ParamName", paramName);
			}
			mParamComboBox->SetChooseListHeightSameWithChooses();
			if (mParamComboBox->GetChooseList()->GetHeight() > 200.0f)
				mParamComboBox->GetChooseList()->SetHeight(200.0f);

			mIsNeedUpdateWidth = true;

			std::string str;
			LParam *param = block->GetLParamByName("val");
			if (param)
			{
				str = param->GetValueScriptStr(false);
			}

			if (!str.empty())
			{
				mParamComboBox->ChooseStr(str);
			}
			else
			{
				mParamComboBox->Choose(0);
			}
		}
	}
	else if (mdt == LBlock::MT_EVENT)
	{
		SetShapeType(ST_EVENT);

		BBlockConnector *cntEvent = new0 BBlockConnector(block->GetLParamByName("Event"), BBlockConnector::CT_PARAM);
		AttachChild(cntEvent);
		cntEvent->SetName("Event");
		cntEvent->LocalTransform.SetTranslateY(-2.0f);
		_AddConnector(cntEvent);
		cntEvent->SetAnchorHor(1.0f, 1.0f);

		BBlockConnector *cntEventDo = new0 BBlockConnector(block->GetLParamByName("EventDo"), BBlockConnector::CT_BLOCK);
		AttachChild(cntEventDo);
		cntEventDo->SetName("EventDo");
		cntEventDo->LocalTransform.SetTranslateY(-2.0f);
		_AddConnector(cntEventDo);
		cntEventDo->SetAnchorHor(1.0f, 1.0f);

		BBlockConnector *cntNext = new0 BBlockConnector(block->GetLParamByName("Next"), BBlockConnector::CT_NEXT);
		AttachChild(cntNext);
		cntNext->SetName("Next");
		cntNext->LocalTransform.SetTranslateY(-2.0f);
		mConnectors.push_back(cntNext);
	}
	else if (mdt == LBlock::MT_CONTROL)
	{
		LBlock::CtrlType ct = block->GetCtrlType();
		if (LBlock::CT_IF == ct)
		{
			SetShapeType(ST_IF);

			BBlockConnector *cntIf = new0 BBlockConnector(block->GetLParamByName("If"), BBlockConnector::CT_PARAM);
			AttachChild(cntIf);
			cntIf->SetName("If");
			cntIf->LocalTransform.SetTranslateY(-2.0f);
			_AddConnector(cntIf);
			cntIf->SetAnchorHor(1.0f, 1.0f);

			BBlockConnector *cntIfDo = new0 BBlockConnector(block->GetLParamByName("IfDo"), BBlockConnector::CT_BLOCK);
			AttachChild(cntIfDo);
			cntIfDo->SetName("IfDo");
			cntIfDo->LocalTransform.SetTranslateY(-2.0f);
			_AddConnector(cntIfDo);
			cntIfDo->SetAnchorHor(1.0f, 1.0f);

			BBlockConnector *cntNext = new0 BBlockConnector(block->GetLParamByName("Next"), BBlockConnector::CT_NEXT);
			AttachChild(cntNext);
			cntNext->SetName("Next");
			cntNext->LocalTransform.SetTranslateY(-2.0f);
			mConnectors.push_back(cntNext);
		}
		else if (LBlock::CT_IFELSE == ct)
		{
			SetShapeType(ST_IFELSE);

			BBlockConnector *cntIf = new0 BBlockConnector(block->GetLParamByName("If"), BBlockConnector::CT_PARAM);
			AttachChild(cntIf);
			cntIf->SetName("If");
			cntIf->LocalTransform.SetTranslateY(-2.0f);
			_AddConnector(cntIf);
			cntIf->SetAnchorHor(1.0f, 1.0f);

			BBlockConnector *cntIfDo = new0 BBlockConnector(block->GetLParamByName("IfDo"), BBlockConnector::CT_BLOCK);
			AttachChild(cntIfDo);
			cntIfDo->SetName("IfDo");
			cntIfDo->LocalTransform.SetTranslateY(-2.0f);
			_AddConnector(cntIfDo);
			cntIfDo->SetAnchorHor(1.0f, 1.0f);

			BBlockConnector *cntElseDo = new0 BBlockConnector(block->GetLParamByName("ElseDo"), BBlockConnector::CT_BLOCK);
			AttachChild(cntElseDo);
			cntElseDo->SetName("ElseDo");
			cntElseDo->LocalTransform.SetTranslateY(-2.0f);
			_AddConnector(cntElseDo);
			cntElseDo->SetAnchorHor(1.0f, 1.0f);

			BBlockConnector *cntNext = new0 BBlockConnector(block->GetLParamByName("Next"), BBlockConnector::CT_NEXT);
			AttachChild(cntNext);
			cntNext->SetName("Next");
			cntNext->LocalTransform.SetTranslateY(-2.0f);
			mConnectors.push_back(cntNext);
		}
		else if (LBlock::CT_WHILE == ct)
		{
			SetShapeType(ST_WHILE);

			BBlockConnector *cntWhile = new0 BBlockConnector(block->GetLParamByName("While"), BBlockConnector::CT_PARAM);
			AttachChild(cntWhile);
			cntWhile->SetName("While");
			cntWhile->LocalTransform.SetTranslateY(-2.0f);
			_AddConnector(cntWhile);
			cntWhile->SetAnchorHor(1.0f, 1.0f);

			BBlockConnector *cntWhileDo = new0 BBlockConnector(block->GetLParamByName("WhileDo"), BBlockConnector::CT_BLOCK);
			AttachChild(cntWhileDo);
			cntWhileDo->SetName("WhileDo");
			cntWhileDo->LocalTransform.SetTranslateY(-2.0f);
			_AddConnector(cntWhileDo);
			cntWhileDo->SetAnchorHor(1.0f, 1.0f);

			BBlockConnector *cntNext = new0 BBlockConnector(block->GetLParamByName("Next"), BBlockConnector::CT_NEXT);
			AttachChild(cntNext);
			cntNext->SetName("Next");
			cntNext->LocalTransform.SetTranslateY(-2.0f);
			mConnectors.push_back(cntNext);
		}
		else if (LBlock::CT_COROUTINE == ct)
		{
			SetShapeType(ST_COROUTINE);

			BBlockConnector *cntCoroutineDo = new0 BBlockConnector(block->GetLParamByName("CorDo"), BBlockConnector::CT_BLOCK);
			AttachChild(cntCoroutineDo);
			cntCoroutineDo->SetName("CorDo");
			cntCoroutineDo->LocalTransform.SetTranslateY(-2.0f);
			_AddConnector(cntCoroutineDo);
			cntCoroutineDo->SetAnchorHor(1.0f, 1.0f);

			BBlockConnector *cntNext = new0 BBlockConnector(block->GetLParamByName("Next"), BBlockConnector::CT_NEXT);
			AttachChild(cntNext);
			cntNext->SetName("Next");
			cntNext->LocalTransform.SetTranslateY(-2.0f);
			mConnectors.push_back(cntNext);
		}
		else if (LBlock::CT_PROGRAM == ct)
		{
			SetShapeType(ST_PROGRAM);

			BBlockConnector *cntStart = new0 BBlockConnector(block->GetLParamByName("Start"), BBlockConnector::CT_BLOCK);
			AttachChild(cntStart);
			cntStart->SetName("Start");
			cntStart->LocalTransform.SetTranslateY(-2.0f);
			_AddConnector(cntStart);
			cntStart->SetAnchorHor(1.0f, 1.0f);

			BBlockConnector *cntFixUpdate = new0 BBlockConnector(block->GetLParamByName("FixUpdate"), BBlockConnector::CT_BLOCK);
			AttachChild(cntFixUpdate);
			cntFixUpdate->SetName("FixUpdate");
			cntFixUpdate->LocalTransform.SetTranslateY(-2.0f);
			_AddConnector(cntFixUpdate);
			cntFixUpdate->SetAnchorHor(1.0f, 1.0f);
		}
		else if (LBlock::CT_PROGRAMSTART == ct)
		{
			SetShapeType(ST_PROGRAMSTART);

			BBlockConnector *cntStart = new0 BBlockConnector(block->GetLParamByName("Start"), BBlockConnector::CT_BLOCK);
			AttachChild(cntStart);
			cntStart->SetName("Start");
			cntStart->LocalTransform.SetTranslateY(-2.0f);
			_AddConnector(cntStart);
			cntStart->SetAnchorHor(1.0f, 1.0f);
		}
		else if (LBlock::CT_PROGRAMFIXUPDATE == ct)
		{
			SetShapeType(ST_PROGRAMFIXUPDATE);

			BBlockConnector *cntFixUpdate = new0 BBlockConnector(block->GetLParamByName("FixUpdate"), BBlockConnector::CT_BLOCK);
			AttachChild(cntFixUpdate);
			cntFixUpdate->SetName("FixUpdate");
			cntFixUpdate->LocalTransform.SetTranslateY(-2.0f);
			_AddConnector(cntFixUpdate);
			cntFixUpdate->SetAnchorHor(1.0f, 1.0f);
		}
	}
	else if (mdt == LBlock::MT_FUNCTION_OPERATOR)
	{
		SetPivot(0.0f, 0.5f);
		SetAnchorHor(0.0f, 0.0f);
		SetAnchorVer(0.5f, 0.5f);
		SetAnchorParamHor(0.0f, 0.0f);
		SetAnchorParamVer(0.0f, 0.0f);

		SetShapeType(ST_FUN_OPERATOR);

		std::vector<LParamPtr> &inputParans = block->GetInputParamsVec();
		for (int i = 0; i < (int)inputParans.size(); i++)
		{
			LParam *param = inputParans[i];

			BBlockConnector *cnt = new0 BBlockConnector(block->GetLParamByName(param->GetName()), BBlockConnector::CT_PARAM);
			AttachChild(cnt);
			cnt->SetName(param->GetName());
			cnt->LocalTransform.SetTranslateY(-2.0f);
			_AddConnector(cnt);
			cnt->SetAnchorHor(1.0f, 1.0f);
		}
	}

	// other
	const std::string &name = block->GetName();
	std::string useStr = name;
	const std::string &str = PX2_LM_APP1.GetValueNoAssert(name);
	if (!str.empty())
		useStr = str;
	mBlockTextName->GetText()->SetText(useStr);
	mBlockTextName->GetText()->SetAligns(TEXTALIGN_LEFT | TEXTALIGN_VCENTER);

	mIsNeedReGenBlock = true;
}
//----------------------------------------------------------------------------
void BBlock::ResetBlock()
{
	SetLBlock(GetLBlock());
	mIsNeedUpdateWidth = true;
	mIsNeedReGenBlock = true;
}
//----------------------------------------------------------------------------
void BBlock::SetShapeType(ShapeType st)
{
	mShapeType = st;
	mIsNeedReGenBlock = true;

	if (ST_PARAM == st)
	{
		SetSize(80.0f, BDefine::BlockHeight);

		LBlock::ParamType pt = mBlock->GetParamType();
		if (LBlock::PT_VARIABLE == pt)
		{
		}
		else if (LBlock::PT_CONST == pt)
		{
		}
		else if (LBlock::PT_VALUE == pt)
		{
			if (mParamEditBox)
				DetachChild(mParamEditBox);

			Float4 borderColor4 = GetBoardColor();
			Float3 borderColor3 = MathHelp::Float4ToFloat3(borderColor4);

			mParamEditBox = new0 UIEditBox();
			AttachChild(mParamEditBox);
			mParamEditBox->GetBackPicBox()->SetColor(borderColor3 * 0.8f);
			mParamEditBox->SetSaveWriteIngore(true);
			mParamEditBox->LocalTransform.SetTranslateY(-5.0f);
			mParamEditBox->SetAnchorHor(0.0f, 1.0f);
			mParamEditBox->SetAnchorParamHor(2.0f, -2.0f);
			mParamEditBox->SetAnchorVer(0.0f, 1.0f);
			mParamEditBox->SetAnchorParamVer(4.0f, -4.0f);
			mParamEditBox->SetText("0");
			mParamEditBox->GetInputText()->SetFontScale(0.7f);
			mParamEditBox->Enable(false);
			mParamEditBox->SetUserData("BBlock", this);
			mParamEditBox->SetMemUICallback(this, (UIFrame::MemUICallback)(&BBlock::_UICallback));
			mBlockTextName->Show(false);
			_SetFont(mParamEditBox->GetInputText());
		}
		else if (LBlock::PT_ENUM == pt)
		{
			if (mParamComboBox)
				DetachChild(mParamComboBox);

			Float4 borderColor4 = GetBoardColor();
			Float3 borderColor3 = MathHelp::Float4ToFloat3(borderColor4);

			mParamComboBox = new0 UIComboBox();
			AttachChild(mParamComboBox);
			mParamComboBox->GetChooseList()->SetTextAlignLeftPos(0.0f);
			mParamComboBox->GetChooseList()->SetFont("Data/BlueBlock/fonts/font.ttf");
			mParamComboBox->GetChooseList()->SetTextColor(Float3::WHITE);
			mParamComboBox->GetSelectButton()->SetStateColor(UIButtonBase::BS_NORMAL, borderColor3);
			mParamComboBox->GetSelectButton()->SetStateColor(UIButtonBase::BS_HOVERED, borderColor3);
			mParamComboBox->GetSelectButton()->SetStateColor(UIButtonBase::BS_PRESSED, borderColor3);
			mParamComboBox->GetSelectButton()->SetStateBrightness(UIButtonBase::BS_NORMAL, 0.8f);
			mParamComboBox->GetSelectButton()->SetStateBrightness(UIButtonBase::BS_HOVERED, 1.2f);
			mParamComboBox->GetSelectButton()->SetStateBrightness(UIButtonBase::BS_PRESSED, 0.6f);
			mParamComboBox->GetChooseList()->SetItemBackColor(borderColor3);
			mParamComboBox->SetSaveWriteIngore(true);
			mParamComboBox->LocalTransform.SetTranslateY(-10.0f);
			mParamComboBox->SetAnchorHor(0.0f, 1.0f);
			mParamComboBox->SetAnchorParamHor(2.0f, -2.0f);
			mParamComboBox->SetAnchorVer(0.0f, 1.0f);
			mParamComboBox->SetAnchorParamVer(2.0f, -2.0f);
			mParamComboBox->Enable(false);
			mParamComboBox->SetUserData("BBlock", this);
			mParamComboBox->GetChooseList()->SetSliderSize(20.0f);
			mParamComboBox->GetChooseList()->SetItemHeight(30.0f);
			mParamComboBox->SetMemUICallback(this, (UIFrame::MemUICallback)(&BBlock::_UICallback));
		}
		else if (LBlock::PT_ENUMSTRING == pt)
		{
			if (mParamComboBox)
				DetachChild(mParamComboBox);

			Float4 borderColor4 = GetBoardColor();
			Float3 borderColor3 = MathHelp::Float4ToFloat3(borderColor4);

			mParamComboBox = new0 UIComboBox();
			AttachChild(mParamComboBox);
			mParamComboBox->GetChooseList()->SetTextAlignLeftPos(0.0f);
			mParamComboBox->GetChooseList()->SetFont("Data/BlueBlock/fonts/font.ttf");
			mParamComboBox->GetChooseList()->SetTextColor(Float3::WHITE);
			mParamComboBox->GetSelectButton()->SetStateColor(UIButtonBase::BS_NORMAL, borderColor3);
			mParamComboBox->GetSelectButton()->SetStateColor(UIButtonBase::BS_HOVERED, borderColor3);
			mParamComboBox->GetSelectButton()->SetStateColor(UIButtonBase::BS_PRESSED, borderColor3);
			mParamComboBox->GetSelectButton()->SetStateBrightness(UIButtonBase::BS_NORMAL, 0.8f);
			mParamComboBox->GetSelectButton()->SetStateBrightness(UIButtonBase::BS_HOVERED, 1.2f);
			mParamComboBox->GetSelectButton()->SetStateBrightness(UIButtonBase::BS_PRESSED, 0.6f);
			mParamComboBox->GetChooseList()->SetItemBackColor(borderColor3);
			mParamComboBox->SetSaveWriteIngore(true);
			mParamComboBox->LocalTransform.SetTranslateY(-10.0f);
			mParamComboBox->SetAnchorHor(0.0f, 1.0f);
			mParamComboBox->SetAnchorParamHor(2.0f, -2.0f);
			mParamComboBox->SetAnchorVer(0.0f, 1.0f);
			mParamComboBox->SetAnchorParamVer(2.0f, -2.0f);
			mParamComboBox->Enable(false);
			mParamComboBox->SetUserData("BBlock", this);
			mParamComboBox->GetChooseList()->SetSliderSize(20.0f);
			mParamComboBox->GetChooseList()->SetItemHeight(30.0f);
			mParamComboBox->SetMemUICallback(this, (UIFrame::MemUICallback)(&BBlock::_UICallback));
		}
		else if (LBlock::PT_VARIABLESELECT == pt || LBlock::PT_VALUESELECT == pt)
		{
			if (mParamComboBox)
				DetachChild(mParamComboBox);

			Float4 borderColor4 = GetBoardColor();
			Float3 borderColor3 = MathHelp::Float4ToFloat3(borderColor4);

			mParamComboBox = new0 UIComboBox();
			AttachChild(mParamComboBox);
			mParamComboBox->GetChooseList()->SetTextAlignLeftPos(0.0f);
			mParamComboBox->GetSelectButton()->SetStateColor(UIButtonBase::BS_NORMAL, borderColor3);
			mParamComboBox->GetSelectButton()->SetStateColor(UIButtonBase::BS_HOVERED, borderColor3);
			mParamComboBox->GetSelectButton()->SetStateColor(UIButtonBase::BS_PRESSED, borderColor3);
			mParamComboBox->GetSelectButton()->SetStateBrightness(UIButtonBase::BS_NORMAL, 0.8f);
			mParamComboBox->GetSelectButton()->SetStateBrightness(UIButtonBase::BS_HOVERED, 1.2f);
			mParamComboBox->GetSelectButton()->SetStateBrightness(UIButtonBase::BS_PRESSED, 0.6f);
			mParamComboBox->GetChooseList()->SetItemBackColor(borderColor3);

			mParamComboBox->SetSaveWriteIngore(true);
			mParamComboBox->LocalTransform.SetTranslateY(-10.0f);
			mParamComboBox->SetAnchorHor(0.0f, 1.0f);
			mParamComboBox->SetAnchorParamHor(2.0f, -2.0f);
			mParamComboBox->SetAnchorVer(0.0f, 1.0f);
			mParamComboBox->SetAnchorParamVer(2.0f, -2.0f);
			mParamComboBox->Enable(false);
			mParamComboBox->SetUserData("BBlock", this);
			mParamComboBox->GetChooseList()->SetSliderSize(20.0f);
			mParamComboBox->GetChooseList()->SetItemHeight(30.0f);
			mParamComboBox->SetMemUICallback(this, (UIFrame::MemUICallback)(&BBlock::_UICallback));
		}
	}

	if (mPic_Type)
		DetachChild(mPic_Type);

	if ((ST_FUN_OUTPUT == st && !mBlock->IsFunOutputConvertToGeneral()) || ST_PARAM == st)
	{

		LBlock::ParamType pt = mBlock->GetParamType();

		mPic_Type = new0 UIFPicBox();
		AttachChild(mPic_Type);
		mPic_Type->SetDoPick(false);
		mPic_Type->SetSaveWriteIngore(true);
		mPic_Type->LocalTransform.SetTranslateY(-5.0f);
		mPic_Type->GetUIPicBox()->SetTexture("Data/engine/white.png");
		mPic_Type->SetColor(Float3::BLACK);
		mPic_Type->SetAnchorHor(0.0f, 0.0f);
		mPic_Type->SetAnchorVer(0.0f, 1.0f);
		mPic_Type->SetPivot(0.0f, 0.5f);
		mPic_Type->SetWidth(4.0f);

		std::vector<FunParam> params = mBlock->GetFunObj().GetOutParams();
		if ((int)params.size() > 0)
		{
			FunParam fp = params[0];
			Float3 color = PX2_BBM.GetParamTypeColor(fp.Type);
			mPic_Type->SetColor(color);
		}
		else
		{
			std::vector<FunParam> paramsIn = mBlock->GetFunObj().GetInParams();
			if ((int)paramsIn.size() > 0)
			{
				FunParam fp = paramsIn[0];
				Float3 color = PX2_BBM.GetParamTypeColor(fp.Type);
				mPic_Type->SetColor(color);
			}
		}
	}

	if ((ST_FUN == st || ST_FUN_OUTPUT == st) && mBlock->GetFunObj().SigletonName.empty() &&
		!mBlock->GetClsName().empty())
	{
		if (mCheck_UseThisPointer)
			DetachChild(mCheck_UseThisPointer);

		mCheck_UseThisPointer = new0 UICheckButton();
		AttachChild(mCheck_UseThisPointer);
		mCheck_UseThisPointer->SetSaveWriteIngore(true);
		mCheck_UseThisPointer->SetName("CheckUseThisPointer");
		mCheck_UseThisPointer->LocalTransform.SetTranslateY(-2.0f);
		mCheck_UseThisPointer->SetPivot(0.0f, 1.0f);
		mCheck_UseThisPointer->SetAnchorHor(0.0f, 0.0f);
		mCheck_UseThisPointer->SetAnchorParamHor(12.0f, 12.0f);
		mCheck_UseThisPointer->SetAnchorVer(1.0f, 1.0f);
		mCheck_UseThisPointer->SetAnchorParamVer(-4.0f, -4.0f);
		mCheck_UseThisPointer->SetSize(10.0f, 10.0f);
		mCheck_UseThisPointer->SetMemUICallback(this, (UIFrame::MemUICallback)(&BBlock::_UICallback));
		mCheck_UseThisPointer->Check(mBlock->IsUseThisPointer(), false);
	}

	if (ST_FUN_OUTPUT == st || (ST_FUN == st && mBlock->IsFunOutputConvertToGeneral()))
	{
		//if (mPic_Convert)
		//	DetachChild(mPic_Convert);

		//mPic_Convert = new0 UIFPicBox();
		//AttachChild(mPic_Convert);
		//mPic_Convert->SetSaveWriteIngore(true);
		//mPic_Convert->LocalTransform.SetTranslateY(-2.0f);
		//mPic_Convert->GetUIPicBox()->SetTexture(
		//	"Data/BlueBlock/images/block/convert.png");
		//mPic_Convert->SetAlpha(0.3f);
		//mPic_Convert->SetColor(Float3::BLACK);
		//mPic_Convert->SetPivot(0.0f, 1.0f);
		//mPic_Convert->SetAnchorHor(0.0f, 0.0f);
		//mPic_Convert->SetAnchorParamHor(1.0f, 1.0f);
		//mPic_Convert->SetAnchorVer(1.0f, 1.0f);
		//mPic_Convert->SetAnchorParamVer(-1.0f, -1.0f);
		//mPic_Convert->AutoMakeSizeFixable();
		//mPic_Convert->LocalTransform.SetUniformScale(0.3f);
	}
}
//----------------------------------------------------------------------------
void BBlock::_UICallback(UIFrame *frame, UICallType type)
{
	UIEditBox *editBox = DynamicCast<UIEditBox>(frame);
	if (editBox)
	{
		if (UICT_EDITBOX_TEXTCHANGED == type)
		{
			const std::string &strText = editBox->GetText();

			BBlock *block = editBox->GetUserData<BBlock*>("BBlock");
			if (block)
			{
				LBlock *lBlock = block->GetLBlock();
				if (lBlock)
				{
					LParam *lParam = lBlock->GetLParamByName("val");
					if (lParam)
					{
						lParam->SetValueFromString(strText);
					}
				}

				PX2_BBM.CompileSetGenScript();
				
				mIsNeedUpdateWidth = true;
			}
		}
	}
	UIComboBox *comboBox = DynamicCast<UIComboBox>(frame);
	if (comboBox)
	{
		if (UICT_COMBOBOX_CHOOSED == type)
		{
			UIItem *chooseItem = comboBox->GetChooseItem();
			std::string strText = comboBox->GetChooseStr();

			BBlock *block = comboBox->GetUserData<BBlock*>("BBlock");
			if (block)
			{
				LBlock *lBlock = block->GetLBlock();
				if (lBlock)
				{
					const std::string &name = lBlock->GetName();

					LParam *lParam = lBlock->GetLParamByName("val");
					if (lParam)
					{ 
						if (LBlock::PT_VARIABLESELECT == lBlock->GetParamType() ||
							LBlock::PT_VALUESELECT == lBlock->GetParamType())
						{
							if (chooseItem)
							{
								std::string paramName = chooseItem->GetUserData<std::string>("ParamName");
								lParam->SetValueFromString(paramName);
							}
						}
						else if (LBlock::PT_ENUM == lBlock->GetParamType())
						{
							std::string paramName = chooseItem->GetUserData<std::string>("ParamName");
							lParam->SetValueFromString(std::string("BBlockSystem") + "." + paramName);
						}
						else if (LBlock::PT_ENUMSTRING == lBlock->GetParamType())
						{
							std::string paramName = chooseItem->GetUserData<std::string>("ParamName");
							lParam->SetValueFromString(name + "::" + paramName);
						}
					}

					PX2_BBM.CompileSetGenScript();
				}
			}
		}
	}
	UICheckButton *checkBut = DynamicCast<UICheckButton>(frame);
	if (checkBut)
	{
		const std::string &name = frame->GetName();
		if ("CheckConvertOutput" == name)
		{
			if (UICT_CHECKED == type)
			{
				if (mBlock)
					mBlock->SetFunOutputConvertToGeneral(true);
			}
			else if (UICT_DISCHECKED == type)
			{
				if (mBlock)
					mBlock->SetFunOutputConvertToGeneral(false);
			}
		}
		else if ("CheckUseThisPointer" == name)
		{
			if (UICT_CHECKED == type)
			{
				if (mBlock)
					mBlock->SetUseThisPointer(true);
			}
			else if (UICT_DISCHECKED == type)
			{
				if (mBlock)
					mBlock->SetUseThisPointer(false);
			}
		}

		mIsNeedReSet = true;
	}
}
//----------------------------------------------------------------------------
void BBlock::SetDoReset()
{
	mIsNeedReSet = true;
}
//----------------------------------------------------------------------------
void BBlock::_UpdateParamWidth()
{
	LBlock::ParamType pt = mBlock->GetParamType();
	if (LBlock::PT_ENUM == pt || LBlock::PT_ENUMSTRING == pt || LBlock::PT_VALUESELECT == pt ||
		LBlock::PT_VARIABLESELECT == pt)
	{
		FunObject funObj = mBlock->GetFunObj();
		float textNameWidth = mBlockTextName->GetText()->GetTextWidth();

		float combosMaxWidth = 0;
		std::vector<LParamPtr> &inputParams = mBlock->GetInputParamsVec();
		for (int i = 0; i < (int)inputParams.size(); i++)
		{
			LParam *lParam = inputParams[i];
			const std::string &paramName = lParam->GetName();
			float paramNameTextWidth = mBlockTextName->GetText()->GetTextWidth(paramName);
			if (paramNameTextWidth > combosMaxWidth)
				combosMaxWidth = paramNameTextWidth;
		}
		combosMaxWidth += mParamComboBox->GetChooseList()->GetSliderSize();

		if (combosMaxWidth < BDefine::BlockParamEditBoxMinWidth)
			combosMaxWidth = BDefine::BlockParamEditBoxMinWidth;

		mBlockTextName->SetAnchorParamHor(BDefine::BlockParamLeft + BDefine::BlockTitleParamHorSpace, -(combosMaxWidth + BDefine::BlockTitleParamHorSpace));
		mParamComboBox->SetAnchorParamHor(BDefine::BlockParamLeft + BDefine::BlockTitleParamHorSpace + textNameWidth + BDefine::BlockTitleParamHorSpace, -BDefine::BlockTitleParamHorSpace);

		if (mPic_Type && LBlock::PT_VARIABLESELECT != pt)
		{
			mPic_Type->Show(false);
		}

		float allWidth = BDefine::BlockParamLeft + BDefine::BlockTitleParamHorSpace + textNameWidth + BDefine::BlockTitleParamHorSpace
			+ combosMaxWidth + BDefine::BlockTitleParamHorSpace;
		SetWidth(allWidth);
	}
	else if (LBlock::PT_VALUE == pt)
	{
		float editBoxTextWidth = mParamEditBox->GetInputText()->GetTextWidth();

		if (editBoxTextWidth < BDefine::BlockParamEditBoxMinWidth)
			editBoxTextWidth = BDefine::BlockParamEditBoxMinWidth;

		if (mPic_Type)
		{
			float allWidth = BDefine::BlockParamLeft + BDefine::BlockTitleParamHorSpace + editBoxTextWidth + BDefine::BlockTitleParamHorSpace +
				BDefine::BlockTitleParamHorSpace;
			SetWidth(allWidth);

			mParamEditBox->SetAnchorParamHor(BDefine::BlockParamLeft + BDefine::BlockTitleParamHorSpace, -BDefine::BlockTitleParamHorSpace - BDefine::BlockTitleParamHorSpace);
		}
	}
	else if (LBlock::PT_CONST == pt || LBlock::PT_VARIABLE == pt)
	{
		if (mPic_Type)
		{
			float allWidth = BDefine::BlockParamLeft +  BDefine::BlockTitleParamHorSpace + 
				mBlockTextName->GetText()->GetTextWidth() + BDefine::BlockTitleParamHorSpace;
			SetWidth(allWidth);
			mBlockTextName->SetAnchorParamHor(BDefine::BlockParamLeft + BDefine::BlockTitleParamHorSpace, -BDefine::BlockTitleParamHorSpace);
		}
	}
}
//----------------------------------------------------------------------------
void BBlock::_Init()
{
	mIsDoSetTexture = false;
	if (mIsDoSetTexture)
		mHeightInOutAdjust = BDefine::ParamInOutAdjust;
	else
		mHeightInOutAdjust = 0.0f;

	mState = BS_NORMAL;
	mIsPressedMoved = false;
	mIsSelected = false;

	mIsNeedReGenBlock = true;
	mEditState = ES_INIT;

	SetPivot(0.0f, 1.0f);

	mShapeType = ST_FUN;
	SetSize(BDefine::BlockFunMinWidth, BDefine::BlockHeight);

	SetWidget(true);

	mIsNeedReSet = false;

	mIsNeedUpdateWidth = true;
}
//----------------------------------------------------------------------------
void BBlock::UpdateWorldData(double applicationTime, double elapsedTime)
{
	UIFrame::UpdateWorldData(applicationTime, elapsedTime);

	if (mIsNeedUpdateWidth)
	{
		mIsNeedUpdateWidth = false;
		_UpdateParamWidth();

		mIsNeedReGenBlock = true;
	}

	if (mIsNeedReGenBlock)
	{
		mIsNeedReGenBlock = false;
		_ReGenLayOut();
	}

	if (mIsNeedReSet)
	{
		mIsNeedReSet = false;
		ResetBlock();

		PX2_BBM._GenDefaultParams(this);
	}
}
//----------------------------------------------------------------------------
float BBlock::GetBlockHeightWithNext()
{
	float height = GetHeight();

	BBlockConnector *cnt = GetBlockConnectorByName("Next");
	if (cnt)
	{
		height += cnt->GetBlockAllHeight();
	}

	return height;
}
//----------------------------------------------------------------------------
void BBlock::OnSelect(bool select)
{
	mIsSelected = select;
	mIsNeedReGenBlock = true;
}
//----------------------------------------------------------------------------
void BBlock::SetPickingOffset(const Float2 &offset)
{
	mPickingOffset = offset;
}
//----------------------------------------------------------------------------
const Float2 &BBlock::GetPickingOffset() const
{
	return mPickingOffset;
}
//----------------------------------------------------------------------------
void BBlock::_GenLayout()
{
	float width = 0.0f;
	float height = 0.0f;
	if (ST_FUN == mShapeType)
	{
		_GenBlockFun(width, height, false);
		SetWidth(width);
		SetHeight(height);
	}
	else if (ST_FUN_OUTPUT == mShapeType)
	{
		_GenBlockFun(width, height, true);
		SetWidth(width);
		SetHeight(height);
	}
	else if (ST_PARAM == mShapeType)
	{
		_GenBlockParam(width, height);
		SetHeight(height);
	}
	else if (ST_FUN_OPERATOR == mShapeType)
	{
		_GenBlockFunOperator(width, height);
		SetWidth(width);
		SetHeight(height);
	}
	else if (ST_IF == mShapeType)
	{
		std::vector<std::string> params;
		params.push_back("IfDo");
		_GenBlockCtrl(width, height, "If", params);

		SetWidth(width);
		SetHeight(height);
	}
	else if (ST_WHILE == mShapeType)
	{
		std::vector<std::string> params;
		params.push_back("WhileDo");
		_GenBlockCtrl(width, height, "While", params);

		SetWidth(width);
		SetHeight(height);
	}
	else if (ST_EVENT == mShapeType)
	{
		std::vector<std::string> params;
		params.push_back("EventDo");
		_GenBlockCtrl(width, height, "Event", params);

		SetWidth(width);
		SetHeight(height);
	}
	else if (ST_COROUTINE == mShapeType)
	{
		std::vector<std::string> params;
		params.push_back("CorDo");
		_GenBlockCtrl(width, height, "", params);

		SetWidth(width);
		SetHeight(height);
	}
	else if (ST_IFELSE == mShapeType)
	{
		std::vector<std::string> params;
		params.push_back("IfDo");
		params.push_back("ElseDo");
		_GenBlockCtrl(width, height, "If", params);

		SetWidth(width);
		SetHeight(height);
	}
	else if (ST_PROGRAM == mShapeType)
	{
		std::vector<std::string> params;
		params.push_back("Start");
		params.push_back("FixUpdate");
		_GenBlockCtrl(width, height, "", params);

		SetWidth(width);
		SetHeight(height);
	}
	else if (ST_PROGRAMSTART == mShapeType)
	{
		std::vector<std::string> params;
		params.push_back("Start");
		_GenBlockCtrl(width, height, "", params);

		SetWidth(width);
		SetHeight(height);
	}
	else if (ST_PROGRAMFIXUPDATE == mShapeType)
	{
		std::vector<std::string> params;
		params.push_back("FixUpdate");
		_GenBlockCtrl(width, height, "", params);

		SetWidth(width);
		SetHeight(height);
	}

	if (mBackPic0)
		mBackPic0->SetAnchorParamHor(BDefine::BlockSpace, 0.0f);

	if (mBackPicBoxVer)
	{
		mBackPicBoxVer->SetAnchorParamHor(BDefine::BlockSpace, 0.0f);
	}

	SetBoardColor(GetBoardColor());

	mPickRangeSizeNodes.clear();
	if (mBackPic0)
		mPickRangeSizeNodes.push_back(mBackPic0);
	if (mBackPic1)
		mPickRangeSizeNodes.push_back(mBackPic1);
	if (mBackPic2)
		mPickRangeSizeNodes.push_back(mBackPic2);
	if (mBackPic3)
		mPickRangeSizeNodes.push_back(mBackPic3);
	if (mBackPicBoxVer)
		mPickRangeSizeNodes.push_back(mBackPicBoxVer);

	SetPickRangeMovables(mPickRangeSizeNodes);
}
//----------------------------------------------------------------------------
void BBlock::_GenBlockFun(float &outWidth, float &outHeight, bool isOutPut)
{
	if (!isOutPut)
	{
		if (mBackPic0)
		{
			mBackPic0->Show(true);
			if (mIsDoSetTexture)
			{
				mBackPic0->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/block.png");
				mBackPic0->GetUIPicBox()->SetTexCornerSize(BDefine::CornorFunLeft, BDefine::CornorFunRight);
			}
			else
				mBackPic0->GetUIPicBox()->SetTexture("Data/PhoenixCode/images/ui/common/whiteline.png");
			mBackPic0->SetAnchorParamVer(-mHeightInOutAdjust + BDefine::BlockSpace, 0.0f);
		}
	}
	else
	{
		if (mBackPic0)
		{
			mBackPic0->Show(true);
			if (mIsDoSetTexture)
			{
				mBackPic0->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/param.png");
				mBackPic0->GetUIPicBox()->SetTexCornerSize(BDefine::CornorGeneral, BDefine::CornorGeneral);
			}
			else
			{
				mBackPic0->GetUIPicBox()->SetPicBoxType(UIPicBox::PBT_NINE);
				mBackPic0->GetUIPicBox()->SetTexture("Data/PhoenixCode/images/ui/common/whitelineleft.png");
				mBackPic0->GetUIPicBox()->SetTexCornerSize(BDefine::CornorGeneral, BDefine::CornorGeneral);
			}

			mBackPic0->SetAnchorParamVer(0.0f, 0.0f);
		}
	}

	float posHor = 0.0f;
	float height = BDefine::BlockHeight;
	if (isOutPut)
		height = BDefine::ParamHeight;

	UIText *text = mBlockTextName->GetText();
	float nameWidth = text->GetTextWidth();
	
	float cntMaxHeight = height;

	// outinput
	std::vector<LParamPtr> &paramsVecIn = mBlock->GetInputParamsVec();
	int numParamsIn = (int)paramsVecIn.size();

	posHor = nameWidth + BDefine::BlockTitleParamHor;
	for (int i = 0; i < numParamsIn; i++)
	{
		posHor += BDefine::BlockTitleParamHorSpace;

		LParam *param = paramsVecIn[i];
		const std::string &paramName = param->GetName();
		BBlockConnector *cnt = GetBlockConnectorByName(paramName);
		if (cnt)
		{
			UIFText *text = cnt->GetNameText();
			if (text)
			{
				float textWidth = text->GetText()->GetTextWidth();
				posHor += textWidth;
			}

			posHor += BDefine::BlockTitleParamHorSpace;

			float contentAllWidth = cnt->GetBlockAllWidth();
			int numChildBlocks = 0;
			float contentAllHeight = cnt->GetBlockAllHeight(&numChildBlocks);
			cnt->SetPivot(0.0f, 0.5f);
			cnt->SetAnchorHor(0.0f, 0.0f);
			cnt->SetAnchorVer(0.5f, 0.5f);
			cnt->SetAnchorParamHor(posHor, posHor);
			cnt->SetAnchorParamVer(0.0f, 0.0f);

			posHor += contentAllWidth;

			if (numChildBlocks > 0)
			{
				contentAllHeight += (BDefine::BlockHeight - BDefine::ParamHeight);
			}

			if (contentAllHeight > cntMaxHeight)
				cntMaxHeight = contentAllHeight;
		}
	}

	posHor += BDefine::BlockTitleParamHorSpace;
	height += (cntMaxHeight - BDefine::ParamHeight);

	if (posHor < BDefine::BlockFunMinWidth)
		posHor = BDefine::BlockFunMinWidth;

	outWidth = posHor;
	outHeight = height;
}
//----------------------------------------------------------------------------
void BBlock::_GenBlockFunOperator(float &outWidth, float &outHeight)
{
	if (mBackPic0)
	{
		mBackPic0->Show(true);
		if (mIsDoSetTexture)
		{
			mBackPic0->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/param.png");
			mBackPic0->GetUIPicBox()->SetTexCornerSize(BDefine::CornorGeneral, BDefine::CornorGeneral);
		}
		else
			mBackPic0->GetUIPicBox()->SetTexture("Data/engine/white.png");
	}

	float posHor = 0.0f;
	float height = BDefine::ParamHeight;

	UIText *text = mBlockTextName->GetText();
	float nameWidth = text->GetTextWidth();

	float cntMaxHeight = height;

	// outinput
	std::vector<LParamPtr> &paramsVecIn = mBlock->GetInputParamsVec();
	int numParamsIn = (int)paramsVecIn.size();
	for (int i = 0; i < numParamsIn; i++)
	{
		if (0 == i)
		{
			posHor += BDefine::BlockTitleParamHorSpace;
		}

		LParam *param = paramsVecIn[i];
		const std::string &paramName = param->GetName();
		BBlockConnector *cnt = GetBlockConnectorByName(paramName);
		if (cnt)
		{
			UIFText *text = cnt->GetNameText();
			if (text)
			{
				float textWidth = text->GetText()->GetTextWidth();
				posHor += textWidth;
			}

			posHor += BDefine::BlockTitleParamHorSpace;

			float contentAllWidth = cnt->GetBlockAllWidth();
			int numChildBlocks = 0;
			float contentAllHeight = cnt->GetBlockAllHeight(&numChildBlocks);
			cnt->SetPivot(0.0f, 0.5f);
			cnt->SetAnchorHor(0.0f, 0.0f);
			cnt->SetAnchorVer(0.5f, 0.5f);
			cnt->SetAnchorParamHor(posHor, posHor);
			cnt->SetAnchorParamVer(0.0f, 0.0f);

			posHor += contentAllWidth;

			if (numChildBlocks > 0)
			{
				contentAllHeight += (BDefine::BlockHeight - BDefine::ParamHeight);
			}

			if (contentAllHeight > cntMaxHeight)
				cntMaxHeight = contentAllHeight;
		}

		if (0 == i)
		{
			posHor += BDefine::BlockTitleParamHorSpace;
			mBlockTextName->SetAnchorParamHor(posHor, posHor);
			posHor += nameWidth;
			posHor += BDefine::BlockTitleParamHorSpace;
		}
	}

	posHor += BDefine::BlockTitleParamHorSpace;
	height += (cntMaxHeight - BDefine::ParamHeight);

	outWidth = posHor;
	outHeight = height;
}
//----------------------------------------------------------------------------
void BBlock::_GenBlockParam(float &outWidth, float &outHeight)
{
	if (mBackPic0)
	{
		mBackPic0->Show(true);
		if (mIsDoSetTexture)
		{
			mBackPic0->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/param.png");
			mBackPic0->GetUIPicBox()->SetTexCornerSize(BDefine::CornorGeneral, BDefine::CornorGeneral);
		}
		else
		{
			mBackPic0->GetUIPicBox()->SetPicBoxType(UIPicBox::PBT_NINE);
			mBackPic0->GetUIPicBox()->SetTexture("Data/PhoenixCode/images/ui/common/whitelineleft.png");
			mBackPic0->GetUIPicBox()->SetTexCornerSize(BDefine::CornorGeneral, BDefine::CornorGeneral);
		}
	}

	float posHeight = 0.0f;
	posHeight = BDefine::ParamHeight;

	outHeight = posHeight;
}
//----------------------------------------------------------------------------
void BBlock::_GenBlockCtrl(float &outWidth, float &outHeight,
	const std::string &paramCnt,
	std::vector<std::string> &cnts)
{
	if (cnts.empty())
		return;

	float blockWidth = 0.0f;

	float anchorParamHor = mBlockTextName->GetAnchorParamHor()[0];
	std::string nameText = mBlockTextName->GetText()->GetText();
	float nameTextWidth = mBlockTextName->GetText()->GetTextWidth();
	float textAnchorParamHor = mBlockTextName->GetAnchorParamHor()[0];

	mBackPic0->SetPivot(0.0f, 1.0f);
	mBackPic0->SetAnchorHor(0.0f, 1.0f);
	mBackPic0->SetAnchorVer(1.0f, 1.0f);
	if (mIsDoSetTexture)
	{
		mBackPic0->GetUIPicBox()->SetTexCornerSize(BDefine::CornorCtrlLeft, BDefine::CornorFunRight);
	}

	float posVer = 0.0f;
	float titleBlockHeight = BDefine::BlockHeight;

	LBlock *lBlock = GetLBlock();
	LBlock::CtrlType ct = lBlock->GetCtrlType();

	if (LBlock::CT_PROGRAM == ct || LBlock::CT_PROGRAMSTART == ct || LBlock::CT_PROGRAMFIXUPDATE == ct 
		|| LBlock::CT_COROUTINE == ct)
	{
		titleBlockHeight = BDefine::BlockHeightTopTitle;
		posVer -= titleBlockHeight;

		if (mIsDoSetTexture)
		{
			if (LBlock::CT_PROGRAM == ct || LBlock::CT_PROGRAMSTART == ct || LBlock::CT_PROGRAMFIXUPDATE == ct)
				mBackPic0->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/p0.png");
			else
				mBackPic0->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/q0.png");
		}
		else
		{
			mBackPic0->GetUIPicBox()->SetTexture("Data/engine/white.png");
		}

		blockWidth = anchorParamHor + nameTextWidth + BDefine::BlockTitleParamHorSpace;

		titleBlockHeight += BDefine::BlockHeightTopTitle;

		if (blockWidth < BDefine::BlockFunMinWidth)
			blockWidth = BDefine::BlockFunMinWidth;
		mBackPic0->SetWidth(blockWidth);
		mBackPic0->SetHeight(titleBlockHeight - BDefine::BlockSpace);

		posVer -= (BDefine::BlockHeightTopTitle);
	}
	else
	{
		if (mIsDoSetTexture)
		{
			mBackPic0->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/q0.png");
		}
		else
		{
			mBackPic0->GetUIPicBox()->SetTexture("Data/engine/white.png");
		}

		blockWidth = anchorParamHor + nameTextWidth + BDefine::BlockTitleParamHorSpace;

		// param
		if (!paramCnt.empty())
		{
			BBlockConnector *cnt = GetBlockConnectorByName(paramCnt);
			cnt->GetNameText()->Show(false);
			float blockAllW = cnt->GetBlockAllWidth();
			float blockAllHeight = cnt->GetBlockAllHeight();

			blockWidth += blockAllW;
			titleBlockHeight = blockAllHeight + (BDefine::BlockHeight - BDefine::ParamHeight);

			float horCntPos = textAnchorParamHor + nameTextWidth + BDefine::BlockTitleParamHorSpace;
			cnt->SetPivot(0.0f, 0.5f);
			cnt->SetAnchorHor(0.0f, 0.0f);
			cnt->SetAnchorParamHor(horCntPos, horCntPos);
			cnt->SetAnchorVer(1.0f, 1.0f);
			cnt->SetAnchorParamVer(-titleBlockHeight*0.5f, -titleBlockHeight*0.5f);

			float textPos = anchorParamHor + nameTextWidth + BDefine::BlockTitleParamHorSpace + blockAllW + BDefine::BlockTitleParamHorSpace
				- BDefine::BlockHeightVer;
			BBlockConnector *cntFirst = GetBlockConnectorByName(cnts[0]);
			cntFirst->GetNameText()->SetAnchorParamHor(textPos, 0.0f);
			cntFirst->GetNameText()->SetHeight(titleBlockHeight);

			blockWidth = anchorParamHor + nameTextWidth + BDefine::BlockTitleParamHorSpace + blockAllW + BDefine::BlockTitleParamHorSpace +
				cntFirst->GetNameText()->GetText()->GetTextWidth() + BDefine::BlockTitleParamHorSpace;
		}

		if (blockWidth < BDefine::BlockFunMinWidth)
			blockWidth = BDefine::BlockFunMinWidth;
		mBackPic0->SetWidth(blockWidth);
		mBackPic0->SetHeight(titleBlockHeight - BDefine::BlockSpace);

		posVer -= (titleBlockHeight);
	}

	int cntSize = (int)cnts.size();
	for (int i = 0; i < cntSize; i++)
	{
		UIFPicBox *usePicBoxLast = mBackPic0;
		UIFPicBox *usePicBox = mBackPic0;

		bool isLast = (i == cntSize - 1);
		const std::string &cntStr = cnts[i];

		BBlockConnector *cnt = GetBlockConnectorByName(cntStr);
		cnt->SetPivot(0.0f, 1.0f);
		cnt->SetAnchorHor(0.0f, 0.0f);
		cnt->SetAnchorParamHor(BDefine::BlockHeightVer, BDefine::BlockHeightVer);
		cnt->SetAnchorVer(1.0f, 1.0f);
		cnt->SetAnchorParamVer(posVer, posVer);

		float cntAllWidth = cnt->GetNameText()->GetText()->GetTextWidth() + BDefine::BlockTitleParamHorSpace;
		float allWidth = BDefine::BlockHeightVer + cntAllWidth;
			
		if (allWidth > blockWidth)
			blockWidth = allWidth;

		float cntAllHeight = cnt->GetBlockAllHeight();
		posVer -= cntAllHeight;
		posVer -= BDefine::ParamInOutAdjust;

		if (0 == i)
		{
			if (!mBackPic1)
			{
				mBackPic1 = new0 UIFPicBox();
				if (mIsDoSetTexture)
				{
					mBackPic1->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/block.png");
				}
				else
					mBackPic1->GetUIPicBox()->SetTexture("Data/engine/white.png");
				AttachChild(mBackPic1);
			}
			usePicBoxLast = 0;
			usePicBox = mBackPic1;
		}
		else if (1 == i)
		{
			if (!mBackPic2)
			{
				mBackPic2 = new0 UIFPicBox();
				if (mIsDoSetTexture)
				{
					mBackPic2->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/block.png");
				}
				else
					mBackPic2->GetUIPicBox()->SetTexture("Data/engine/white.png");
				AttachChild(mBackPic2);
			}
			usePicBoxLast = mBackPic1;
			usePicBox = mBackPic2;
		}
		else if (2 == i)
		{
			if (!mBackPic3)
			{
				mBackPic3 = new0 UIFPicBox();
				if (mIsDoSetTexture)
				{
					mBackPic3->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/block.png");
				}
				else
					mBackPic3->GetUIPicBox()->SetTexture("Data/engine/white.png");
				AttachChild(mBackPic3);
			}
			usePicBoxLast = mBackPic2;
			usePicBox = mBackPic3;
		}

		if (usePicBoxLast)
		{
			usePicBoxLast->SetName(cntStr);
		}

		float useHeight = 0.0f;
		if (!isLast)
		{
			if (mIsDoSetTexture)
				usePicBox->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/p1.png");
			else
				usePicBox->GetUIPicBox()->SetTexture("Data/engine/white.png");

			useHeight = BDefine::BlockHeightMiddle + BDefine::SquareAdjust * 2.0f - BDefine::BlockSpace;
		}
		else
		{
			if (LBlock::CT_PROGRAM == ct || LBlock::CT_PROGRAMSTART == ct || LBlock::CT_PROGRAMFIXUPDATE == ct)
			{
				if (mIsDoSetTexture)
					usePicBox->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/p2.png");
				else
					usePicBox->GetUIPicBox()->SetTexture("Data/engine/white.png");
			}
			else
			{
				if (mIsDoSetTexture)
					usePicBox->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/q1.png");
				else
					usePicBox->GetUIPicBox()->SetTexture("Data/engine/white.png");
			}

			useHeight = BDefine::BlockHeightMiddle + BDefine::SquareAdjust - BDefine::BlockSpace;
		}

		if (mIsDoSetTexture)
			usePicBox->GetUIPicBox()->SetPicBoxType(UIPicBox::PBT_NINE);
		usePicBox->SetWidget(false);
		usePicBox->SetHeight(useHeight);
		usePicBox->SetPivot(0.0f, 1.0f);
		usePicBox->SetAnchorHor(0.0f, 0.0f);
		usePicBox->SetAnchorParamHor(0.0f, 0.0f);
		usePicBox->SetAnchorVer(1.0f, 1.0f);
		usePicBox->GetUIPicBox()->SetPicBoxType(UIPicBox::PBT_NINE);
		usePicBox->SetAnchorParamVer(posVer + BDefine::SquareAdjust, posVer + BDefine::SquareAdjust);

		if (!isLast)
		{
			usePicBox->LocalTransform.SetTranslateY(-2.0f);
			usePicBox->SetAnchorParamHor(BDefine::BlockHeightVer, 0.0f);
			if (mIsDoSetTexture)
			{
				usePicBox->GetUIPicBox()->SetTexCornerSize(BDefine::CornorMiddleLeft, BDefine::CornorMiddleRight);
			}
		}
		else
		{
			usePicBox->SetAnchorParamHor(BDefine::BlockSpace, 0.0f);
			if (mIsDoSetTexture)
			{
				usePicBox->GetUIPicBox()->SetTexCornerSize(BDefine::CornorFunLeft, BDefine::CornorFunRight);
				usePicBox->AutoMakeSizeFixable();
			}
		}

		if (usePicBoxLast)
		{
			float useWidth = cntAllWidth;
			float adjustWidth = BDefine::CornorMiddleLeft.Width + BDefine::CornorMiddleRight.Width + 2.0f;
			if (useWidth < adjustWidth)
				useWidth = adjustWidth;

			usePicBoxLast->GetUIPicBox()->SetTexCornerSize(BDefine::CornorMiddleLeft, BDefine::CornorMiddleRight);
			usePicBoxLast->SetWidth(useWidth);
		}

		posVer -= BDefine::BlockHeightMiddle;
	}

	outWidth = blockWidth;
	outHeight = -posVer;

	if (!mBackPicBoxVer)
	{
		mBackPicBoxVer = new0 UIFPicBox();
		AttachChild(mBackPicBoxVer);
	}
	mBackPicBoxVer->GetUIPicBox()->SetPicBoxType(UIPicBox::PBT_NINE);
	mBackPicBoxVer->SetWidget(false);
	if (mIsDoSetTexture)
		mBackPicBoxVer->GetUIPicBox()->SetTexture("Data/BlueBlock/images/block/ver.png");
	else
		mBackPicBoxVer->GetUIPicBox()->SetTexture("Data/engine/white.png");
	mBackPicBoxVer->SetWidth(BDefine::BlockHeightVer - BDefine::BlockSpace);
	mBackPicBoxVer->SetAnchorHor(0.0f, 0.0f);
	mBackPicBoxVer->SetAnchorVer(0.0f, 1.0f);
	mBackPicBoxVer->SetAnchorParamVer(BDefine::BlockHeightMiddle,
		-titleBlockHeight + BDefine::BlockSpace);
	mBackPicBoxVer->SetPivot(0.0f, 0.5f);
}
//----------------------------------------------------------------------------
void BBlock::_DetachConnector(const std::string &name)
{
	std::vector<Pointer0<BBlockConnector> >::iterator it1 = mConnectors.begin();
	for (; it1 != mConnectors.end();)
	{
		if (name == (*it1)->GetName())
		{
			DetachChild(*it1);
			it1 = mConnectors.erase(it1);
		}
		else
		{
			it1++;
		}
	}
}
//----------------------------------------------------------------------------
void BBlock::_AddConnector(BBlockConnector *cnt)
{
	mConnectors.push_back(cnt);
}
//----------------------------------------------------------------------------
TriMesh *BBlock::_GenTriMesh(const std::vector<Vector2f> &pos,
	const std::vector<int> indexs, bool isShadow)
{
	if (pos.empty())
		return 0;

	Float2 tc0 = Float2(0.0f, 0.0f);
	VertexFormat *vformat = PX2_GR.GetVertexFormat(GraphicsRoot::VFT_PCNT1);
	int vstride = vformat->GetStride();

	Float4 color;
	if (isShadow)
	{
		if (mIsSelected)
		{
			color = Float4::MakeColor(34, 177, 76, 255);
		}
		else
		{
			color = Float4(0.1f, 0.1f, 0.1f, 0.2f);
		}
	}
	else
	{
		BBlock::BlockState bs = GetState();
		if (BS_NORMAL == bs)
		{
			color = mBoardColor;
		}
		else if (BS_PRESSED == bs)
		{
			color = Float4::MakeColor(200, 200, 200, 255);
		}
	}

	int numVertexs = (int)pos.size();
	VertexBuffer* vbuffer = new0 VertexBuffer(numVertexs, vstride);
	VertexBufferAccessor vba(vformat, vbuffer);
	for (int i = 0; i < numVertexs; i++)
	{
		vba.Position<Float3>(i) = Float3(pos[i].X(), 0.0f, pos[i].Y());
		vba.Normal<Float3>(i) = Float3(0.0f, -1.0f, 0.0f);
		vba.Color<Float4>(0, i) = color;
	}

	int numIndexes = (int)indexs.size();
	IndexBuffer* ibuffer = new0 IndexBuffer(numIndexes, sizeof(int));
	int* indices = (int*)ibuffer->GetData();
	for (int i = 0; i < numIndexes; i++)
	{
		indices[i] = indexs[i];
	}

	TriMesh *triMesh = new0 TriMesh(vformat, vbuffer, ibuffer);
	VertexColor4Material *vcMtl = new0 VertexColor4Material();
	triMesh->SetMaterialInstance(vcMtl->CreateInstance());
	if (isShadow)
		vcMtl->GetAlphaProperty(0, 0)->BlendEnabled = true;
	triMesh->UpdateModelSpace(Renderable::GU_MODEL_BOUND_ONLY);

	return triMesh;
}
//----------------------------------------------------------------------------
void BBlock::SetBoardColor(const Float4 &color)
{
	mBoardColor = color;

	Float3 color3 = MathHelp::Float4ToFloat3(mBoardColor);

	if (mBackPic0)
		mBackPic0->SetColor(color3);

	if (mBackPic1)
		mBackPic1->SetColor(color3);

	if (mBackPic2)
		mBackPic2->SetColor(color3);

	if (mBackPic3)
		mBackPic3->SetColor(color3);

	if (mBackPicBoxVer)
		mBackPicBoxVer->SetColor(color3);
}
//----------------------------------------------------------------------------
void BBlock::SetBoardBrightness(float brightness)
{
	if (mBackPic0)
		mBackPic0->SetBrightness(brightness);

	if (mBackPic1)
		mBackPic1->SetBrightness(brightness);

	if (mBackPic2)
		mBackPic2->SetBrightness(brightness);

	if (mBackPic3)
		mBackPic3->SetBrightness(brightness);

	if (mBackPicBoxVer)
		mBackPicBoxVer->SetBrightness(brightness);
}
//----------------------------------------------------------------------------
const Float4 &BBlock::GetBoardColor() const
{
	return mBoardColor;
}
//----------------------------------------------------------------------------
BBlockConnector *BBlock::GetLastNextConnector()
{
	BBlockConnector *cnt = GetBlockConnectorByName("Next");
	if (cnt)
	{
		BBlock *block = cnt->GetCurBlock();
		if (block)
		{
			return block->GetLastNextConnector();
		}
		else
		{
			return cnt;
		}
	}

	return 0;
}
//----------------------------------------------------------------------------
BBlockConnector *BBlock::GetBlockConnectorByName(const std::string &name)
{
	for (int i = 0; i < (int)mConnectors.size(); i++)
	{
		BBlockConnector *connector = mConnectors[i];
		if (name == connector->GetName())
		{
			return connector;
		}
	}

	return 0;
}
//----------------------------------------------------------------------------
bool BBlock::_IsTypeCanAdd(BBlock *block, BBlockConnector *connector)
{
	LBlock *lBlock = block->GetLBlock();
	LBlock::BlockType bt = lBlock->GetBlockType();
	LBlock::CtrlType ctrlType = lBlock->GetCtrlType();
	bool isFunOutputToGenFun = lBlock->IsFunOutputConvertToGeneral();

	BBlockConnector::ConnectorType ct = connector->GetConnectorType();
	int numChildUIBlocks = connector->GetNumChildUIBlock();

	if (BBlockConnector::CT_PARAM == ct && 
		(LBlock::MT_PARAM == bt ||
		LBlock::MT_FUNCTION_OPERATOR == bt ||
		(LBlock::MT_FUNCTION_OUTPUT == bt && !isFunOutputToGenFun) ))
	{
		if (BBlockConnector::CT_PARAM == ct && LBlock::MT_PARAM == bt)
		{
			if (lBlock->GetNumInputs() > 0)
			{
				LParam *param = lBlock->GetInputParam(0);
				if (param)
				{
					LParam *clParam = connector->GetLParam();
					FunParamType cDataType = clParam->GetDataType();
					FunParamType pDataType = param->GetDataType();

					if (clParam->IsEnum() && !clParam->IsEnum())
					{
						return false;
					}

					if (clParam->IsEnum() && clParam->IsEnum())
					{
						if (clParam->GetDataTypeName() != clParam->GetDataTypeName())
						{
							return false;
						}
					}

					if (cDataType == pDataType ||
						(FPT_CHAR == cDataType && FPT_INT==pDataType) ||
						(FPT_INT == cDataType && FPT_CHAR == pDataType)||
						(FPT_INT == cDataType && FPT_FLOAT == pDataType)||
						(FPT_FLOAT == cDataType && FPT_INT == pDataType) ||
						(FPT_POINTER == cDataType && FPT_POINTER_THIS == pDataType) ||
						(FPT_POINTER_THIS == cDataType && FPT_POINTER == pDataType))
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
		else if (BBlockConnector::CT_PARAM == ct && LBlock::MT_FUNCTION_OUTPUT == bt)
		{
			if (lBlock->GetNumOutputs() > 0)
			{
				LParam *outParam = lBlock->GetOutputParam(0);
				if (outParam)
				{
					LParam *clParam = connector->GetLParam();
					FunParamType cDataType = clParam->GetDataType();
					FunParamType pDataType = outParam->GetDataType();

					if (clParam->IsEnum() && !outParam->IsEnum())
					{
						return false;
					}

					if (clParam->IsEnum() && outParam->IsEnum())
					{
						if (clParam->GetDataTypeName() != outParam->GetDataTypeName())
						{
							return false;
						}
					}

					if (cDataType == pDataType ||
						(FPT_CHAR == cDataType && FPT_INT == pDataType) ||
						(FPT_INT == cDataType && FPT_CHAR == pDataType) ||
						(FPT_INT == cDataType && FPT_FLOAT == pDataType) ||
						(FPT_FLOAT == cDataType && FPT_INT == pDataType) ||
						(FPT_POINTER == cDataType && FPT_POINTER_THIS == pDataType) ||
						(FPT_POINTER_THIS == cDataType && FPT_POINTER == pDataType))
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}

		return true;
	}
	else if (BBlockConnector::CT_BLOCK == ct && 
		(LBlock::MT_FUNCTION_GENERAL == bt || 
		(LBlock::MT_FUNCTION_OUTPUT == bt && isFunOutputToGenFun) ||
		LBlock::MT_EVENT == bt ||
		(LBlock::MT_CONTROL == bt && (LBlock::CT_IF == ctrlType || LBlock::CT_IFELSE == ctrlType || LBlock::CT_WHILE == ctrlType || LBlock::CT_COROUTINE == ctrlType
			) ) 
			)
		)
	{
		return true;
	}
	else if (BBlockConnector::CT_NEXT == ct &&
		(LBlock::MT_FUNCTION_GENERAL == bt || 
		(LBlock::MT_FUNCTION_OUTPUT == bt && isFunOutputToGenFun) ||
		LBlock::MT_EVENT == bt ||
		(LBlock::MT_CONTROL == bt && (LBlock::CT_IF == ctrlType || LBlock::CT_IFELSE == ctrlType || LBlock::CT_WHILE == ctrlType || LBlock::CT_COROUTINE == ctrlType
			|| LBlock::CT_COROUTINE == ctrlType) )
			)
		)
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
BBlockConnector *BBlock::GetCloestConnector(BBlock *block)
{
	if (block == this)
		return 0;

	for (int i = 0; i < (int)mConnectors.size(); i++)
	{
		const APoint &blockWorldTrans = block->WorldTransform.GetTranslate();

		BBlockConnector *connector = mConnectors[i];
		const Rectf &cntWorldRect = connector->GetConnectRectFrame()->GetWorldRect();

		if (cntWorldRect.IsInsize(blockWorldTrans.X(), blockWorldTrans.Z())
			&& _IsTypeCanAdd(block, connector))
		{
			connector->ShowHitPicBox(true);
			return connector;
		}
		else
		{
			connector->ShowHitPicBox(false);
		}

		for (int j = 0; j < connector->GetNumChildren(); j++)
		{
			BBlock *uiBlock = DynamicCast<BBlock>(connector->GetChild(j));
			if (uiBlock)
			{
				BBlockConnector *cnt = uiBlock->GetCloestConnector(block);
				if (cnt)
				{
					cnt->ShowHitPicBox(true);
					return cnt;
				}
			}
		}
	}

	return 0;
}
//----------------------------------------------------------------------------
void BBlock::OnEvent(Event *ent)
{
	if (BBlockES::IsEqual(ent, BBlockES::RefreshParamObject))
	{
		FunObject *funObj = ent->GetData<FunObject*>();
		if (LBlock::PT_VARIABLESELECT == mBlock->GetFunObj().GetParamType() ||
			LBlock::PT_VALUESELECT == mBlock->GetFunObj().GetParamType())
		{
			if (funObj->Name == mBlock->GetFunObj().Name)
			{
				std::string valStr;
				LParam *lParam = mBlock->GetLParamByName("val");
				if (lParam)
				{
					valStr = lParam->GetValueStr();
				}

				mBlock->RegistFunObj(*funObj);

				mParamComboBox->RemoveAllChooseStr();

				std::vector<LParamPtr> &inputParams = mBlock->GetInputParamsVec();
				for (int i = 0; i < (int)inputParams.size(); i++)
				{
					LParam *lParam = inputParams[i];
					const std::string &paramName = lParam->GetName();

					UIItem *item = mParamComboBox->AddChooseStr(paramName);
					item->SetUserData("ParamName", paramName);
				}
				mParamComboBox->SetChooseListHeightSameWithChooses();
				if (mParamComboBox->GetChooseList()->GetHeight() > 200.0f)
					mParamComboBox->GetChooseList()->SetHeight(200.0f);
				mParamComboBox->ChooseStr(valStr);
			}

			mIsNeedUpdateWidth = true;
		}
	}
	else if (BBlockES::IsEqual(ent, BBlockES::DeleteVariable))
	{
		FunObject *funObj = ent->GetData<FunObject*>();
		const std::string &funObjName = funObj->Name;
		const std::string &name = GetName();

		if (name == funObjName)
		{
			Node *parentNode = DynamicCast<Node>(GetParent());
			if (parentNode)
			{
				parentNode->DetachChild(this);
			}
		}
	}
}
//----------------------------------------------------------------------------
std::vector<Pointer0<BBlockConnector> > &BBlock::GetConnectors()
{
	return mConnectors;
}
//----------------------------------------------------------------------------
void BBlock::_ReGenLayOut()
{
	_GenLayout();

	BBlockConnector *cnt = DynamicCast<BBlockConnector>(GetParent());
	if (cnt)
	{
		BBlock *parBlock = DynamicCast<BBlock>(cnt->GetParent());
		if (parBlock)
		{
			parBlock->_ReGenLayOut();
		}
	}
}
//----------------------------------------------------------------------------
void _UITravelSetMaskNormal(Movable *mov, Any *data, bool &goOn)
{
	PX2_UNUSED(data);
	PX2_UNUSED(goOn);

	Renderable *renderable = DynamicCast<Renderable>(mov);
	if (renderable)
	{
		StencilProperty *sp = renderable->GetMaterialInstance()->GetMaterial()
			->GetStencilProperty(0, 0);
		sp->Enabled = false;
	}
}
//----------------------------------------------------------------------------
void BBlock::OnWidgetPicked(const CanvasInputData &inputData)
{
	UIFrame::OnWidgetPicked(inputData);

	if (UIPT_PRESSED == inputData.PickType)
	{
		mIsPressedMoved = false;

		if (BS_PRESSED != GetState())
		{
			SetState(BS_PRESSED);
		}

		float pivotY = GetPivot()[1];
		const Rectf &worldRect = GetWorldRect();
		float left = worldRect.Left;
		float top = worldRect.Top;

		float offsetX = inputData.CameraLogicPos.X() - left;
		float offsetZ = inputData.CameraLogicPos.Z() - top + worldRect.Height() * (1.0f-pivotY);
		SetPickingOffset(Float2(offsetX, offsetZ));

		if (ES_EDITOR == GetEditState())
		{
			PX2_BBM.SetEditorPressingBBlock(this);
			PX2_BBM.SetSelectBBlockEditor(this);
		}
		else
		{
			PX2_BBM.SetSelectBBlockCata(this);
		}
	}
	else if (UIPT_RELEASED == inputData.PickType)
	{
		if (BS_NORMAL != GetState())
		{
			SetState(BS_NORMAL);
		}

		if (this == PX2_BBM.GetEditorPressingBBlock())
		{
			PX2_BBM.SetEditorPressingBBlock(0);
		}

		if (ES_EDITOR == GetEditState())
		{
			if (this == PX2_BBM.GetDragingBBlock())
			{
				PX2_BBM.SetDragingBBlock(0);
			}
		}

		mIsPressedMoved = false;
	}
	else if (UIPT_MOVED == inputData.PickType)
	{
		float moveSquaredLength = inputData.MoveDelta.SquaredLength();
		//if (moveSquaredLength >= 0.1f)
		{
			BBlock::BlockState bs = GetState();

			if (BS_PRESSED == bs)
			{
				mIsPressedMoved = true;
			}

			if (mIsPressedMoved)
			{
				BBlock *dragUIBlock = PX2_BBM.GetDragingBBlock();
				if (!dragUIBlock)
				{
					if (ES_INIT == GetEditState())
					{
						BBlock *block = DynamicCast<BBlock>(this->CopyAll(ES_PRE_EDITOR));
						if (block)
						{
							this->SetState(BBlock::BS_NORMAL);

							Node::TravelExecute(block, _UITravelSetMaskNormal);

							block->OnSelect(true);
							block->SetPickingOffset(this->GetPickingOffset());

							PX2_BBM.SetDragingBBlock(block);
							PX2_BBM.SetSelectBBlockEditor(block);
							PX2_BBM.ShowBlockCata("");
						}
					}
					else
					{
						BBlock *dragUIBlock = PX2_BBM.GetDragingBBlock();
						if (!dragUIBlock)
						{
							if (this->IsCanBeDragingDetached())
								PX2_BBM.SetDragingBBlock(this);
						}
					}
				}
			}
		}
	}
}
//----------------------------------------------------------------------------
void BBlock::OnSizeNodeNotPicked(const CanvasInputData &inputData)
{
	UIFrame::OnSizeNodeNotPicked(inputData);

	mIsPressedMoved = false;

	if (BS_NORMAL != GetState())
		SetState(BS_NORMAL);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
BBlock::BBlock(LoadConstructor value) :
UIFrame(value)
{
	_Init();
}
//----------------------------------------------------------------------------
void BBlock::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadPointer(mBlock);
	source.ReadPointer(mBlockTextName);
	source.ReadPointer(mBackPic0);
	source.ReadPointer(mBackPic1);
	source.ReadPointer(mBackPic2);
	source.ReadPointer(mBackPic3);
	source.ReadPointer(mBackPicBoxVer);
	source.ReadAggregate(mBoardColor);

	PX2_END_DEBUG_STREAM_LOAD(BBlock, source);
}
//----------------------------------------------------------------------------
void BBlock::Link(InStream& source)
{
	UIFrame::Link(source);

	source.ResolveLink(mBlock);
	source.ResolveLink(mBlockTextName);
	source.ResolveLink(mBackPic0);
	source.ResolveLink(mBackPic1);
	source.ResolveLink(mBackPic2);
	source.ResolveLink(mBackPic3);
	source.ResolveLink(mBackPicBoxVer);
}
//----------------------------------------------------------------------------
void BBlock::PostLink()
{
	UIFrame::PostLink();

	if (mBlock)
		mBlock->PostLink();

	if (mBlockTextName)
		mBlockTextName->PostLink();

	if (mBackPic0)
		mBackPic0->PostLink();

	if (mBackPic1)
		mBackPic1->PostLink();

	if (mBackPic2)
		mBackPic2->PostLink();

	if (mBackPic3)
		mBackPic3->PostLink();

	if (mBackPicBoxVer)
		mBackPicBoxVer->PostLink();

	SetLBlock(mBlock);

	ComeInEventWorld();
}
//----------------------------------------------------------------------------
bool BBlock::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		if (mBlock)
		{
			target.Register(mBlock);
		}

		if (mBlockTextName)
		{
			target.Register(mBlockTextName);
		}

		if (mBackPic0)
		{
			target.Register(mBackPic0);
		}

		if (mBackPic1)
		{
			target.Register(mBackPic1);
		}

		if (mBackPic2)
		{
			target.Register(mBackPic2);
		}

		if (mBackPic3)
		{
			target.Register(mBackPic3);
		}

		if (mBackPicBoxVer)
		{
			target.Register(mBackPicBoxVer);
		}

		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void BBlock::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	target.WritePointer(mBlock);
	target.WritePointer(mBlockTextName);
	target.WritePointer(mBackPic0);
	target.WritePointer(mBackPic1);
	target.WritePointer(mBackPic2);
	target.WritePointer(mBackPic3);
	target.WritePointer(mBackPicBoxVer);
	target.WriteAggregate(mBoardColor);

	PX2_END_DEBUG_STREAM_SAVE(BBlock, target);
}
//----------------------------------------------------------------------------
int BBlock::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	size += PX2_POINTERSIZE(mBlock);
	size += PX2_POINTERSIZE(mBlockTextName);
	size += PX2_POINTERSIZE(mBackPic0);
	size += PX2_POINTERSIZE(mBackPic1);
	size += PX2_POINTERSIZE(mBackPic2);
	size += PX2_POINTERSIZE(mBackPic3);
	size += PX2_POINTERSIZE(mBackPicBoxVer);

	size += sizeof(mBoardColor);

	return size;
}
//----------------------------------------------------------------------------