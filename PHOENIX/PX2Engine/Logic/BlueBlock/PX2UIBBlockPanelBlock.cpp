// PX2UIBBlockPanelBlock.cpp

#include "PX2UIBBlockPanelBlock.hpp"
#include "PX2LogicManager.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2BBManager.hpp"
#include "PX2BBlock.hpp"
#include "PX2Time.hpp"
#include "PX2Log.hpp"
#include "PX2BBlockEvents.hpp"
#include "PX2FunObject.hpp"
#include "PX2BBlockScriptGenController.hpp"
#include "PX2UICollapseItem.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, BUIBlockPanelBlock);
PX2_IMPLEMENT_STREAM(BUIBlockPanelBlock);
PX2_IMPLEMENT_FACTORY(BUIBlockPanelBlock);

//----------------------------------------------------------------------------
BUIBlockPanelBlock::BUIBlockPanelBlock() :
mABlockWidth(100.0f),
mSpaceHeight(20.0f),
mNumCurAddedItems(0),
mNumWidth(2),
mIsNeedReAlign(true)
{
	ComeInEventWorld();
	SetAnchorHor(0.0f, 1.0f);
	SetAnchorVer(0.0f, 1.0f);
	SetPivot(0.5f, 1.0f);
	SetSize(0.0f, 100.0f);
}
//----------------------------------------------------------------------------
BUIBlockPanelBlock::~BUIBlockPanelBlock()
{
}
//----------------------------------------------------------------------------
void BUIBlockPanelBlock::Show(bool show)
{
	UIFrame::Show(show);
}
//----------------------------------------------------------------------------
void BUIBlockPanelBlock::SetCatalogue(const std::string &cata)
{
	mCatalogue = cata;
	SetName(mCatalogue);

	_UpdateEvents();
	_UpdateCtrls();
	_UpdateParams();
	_UpdateOperators();
	_UpdateFunctions();

	mIsNeedReAlign = true;
}
//----------------------------------------------------------------------------
void BUIBlockPanelBlock::OnSizeChanged()
{
	UIFrame::OnSizeChanged();

	mIsNeedReAlign = true;
}
//----------------------------------------------------------------------------
void BUIBlockPanelBlock::UpdateWorldData(double applicationTime, double elapsedTime)
{
	UIFrame::UpdateWorldData(applicationTime, elapsedTime);

	if (mIsNeedReAlign)
	{
		mIsNeedReAlign = false;

		float height = _UpdateAligns(0);
		SetHeight(height);

		UICollapseItem *parentItem = (UICollapseItem*)GetUserDataPointer("UICollapseItem");
		if (parentItem)
		{
			parentItem->SetContentHeight(height);
		}
	}
}
//----------------------------------------------------------------------------
const std::string &BUIBlockPanelBlock::GetCatalogue() const
{
	return mCatalogue;
}
//----------------------------------------------------------------------------
void BUIBlockPanelBlock::OnEvent(Event *ent)
{
	if ("ParamCreated" == mCatalogue)
	{
		if (BBlockES::IsEqual(ent, BBlockES::CreateVariable))
		{
			FunObject *funObj = ent->GetData<FunObject*>();
			_AddParam(funObj);

			mIsNeedReAlign = true;
		}
		else if (BBlockES::IsEqual(ent, BBlockES::DeleteVariable))
		{
			FunObject *funObj = ent->GetData<FunObject*>();
			_RemoveParam(funObj);

			mIsNeedReAlign = true;
		}
	}
}
//----------------------------------------------------------------------------
bool BUIBlockPanelBlock::_IsObjectHasTag(Object *obj, const std::string &tag)
{
	PX2_UNUSED(obj);
	PX2_UNUSED(tag);

	return true;
}
//----------------------------------------------------------------------------
void BUIBlockPanelBlock::AddBBlock(BBlock *uiblock)
{
	AttachChild(uiblock);
	uiblock->LocalTransform.SetTranslateY(-2.0f);
	mBlocks.push_back(uiblock);
	uiblock->Update(Time::GetTimeInSeconds(), 0.0f);
}
//----------------------------------------------------------------------------
float BUIBlockPanelBlock::_UpdateAligns(Object *obj)
{
	float lineMaxHeight = 0.0f;

	float spaceHor = 15.0f;
	float anchorVer = -15.0f;

	bool isCurPosLeft = true;
	for (int i = 0; i < (int)mBlocks.size();)
	{
		BBlock *uiblock = mBlocks[i];
		uiblock->SetAnchorVer(1.0f, 1.0f);

		if (obj)
		{
			LBlock *lBlock = uiblock->GetLBlock();
			if (!_IsObjectHasTag(obj, lBlock->GetFunObj().Tag))
			{
				uiblock->Show(false);
				i++;
				continue;
			}
			else
			{
				uiblock->Show(true);
			}
		}

		float panelWidth = GetSize().Width;
		const Sizef &sz = uiblock->GetSize();
		float blockWidth = sz.Width;
		float blockHeight = sz.Height;
		float minusHeight = blockHeight * (1.0f - uiblock->GetPivot()[1]);

		bool isLarge = (blockWidth >= (panelWidth*0.5f - 5.0f));
		isLarge = true;

		if (isCurPosLeft)
		{
			uiblock->SetAnchorHor(0.0f, 0.0f);
			uiblock->SetAnchorParamHor(spaceHor, spaceHor);
			uiblock->SetAnchorParamVer(anchorVer - minusHeight, anchorVer - minusHeight);

			lineMaxHeight = blockHeight;
			isCurPosLeft = false;

			if (i != ((int)mBlocks.size() - 1))
			{
				if (isLarge)
				{
					anchorVer -= (lineMaxHeight + mSpaceHeight);
					isCurPosLeft = true;
				}
			}
			else
			{
				anchorVer -= (lineMaxHeight + mSpaceHeight);
			}

			i++;
		}
		else
		{
			uiblock->SetAnchorHor(0.5f, 0.5f);

			if (isLarge)
			{
				anchorVer -= (lineMaxHeight + mSpaceHeight);
				isCurPosLeft = true;
			}
			else
			{
				uiblock->SetAnchorParamHor(spaceHor, 0.0f);
				uiblock->SetAnchorParamVer(anchorVer - minusHeight, anchorVer - minusHeight);

				if (blockHeight > lineMaxHeight)
				{
					lineMaxHeight = blockHeight;
				}

				anchorVer -= (lineMaxHeight + mSpaceHeight);
				isCurPosLeft = true;

				i++;
			}
		}
	}

	SetHeight(-anchorVer);

	UICollapseItem *ptr = (UICollapseItem*)GetUserDataPointer("UICollapseItem");
	if (ptr)
	{
		ptr->SetContentHeight(-anchorVer);
	}

	return -anchorVer;
}
//----------------------------------------------------------------------------
void BUIBlockPanelBlock::_UpdateEvents()
{
	const std::map<std::string, std::vector<std::string> > &events = PX2_LOGICM.GetEvents();
	auto it = events.begin();
	for (; it != events.end(); it++)
	{
		std::string cata = it->first;
		const std::string &name = GetName();
		if (cata == name)
		{
			const std::vector<std::string> &ents = it->second;

			for (int i = 0; i < (int)ents.size(); i++)
			{
				const std::string &entName = ents[i];
				FunObject *funObj = PX2_LOGICM.GetEvent(entName);
				if (funObj)
				{
					// general
					BBlock *uiblock = new0 BBlock();
					mBlocks.push_back(uiblock);

					LBlock *lBlock = new0 LBlock(LBlock::MT_EVENT);
					lBlock->RegistFunObj(*funObj);
					uiblock->SetLBlock(lBlock);
					AttachChild(uiblock);
					uiblock->Update(Time::GetTimeInSeconds(), 0.0f);
				}
			}
		}
	}
}
//----------------------------------------------------------------------------
void BUIBlockPanelBlock::_UpdateFunctions()
{
	const std::map<std::string, std::vector<std::string> > &genFuns = PX2_LOGICM.GetGFs();
	auto it = genFuns.begin();
	for (; it != genFuns.end(); it++)
	{
		std::string cata = it->first;
		const std::string &name = GetName();
		if (cata == name)
		{
			const std::vector<std::string> &genFuns = it->second;

			for (int i = 0; i < (int)genFuns.size(); i++)
			{
				const std::string &genFunName = genFuns[i];
				FunObject *funObj = PX2_LOGICM.GetGF(genFunName);
				if (funObj)
				{
					BBlock *uiblock = new0 BBlock();
					LBlock *lBlock = 0;
					if (funObj->GetOutParams().size() > 0)
					{
						lBlock = new0 LBlock(LBlock::MT_FUNCTION_OUTPUT);
					}
					else
					{
						lBlock = new0 LBlock(LBlock::MT_FUNCTION_GENERAL);
					}

					lBlock->RegistFunObj(*funObj);
					uiblock->SetLBlock(lBlock);
					AddBBlock(uiblock);
				}
			}
		}
	}
}
//----------------------------------------------------------------------------
void BUIBlockPanelBlock::_UpdateCtrls()
{
	const std::map<std::string, std::vector<std::string> > &ctrls = PX2_LOGICM.GetCtrls();
	auto it1 = ctrls.begin();
	for (; it1 != ctrls.end(); it1++)
	{
		std::string cata = it1->first;
		const std::string &name = GetName();
		if (cata == name)
		{
			const std::vector<std::string> &ctrls = it1->second;

			for (int i = 0; i < (int)ctrls.size(); i++)
			{
				const std::string &genFunName = ctrls[i];
				FunObject *funObj = PX2_LOGICM.GetCtrl(genFunName);
				if (funObj)
				{
					// ctrls
					BBlock *uiblock = new0 BBlock();
					mBlocks.push_back(uiblock);

					LBlock *lBlock = new0 LBlock(LBlock::MT_CONTROL);

					if ("If" == funObj->Name)
					{
						lBlock->SetCtrlType(LBlock::CT_IF);
					}
					else if ("IfElse" == funObj->Name)
					{
						lBlock->SetCtrlType(LBlock::CT_IFELSE);
					}
					else if ("While" == funObj->Name)
					{
						lBlock->SetCtrlType(LBlock::CT_WHILE);
					}
					else if ("Program" == funObj->Name)
					{
						lBlock->SetCtrlType(LBlock::CT_PROGRAM);
					}
					else if ("ProgramStart" == funObj->Name)
					{
						lBlock->SetCtrlType(LBlock::CT_PROGRAMSTART);
					}
					else if ("ProgramFixUpdate" == funObj->Name)
					{
						lBlock->SetCtrlType(LBlock::CT_PROGRAMFIXUPDATE);
					}
					else if ("Coroutine" == funObj->Name)
					{
						lBlock->SetCtrlType(LBlock::CT_COROUTINE);
					}

					lBlock->RegistFunObj(*funObj);
					uiblock->SetLBlock(lBlock);
					AttachChild(uiblock);
					uiblock->Update(Time::GetTimeInSeconds(), 0.0f);
				}
			}
		}
	}
}
//----------------------------------------------------------------------------
void BUIBlockPanelBlock::_UpdateParams()
{
	const std::map<std::string, std::vector<std::string> > &ctrls = PX2_LOGICM.GetParams();
	auto it1 = ctrls.begin();
	for (; it1 != ctrls.end(); it1++)
	{
		std::string cata = it1->first;
		const std::string &name = GetName();
		if (cata == name)
		{
			const std::vector<std::string> &ctrls = it1->second;

			for (int i = 0; i < (int)ctrls.size(); i++)
			{
				const std::string &genFunName = ctrls[i];
				FunObject *funObj = PX2_LOGICM.GetParam(genFunName);
				if (funObj)
				{
					_AddParam(funObj);
				}
			}
		}
	}
}
//----------------------------------------------------------------------------
void BUIBlockPanelBlock::_AddParam(FunObject *funObj)
{
	if (mCatalogue == "ParamCreated")
	{
		BBlock *block = DynamicCast<BBlock>(GetObjectByName(funObj->Name));
		if (block)
			return;
	}

	// params
	BBlock *uiblock = new0 BBlock();
	mBlocks.push_back(uiblock);

	uiblock->SetName(funObj->Name);

	LBlock *lBlock = new0 LBlock(LBlock::MT_PARAM);
	FunObject::ParamType pt = funObj->GetParamType();
	if (FunObject::PT_CONST == pt)
	{
		lBlock->SetParamType(LBlock::PT_CONST);
	}
	else if (FunObject::PT_VARIABLE == pt)
	{
		lBlock->SetParamType(LBlock::PT_VARIABLE);
	}
	else if (FunObject::PT_VALUE == pt)
	{
		lBlock->SetParamType(LBlock::PT_VALUE);
	}
	lBlock->RegistFunObj(*funObj);

	uiblock->SetLBlock(lBlock);
	uiblock->SetEditState(BBlock::ES_INIT);
	AttachChild(uiblock);
	uiblock->Update(Time::GetTimeInSeconds(), 0.0f);
}
//----------------------------------------------------------------------------
void BUIBlockPanelBlock::_RemoveParam(FunObject *funObj)
{
	if (mCatalogue == "ParamCreated")
	{
		BBlock *block = DynamicCast<BBlock>(GetObjectByName(funObj->Name));
		if (!block)
			return;

		auto it = mBlocks.begin();
		for (; it != mBlocks.end();)
		{
			if (*it == block)
			{
				it = mBlocks.erase(it);
			}
			else
			{
				it++;
			}
		}

		DetachChild(block);
	}
}
//----------------------------------------------------------------------------
void BUIBlockPanelBlock::_UpdateOperators()
{
	const std::map<std::string, std::vector<std::string> > &ctrls = PX2_LOGICM.GetOperators();
	auto it1 = ctrls.begin();
	for (; it1 != ctrls.end(); it1++)
	{
		std::string cata = it1->first;
		const std::string &name = GetName();
		if (cata == name)
		{
			const std::vector<std::string> &ctrls = it1->second;

			for (int i = 0; i < (int)ctrls.size(); i++)
			{
				const std::string &funName = ctrls[i];
				FunObject *funObj = PX2_LOGICM.GetOperator(funName);
				if (funObj)
				{
					// params
					BBlock *uiblock = new0 BBlock();
					mBlocks.push_back(uiblock);

					LBlock *lBlock = new0 LBlock(LBlock::MT_FUNCTION_OPERATOR);
					lBlock->RegistFunObj(*funObj);

					uiblock->SetLBlock(lBlock);
					AttachChild(uiblock);
					uiblock->Update(Time::GetTimeInSeconds(), 0.0f);
				}
			}
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
BUIBlockPanelBlock::BUIBlockPanelBlock(LoadConstructor value) :
UIFrame(value),
mNumCurAddedItems(0)
{
}
//----------------------------------------------------------------------------
void BUIBlockPanelBlock::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(BUIBlockPanelBlock, source);
}
//----------------------------------------------------------------------------
void BUIBlockPanelBlock::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void BUIBlockPanelBlock::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool BUIBlockPanelBlock::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void BUIBlockPanelBlock::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(BUIBlockPanelBlock, target);
}
//----------------------------------------------------------------------------
int BUIBlockPanelBlock::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------