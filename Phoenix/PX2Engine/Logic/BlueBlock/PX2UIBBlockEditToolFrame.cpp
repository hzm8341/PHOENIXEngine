// PX2UIBBlockEditToolFrame.cpp

#include "PX2UIBBlockEditToolFrame.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2UIButton.hpp"
#include "PX2EditEventType.hpp"
#include "PX2RedoUndo.hpp"
#include "PX2RUStateManager.hpp"
#include "PX2BBManager.hpp"
#include "PX2BBlockEvents.hpp"
#include "PX2LogicManager.hpp"
#include "PX2BBlockEvent.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, UIBBlockEditToolFrame);
PX2_IMPLEMENT_STREAM(UIBBlockEditToolFrame);
PX2_IMPLEMENT_FACTORY(UIBBlockEditToolFrame);

//----------------------------------------------------------------------------
UIBBlockEditToolFrame::UIBBlockEditToolFrame()
{
	ComeInEventWorld();

	float butSize = 100.0f;
	float butSpace = 15.0f;

	float alpha = 1.0f;

	std::vector<UIFrame*> buts;

	mButCode = new0 UIButton();
	AttachChild(mButCode);
	mButCode->LocalTransform.SetTranslateY(-1.0f);
	mButCode->SetAnchorVer(0.5f, 0.5f);
	mButCode->SetName("ButCode");
	mButCode->SetMemUICallback(this, (UIFrame::MemUICallback)(&UIBBlockEditToolFrame::_UIButCallback));
	mButCode->GetPicBoxAtState(UIButtonBase::BS_NORMAL)
		->SetTexture("Data/BlueBlock/images/icons/code.png");
	mButCode->SetStateColor(UIButtonBase::BS_NORMAL, Float3::WHITE);
	mButCode->SetStateColor(UIButtonBase::BS_HOVERED, Float3::WHITE);
	mButCode->SetStateColor(UIButtonBase::BS_PRESSED, Float3::WHITE);
	mButCode->SetStateAlpha(UIButtonBase::BS_NORMAL, alpha);
	mButCode->SetStateAlpha(UIButtonBase::BS_HOVERED, alpha);
	mButCode->SetStateAlpha(UIButtonBase::BS_PRESSED, 1.0f);
	mButCode->AutoMakeSizeFixable();
	buts.push_back(mButCode);

	mButClone = new0 UIButton();
	AttachChild(mButClone);
	mButClone->LocalTransform.SetTranslateY(-1.0f);
	mButClone->SetAnchorVer(0.5f, 0.5f);
	mButClone->SetName("ButClone");
	mButClone->SetMemUICallback(this, (UIFrame::MemUICallback)(&UIBBlockEditToolFrame::_UIButCallback));
	mButClone->GetPicBoxAtState(UIButtonBase::BS_NORMAL)
		->SetTexture("Data/BlueBlock/images/icons/clone.png");
	mButClone->SetStateColor(UIButtonBase::BS_NORMAL, Float3::WHITE);
	mButClone->SetStateColor(UIButtonBase::BS_HOVERED, Float3::WHITE);
	mButClone->SetStateColor(UIButtonBase::BS_PRESSED, Float3::WHITE);
	mButClone->SetStateAlpha(UIButtonBase::BS_NORMAL, alpha);
	mButClone->SetStateAlpha(UIButtonBase::BS_HOVERED, alpha);
	mButClone->SetStateAlpha(UIButtonBase::BS_PRESSED, 1.0f);
	mButClone->AutoMakeSizeFixable();
	buts.push_back(mButClone);

	mButUnDo = new0 UIButton();
	AttachChild(mButUnDo);
	mButUnDo->LocalTransform.SetTranslateY(-1.0f);
	mButUnDo->SetAnchorVer(0.5f, 0.5f);
	mButUnDo->GetPicBoxAtState(UIButtonBase::BS_NORMAL)
		->SetTexture("Data/BlueBlock/images/icons/undo.png");
	mButUnDo->SetStateColor(UIButtonBase::BS_NORMAL, Float3::WHITE);
	mButUnDo->SetStateColor(UIButtonBase::BS_HOVERED, Float3::WHITE);
	mButUnDo->SetStateColor(UIButtonBase::BS_PRESSED, Float3::WHITE);
	mButUnDo->SetStateAlpha(UIButtonBase::BS_NORMAL, alpha);
	mButUnDo->SetStateAlpha(UIButtonBase::BS_HOVERED, alpha);
	mButUnDo->SetStateAlpha(UIButtonBase::BS_PRESSED, 1.0f);
	mButUnDo->SetStateAlpha(UIButtonBase::BS_DISABLED, 0.5f);
	mButUnDo->SetName("ButUnDo");
	mButUnDo->SetMemUICallback(this, (UIFrame::MemUICallback)(&UIBBlockEditToolFrame::_UIButCallback));
	mButUnDo->Enable(false);
	mButUnDo->AutoMakeSizeFixable();
	buts.push_back(mButUnDo);

	mButReDo = new0 UIButton();
	AttachChild(mButReDo);
	mButReDo->LocalTransform.SetTranslateY(-1.0f);
	mButReDo->SetAnchorVer(0.5f, 0.5f);
	mButReDo->GetPicBoxAtState(UIButtonBase::BS_NORMAL)
		->SetTexture("Data/BlueBlock/images/icons/redo.png");
	mButReDo->SetStateColor(UIButtonBase::BS_NORMAL, Float3::WHITE);
	mButReDo->SetStateColor(UIButtonBase::BS_HOVERED, Float3::WHITE);
	mButReDo->SetStateColor(UIButtonBase::BS_PRESSED, Float3::WHITE);
	mButReDo->SetStateAlpha(UIButtonBase::BS_NORMAL, alpha);
	mButReDo->SetStateAlpha(UIButtonBase::BS_HOVERED, alpha);
	mButReDo->SetStateAlpha(UIButtonBase::BS_PRESSED, 1.0f);
	mButReDo->SetStateAlpha(UIButtonBase::BS_DISABLED, 0.5f);
	mButReDo->SetName("ButReDo");
	mButReDo->SetMemUICallback(this, (UIFrame::MemUICallback)(&UIBBlockEditToolFrame::_UIButCallback));
	mButReDo->Enable(false);
	mButReDo->AutoMakeSizeFixable();
	buts.push_back(mButReDo);

	int numButs = (int)buts.size();
	float perc = 1.0f / (numButs);
	for (int i = 0; i < numButs; i++)
	{
		float anchorHor = (i+0.5f)*perc;
		UIFrame *but = buts[i];
		but->SetAnchorHor(anchorHor, anchorHor);
	}

	mButRecycle = new0 UIButton();
	AttachChild(mButRecycle);
	mButRecycle->LocalTransform.SetTranslateY(-10.0f);
	mButRecycle->GetPicBoxAtState(UIButtonBase::BS_NORMAL)
		->SetTexture("Data/BlueBlock/images/icons/delete.png");
	mButRecycle->SetStateColor(UIButtonBase::BS_NORMAL, Float3::WHITE);
	mButRecycle->SetStateColor(UIButtonBase::BS_HOVERED, Float3::WHITE);
	mButRecycle->SetStateColor(UIButtonBase::BS_PRESSED, Float3::WHITE);
	mButRecycle->SetStateAlpha(UIButtonBase::BS_NORMAL, alpha);
	mButRecycle->SetStateAlpha(UIButtonBase::BS_HOVERED, alpha);
	mButRecycle->SetStateAlpha(UIButtonBase::BS_PRESSED, 1.0f);
	mButRecycle->SetStateBrightness(UIButtonBase::BS_HOVERED, 1.2f);
	mButRecycle->AutoMakeSizeFixable();
	mButRecycle->SetName("ButRecycle");
	mButRecycle->SetMemUICallback(this, (UIFrame::MemUICallback)(&UIBBlockEditToolFrame::_UIButCallback));
	PX2_BBM.SetRecycleButton(mButRecycle);
	mButRecycle->SetAnchorHor(0.5f, 0.5f);
	mButRecycle->SetAnchorVer(0.5f, 0.5f);
	mButRecycle->Show(false);

	mShowType = ST_NORMAL;

	ComeInEventWorld();
}
//----------------------------------------------------------------------------
UIBBlockEditToolFrame::~UIBBlockEditToolFrame()
{
}
//----------------------------------------------------------------------------
void UIBBlockEditToolFrame::OnEvent(Event *ent)
{
	if (EditES::IsEqual(ent, EditES::PushUnDo))
	{
		if (mButUnDo)
			mButUnDo->Enable(true);
	}
	else if (EditES::IsEqual(ent, EditES::UnDo))
	{
		if (mButReDo)
			mButReDo->Enable(true);
	}
	else if (EditES::IsEqual(ent, EditES::ReDo))
	{
		if (mButUnDo)
			mButUnDo->Enable(true);
	}
	else if (EditES::IsEqual(ent, EditES::NoUnDo))
	{
		if (mButUnDo)
			mButUnDo->Enable(false);
	}
	else if (EditES::IsEqual(ent, EditES::NoReDo))
	{
		if (mButReDo)
			mButReDo->Enable(false);
	}
	else if (BBlockES::IsEqual(ent, BBlockES::SetDragingBBlock))
	{
		BBlock *block = ent->GetData<BBlock*>();
		if (block)
		{
			BBlock::ShapeType st = block->GetShapeType();		
			//if (st == BBlock::ST_PROGRAM || st == BBlock::ST_PROGRAMSTART)
			{
			//	SetShowType(UIBBlockEditToolFrame::ST_RECYCLEDISABLE);
			}
			//else
			{
				SetShowType(UIBBlockEditToolFrame::ST_RECYCLE);
			}
		}
		else
		{
			SetShowType(UIBBlockEditToolFrame::ST_NORMAL);
		}
	}
}
//----------------------------------------------------------------------------
UIButton *UIBBlockEditToolFrame::GetButtonRecycle()
{
	return mButRecycle;
}
//----------------------------------------------------------------------------
void UIBBlockEditToolFrame::SetShowType(ShowType st)
{
	mShowType = st;

	if (ST_NORMAL == mShowType)
	{
		mButCode->Show(true);
		mButClone->Show(true);
		mButUnDo->Show(true);
		mButReDo->Show(true);
		mButRecycle->Show(false);
	}
	else if (ST_RECYCLE == mShowType)
	{
		mButCode->Show(false);
		mButClone->Show(false);
		mButUnDo->Show(false);
		mButReDo->Show(false);
		mButRecycle->Show(true);
	}
	else if (ST_RECYCLEDISABLE == mShowType)
	{
		mButCode->Show(false);
		mButClone->Show(false);
		mButUnDo->Show(false);
		mButReDo->Show(false);
		mButRecycle->Show(false);
	}
}
//----------------------------------------------------------------------------
UIBBlockEditToolFrame::ShowType UIBBlockEditToolFrame::GetShowType() const
{
	return mShowType;
}
//----------------------------------------------------------------------------
void UIBBlockEditToolFrame::_UIButCallback(UIFrame *frame, UICallType type)
{
	const std::string &name = frame->GetName();
	UIButton *but = DynamicCast<UIButton>(frame);
	PX2_UNUSED(but);

	if (UICT_RELEASED == type)
	{
		if ("ButCreate" == name)
		{
			PX2_BBM.ShowBlockCata("abc");
		}
		else if ("ButUnDo" == name)
		{
			PX2_URSTATE_MAN.UnDo();
		}
		else if ("ButReDo" == name)
		{
			PX2_URSTATE_MAN.ReDo();
		}
		else if ("ButClone" == name)
		{
			BBlock *block = PX2_BBM.GetSelectBBlockEditor();
			if (block)
			{
				APoint worldPos = block->WorldTransform.GetTranslate();

				BBlockPtr copyedBlock = DynamicCast<BBlock>(block->CopyAll(BBlock::ES_EDITOR));
				if (copyedBlock)
				{
					copyedBlock->OnSelect(false);
					copyedBlock->SetEditState(BBlock::ES_EDITOR);
					copyedBlock->SetPickingOffset(Float2::ZERO);
					copyedBlock->SetAnchorHor(0.0f, 0.0f);
					copyedBlock->SetAnchorVer(1.0f, 1.0f);

					Event *ent = BBlockES::CreateEventX(BBlockES::CopyedBlock);
					CopyedBlockData data;
					data.From = block;
					data.TheBlock = copyedBlock;
					ent->SetData<CopyedBlockData>(data);
					PX2_EW.BroadcastingLocalEvent(ent);
				}
			}
		}
		else if ("ButCode" == name)
		{			
			Event *ent = PX2_CREATEEVENTEX(BBlockES, ShowCodeView);
			ent->SetDataStr0("true");
			ent->SetData<bool>(true);
			PX2_EW.BroadcastingLocalEvent(ent);
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
UIBBlockEditToolFrame::UIBBlockEditToolFrame(LoadConstructor value) :
UIFrame(value)
{
}
//----------------------------------------------------------------------------
void UIBBlockEditToolFrame::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(UIBBlockEditToolFrame, source);
}
//----------------------------------------------------------------------------
void UIBBlockEditToolFrame::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void UIBBlockEditToolFrame::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool UIBBlockEditToolFrame::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void UIBBlockEditToolFrame::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(UIBBlockEditToolFrame, target);
}
//----------------------------------------------------------------------------
int UIBBlockEditToolFrame::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------