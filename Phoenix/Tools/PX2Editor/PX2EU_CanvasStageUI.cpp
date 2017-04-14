// PX2EU_CanvasStageUI.cpp

#include "PX2EU_CanvasStageUI.hpp"
#include "PX2Project.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2EditorEventType.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2VertexColor4Material.hpp"
#include "PX2Edit.hpp"
#include "PX2Renderer.hpp"
#include "PX2Edit.hpp"
#include "PX2SelectionManager.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2Picker.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2EU_ProjectEventController.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Canvas, EU_CanvasStageUI);
PX2_IMPLEMENT_STREAM(EU_CanvasStageUI);
PX2_IMPLEMENT_FACTORY(EU_CanvasStageUI);

//----------------------------------------------------------------------------
EU_CanvasStageUI::EU_CanvasStageUI() :
mIsInitSizeChanged(false)
{
	SetName("EU_CanvasStageUI");

	SetClearFlag(false, true, true);
	SetClearColor(Float4::MakeColor(0, 162, 232, 255));

	SetAnchorHor(0.0f, 1.0f);
	SetAnchorVer(0.0f, 1.0f);
	EnableAnchorLayout(true);

	_CreateGridGeometry();
	_CreateCanvas();

	CameraNode *cn = CreateUICameraNode();
	SetOverCameraNode(cn);
	EnableUICameraAutoAdjust(false);

	SetPickPosRecal(true);

	Enable(false);

	SetActivateSelfCtrled(false);
}
//----------------------------------------------------------------------------
EU_CanvasStageUI::~EU_CanvasStageUI()
{
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::Enable(bool enable)
{
	Canvas::Enable(enable);
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::Draw(Renderer *renderer)
{
	Project *proj = Project::GetSingletonPtr();
	if (proj)
	{
		UI *ui = proj->GetUI();
		if (ui) PX2_GR.SetCurEnvirParamController(ui->GetEnvirParamController());
	}

	Canvas::Draw(renderer);
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::OnEvent(Event *event)
{
	Canvas::OnEvent(event);

	if (EditorEventSpace::IsEqual(event, EditorEventSpace::SetEditType))
	{
		Edit::EditType editType = PX2_EDIT.GetEditType();
		bool editUI = (Edit::EditType::ET_UI == editType);
		Enable(editUI);
		Show(editUI);
	}
	else if (ProjectES_Internal::IsEqual(event, 
		ProjectES_Internal::UISizeChanged))
	{
		_UpdateUIRange();
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::OnSizeChanged()
{
	Canvas::OnSizeChanged();

	if (!mIsInitSizeChanged)
	{
		Camera *editorCamera = mUICameraNode->GetCamera();
		if (editorCamera)
		{
			float helfWidth = mSize.Width / 2.0f;
			float helfHeight = mSize.Height / 2.0f;
			editorCamera->SetFrustum(0.1f, Mathf::FAbs(msUICameraY) + 1000.0f,
				-helfHeight, helfHeight, -helfWidth, helfWidth);
		}

		mIsInitSizeChanged = true;
	}

	_ZoomCamera(0.0f);
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::UpdateWorldData(double applicationTime,
	double elapsedTime)
{
	Canvas::UpdateWorldData(applicationTime, elapsedTime);
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::_CreateGridGeometry()
{
	VertexFormat *vf = PX2_GR.GetVertexFormat(GraphicsRoot::VFT_PC);

	VertexBuffer *vertexBuffer = new0 VertexBuffer(5, vf->GetStride());
	mProjRangeSegment = new0 Polysegment(vf, vertexBuffer, true);
	mProjRangeSegment->SetNumSegments(4);
	mProjRangeSegment->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	mProjRangeSegment->Culling = Movable::CULL_NEVER;
	mProjRangeSegment->GetMaterialInstance()->GetMaterial()
		->GetAlphaProperty(0, 0)->BlendEnabled = true;

	_UpdateUIRange();

	mRangeNode = new0 Node();
	mRangeNode->AttachChild(mProjRangeSegment);

	mGridCanvas = new0 Canvas();
	AttachChild(mGridCanvas);
	mGridCanvas->LocalTransform.SetTranslateY(-1.0f);
	mGridCanvas->SetName("UIGridCanvas");
	mGridCanvas->SetRenderNode(mRangeNode);
	mGridCanvas->SetRenderNodeUpdate(true);
	mGridCanvas->SetAnchorHor(0.0f, 1.0f);
	mGridCanvas->SetAnchorVer(0.0f, 1.0f);
	mGridCanvas->SetClearFlag(false, false, false);
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::_CreateCanvas()
{
	mCanvas = new0 Canvas();
	AttachChild(mCanvas);
	mCanvas->LocalTransform.SetTranslateY(-2.0f);
	mCanvas->SetName("UICanvas");
	mCanvas->SetAnchorHor(0.0f, 1.0f);
	mCanvas->SetAnchorVer(0.0f, 1.0f);
	mCanvas->SetClearFlag(false, false, false);
	mCanvas->SetRenderNodeUpdate(false);

	mCanvas->AttachController(new0 EU_ProjectEventController());
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::SetOverCameraNode(CameraNode *cameraNode)
{
	mGridCanvas->SetOverCamera(cameraNode->GetCamera());
	mCanvas->SetOverCamera(cameraNode->GetCamera());
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::_UpdateUIRange()
{
	Project *proj = Project::GetSingletonPtr();
	if (!proj)
		return;

	UI *ui = proj->GetUI();

	float uiWidth = ui->GetWidth();
	float uiHeight = ui->GetHeight();

	VertexBufferAccessor vba(mProjRangeSegment);
	vba.Position<Float3>(0) = Float3(-1.0f, 0.0f, -1.0f);
	vba.Position<Float3>(1) = Float3(uiWidth, 0.0f, -1.0f);
	vba.Position<Float3>(2) = Float3(uiWidth, 0.0f, uiHeight);
	vba.Position<Float3>(3) = Float3(-1.0f, 0.0f, uiHeight);
	vba.Position<Float3>(4) = Float3(-1.0f, 0.0f, -1.0f);
	Float4 color = Float4::MakeColor(50, 50, 50, 165);
	vba.Color<Float4>(0, 0) = color;
	vba.Color<Float4>(0, 1) = color;
	vba.Color<Float4>(0, 2) = color;
	vba.Color<Float4>(0, 3) = color;
	vba.Color<Float4>(0, 4) = color;

	mProjRangeSegment->UpdateModelSpace(Renderable::GU_MODEL_BOUND_ONLY);
	Renderer::UpdateAll(mProjRangeSegment->GetVertexBuffer());

	mUICameraNode->LocalTransform.SetTranslate(uiWidth / 2.0f, msUICameraY,
		uiHeight / 2.0f);
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::_AdjustCameraPercent()
{
	Project *proj = Project::GetSingletonPtr();
	if (!proj) return;

	float uiCameraPercent = proj->GetEdit_UICameraPercent();
	Sizef size = Sizef(mSize.Width*uiCameraPercent, 
		mSize.Height*uiCameraPercent);
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::OnLeftDown(const APoint &screenPos, const APoint &logicPos)
{
	if (!IsEnable())
		return;

	Canvas::OnLeftDown(screenPos, logicPos);

	APoint viewPortPos = WorldPosToViewPortPos(logicPos);
	_ClickSelectPos(viewPortPos);

	Edit::EditType et = PX2_EDIT.GetEditType();
	if (Edit::ET_UI == et)
	{
		_ClickSelectUI(viewPortPos);
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::OnLeftUp(const APoint &screenPos, const APoint &logicPos)
{
	if (!IsEnable())
		return;

	Canvas::OnLeftUp(screenPos, logicPos);
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::OnLeftDClick(const APoint &screenPos, const APoint &logicPos)
{
	if (!IsEnable())
		return;

	Canvas::OnLeftDClick(screenPos, logicPos);
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::OnMiddleDown(const APoint &screenPos, const APoint &logicPos)
{
	if (!IsEnable())
		return;

	Canvas::OnMiddleDown(screenPos, logicPos);

	mMiddlePickPos = logicPos;
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::OnMiddleUp(const APoint &screenPos, const APoint &logicPos)
{
	if (!IsEnable())
		return;

	Canvas::OnMiddleUp(screenPos, logicPos);
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::OnMouseWheel(const APoint &screenPos, const APoint &logicPos, float delta)
{
	if (!IsEnable())
		return;

	Canvas::OnMouseWheel(screenPos, logicPos, delta);

	_ZoomCamera(delta);
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::OnRightDown(const APoint &screenPos, const APoint &logicPos)
{
	if (!IsEnable())
		return;

	Canvas::OnRightDown(screenPos, logicPos);

	APoint viewPortPos = WorldPosToViewPortPos(logicPos);
	_ClickSelectPos(viewPortPos);
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::OnRightUp(const APoint &screenPos, const APoint &logicPos)
{
	if (!IsEnable())
		return;

	Project *proj = Project::GetSingletonPtr();
	if (!proj)
		return;

	if (mIsRightPressed)
	{
		CreateMenuOnSelect(logicPos);
	}

	Canvas::OnRightUp(screenPos, logicPos);
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::OnMotion(const APoint &screenPos, const APoint &logicPos)
{
	if (!IsEnable())
		return;

	Canvas::OnMotion(screenPos, logicPos);

	if (mIsMiddlePressed)
	{
		// Camera 位置已经改变，通过这里获取移动位移
		Float2 moveDelta = RenderWindow::GetMoveDelta();
		_PanCamera(-moveDelta.X(), moveDelta.Y());
	}
}
//----------------------------------------------------------------------------
std::pair<float, float> EU_CanvasStageUI::CalPixelToWorld()
{
	Rectf viewPort = mScreenRect;
	if (viewPort.IsEmpty())
		viewPort = Rectf(0.0f, 0.0f, mSize.Width, mSize.Height);

	std::pair<float, float> pixelToWorld;

	if (mUICameraNode)
	{
		Camera *camera = mUICameraNode->GetCamera();

		float rMin = camera->GetRMin();
		float uMin = camera->GetUMin();
		float viewPortWidth = viewPort.Width();
		float viewPortHeight = viewPort.Height();

		float worldW = 2.0f * -rMin;
		float worldH = 2.0f * -uMin;

		pixelToWorld.first = worldW / (float)viewPortWidth;
		pixelToWorld.second = worldH / (float)viewPortHeight;
	}

	mPixelToWorld = pixelToWorld;

	return mPixelToWorld;
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::_PanCamera(const float &horz, const float &vert)
{
	if (!Project::GetSingletonPtr()) return;

	UI *ui = PX2_PROJ.GetUI();
	if (!ui) return;

	if (mUICameraNode)
	{
		APoint position = mUICameraNode->LocalTransform.GetTranslate();

		position.Z() -= vert * 1.0f;
		position.X() += horz * 1.0f;

		mUICameraNode->LocalTransform.SetTranslate(position);
		mUICameraNode->Update(Time::GetTimeInSeconds(), 0.0f);
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::_ZoomCamera(float zoom)
{
	if (!Project::GetSingletonPtr()) return;

	UI *ui = PX2_PROJ.GetUI();
	if (!ui) return;

	const Sizef &size = GetSize();

	if (mUICameraNode)
	{
		float rMin = 0.0f;
		float rMax = 0.0f;
		float uMin = 0.0f;
		float uMax = 0.0f;
		float dMin = 0.0f;
		float dMax = 0.0f;
		float orthoFrustumMin = 1.0f;
		mUICameraNode->GetCamera()->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
		uMin += (zoom * 1.0f);
		if (uMin > -orthoFrustumMin)
			uMin = -orthoFrustumMin;
		uMax = -uMin;
		rMin = uMin * size.Width / size.Height;
		rMax = -rMin;

		mUICameraNode->GetCamera()->SetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
	}
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::_ClickSelectPos(const APoint &scrPos)
{
	if (!Project::GetSingletonPtr()) 
		return;

	UI *ui = PX2_PROJ.GetUI();
	if (!ui) return;

	Camera *camera = mUICameraNode->GetCamera();

	APoint origin;
	AVector direction;
	camera->GetPickRay(scrPos.X(), scrPos.Z(), GetSize(), origin, direction);

	Picker picker;
	picker.Execute(ui, origin, direction, 0.0f, Mathf::MAX_REAL);
	if ((int)picker.Records.size() > 0)
	{
		const PickRecord &record = picker.GetClosestToZero();
		mSelectPoint = origin + direction*record.T;
		PX2_EDIT.SetPickPos(mSelectPoint);
	}
	else
	{
		PX2::TriMesh *xyPlane = PX2_GR.GetXZPlane();
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
void EU_CanvasStageUI::_ClickSelectUI(const APoint &scrPos)
{
	if (!Project::GetSingletonPtr())
		return;

	UI *ui = PX2_PROJ.GetUI();
	if (!ui) 
		return;

	SelectMode mode = SM_SINGLE;
	if (PX2_EDIT.IsCtrlDown) mode = SM_MULTI;

	Camera *camera = mUICameraNode->GetCamera();

	APoint origin;
	AVector direction;
	camera->GetPickRay(scrPos.X(), scrPos.Z(), GetSize(), origin, direction);

	Picker picker;
	picker.Execute(ui, origin, direction, 0.0f, Mathf::MAX_REAL);
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
				PX2_SELECTM_E->Clear();
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
void EU_CanvasStageUI::CreateMenuOnSelect(const APoint &pos)
{
	PX2EU_MAN.CreateEditMenu(pos, EU_Manager::EMT_UI);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EU_CanvasStageUI::EU_CanvasStageUI(LoadConstructor value) :
Canvas(value)
{
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Canvas::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(EU_CanvasStageUI, source);
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::Link(InStream& source)
{
	Canvas::Link(source);
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::PostLink()
{
	Canvas::PostLink();
}
//----------------------------------------------------------------------------
bool EU_CanvasStageUI::Register(OutStream& target) const
{
	if (Canvas::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EU_CanvasStageUI::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Canvas::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(EU_CanvasStageUI, target);
}
//----------------------------------------------------------------------------
int EU_CanvasStageUI::GetStreamingSize(Stream &stream) const
{
	int size = Canvas::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------