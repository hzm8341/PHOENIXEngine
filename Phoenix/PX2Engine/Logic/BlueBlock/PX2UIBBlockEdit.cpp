// UIBBlockEdit.cpp

#include "PX2UIBBlockEdit.hpp"
#include "PX2Time.hpp"
#include "PX2InputManager.hpp"
#include "PX2SelectionManager.hpp"
#include "PX2EditEventType.hpp"
#include "PX2RUStateManager.hpp"
#include "PX2LogicManager.hpp"
#include "PX2EngineCanvas.hpp"
#include "PX2BBlock.hpp"
#include "PX2BBManager.hpp"
#include "PX2BBlockEvents.hpp"
#include "PX2BBlockScriptGenController.hpp"
#include "PX2LogicES.hpp"
#include "PX2BBlockSprite.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, UIBBlockEdit);
PX2_IMPLEMENT_STREAM(UIBBlockEdit);
PX2_IMPLEMENT_FACTORY(UIBBlockEdit);

//----------------------------------------------------------------------------
UIBBlockEdit::UIBBlockEdit() :
mStartDragParent(0)
{
	mEditPlaygroundCanvas = new0 UIBBlockEditCanvas();
	AttachChild(mEditPlaygroundCanvas);
	mEditPlaygroundCanvas->LocalTransform.SetTranslateY(-2.0f);
	mEditPlaygroundCanvas->SetAnchorHor(0.0f, 1.0f);
	mEditPlaygroundCanvas->SetAnchorParamHor(0.0f, 1.0f);
	mEditPlaygroundCanvas->SetAnchorVer(0.0f, 1.0f);
	mEditPlaygroundCanvas->SetAnchorParamVer(0.0f, 0.0f);

	SetChildPickOnlyInSizeRange(false);
	ComeInEventWorld();
}
//----------------------------------------------------------------------------
UIBBlockEdit::~UIBBlockEdit()
{
}
//----------------------------------------------------------------------------
void UIBBlockEdit::OnEvent(Event *ent)
{
	if (BBlockES::IsEqual(ent, BBlockES::SetDragingBBlock))
	{
		BBlock *uiBlock = ent->GetData<BBlock*>();

		if (uiBlock)
		{
			Movable *parent = uiBlock->GetParent();
			if (!parent)
			{
				mStartDragParent = 0;

				BBlockSprite *bSprite = PX2_BBM.GetSelectSprite();
				LFile *lFile = bSprite->GetScriptGenController()->GetLFile();
				assertion(0!=lFile, "LFile must exist!");
				if (lFile)
				{
					LBlock *lBlock = uiBlock->GetLBlock();
					LBlock::CtrlType ct = lBlock->GetCtrlType();
					if (LBlock::CT_PROGRAM == ct ||
						LBlock::CT_PROGRAMSTART == ct ||
						LBlock::CT_PROGRAMFIXUPDATE == ct)
					{
						LFile *lFile = uiBlock->GetLBlock()->GetLFile();
						if (lFile)
						{
							lFile->AddBlockPrograms(lBlock);
						}
					}

					mEditPlaygroundCanvas->GetPlaygroundBlocks()->AttachChild(uiBlock);
					_UpdateUIDraing(mCurInputData);
				}
			}
			else
			{
				if (parent == mEditPlaygroundCanvas->GetPlaygroundBlocks())
				{
					mStartDragParent = mEditPlaygroundCanvas->GetPlaygroundBlocks();

					mStartDragTransStateObj.mAnchorHor = uiBlock->GetAnchorHor();
					mStartDragTransStateObj.mAnchorParamHor = uiBlock->GetAnchorParamHor();
					mStartDragTransStateObj.mAnchorVer = uiBlock->GetAnchorVer();
					mStartDragTransStateObj.mAnchorParamVer = uiBlock->GetAnchorParamVer();
				}
				else
				{ // connector
					if (uiBlock->IsAttachedToBlockConnector() && BBlock::BS_PRESSED == uiBlock->GetState())
					{
						BBlockConnector *ctn = DynamicCast<BBlockConnector>(uiBlock->GetParent());
						if (ctn)
						{
							mStartDragParent = ctn;

							mStartDragTransStateObj.mAnchorHor = Float2::ZERO;
							mStartDragTransStateObj.mAnchorParamHor = Float2::ZERO;
							mStartDragTransStateObj.mAnchorVer = Float2::UNIT;
							mStartDragTransStateObj.mAnchorParamVer = Float2::ZERO;

							ctn->DetachChild(uiBlock);
							mEditPlaygroundCanvas->GetPlaygroundBlocks()->AttachChild(uiBlock);
							_UpdateUIDraing(mCurInputData);
						}
					}
				}
			}
		}
	}
	else if (BBlockES::IsEqual(ent, BBlockES::CloseProject))
	{
		_RefreshFile(0);
	}
	else if (LogicES::IsEqual(ent, LogicES::SetSelectLogicObject))
	{
		Object *obj = PX2_LOGICM.GetSelectLogicObject();
		if (obj)
		{
			BBlockSprite *bSprite = DynamicCast<BBlockSprite>(obj);
			if (bSprite)
			{
				BBlockScriptGenController *scriptCtrl = bSprite->GetScriptGenController();
				if (scriptCtrl)
				{
					LFile *lFile = scriptCtrl->GetLFile();
					_RefreshFile(lFile);
				}
			}
		}
	}
	else if (BBlockES::IsEqual(ent, BBlockES::CopyedBlock))
	{
		CopyedBlockData data = ent->GetData<CopyedBlockData>();
		BBlock *from = data.From;
		BBlock *block = data.TheBlock;

		Rectf worldRect = mEditPlaygroundCanvas->GetPlaygroundBlocks()->GetWorldRect();

		APoint fromWPos = from->WorldTransform.GetTranslate();
		float diffX = fromWPos.X() - worldRect.Left;
		float diffZ = fromWPos.Z() - worldRect.Top;
		
		if (block)
		{
			float appendX = 40.0f;
			float appendZ = 40.0f;

			block->SetAnchorParamHor(diffX + appendX, diffX + appendX);
			block->SetAnchorParamVer(diffZ - appendZ, diffZ - appendZ);
			block->LocalTransform.SetTranslateY(-50.0f);

			mEditPlaygroundCanvas->GetPlaygroundBlocks()->AttachChild(block);
		}
	}
}
//----------------------------------------------------------------------------
BBlockConnector *UIBBlockEdit::_GetPickingConnector(BBlock *block)
{
	for (int i = 0; i < mEditPlaygroundCanvas->GetPlaygroundBlocks()->GetNumChildren(); i++)
	{
		BBlock *uiBlock = DynamicCast<BBlock>(mEditPlaygroundCanvas->GetPlaygroundBlocks()->GetChild(i));
		if (uiBlock)
		{
			BBlockConnector *connector = uiBlock->GetCloestConnector(block);
			if (connector)
			{
				return connector;
			}
		}
	}

	return 0;
}
//----------------------------------------------------------------------------
bool UIBBlockEdit::_IsOverRecycle(BBlock *block)
{
	CameraNode *camNode = mEditPlaygroundCanvas->GetUICameraNode();
	const APoint &camWorldPos = camNode->WorldTransform.GetTranslate();

	const Rectf &localRect = block->GetLocalRect();
	const APoint &worldPos = block->WorldTransform.GetTranslate();
	
	float xDiff = worldPos.X() - camWorldPos.X();
	float zDiff = worldPos.Z() - camWorldPos.Z();

	Rectf useRect = localRect;
	useRect.Left += xDiff + WorldTransform.GetTranslate().X();
	useRect.Right += xDiff + WorldTransform.GetTranslate().X();
	useRect.Bottom += zDiff + WorldTransform.GetTranslate().Z();
	useRect.Top += zDiff + WorldTransform.GetTranslate().Z();

	UIButton *butRecycle = PX2_BBM.GetRecycleButton();
	if (butRecycle && butRecycle->IsShow())
	{
		const Rectf &recycleWorldRect = butRecycle->GetWorldRect();
		if (useRect.IsIntersect(recycleWorldRect))
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void UIBBlockEdit::OnSizeNodePicked(const CanvasInputData &inputData)
{
	EngineUICanvas *euc = EngineUICanvas::GetSingletonPtr();
	Movable *topestMov = euc->GetTopestMovable();
	if (topestMov)
		return;

	mCurInputData = inputData;

	UIFrame::OnSizeNodePicked(inputData);

	if (UIPT_PRESSED == inputData.PickType)
	{
		_UpdateUIDraing(inputData);
	}
	else if (UIPT_MOVED == inputData.PickType)
	{
		BBlock *dragingUIBlock = PX2_BBM.GetDragingBBlock();

		_UpdateUIDraing(inputData);

		if (dragingUIBlock)
		{
			BBlockConnector *connector = _GetPickingConnector(dragingUIBlock);
			bool isOverRecycle = _IsOverRecycle(dragingUIBlock);

			if (isOverRecycle)
			{
				UIButton *butRecycle = PX2_BBM.GetRecycleButton();
				if (butRecycle)
					butRecycle->SetColor(Float3::RED);
			}
			else
			{
				UIButton *butRecycle = PX2_BBM.GetRecycleButton();
				if (butRecycle)
					butRecycle->SetColor(Float3::WHITE);
			}
		}
	}
	else if (UIPT_RELEASED == inputData.PickType)
	{
		BBlock *dragingUIBlock = PX2_BBM.GetDragingBBlock();
		if (dragingUIBlock)
		{
			BBlockConnector *connector = _GetPickingConnector(dragingUIBlock);
			bool isOverRecycle = _IsOverRecycle(dragingUIBlock);

			if (isOverRecycle)
			{
				LBlock::CtrlType ct = dragingUIBlock->GetLBlock()->GetCtrlType();	
				if (LBlock::CT_PROGRAM == ct ||
					LBlock::CT_PROGRAMSTART == ct ||
					LBlock::CT_PROGRAMFIXUPDATE == ct)
				{
					LFile *lFile = dragingUIBlock->GetLBlock()->GetLFile();
					if (lFile)
					{
						lFile->RemoveBlockProgram(dragingUIBlock->GetLBlock());
					}
				}

				Node *parent = DynamicCast<Node>(dragingUIBlock->GetParent());
				if (parent)
				{
					parent->DetachChild(dragingUIBlock);
				}

				if (BBlock::ES_EDITOR == dragingUIBlock->GetEditState())
				{
					TransState *state = new0 TransState(mStartDragParent, mStartDragTransStateObj, dragingUIBlock, true);
					PX2_URSTATE_MAN.PushUnDo(state);
				}

				// set normal color
				UIButton *butRecycle = PX2_BBM.GetRecycleButton();
				if (butRecycle)
					butRecycle->SetColor(Float3::WHITE);
			}
			else
			{
				Node *parent = DynamicCast<Node>(dragingUIBlock->GetParent());

				bool isPreEditor = BBlock::ES_PRE_EDITOR == dragingUIBlock->GetEditState();
				if (isPreEditor)
				{
					TransState *state = new0 TransState(mStartDragParent, mStartDragTransStateObj, dragingUIBlock, true);
					PX2_URSTATE_MAN.PushUnDo(state);
					PX2_BBM._GenDefaultParams(dragingUIBlock);

					dragingUIBlock->SetEditState(BBlock::ES_EDITOR);
				}

				if (connector)
				{
					if (parent != connector)
					{
						parent->DetachChild(dragingUIBlock);
						BBlockPtr curBlock;						
						BBlockConnector::ConnectorType ct = connector->GetConnectorType();
						if (BBlockConnector::CT_PARAM == ct)
						{
							curBlock = connector->GetCurBlock();
						}
						else if (BBlockConnector::CT_BLOCK == ct)
						{
							curBlock = connector->GetCurBlock();
						}
						else if (BBlockConnector::CT_NEXT == ct)
						{
							curBlock = connector->GetCurBlock();
						}
						if (curBlock)
							connector->DetachChild(curBlock);

						connector->AttachChild(dragingUIBlock);

						if (curBlock)
						{
							if (BBlockConnector::CT_PARAM == ct)
							{
								UIFrame *playgourndBlocks = mEditPlaygroundCanvas->GetPlaygroundBlocks();
								playgourndBlocks->AttachChild(curBlock);

								Float2 pos = _GetDragingPos(mCurInputData);
								curBlock->SetAnchorHor(0.0f, 0.0f);
								curBlock->SetAnchorVer(1.0f, 1.0f);
								curBlock->SetAnchorParamHor(pos.X() + 100.0f, 0.0f);
								curBlock->SetAnchorParamVer(pos.Y() - 100.0f, 0.0f);
							}
							else if (BBlockConnector::CT_BLOCK == ct)
							{
								BBlockConnector *blockConnectorNext = dragingUIBlock->GetLastNextConnector();
								if (blockConnectorNext)
								{
									blockConnectorNext->AttachChild(curBlock);
								}
							}
							else if (BBlockConnector::CT_NEXT == ct)
							{
								BBlockConnector *blockConnectorNext = dragingUIBlock->GetLastNextConnector();
								if (blockConnectorNext)
								{
									blockConnectorNext->AttachChild(curBlock);
								}
							}
						}

						TransState *state = new0 TransState(mStartDragParent, mStartDragTransStateObj, dragingUIBlock, true);
						PX2_URSTATE_MAN.PushUnDo(state);
					}
				}
				else
				{
					if (!isPreEditor && parent == mEditPlaygroundCanvas->GetPlaygroundBlocks())
					{
						float sideSize = 120.0f;
						float sideSizeVer = 40.0f;
						const Sizef &pSize = mEditPlaygroundCanvas->GetPlaygourndSize();

						float horPos = dragingUIBlock->GetAnchorParamHor().X();
						if (horPos > (pSize.Width - sideSize))
							horPos = pSize.Width - sideSize;
						if (horPos < 0.0f)
							horPos = 0.0f;

						float verPos = dragingUIBlock->GetAnchorParamVer().X();
						if (verPos > -sideSizeVer)
							verPos = -sideSizeVer;
						if (verPos < -pSize.Height + sideSizeVer)
							verPos = -pSize.Height + sideSizeVer;

						dragingUIBlock->SetAnchorParamHor(horPos, horPos);
						dragingUIBlock->SetAnchorParamVer(verPos, verPos);

						TransState *state = new0 TransState(mStartDragParent, mStartDragTransStateObj, dragingUIBlock, true);
						PX2_URSTATE_MAN.PushUnDo(state);
					}
				}
			}

			PX2_BBM.SetDragingBBlock(0);
		}
	}
}
//----------------------------------------------------------------------------
void UIBBlockEdit::_UpdateUIDraing(const CanvasInputData &inputData)
{
	BBlock *dragingUIBlock = PX2_BBM.GetDragingBBlock();
	if (dragingUIBlock)
	{
		Float2 dragingPos = _GetDragingPos(inputData);

		float offsetX = dragingUIBlock->GetPickingOffset()[0];
		float offsetZ = dragingUIBlock->GetPickingOffset()[1];

		dragingUIBlock->SetAnchorHor(0.0f, 0.0f);
		dragingUIBlock->SetAnchorVer(1.0f, 1.0f);

		float posHor = dragingPos[0] - offsetX;
		float posVer = dragingPos[1] - offsetZ;
		dragingUIBlock->SetAnchorParamHor(posHor, posHor);
		dragingUIBlock->SetAnchorParamVer(posVer, posVer);

		LBlock *lblock = dragingUIBlock->GetLBlock();
		if (lblock)
		{
			LBlock::CtrlType ct= lblock->GetCtrlType();
			if (LBlock::CT_PROGRAM == ct || LBlock::CT_PROGRAMSTART == ct ||
				LBlock::CT_PROGRAMFIXUPDATE == ct)
			{
				lblock->SetAnchorParam(posHor, posVer);
			}
		}
	}
}
//----------------------------------------------------------------------------
Float2 UIBBlockEdit::_GetDragingPos(const CanvasInputData &inputData)
{
	const APoint &worldPos = inputData.LogicPos;

	const Sizef &size = GetSize();
	PX2_UNUSED(size);
	const Rectf &worldRect = GetWorldRect();
	float posSizePercentWdith = (worldPos[0] - worldRect.Left) / worldRect.Width();
	float posSizePercentHeight = (worldPos[2] - worldRect.Bottom) / worldRect.Height();

	UIFrame *playgroundBlocks = mEditPlaygroundCanvas->GetPlaygroundBlocks();
	Sizef pbSize = playgroundBlocks->GetSize();
	CameraNode *camNode = mEditPlaygroundCanvas->GetUICameraNode();
	Camera *cam = camNode->GetCamera();
	APoint camNodeLocalPos = camNode->LocalTransform.GetTranslate();
	float rMin = 0.0f; float rMax = 0.0f;
	float uMin = 0.0f; float uMax = 0.0f;
	float dMin = 0.0f; float dMax = 0.0f;
	cam->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
	float camWidth = rMax - rMin;
	float camHeight = uMax - uMin;
	float posX = camWidth * posSizePercentWdith;
	float posY = camHeight * posSizePercentHeight;

	APoint dragingPos(camNodeLocalPos.X() - rMax + posX, 0.0f, camNodeLocalPos.Z() - uMax + posY);
	float dragingLeft = dragingPos.X() - (-pbSize.Width*0.5f);
	float dragingUp = dragingPos.Z() - pbSize.Height*0.5f;

	return Float2(dragingLeft, dragingUp);
}
//----------------------------------------------------------------------------
void UIBBlockEdit::_RefreshFile(LFile *lFile)
{
	mEditPlaygroundCanvas->GetPlaygroundBlocks()->DetachAllChildren();

	if (lFile)
	{
		std::vector<LBlockPtr> &programs = lFile->GetBlockPrograms();
		for (int i = 0; i < (int)programs.size(); i++)
		{
			LBlock *lBlock = programs[i];
			_RefreshBlock(0, lBlock);
		}

		PX2_BBM.SetNeedCompileScript(true);
	}
}
//----------------------------------------------------------------------------
void UIBBlockEdit::_RefreshBlock(Node *parentNode, LBlock *lBlock)
{
	BBlock *uiBlock = new0 BBlock();
	uiBlock->SetLBlock(lBlock);
	uiBlock->SetEditState(BBlock::ES_EDITOR);

	if (parentNode)
	{
		parentNode->AttachChild(uiBlock);

		uiBlock->SetAnchorHor(0.0f, 0.0f);
		uiBlock->SetAnchorParamHor(0.0f, 0.0f);

		BBlockConnector *parentCnt = DynamicCast<BBlockConnector>(parentNode);
		if (parentCnt)
		{
			BBlockConnector::ConnectorType ct = parentCnt->GetConnectorType();
			if (BBlockConnector::CT_PARAM == ct)
			{
				uiBlock->SetAnchorVer(0.5f, 0.5f);
				uiBlock->SetAnchorParamVer(0.0f, 0.0f);
			}
			else
			{
				uiBlock->SetAnchorVer(1.0f, 1.0f);
				uiBlock->SetAnchorParamVer(0.0f, 0.0f);
			}
		}
	}
	else
	{
		Vector3f pos = lBlock->GetAnchorParam();
		if (pos == Vector3f::ZERO)
		{
			float posX = 40.0f;
			uiBlock->SetAnchorHor(0.0f, 0.0f);
			uiBlock->SetAnchorVer(1.0f, 1.0f);
			uiBlock->SetAnchorParamHor(posX, posX);
			uiBlock->SetAnchorParamVer(-posX, -posX);
		}
		else
		{
			uiBlock->SetAnchorHor(0.0f, 0.0f);
			uiBlock->SetAnchorVer(1.0f, 1.0f);
			uiBlock->SetAnchorParamHor(pos.X(), pos.X());
			uiBlock->SetAnchorParamVer(pos.Y(), pos.Y());
		}

		mEditPlaygroundCanvas->GetPlaygroundBlocks()->AttachChild(uiBlock);
	}

	int numInputs = lBlock->GetNumInputs();
	for (int i = 0; i < numInputs; i++)
	{
		LParam *lParam = lBlock->GetInputParam(i);
		if (lParam)
		{
			LBlock *linkBlock = lParam->GetLinkBlock();
			if (linkBlock)
			{
				const std::string &paramName = lParam->GetName();
				BBlockConnector *cnt = uiBlock->GetBlockConnectorByName(paramName);

				_RefreshBlock(cnt, linkBlock);
			}
		}
	}

	int numOutputs = lBlock->GetNumOutputs();
	for (int i = 0; i < numOutputs; i++)
	{
		LParam *lParam = lBlock->GetOutputParam(i);
		if (lParam)
		{
			LBlock *linkBlock = lParam->GetLinkBlock();
			if (linkBlock)
			{
				const std::string &paramName = lParam->GetName();
				BBlockConnector *cnt = uiBlock->GetBlockConnectorByName(paramName);

				_RefreshBlock(cnt, linkBlock);
			}
		}
	}

	LParam *nextParam = lBlock->GetLParamByName("Next");
	if (nextParam)
	{
		LBlock *linkBlock = nextParam->GetLinkBlock();
		if (linkBlock)
		{
			BBlockConnector *cnt = uiBlock->GetBlockConnectorByName("Next");
			_RefreshBlock(cnt, linkBlock);
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
UIBBlockEdit::UIBBlockEdit(LoadConstructor value) :
UIFrame(value)
{
}
//----------------------------------------------------------------------------
void UIBBlockEdit::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(UIBBlockEdit, source);
}
//----------------------------------------------------------------------------
void UIBBlockEdit::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void UIBBlockEdit::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool UIBBlockEdit::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void UIBBlockEdit::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(UIBBlockEdit, target);
}
//----------------------------------------------------------------------------
int UIBBlockEdit::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------