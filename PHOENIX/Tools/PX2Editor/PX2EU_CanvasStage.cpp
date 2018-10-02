// PX2EU_CanvasStage.cpp

#include "PX2EU_CanvasStage.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2InputEventData.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2SelectionManager.hpp"
#include "PX2Project.hpp"
#include "PX2Edit.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditorEventType.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2SelectionManager.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2VertexColor4Material.hpp"
#include "PX2Application.hpp"
#include "PX2EU_ProjectEventController.hpp"
#include "PX2Picker.hpp"
#include "PX2GraphicsEventType.hpp"
#include "PX2RenderWindow.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Canvas, EU_CanvasStage);
PX2_IMPLEMENT_STREAM(EU_CanvasStage);
PX2_IMPLEMENT_FACTORY(EU_CanvasStage);

//----------------------------------------------------------------------------
EU_CanvasStage::EU_CanvasStage():
mViewType(VT_PERSPECTIVE),
mViewDetail(VD_TEXTURED),
mCameraDragType(CDT_NONE),
mCurCameraMoveSpeed_W(0.0f),
mCurCameraMoveSpeed_S(0.0f),
mCurCameraMoveSpeed_A(0.0f),
mCurCameraMoveSpeed_D(0.0f)
{
	SetName("EU_CanvasStage");

	SetClearFlag(true, true, true);
	SetClearColor(PX2_UISM.Color_ViewBackground4);

	CreateUICameraNode();
	GetUICameraNode()->GetCamera()->SetClearFlag(false, false, false);
	GetUICameraNode()->GetCamera()->SetName("EU_CanvasStageCameraNode");

	SetAnchorHor(0.0f, 1.0f);
	SetAnchorVer(0.0f, 1.0f);

	mStageCameraNodeRoot = new0 Node();
	AttachChild(mStageCameraNodeRoot);
	mStageCameraNodeRoot->WorldTransformIsCurrent = true;

	mStageCameraNode = PX2_CREATER.CreateNode_Camera();
	mStageCameraNode->SetName("MainCameraNode");
	mStageCameraNode->GetCamera()->SetName("MainCamera");
	mStageCameraNode->GetCamera()->SetClearFlag(false, false, false);
	mStageCameraNodeRoot->AttachChild(mStageCameraNode);
	SetViewType(EU_CanvasStage::VT_PERSPECTIVE);
	PX2_EDIT.SetCameraMode(Edit::CM_PERSPECTIVE);

	Camera *editorCamera = mStageCameraNode->GetCamera();
	float upFovDegrees = 0.0f;
	float aspectRation = 0.0f;
	float dMin = 0.0f;
	float dMax = 0.0f;
	editorCamera->GetFrustum(upFovDegrees, aspectRation, dMin, dMax);
	aspectRation = mSize.Width / mSize.Height;
	editorCamera->SetFrustum(upFovDegrees, aspectRation, dMin, 5000.0f);
	PX2_EDIT.SetEditorCameraNode(mStageCameraNode);
	InterpCurveTranslateController *transCtrl = new0 InterpCurveTranslateController();
	mStageCameraNode->AttachController(transCtrl);
	transCtrl->SetName("Camera_ICTC");
	transCtrl->SetPlaySelfCtrl(true);

	_CreateGridGeometry();
	_CreateSceneCanvas();
	_CreateNodeCtrl();
	_CreateCameraViewCanvas();
	ShowContent(false);

	Enable(false);

	SetOverCameraNode(mStageCameraNode);

	SetPickPosRecal(true);
	SetActivateSelfCtrled(false);
}
//----------------------------------------------------------------------------
EU_CanvasStage::~EU_CanvasStage()
{
	if (mSceneNodeCtrl)
		PX2_EW.GoOut(mSceneNodeCtrl);

	if (mBoundCtrl)
		PX2_EW.GoOut(mBoundCtrl);
}
//----------------------------------------------------------------------------
void EU_CanvasStage::SetOverCameraNode(CameraNode *cameraNode)
{
	mStageCameraNode = cameraNode;

	if (mGridCanvas)
		mGridCanvas->SetOverCamera(mStageCameraNode->GetCamera());
	if (mSceneCanvas)
		mSceneCanvas->SetOverCamera(mStageCameraNode->GetCamera());
	if (mSceneNodeCtrlCanvas)
		mSceneNodeCtrlCanvas->SetOverCamera(mStageCameraNode->GetCamera());
}
//----------------------------------------------------------------------------
CameraNode *EU_CanvasStage::GetOverCameraNode()
{
	return mStageCameraNode;
}
//----------------------------------------------------------------------------
void EU_CanvasStage::SetViewType(ViewType viewType)
{
	mViewType = viewType;

	APoint pos = mStageCameraNode->LocalTransform.GetTranslate();

	if (VT_PERSPECTIVE == mViewType)
	{
		mStageCameraNode->GetCamera()->SetPerspective(true);
		mStageCameraNode->LocalTransform.SetTranslate(-20.0f, -20.0f, 10.0f);
		mStageCameraNode->LookAt(APoint(0.0f, 0.0f, 0.0f), AVector::UNIT_Z);
		_UpdateCamera();
		mStageCameraNode->Update();
		if (0 == PX2_SELECTM_E->GetNumObjects())
		{
		}
		else
		{
			PX2_EDIT.FocusOnSelection();
		}
	}
	else if (VT_LEFT == mViewType)
	{
		mStageCameraNode->GetCamera()->SetPerspective(false);
		mStageCameraNode->LookDir(AVector::UNIT_X);
	}
	else if (VT_TOP == mViewType)
	{
		mStageCameraNode->LocalTransform.SetTranslateZ(100.0);
		mStageCameraNode->GetCamera()->SetPerspective(false);
		mStageCameraNode->LookDir(-AVector::UNIT_Z, AVector::UNIT_Y);
		mStageCameraNode->Update();
		PX2_EDIT.FocusOnSelection();
	}
}
//----------------------------------------------------------------------------
EU_CanvasStage::ViewType EU_CanvasStage::GetViewType()
{
	return mViewType;
}
//----------------------------------------------------------------------------
void EU_CanvasStage::SetViewDetail(ViewDetail viewDetail)
{
	mViewDetail = viewDetail;
	
	if (ViewDetail::VD_WIREFRAME == mViewDetail)
	{
		SetOverWireframe(true);
	}
	else
	{
		SetOverWireframe(false);
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStage::SetCameraDragType(CameraDragType type)
{
	mCameraDragType = type;
}
//----------------------------------------------------------------------------
EU_CanvasStage::CameraDragType EU_CanvasStage::GetCameraDragType() const
{
	return mCameraDragType;
}
//----------------------------------------------------------------------------
EU_CanvasStage::ViewDetail EU_CanvasStage::GetViewDetail() const
{
	return mViewDetail;
}
//----------------------------------------------------------------------------
void EU_CanvasStage::Enable(bool enable)
{
	Canvas::Enable(enable);
}
//----------------------------------------------------------------------------
void EU_CanvasStage::ShowContent(bool show)
{
	if (mGridCanvas)
		mGridCanvas->Show(show);
	if (mSceneCanvas)
		mSceneCanvas->Show(show);
	if (mSceneNodeCtrlCanvas)
		mSceneNodeCtrlCanvas->Show(show);
}
//----------------------------------------------------------------------------
void EU_CanvasStage::Draw(Renderer *renderer)
{
	Project *proj = Project::GetSingletonPtr();
	if (proj)
	{
		Scene *scene = proj->GetScene();
		if (scene)
			PX2_GR.SetCurEnvirParamController(scene->GetEnvirParamController());
	}

	Canvas::Draw(renderer);
}
//----------------------------------------------------------------------------
void EU_CanvasStage::OnEvent(Event *event)
{
	Canvas::OnEvent(event);

	if (InputEventSpace::IsEqual(event, InputEventSpace::KeyPressed))
	{
		if (!PX2_EDIT.IsLeftMouseDown && !PX2_EDIT.IsRightMouseDown &&
			!PX2_EDIT.IsMidMouseDown)
		{
			InputEventData ieData = event->GetData<InputEventData>();

			if (KC_Q == ieData.KCode)
			{
				PX2_EDIT.SetEditMode(Edit::EM_SELECT);
			}
			else if (KC_W == ieData.KCode)
			{
				PX2_EDIT.SetEditMode(Edit::EM_TRANSLATE);
			}
			else if (KC_E == ieData.KCode)
			{
				PX2_EDIT.SetEditMode(Edit::EM_ROTATE);
			}
			else if (KC_R == ieData.KCode)
			{
				PX2_EDIT.SetEditMode(Edit::EM_SCALE);
			}
		}
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::SetEditType))
	{
		Edit::EditType editType = PX2_EDIT.GetEditType();
		bool editScene = (Edit::EditType::ET_SCENE == editType ||
			Edit::EditType::ET_TERRAIN == editType);
		Enable(editScene);
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::SetRenderMode))
	{
		Edit::RenderMode rm = PX2_EDIT.GetRenderMode();
		if (Edit::RenderMode::RM_NORMAL == rm)
		{
			SetViewDetail(EU_CanvasStage::VD_SOLID);
		}
		else if (Edit::RenderMode::RM_WIREFRAME == rm)
		{
			SetViewDetail(EU_CanvasStage::VD_WIREFRAME);
		}
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::SetCameraMode))
	{
		Edit::CameraMode cm = PX2_EDIT.GetCameraMode();
		if (Edit::CameraMode::CM_PERSPECTIVE == cm)
		{
			SetViewType(ViewType::VT_PERSPECTIVE);
		}
		else if (Edit::CameraMode::CM_TOP == cm)
		{
			SetViewType(ViewType::VT_TOP);
		}
		else if (Edit::CameraMode::CM_LEFT == cm)
		{
			SetViewType(ViewType::VT_LEFT);
		}
		else if (Edit::CameraMode::CM_FRONT == cm)
		{
			SetViewType(ViewType::VT_FRONT);
		}
	}
	else if (EditES::IsEqual(event, EditES::AddSelect))
	{
		_UpdateCameraCanvas();
	}
	else if (EditES::IsEqual(event, EditES::RemoveSelect))
	{
		_UpdateCameraCanvas();
		mURDoCommand = 0;
	}
	else if (EditES::IsEqual(event, EditES::RemoveAllSelects))
	{
		_UpdateCameraCanvas();
		mURDoCommand = 0;
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStage::OnSizeChanged()
{
	Canvas::OnSizeChanged(); 

	Camera *editorCamera = mStageCameraNode->GetCamera();

	if (editorCamera)
	{
		float upFovDegrees = 0.0f;
		float aspectRation = 0.0f;
		float dMin = 0.0f;
		float dMax = 0.0f;
		editorCamera->GetFrustum(upFovDegrees, aspectRation, dMin, dMax);

		aspectRation = mSize.Width / mSize.Height;
		editorCamera->SetFrustum(upFovDegrees, aspectRation, dMin, dMax);
	}

	if (mCameraCanvasView)
	{
		Sizef cameraCanvasSize = mCameraCanvasSize;

		const Sizef &size = GetSize();
		if (size.Width < cameraCanvasSize.Width)
		{
			cameraCanvasSize.Width = size.Width;
		}
		if (cameraCanvasSize.Width < 0.0f)
			cameraCanvasSize.Width = 0.0f;

		if (size.Height < cameraCanvasSize.Height)
		{
			cameraCanvasSize.Height = size.Height;
		}
		if (cameraCanvasSize.Height < 0.0f)
			cameraCanvasSize.Height = 0.0f;

		mCameraCanvasView->SetSize(cameraCanvasSize);
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStage::UpdateWorldData(double applicationTime,
	double elapsedTime)
{
	Float2 delta = RenderWindow::GetMoveDelta();

	if (RenderWindow::IsScreenDrag())
	{	
		if (mSceneNodeCtrl && mSceneNodeCtrl->IsDragNone())
		{
			float speedVal = 0.5f;
			if (VT_PERSPECTIVE == mViewType)
			{
				CameraDragType cdt = GetCameraDragType();
				if (PX2_EDIT.IsAltDown)
				{
					if (CDT_NORMAL_MIDDLE == GetCameraDragType())
					{
						Movable *mov = DynamicCast<Movable>(PX2_SELECTM_E->GetFirstObject());
						if (mov)
						{
							_RoundCamera(delta[0] * speedVal, -delta[1] * speedVal);
						}
						else
						{
							_PanCamera(delta[0] * speedVal, delta[1] * speedVal);
						}
					}
					else if (CDT_NORMAL_RIGHT == GetCameraDragType())
					{
						_ZoomCamera(-delta[1] * PX2_EDIT.GetCameraMoveSpeed()*speedVal * 0.05f);
					}
				}
				else
				{
					if (CDT_NORMAL_RIGHT == cdt)
					{
						_RolateCamera(delta[0] * speedVal, -delta[1] * speedVal * 0.5f);
					}
					else if (CDT_NORMAL_MIDDLE == cdt)
					{
						_PanCamera(-delta[0] * speedVal, delta[1] * speedVal);
					}
				}
			}
			else
			{
				_PanCamera(-delta[0] * speedVal, delta[1] * speedVal);
			}
		}
	}

	Canvas::UpdateWorldData(applicationTime, elapsedTime);

	if (mStageCameraNodeRoot)
	{
		mStageCameraNodeRoot->Update(applicationTime, elapsedTime);
	}

	if (mSceneNodeCtrl)
		mSceneNodeCtrl->UpdateCtrlTrans();
	if (mBoundCtrl)
		mBoundCtrl->UpdateCtrl();
}
//----------------------------------------------------------------------------
void EU_CanvasStage::_UpdateCameraCanvas()
{
	int numObjscts = PX2_SELECTM_E->GetNumObjects();
	if (1 == numObjscts)
	{
		Object *firstSelObj = PX2_SELECTM_E->GetFirstObject();
		CameraNode *camNode = DynamicCast<CameraNode>(firstSelObj);
		if (camNode)
		{
			if (mCameraCanvasView)
			{
				Scene *scene = PX2_PROJ.GetScene();

				mCameraCanvasView->SetOverCamera(camNode->GetCamera());
				mCameraCanvasView->SetRenderNode(scene);
				mCameraCanvasView->Show(true);
			}
		}
		else
		{
			if (mCameraCanvasView)
			{
				mCameraCanvasView->SetOverCamera(0);
				mCameraCanvasView->SetRenderNode(0);
				mCameraCanvasView->Show(false);
			}
		}
	}
	else
	{
		if (mCameraCanvasView)
		{
			mCameraCanvasView->SetOverCamera(0);
			mCameraCanvasView->SetRenderNode(0);
			mCameraCanvasView->Show(false);
		}
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStage::_CreateGridGeometry()
{
	float gridSize = PX2EU_MAN.GetEditParams()->GridSize;

	VertexFormat *vf = PX2_GR.GetVertexFormat(GraphicsRoot::VFT_PC);
	StandardMesh sM(vf);
	mGrid = sM.LineRectangleForEditor(81, 81, gridSize, gridSize,
		Float4(0.43f, 0.43f, 0.43f, 0.7f));

	PX2::RenderablePtr mGridAxis;
	PX2::VertexBufferAccessor mGridAxisAssessor;

	VertexBuffer *vb = new0 VertexBuffer(4, vf->GetStride(), Buffer::BU_DYNAMIC);
	VertexBufferAccessor vba;

	vba.ApplyTo(vf, vb);
	vba.Position<Float3>(0) = Float3(-gridSize, 0.0f, 0.0f);
	vba.Color<Float4>(0, 0) = Float4::RED;
	vba.Position<Float3>(1) = Float3(gridSize, 0.0f, 0.0f);
	vba.Color<Float4>(0, 1) = Float4::RED;

	vba.Position<Float3>(2) = Float3(0.0f, -gridSize, 0.0f);
	vba.Color<Float4>(0, 2) = Float4::GREEN;
	vba.Position<Float3>(3) = Float3(0.0f, gridSize, 0.0f);
	vba.Color<Float4>(0, 3) = Float4::GREEN;

	mGridAxis = new0 Polysegment(vf, vb, false);
	mGridAxis->UpdateModelSpace(Renderable::GU_MODEL_BOUND_ONLY);

	VertexColor4MaterialPtr mtl = new0 VertexColor4Material();
	mtl->GetAlphaProperty(0, 0)->BlendEnabled = true;

	mGrid->SetMaterialInstance(mtl->CreateInstance());
	mGridAxis->SetMaterialInstance(mtl->CreateInstance());

	mGridNode = new0 Node();
	mGridNode->AttachChild(mGridAxis);
	mGridNode->AttachChild(mGrid);
	mGridNode->Update(Time::GetTimeInSeconds(), true);

	mGridCanvas = new0 Canvas();
	AttachChild(mGridCanvas);
	mGridCanvas->LocalTransform.SetTranslateY(-1.0f);
	mGridCanvas->SetName("SceneGridCanvas");
	mGridCanvas->SetRenderNode(mGridNode);
	mGridCanvas->SetRenderNodeUpdate(true);
	mGridCanvas->SetAnchorHor(0.0f, 1.0f);
	mGridCanvas->SetAnchorVer(0.0f, 1.0f);
	mGridCanvas->SetClearFlag(false, false, false);
}
//----------------------------------------------------------------------------
void EU_CanvasStage::_CreateSceneCanvas()
{
	mSceneCanvas = new0 Canvas();
	AttachChild(mSceneCanvas);
	mSceneCanvas->LocalTransform.SetTranslateY(-2.0f);
	mSceneCanvas->SetName("SceneCanvas");
	mSceneCanvas->SetAnchorHor(0.0f, 1.0f);
	mSceneCanvas->SetAnchorVer(0.0f, 1.0f);
	mSceneCanvas->SetClearFlag(false, false, false);
	mSceneCanvas->SetRenderNodeUpdate(false);

	mSceneCanvas->AttachController(new0 EU_ProjectEventController());
}
//----------------------------------------------------------------------------
void EU_CanvasStage::_CreateCameraViewCanvas()
{
	mCameraCanvasSize = Sizef(150.0f, 100.0f);

	mCameraCanvasView = new0 Canvas();
	AttachChild(mCameraCanvasView);
	mCameraCanvasView->LocalTransform.SetTranslateY(-4.0f);
	mCameraCanvasView->SetAnchorHor(1.0f, 1.0f);
	mCameraCanvasView->SetAnchorVer(1.0f, 1.0f);
	mCameraCanvasView->SetSize(mCameraCanvasSize);
	mCameraCanvasView->SetPivot(1.0f, 1.0f);
	mCameraCanvasView->RemoveAllCameras();
	mCameraCanvasView->SetClearFlag(true, true, true);
	mCameraCanvasView->SetClearColor(Float4::BLUE);
	mCameraCanvasView->Show(false);
}
//----------------------------------------------------------------------------
void EU_CanvasStage::_CreateNodeCtrl()
{
	mSceneNodeCtrl = new0 SceneNodeCtrl();
	PX2_EW.ComeIn(mSceneNodeCtrl);

	mBoundCtrl = new0 BoundCtrl();
	PX2_EW.ComeIn(mBoundCtrl);

	mCameraCtrl = new0 CameraCtrl();
	PX2_EW.ComeIn(mCameraCtrl);

	mSceneCtrlNode = new0 Node();
	mSceneCtrlNode->AttachChild(mSceneNodeCtrl->GetCtrlsGroup());
	mSceneCtrlNode->AttachChild(mBoundCtrl->GetCtrlsGroup());
	mSceneCtrlNode->AttachChild(mCameraCtrl->GetNode());
	mSceneCtrlNode->Update(Time::GetTimeInSeconds(), true);
	mSceneCtrlNode->AttachChild(PX2_EDIT.GetHelpNode());

	mSceneNodeCtrlCanvas = new0 Canvas();
	AttachChild(mSceneNodeCtrlCanvas);
	mSceneNodeCtrlCanvas->LocalTransform.SetTranslateY(-4.0f);
	mSceneNodeCtrlCanvas->SetName("SceneCtrlNodeCanvas");
	mSceneNodeCtrlCanvas->SetAnchorHor(0.0f, 1.0f);
	mSceneNodeCtrlCanvas->SetAnchorParamHor(0.0f, 0.0f);
	mSceneNodeCtrlCanvas->SetAnchorVer(0.0f, 1.0f);
	mSceneNodeCtrlCanvas->SetAnchorParamVer(0.0f, 1.0f);
	mSceneNodeCtrlCanvas->SetRenderNode(mSceneCtrlNode);
	mSceneNodeCtrlCanvas->SetRenderNodeUpdate(true);
	mSceneNodeCtrlCanvas->SetClearFlag(false, true, true);
}
//----------------------------------------------------------------------------
void EU_CanvasStage::OnEnter()
{
	Canvas::OnEnter();
}
//----------------------------------------------------------------------------
void EU_CanvasStage::OnLeave()
{
	Canvas::OnLeave();

	mIsLeftPressed = false;
	mIsMiddlePressed = false;
	mIsRightPressed = false;
}
//----------------------------------------------------------------------------
void EU_CanvasStage::OnLeftDown(const PickInputData &data)
{
	if (!IsEnable())
		return;

	Canvas::OnLeftDown(data);

	mIsSelectMovableTransChanged = false;
	mURDoCommand = 0;

	_ClickSelectPos(data.LogicPos);

	Edit::EditType et = PX2_EDIT.GetEditType();
	if (Edit::ET_SCENE == et && mSceneNodeCtrl)
	{
		Camera *camera = mSceneNodeCtrlCanvas->GetOverCamera();
		mSceneNodeCtrl->OnLeftDown(camera, data.LogicPos, GetSize());

		mSceneNodeCtrl->OnMotionCalDragType(camera, mCurPickPos,
			GetSize());
		if (!mSceneNodeCtrl->IsDragNone())
		{
			RenderWindow::SetScreenDragType(RenderWindow::SDT_LEFT);
			SetCameraDragType(CDT_SCENENODE);

			mURDoCommand = new0 MovablesTransURDo();
		}
		else
		{
			_ClickSelectScene(mCurPickPos);
		}
	}
	else if (Edit::ET_TERRAIN == et)
	{
		PX2_EDIT.GetTerrainEdit()->GetBrush()->SelectPage();
		PX2_EDIT.GetTerrainEdit()->Apply(true);

		_UpdateBrushPos(data.LogicPos);
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStage::_ClickSelectPos(const APoint &scrPos)
{
	if (!Project::GetSingletonPtr()) 
		return;

	Scene *scene = PX2_PROJ.GetScene();
	if (!scene) return;

	Camera *camera = mStageCameraNode->GetCamera();

	APoint origin;
	AVector direction;
	camera->GetPickRay(scrPos.X(), scrPos.Z(), GetSize(), origin, direction);

	Picker picker;
	picker.Execute(scene, origin, direction, 0.0f, Mathf::MAX_REAL);
	if ((int)picker.Records.size() > 0)
	{
		const PickRecord &record = picker.GetClosestToZero();
		mSelectPoint = origin + direction*record.T;
		PX2_EDIT.SetPickPos(mSelectPoint);
	}
	else
	{
		PX2::TriMesh *xyPlane = PX2_GR.GetXYPlane();
		xyPlane->WorldTransform.SetTranslate(APoint::ORIGIN);

		Picker picker;
		picker.Execute(xyPlane, origin, direction, 0.0f, Mathf::MAX_REAL);
		if ((int)picker.Records.size() > 0)
		{
			const PickRecord &rec = picker.GetClosestToZero();
			mSelectPoint = origin + direction*rec.T;
			PX2_EDIT.SetPickPos(mSelectPoint);
		}
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStage::_ClickSelectScene(const APoint &scrPos)
{
	if (!Project::GetSingletonPtr()) 
		return;

	Scene *scene = PX2_PROJ.GetScene();
	if (!scene) return;

	SelectMode mode = SM_SINGLE;
	if (PX2_EDIT.IsCtrlDown) mode = SM_MULTI;
	
	Camera *camera = mStageCameraNode->GetCamera();

	APoint origin;
	AVector direction;
	camera->GetPickRay(scrPos.X(), scrPos.Z(), GetSize(), origin, direction);

	Picker picker;
	picker.Execute(scene, origin, direction, 0.0f, Mathf::MAX_REAL);
	if ((int)picker.Records.size() > 0)
	{
		const PickRecord &record = picker.GetClosestToZero();
		Object *recordObj = record.Intersected;

		mSelectPoint = origin + direction*record.T;
		PX2_EDIT.SetPickPos(mSelectPoint);

		if (SM_SINGLE == mode)
		{
			int numObjs = PX2_SELECTM_E->GetNumObjects();
			if (1 == numObjs && recordObj == PX2_SELECTM_E->GetFirstObject())
			{
				/*_*/
			}
			else
			{
				PX2_SELECTM_E->Clear();
				PX2_SELECTM_E->AddObject(recordObj);
			}
		}
		else if (SM_MULTI == mode)
		{
			if (PX2_SELECTM_E->IsObjectIn(recordObj))
			{
				PX2_SELECTM_E->RemoveObject(recordObj);
			}
			else
			{
				PX2_SELECTM_E->AddObject(recordObj);
			}
		}
	}
	else
	{
		if (SM_SINGLE == mode)
		{
			PX2_SELECTM_E->Clear();
		}
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStage::OnLeftUp(const PickInputData &data)
{
	if (!IsEnable())
		return;

	if (mSceneNodeCtrl && !mSceneNodeCtrl->IsDragNone())
	{
		mSceneNodeCtrl->SetDragType(SceneNodeCtrl::DT_NONE);

		if (!PX2_EDIT.IsEditModeNone())
		{
			if (mIsSelectMovableTransChanged)
			{
				PX2_URDOM.PushUnDo(mURDoCommand);
				mURDoCommand = 0;
				mIsSelectMovableTransChanged = false;
			}
		}
	}

	Canvas::OnLeftUp(data);
}
//----------------------------------------------------------------------------
void EU_CanvasStage::OnLeftDClick(const PickInputData &data)
{
	Canvas::OnLeftDClick(data);
}
//----------------------------------------------------------------------------
void EU_CanvasStage::OnMiddleDown(const PickInputData &data)
{
	Canvas::OnMiddleDown(data);
}
//----------------------------------------------------------------------------
void EU_CanvasStage::OnMiddleUp(const PickInputData &data)
{
	Canvas::OnMiddleUp(data);

	SetCameraDragType(CDT_NONE);
}
//----------------------------------------------------------------------------
void EU_CanvasStage::OnMouseWheel(const PickInputData &data)
{
	if (!IsEnable())
		return;

	Canvas::OnMouseWheel(data);

	float delta1 = data.Wheel * 0.003f * PX2_EDIT.GetCameraMoveSpeed();
	_ZoomCamera(delta1);

	if (mSceneNodeCtrl)
	{
		Camera *camera = mSceneNodeCtrlCanvas->GetOverCamera();
		mSceneNodeCtrl->OnMouseWheel(camera, delta1, GetSize());
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStage::OnRightDown(const PickInputData &data)
{
	if (!IsEnable())
		return;

	_ClickSelectPos(data.LogicPos);

	Canvas::OnRightDown(data);
}
//----------------------------------------------------------------------------
void EU_CanvasStage::OnRightUp(const PickInputData &data)
{
	if (!IsEnable())
		return;

	Project *proj = Project::GetSingletonPtr();
	if (!proj)
		return;

	SetCameraDragType(CDT_NONE);

	if (!RenderWindow::IsScreenDrag())
	{
		if (mIsRightPressed)
		{
			CreateMenuOnSelect(data.ScreenPos);
		}
	}

	Canvas::OnRightUp(data);
}
//----------------------------------------------------------------------------
void EU_CanvasStage::OnMotion(const PickInputData &data)
{
	if (!IsEnable())
		return;

	APoint lastPickPos = mCurPickPos;
	Canvas::OnMotion(data);

	if (!Project::GetSingletonPtr()) return;
	if (!PX2_PROJ.GetScene()) return;

	if (mMoveDelta == AVector::ZERO) return;

	if (!PX2_EDIT.IsEditModeNone())
	{
		Camera *camera = mSceneNodeCtrlCanvas->GetOverCamera();

		mSceneNodeCtrl->OnMotionCalDragType(camera, mCurPickPos,
			GetSize());

		mSceneNodeCtrl->OnDraging(camera,
			mCurPickPos, lastPickPos, GetSize());
		mIsSelectMovableTransChanged = true;
	}

	Edit::EditType et = PX2_EDIT.GetEditType();
	if (et == Edit::ET_TERRAIN)
	{
		_UpdateBrushPos(data.LogicPos);
	}

	Float2 delta = RenderWindow::GetMoveDelta();

	if (mSceneNodeCtrl && mSceneNodeCtrl->IsDragNone())
	{
		if (!RenderWindow::IsScreenDrag() && IsEntered())
		{
			if (mIsRightPressed || mIsMiddlePressed)
			{
				if (Float2::ZERO != delta)
				{
					if (mIsRightPressed)
					{
						SetCameraDragType(CDT_NORMAL_RIGHT);
						RenderWindow::SetScreenDragType(RenderWindow::SDT_RIGHT);
					}
					else if (mIsMiddlePressed)
					{
						SetCameraDragType(CDT_NORMAL_MIDDLE);
						RenderWindow::SetScreenDragType(RenderWindow::SDT_MIDDLE);
					}
				}
			}
		}
	}

	if (!RenderWindow::IsScreenDrag())
	{
		if (mIsLeftPressed) 
		{
			PX2_EDIT.GetTerrainEdit()->Apply(false);
		}
	}
}
//----------------------------------------------------------------------------
std::pair<float, float> EU_CanvasStage::CalPixelToWorld()
{
	Rectf viewPort = mScreenRect;
	if (viewPort.IsEmpty())
		viewPort = Rectf(0.0f, 0.0f, mSize.Width, mSize.Height);

	std::pair<float, float> pixelToWorld;

	if (mStageCameraNode)
	{
		Camera *camera = mStageCameraNode->GetCamera();

		float rMin = camera->GetRMin();
		float uMin = camera->GetUMin();
		float viewPortWidth = viewPort.Width();
		float viewPortHeight = viewPort.Height();

		float worldW = 2.0f * -rMin;
		float worldH = 2.0f * -uMin;
		
		worldW *= 1000.0f;
		worldH *= 1000.0f;

		pixelToWorld.first = worldW / (float)viewPortWidth;
		pixelToWorld.second = worldH / (float)viewPortHeight;
	}

	mPixelToWorld = pixelToWorld;

	return mPixelToWorld;
}
//----------------------------------------------------------------------------
void EU_CanvasStage::_ProcessKeyMove(bool isPress, float cameraMoveSpeed,
	float elapsedTime, float &speed)
{
	float speedParam0 = (cameraMoveSpeed / 0.2f);
	float speedParam1 = (cameraMoveSpeed / 0.1f);

	if (isPress)
	{
		speed = cameraMoveSpeed;
	}
	else
	{
		float curSpeedTemp = speed;
		curSpeedTemp -= (float)elapsedTime * (speedParam0 + speedParam1*(float)elapsedTime);
		if (curSpeedTemp >= 0.0f)
		{
			speed = curSpeedTemp;
		}
		else
		{
			speed = 0.0f;
		}
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStage::_MoveCamera(float horz, float vert)
{
	if (!Project::GetSingletonPtr()) return;

	Scene *scene = PX2_PROJ.GetScene();
	if (!scene) return;

	if (mStageCameraNode)
	{
		APoint position = mStageCameraNode->LocalTransform.GetTranslate();
		AVector rVector;
		AVector dVector;
		AVector uVector;
		mStageCameraNode->LocalTransform.GetRDUVector(rVector, dVector, uVector);

		if (mViewType == VT_PERSPECTIVE)
		{
			dVector.Z() = 0.0f;
			dVector.Normalize();
			rVector.Z() = 0.0f;
			rVector.Normalize();
			position += dVector * vert;
			position -= rVector * horz;
		}
		else if (mViewType == VT_TOP)
		{
			position.Y() += vert * 1.0f;
			position.X() -= horz * 1.0f;
		}
		else if (mViewType == VT_LEFT)
		{
			position.Z() += vert * 1.0f;
			position.Y() += horz * 1.0f;
		}
		else if (mViewType == VT_FRONT)
		{
			position.Z() += vert * 1.0f;
			position.X() -= horz * 1.0f;
		}

		mStageCameraNode->LocalTransform.SetTranslate(position);
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStage::_PanCamera(const float &hor, const float &ver)
{
	if (!Project::GetSingletonPtr()) return;

	Scene *scene = PX2_PROJ.GetScene();
	if (!scene) return;

	if (mStageCameraNode)
	{
		APoint position = mStageCameraNode->LocalTransform.GetTranslate();
		AVector rVector;
		AVector dVector;
		AVector uVector;
		mStageCameraNode->LocalTransform.GetRDUVector(rVector, dVector, uVector);
		Camera *cam = mStageCameraNode->GetCamera();
		// VF_DMIN = 0,  //< near
		// VF_DMAX = 1,  //< far
		// VF_UMIN = 2,  //< bottom
		// VF_UMAX = 3,  //< top
		// VF_RMIN = 4,  //< left
		// VF_RMAX = 5,  //< right
		const float *frust = cam->GetFrustum();

		if (mViewType == VT_PERSPECTIVE)
		{
			float transDist = 50.0f;
			int numMovs = 0;
			APoint posCenter;
			APoint boundCenter;
			float radius = 0.0f;
			PX2_EDIT.GetSelectionCenterRadius(numMovs, posCenter, boundCenter, radius);
			if (radius > transDist)
			{
				transDist = radius;
			}
			Sizef scSize = RenderWindow::GetDeskScreenSize();
			float horz = (hor / scSize.Width) * transDist;
			float vert = (ver / scSize.Height) * transDist;

			rVector.Normalize();
			position += rVector * horz;

			uVector.Normalize();
			position -= uVector * vert;
		}
		else
		{
			float horDist = frust[Camera::VF_RMAX] - frust[Camera::VF_RMIN];
			float verDist = frust[Camera::VF_UMAX] - frust[Camera::VF_UMIN];
			float horAdjust = horDist / GetSize().Width;
			float verAdjust = verDist / GetSize().Height;

			if (mViewType == VT_TOP)
			{
				position.Y() -= ver * horAdjust;
				position.X() += hor * verAdjust;
			}
			else if (mViewType == VT_LEFT)
			{
				position.Z() += ver * horAdjust;;
				position.Y() += hor * verAdjust;
			}
			else if (mViewType == VT_FRONT)
			{
				position.Z() += ver * horAdjust;
				position.X() -= hor * verAdjust;
			}
		}
		mStageCameraNode->LocalTransform.SetTranslate(position);
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStage::_ZoomCamera(float zoom)
{
	if (!Project::GetSingletonPtr()) return;

	Scene *scene = PX2_PROJ.GetScene();
	if (!scene) return;

	const Sizef &size = GetSize();

	if (mStageCameraNode)
	{
		if (VT_PERSPECTIVE == mViewType)
		{
			APoint position = mStageCameraNode->LocalTransform.GetTranslate();
			AVector rVector;
			AVector dVector;
			AVector uVector;
			mStageCameraNode->LocalTransform.GetRDUVector(rVector, dVector, uVector);
			dVector.Normalize();

			position += dVector*zoom;
			mStageCameraNode->LocalTransform.SetTranslate(position);
		}
		else if (VT_TOP == mViewType)
		{
			float rMin = 0.0f;
			float rMax = 0.0f;
			float uMin = 0.0f;
			float uMax = 0.0f;
			float dMin = 0.0f;
			float dMax = 0.0f;
			float orthoFrustumMin = 1.0f;
			mStageCameraNode->GetCamera()->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
			uMin += (zoom * 1.0f);
			if (uMin > -orthoFrustumMin)
				uMin = -orthoFrustumMin;
			uMax = -uMin;
			rMin = uMin * size.Width / size.Height;
			rMax = -rMin;

			mStageCameraNode->GetCamera()->SetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
		}
		else if (VT_FRONT == mViewType)
		{
			float rMin = 0.0f;
			float rMax = 0.0f;
			float uMin = 0.0f;
			float uMax = 0.0f;
			float dMin = 0.0f;
			float dMax = 0.0f;
			float orthoFrustumMin = 1.0f;
			mStageCameraNode->GetCamera()->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
			uMin += (zoom * 1.0f);
			if (uMin > -orthoFrustumMin)
				uMin = -orthoFrustumMin;
			uMax = -uMin;
			rMin = uMin * size.Width / size.Height;
			rMax = -rMin;

			mStageCameraNode->GetCamera()->SetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
		}
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStage::_RolateCamera(float hor, float ver)
{
	Scene *scene = PX2_PROJ.GetScene();
	if (!scene) return;

	Sizef scSize = RenderWindow::GetDeskScreenSize();
	float horz = (hor / scSize.Width) * 360.0f * Mathf::DEG_TO_RAD;
	float vert = (ver / scSize.Height) * 360.0f * Mathf::DEG_TO_RAD;

	if (VT_PERSPECTIVE == mViewType)
	{
		AVector rVector;
		AVector dVector;
		AVector uVector;
		mStageCameraNode->LocalTransform.GetRDUVector(rVector, dVector, uVector);

		// vert
		HMatrix kIncrV(rVector, -vert);
		dVector = kIncrV * dVector;
		uVector = kIncrV * uVector;

		// horz
		HMatrix incrH(AVector::UNIT_Z, -horz);
		dVector = incrH * dVector;
		uVector = incrH * uVector;
		rVector = incrH * rVector;

		dVector.Normalize();

		AVector::Orthonormalize(dVector, uVector, rVector);
		mStageCameraNode->LocalTransform.SetRotate(HMatrix(rVector, dVector,
			uVector, AVector::ZERO, true));
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStage::_RoundCamera(float horz, float vert)
{
	if (!Project::GetSingletonPtr()) return;

	Scene *scene = PX2_PROJ.GetScene();
	if (!scene) return;

	if (mViewType == VT_PERSPECTIVE)
	{
		PX2::Object *obj = PX2_SELECTM_E->GetFirstObject();

		bool hasTarget = false;
		APoint pos;
		Movable *mov = DynamicCast<Movable>(obj);
		if (mov)
		{
			pos = mov->WorldTransform.GetTranslate();
			hasTarget = true;
		}

		if (hasTarget)
		{
			const APoint &camPos = mStageCameraNode->LocalTransform.GetTranslate();
			AVector rVector;
			AVector dVector;
			AVector uVector;
			mStageCameraNode->LocalTransform.GetRDUVector(rVector, dVector, uVector);

			AVector targetDir = pos - camPos;
			float targetLength = targetDir.Normalize();

			// horz
			HMatrix incrH(AVector::UNIT_Z, -horz*1.0f / 90.0f);
			targetDir = incrH * targetDir;
			dVector = incrH * dVector;
			uVector = incrH * uVector;
			rVector = incrH * rVector;

			// ver
			HMatrix incrV(rVector, -vert*1.0f / 90.0f);
			targetDir = incrV * targetDir;
			dVector = incrV * dVector;
			uVector = incrV * uVector;

			APoint newPos = pos - targetDir*targetLength;
			mStageCameraNode->LocalTransform.SetTranslate(newPos);

			AVector::Orthonormalize(dVector, uVector, rVector);
			mStageCameraNode->LocalTransform.SetRotate(
				HMatrix(rVector, dVector, uVector, AVector::ZERO, true));
		}
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStage::_UpdateBrushPos(const APoint &scrPos)
{
	Project *proj = Project::GetSingletonPtr();
	if (!proj) return;

	Scene *scene = proj->GetScene();
	if (!scene) return;

	Terrain *terrain = scene->GetTerrain();
	if (!terrain) return;

	Movable *pickObject = terrain;

#ifdef _DEBUG
	pickObject = PX2_GR.GetXYPlane();
	pickObject->WorldTransform.SetTranslate(APoint::ORIGIN);
#endif

	Camera *camera = mStageCameraNode->GetCamera();
	APoint origin;
	AVector direction;
	camera->GetPickRay(scrPos.X(), scrPos.Z(), GetSize(), origin, direction);

	Picker picker;
	picker.Execute(pickObject, origin, direction, 0.0f, Mathf::MAX_REAL);
	if ((int)picker.Records.size() > 0)
	{
		PX2::PickRecord pickRecord = picker.GetClosestToZero();
		PX2::APoint dest = origin + direction*pickRecord.T;

		PX2_EDIT.GetTerrainEdit()->GetBrush()->SetPos(dest);
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStage::CreateMenuOnSelect(const APoint &pos)
{
	PX2EU_MAN.CreateEditMenu("STAGE", pos, EU_Manager::EMT_SCENE);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EU_CanvasStage::EU_CanvasStage(LoadConstructor value) :
Canvas(value)
{
}
//----------------------------------------------------------------------------
void EU_CanvasStage::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Canvas::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(EU_CanvasStage, source);
}
//----------------------------------------------------------------------------
void EU_CanvasStage::Link(InStream& source)
{
	Canvas::Link(source);
}
//----------------------------------------------------------------------------
void EU_CanvasStage::PostLink()
{
	Canvas::PostLink();
}
//----------------------------------------------------------------------------
bool EU_CanvasStage::Register(OutStream& target) const
{
	if (Canvas::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EU_CanvasStage::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Canvas::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(EU_CanvasStage, target);
}
//----------------------------------------------------------------------------
int EU_CanvasStage::GetStreamingSize(Stream &stream) const
{
	int size = Canvas::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------