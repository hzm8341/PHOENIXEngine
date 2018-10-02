// PX2Edit.cpp

#include "PX2Edit.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2SelectionManager.hpp"
#include "PX2Creater.hpp"
#include "PX2RedoUndo.hpp"
#include "PX2Project.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2EditorEventType.hpp"
#include "PX2Animation.hpp"
#include "PX2EditorToLua.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2LuaPlusContext.hpp"
#include "PX2InputEvent.hpp"
#include "PX2InputEventData.hpp"
#include "PX2RenderWindow.hpp"
#include "PX2EditorEventType.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
int Edit::msEditorID = 10001;
//----------------------------------------------------------------------------
Edit::Edit() :
mEditType(ET_SCENE),
mEditAxisMode(EAM_WORLD),
mEditMode(EM_NONE),
mRenderMode(RM_NORMAL),
mCameraMode(CM_PERSPECTIVE),
mGeoObjFactory(0),
IsAltDown(false),
IsCtrlDown(false),
IsShiftDown(false),
IsKeyDown_W(false),
IsKeyDown_S(false),
IsKeyDown_A(false),
IsKeyDown_D(false),
IsLeftMouseDown(false),
IsRightMouseDown(false),
IsMidMouseDown(false),
mCameraMoveLevel(1),
mCameraMoveSpeedBase(20.0f),
mEU_Man(0)
{
	PX2_LOGICM.SetPlatformType(LogicManager::PT_EDITOR);

	mTimeLineEidt = new0 TimeLineEdit();
	mTerrainEdit = new0 TerrainEdit();

	mHelpNode = new0 Node();
	mHelpNode->AttachChild(mTerrainEdit->GetBrush()->GetRenderable());

	LuaPlusContext *lpc = (LuaPlusContext*)PX2_SC_LUA;
	lua_State *luaState = (lua_State*)lpc->GetLuaState();

	luaopen_PX2Editor(luaState);

	PX2_SC_LUA->SetUserTypePointer("PX2_EDIT", "Edit", Edit::GetSingletonPtr());
	PX2_SC_LUA->SetUserTypePointer("PX2EU_MAN", "EU_Manager", 
		EU_Manager::GetSingletonPtr());

	PX2_EW.ComeIn(this);
}
//----------------------------------------------------------------------------
Edit::~Edit()
{
	PX2_EW.GoOut(this);

	delete0(mTimeLineEidt);
	delete0(mTerrainEdit);
}
//----------------------------------------------------------------------------
bool Edit::Initlize(const std::string &tag)
{
	mGeoObjFactory = new0 GeoObjFactory();

	PX2_APP.SetInEditor(true);

	mEU_Man = new0 EU_Manager();
	mEU_Man->Initlize(tag);
	
	return true;
}
//----------------------------------------------------------------------------
bool Edit::Initlize1(const std::string &tag)
{
	mEU_Man->Initlize1(tag);

	return true;
}
//----------------------------------------------------------------------------
bool Edit::Terminate()
{
	PX2_UIAUIM.Clear();

	mEditCameraNode = 0;

	mCopyObject = 0;

	if (mEU_Man)
	{
		mEU_Man->Terminate1();
		delete0(mEU_Man);
		EU_Manager::Set(0);
	}

	if (mGeoObjFactory)
	{
		delete0(mGeoObjFactory);
	}
	
	return true;
}
//----------------------------------------------------------------------------
void Edit::Reset()
{
	mCopyObject = 0;
	mSelectPath_ChildFilenames.clear();
	mSelectPath_ChildPaths.clear();

	SetEditType(ET_SCENE);
	SetEditMode(EM_NONE);
}
//----------------------------------------------------------------------------
void Edit::SetEditType(EditType type)
{
	mEditType = type;

	Event *ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::SetEditType);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::SetEditAxisMode(EditAxisMode mode)
{
	mEditAxisMode = mode;

	Event *ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::SetEditAxisMode);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::SetEditMode(EditMode mode)
{
	mEditMode = mode;

	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::SetEditMode);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::SetRenderMode(RenderMode mode)
{
	mRenderMode = mode;

	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::SetRenderMode);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::SetCameraMode(CameraMode camMode)
{
	mCameraMode = camMode;

	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::SetCameraMode);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::SetSimuRenderViewMode(SimuRenderViewMode mode)
{
	mSimuRenderViewMode = mode;

	Event *ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::SetSimuRenderViewMode);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::SetEditorCameraNode(CameraNode *editCameraNode)
{
	mEditCameraNode = editCameraNode;
}
//----------------------------------------------------------------------------
CameraNode *Edit::GetEditorCameraNode()
{
	return mEditCameraNode;
}
//----------------------------------------------------------------------------
int Edit::GetEditID()
{
	return msEditorID++;
}
//----------------------------------------------------------------------------
void Edit::SetPickPos(const APoint &pos)
{
	mPickPos = pos;

	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::SetPickPos);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
APoint Edit::GetPickLocalPos(Movable *nodeParent)
{
	APoint localPos;

	if (nodeParent)
	{
		Transform inversTrans = nodeParent->WorldTransform.InverseTransform();
		localPos = inversTrans * mPickPos;
	}
	else
	{
		localPos = mPickPos;
	}

	return localPos;
}
//----------------------------------------------------------------------------
void Edit::FocusOnSelection()
{
	int numMovs = 0;
	APoint center;
	APoint boundCenter;
	float radius = 0.0f;
	GetSelectionCenterRadius(numMovs, center, boundCenter, radius);

	if (0 == numMovs)
		return;

	if (0.0f == radius)
	{
		radius = 10.0f;
	}

	CameraNode *editorCameraNode = PX2_EDIT.GetEditorCameraNode();
	const APoint &curPos = editorCameraNode->WorldTransform.GetTranslate();
	AVector dir = editorCameraNode->GetCamera()->GetDVector();
	dir.Normalize();
	float upFovDegrees = 0.0f;
	float aspectRatio = 0.0f;
	float dMin = 0.0f;
	float dMax = 0.0f;
	editorCameraNode->GetCamera()->GetFrustum(upFovDegrees, aspectRatio, dMin, dMax);
	APoint toPos = center;
	toPos -= dir * (radius + dMin * 10.0f);

	InterpCurveTranslateController *transCtrl = 
		DynamicCast<InterpCurveTranslateController>(
		editorCameraNode->GetControllerByName("Camera_ICTC"));
	if (transCtrl)
	{
		transCtrl->SetWorld(true);
		transCtrl->mValues.Reset();
		transCtrl->mValues.AddPoint(0.0f, curPos, Float3::ZERO, Float3::ZERO,
			ICM_CURVE_AUTO);
		transCtrl->mValues.AddPoint(0.5f, toPos, Float3::ZERO, Float3::ZERO, 
			ICM_CURVE_AUTO);
		transCtrl->MaxTime = 0.5f;
		transCtrl->SetMaxPlayTime(0.5f);
		transCtrl->ResetPlay();
	}	
}
//----------------------------------------------------------------------------
void Edit::GetSelectionCenterRadius(int &numMovs, APoint &center, 
	APoint &boundCenter,
	float &radius)
{
	APoint pos;
	Bound bound;

	int numMovable = 0;
	int numObjscts = PX2_SELECTM_E->GetNumObjects();
	if (numObjscts > 0)
	{
		int firstBound = true;

		for (int i = 0; i < numObjscts; i++)
		{
			Object *obj = PX2_SELECTM_E->GetObjectAt(i);
			Movable *movable = DynamicCast<Movable>(obj);
			CameraNode *camNode = DynamicCast<CameraNode>(obj);
			PX2_UNUSED(camNode);

			if (movable)
			{
				pos += movable->WorldTransform.GetTranslate();

				if (0.0f != movable->WorldBound.GetRadius())
				{
					if (firstBound)
					{
						bound = movable->WorldBound;
						firstBound = false;
					}
					else
					{
						bound.GrowToContain(movable->WorldBound);
					}
				}

				numMovable++;
			}
		}

		pos = pos / (float)numObjscts;
	}

	numMovs = numMovable;
	center = pos;
	boundCenter = bound.GetCenter();
	radius = bound.GetRadius();
}
//----------------------------------------------------------------------------
bool Edit::DeleteSelection()
{
	bool deleted = false;

	int numObjs = PX2_SELECTM_E->GetNumObjects();
	for (int i = 0; i < numObjs; i++)
	{
		Object *obj = PX2_SELECTM_E->GetObjectAt(i);
		if (PX2_CREATER.RemoveObject(obj))
		{
			deleted = true;
		}
	}

	if (deleted)
	{
		PX2_SELECTM_E->Clear();
	}

	return deleted;
}
//----------------------------------------------------------------------------
void Edit::ChangeSelectResDir(const std::string &path, ChangeDirType cdt)
{
	mSelectResDir = path;

	Event *ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::ChangeResDir);
	ent->SetData<Edit::ChangeDirType>(cdt);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::SetSelectedResource(const SelectResData &data)
{
	mSelectResData = data;

	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::SelectRes);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::CopySelectResourcePath()
{
	const SelectResData &resData = PX2_EDIT.GetSelectedResource();
	SelectResData::SelectResType type = resData.GetSelectResType();

	if (type == SelectResData::RT_NORMAL)
	{
		SetCopyText(resData.ResPathname);
	}
	else
	{
		SetCopyText(resData.EleName);
	}
}
//----------------------------------------------------------------------------
void Edit::CopyObject()
{
	Event *ent = PX2_CREATEEVENTEX(EditorEventSpace, Copy);
	PX2_EW.BroadcastingLocalEvent(ent);

	int numObjects = PX2_SELECTM_E->GetNumObjects();
	if (1 == numObjects)
	{
		SetCopyObject(PX2_SELECTM_E->GetFirstObject());
	}
	else
	{
		SetCopyObject(0);
	}
}
//----------------------------------------------------------------------------
void Edit::PasteCopyedObject()
{
	Movable *mov = DynamicCast<Movable>(mCopyObject);
	Node *parentNode = DynamicCast<Node>(PX2_SELECTM_E->GetFirstObject());

	if (mov && parentNode)
	{
		MovablePtr newMov = DynamicCast<Movable>(PX2_RM.ShareCopy(mov, true, true, false));	
		PX2_CREATER.AddObject(parentNode, newMov);
	}

	Event *ent = PX2_CREATEEVENTEX(EditorEventSpace, Paste);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::CloneSelectedObject()
{
	int numObjects = PX2_SELECTM_E->GetNumObjects();
	if (1 == numObjects)
	{
		SetCopyObject(PX2_SELECTM_E->GetFirstObject());
	}
	else
	{
		SetCopyObject(0);
	}

	for (int i = 0; i < numObjects; i++)
	{
		Movable *mov = DynamicCast<Movable>(PX2_SELECTM_E->GetObjectAt(i));
		if (mov)
		{
			Node *nodeParent = DynamicCast<Node>(mov->GetParent());
			if (mov && nodeParent)
			{
				MovablePtr newMov = DynamicCast<Movable>(PX2_RM.ShareCopy(mov, false, false, false));
				PX2_CREATER.AddObject(nodeParent, newMov);
			}
		}
	}

	Event *ent = PX2_CREATEEVENTEX(EditorEventSpace, Clone);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::DeleteObject()
{
	Event *ent = PX2_CREATEEVENTEX(EditorEventSpace, Delete);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::SetCopyText(const std::string &copyText)
{
	mCopyText = copyText;
	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::SetCopyText);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
const std::string &Edit::GetCopyText() const
{
	return mCopyText;
}
//----------------------------------------------------------------------------
bool Edit::Import(const char *pathname)
{
	int numObjs = PX2_SELECTM_E->GetNumObjects();
	if (1 != numObjs) return false;

	Object *selectObj = PX2_SELECTM_E->GetFirstObject();

	InStream inStream;
	if (inStream.Load(pathname))
	{
		Object *obj = inStream.GetObjectAt(0);
		PX2_CREATER.AddObject(selectObj, obj);

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
bool Edit::Export(PX2::Object *obj, const char *pathname)
{
	if (!obj) return false;

	Controller *ctrl = DynamicCast<Controller>(obj);
	Movable *mov = DynamicCast<Movable>(obj);

	Controlledable *ctrlAble = 0;
	Node *node = 0;

	if (ctrl)
	{
		ctrlAble = ctrl->GetControlledable();
		ctrlAble->DetachController(ctrl);
	}
	else if (mov)
	{
		node = DynamicCast<Node>(mov->GetParent());
		if (node) node->DetachChild(mov);
	}

	OutStream outStream;
	outStream.Insert(obj);
	if (outStream.Save(pathname))
	{
		if (ctrl && ctrlAble)
		{
			ctrlAble->AttachController(ctrl);
		}
		else if (mov && node)
		{
			node->AttachChild(mov);
		}

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void Edit::AnimPlay()
{
	Object *obj = PX2_SELECTM_E->GetFirstObject();
	Controller *ctrl = DynamicCast<Controller>(obj);
	Controlledable *ctrlable = DynamicCast<Controlledable>(obj);
	Animation *anim = DynamicCast<Animation>(obj);

	if (ctrl)
	{
		ctrl->Play();
	}
	else if (ctrlable)
	{
		ctrlable->Play();
	}
	else if (anim)
	{
		anim->LetCharacterPlay();
	}
}
//----------------------------------------------------------------------------
void Edit::AnimResetPlay()
{
	Object *obj = PX2_SELECTM_E->GetFirstObject();
	Controller *ctrl = DynamicCast<Controller>(obj);
	Controlledable *ctrlable = DynamicCast<Controlledable>(obj);
	Animation *anim = DynamicCast<Animation>(obj);

	if (ctrl)
	{
		ctrl->ResetPlay();
	}
	else if (ctrlable)
	{
		ctrlable->ResetPlay();
	}
	else if (anim)
	{
		anim->LetCharacterPlay();
	}
}
//----------------------------------------------------------------------------
void Edit::AnimStop()
{
	Object *obj = PX2_SELECTM_E->GetFirstObject();
	Controller *ctrl = DynamicCast<Controller>(obj);
	Controlledable *ctrlable = DynamicCast<Controlledable>(obj);
	Animation *anim = DynamicCast<Animation>(obj);

	if (ctrl)
	{
		ctrl->Pause();
	}
	else if (ctrlable)
	{
		ctrlable->Pause();
	}
	else if (anim)
	{
		anim->Pause();
	}
}
//----------------------------------------------------------------------------
void Edit::AnimReset()
{
	Object *obj = PX2_SELECTM_E->GetFirstObject();
	Controller *ctrl = DynamicCast<Controller>(obj);
	Controlledable *ctrlable = DynamicCast<Controlledable>(obj);
	Animation *anim = DynamicCast<Animation>(obj);

	if (ctrl)
	{
		ctrl->Reset();
	}
	else if (ctrlable)
	{
		ctrlable->Reset();
	}
	else if (anim)
	{
		anim->Pause();
	}
}
//----------------------------------------------------------------------------
bool Edit::IsAnimPlaying()
{
	Object *obj = PX2_SELECTM_E->GetFirstObject();
	Controller *ctrl = DynamicCast<Controller>(obj);
	Controlledable *ctrlable = DynamicCast<Controlledable>(obj);
	Animation *anim = DynamicCast<Animation>(obj);

	if (ctrl)
	{
		return ctrl->IsPlaying();
	}
	else if (ctrlable)
	{
		return ctrlable->IsPlaying();
	}
	else if (anim)
	{
		return anim->IsPlaying();
	}

	return false;
}
//----------------------------------------------------------------------------
void Edit::AnimPlayStop()
{
	if (IsAnimPlaying())
		AnimStop();
	else
		AnimPlay();
}
//----------------------------------------------------------------------------
void Edit::MakeSelectTimeLineEdit()
{
	PX2::Object *obj = PX2_SELECTM_E->GetFirstObject();

	EffectModule *eftModule = DynamicCast<EffectModule>(obj);
	InterpCurveController *interpCurve = DynamicCast<InterpCurveController>(obj);

	if (eftModule || interpCurve)
	{
		if (!mTimeLineEidt->HasCurveGroup(obj))
		{
			mTimeLineEidt->CreateAddCurveGroup(obj);
		}
	}
}
//----------------------------------------------------------------------------
void Edit::TimeLine_UIGroup_Delete()
{
	UICurveGroup *group = PX2_EDIT.GetTimeLineEdit()->GetSelectedUICurveGroup();

	if (group)
	{
		PX2_EDIT.GetTimeLineEdit()->ClearGroup(group);
		PX2_EDIT.GetTimeLineEdit()->SetSelectedUICurveGroup(0);
	}
}
//----------------------------------------------------------------------------
void Edit::TimeLine_UIGroup_DeleteAll()
{
	PX2_EDIT.GetTimeLineEdit()->ClearAllGroups();
	PX2_EDIT.GetTimeLineEdit()->SetSelectedUICurveGroup(0);
}
//----------------------------------------------------------------------------
void Edit::TimeLine_AddPoint()
{
	GetTimeLineEdit()->AddPoint();
}
//----------------------------------------------------------------------------
void Edit::TimeLine_DeletePoint()
{
	GetTimeLineEdit()->DeletePoint();
}
//----------------------------------------------------------------------------
void Edit::TimeLine_SetInValue()
{
	GetTimeLineEdit()->SetInValue();
}
//----------------------------------------------------------------------------
void Edit::TimeLine_SetOutValue()
{
	GetTimeLineEdit()->SetOutValue();
}
//----------------------------------------------------------------------------
void Edit::FindSelectInProjTree()
{
	Object *obj = PX2_SELECTM_E->GetFirstObject();
	if (obj)
	{
		Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::FindActorInProjectTree);
		ent->SetData<Object*>(obj);
		PX2_EW.BroadcastingLocalEvent(ent);
	}
}
//----------------------------------------------------------------------------
void Edit::FindSelectInResTree()
{
	Object *obj = PX2_SELECTM_E->GetFirstObject();
	if (obj)
	{
		Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::FindObjectInResTree);
		ent->SetData<Object*>(obj);
		PX2_EW.BroadcastingLocalEvent(ent);
	}
}
//----------------------------------------------------------------------------
void Edit::SetPreViewObject(Object *obj)
{
	mPreObject = obj;

	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::SetPreViewObject);
	ent->SetData<PX2::Object*>(obj);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::Undo()
{
	PX2_URDOM.UnDo();

	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::Undo);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::Redo()
{
	PX2_URDOM.ReDo();

	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::Redo);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::OnEvent(Event *event)
{
	if (InputEventSpace::IsEqual(event, InputEventSpace::KeyPressed))
	{
		InputEventData ied = event->GetData<InputEventData>();
		if (KeyCode::KC_F == ied.KCode)
		{
			FocusOnSelection();
		}
	}
}
//----------------------------------------------------------------------------
void Edit::AddOpenedFile(const std::string &path)
{
	//mOpenedFiles.push_back(path);

	std::string outPath;
	std::string outBaseName;
	std::string outExtention;
	StringHelp::SplitFullFilename(path, outPath, outBaseName, outExtention);
	std::string filename = outBaseName + "." + outExtention;

	Event *ent = PX2_CREATEEVENTEX(EditorEventSpace, OpenContentRes);
	ent->SetDataStr0(path);
	ent->SetDataStr1(filename);
	ent->SetDataStr2(outExtention);
	ent->SetData<std::string>(path);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
bool Edit::IsAddedOpenedFile(const std::string &path)
{
	auto it = mOpenedFiles.begin();
	for (; it != mOpenedFiles.end(); it++)
	{
		if (path == *it)
		{
			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
bool Edit::RemoveOpenedFile(const std::string &path)
{
	auto it = mOpenedFiles.begin();
	for (; it != mOpenedFiles.end();)
	{
		if (path == *it)
		{
			it = mOpenedFiles.erase(it);

			Event *ent = PX2_CREATEEVENTEX(EditorEventSpace, RemoveContentRes);
			ent->SetDataStr0(path);
			ent->SetData<std::string>(path);
			PX2_EW.BroadcastingLocalEvent(ent);

			return true;
		}
		else
		{
			it++;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
void Edit::SetActivateOpenedFile(const std::string &path)
{
	mActivateOpenedFile = path;
}
//----------------------------------------------------------------------------
const std::string &Edit::GetActivateOpenedFile() const
{
	return mActivateOpenedFile;
}
//----------------------------------------------------------------------------
void Edit::BroadCastEditorEventRefreshRes()
{
	Event *ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::RefreshRes);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::BraodCastEditorEventClearRes()
{
	Event *ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::ClearRes);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::BroadCastEditorEventUp()
{
	Event *ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::UpRes);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::BroadCastEditorEventDown()
{
	Event *ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::DownRes);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::BroadCastEditorEventPlayInWindow()
{
	Event *ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::N_PlayInWindow);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::BroadCastEditorSaveText()
{
	Event *ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::SaveText);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Edit::OpenResIn(const std::string &pathFilename)
{
	if (!PX2_EDIT.IsAddedOpenedFile(pathFilename))
	{
		PX2_EDIT.AddOpenedFile(pathFilename);
	}
}
//----------------------------------------------------------------------------
void Edit::OpenResOut(const std::string &pathFilename)
{
	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::OpenRes);
	ent->SetData<std::string>(pathFilename);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------