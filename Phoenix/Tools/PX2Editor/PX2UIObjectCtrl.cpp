// PX2UIObjectCtrl.cpp

#include "PX2UIObjectCtrl.hpp"
#include "PX2GeoObjFactory.hpp"
#include "PX2Edit.hpp"
#include "PX2UIPicBox.hpp"
#include "PX2UIButton.hpp"
#include "PX2UIProgressBar.hpp"
#include "PX2UIEditBox.hpp"
#include "PX2SelectionManager.hpp"
#include "PX2Project.hpp"
#include "PX2GraphicsEventType.hpp"
#include "PX2Picker.hpp"
#include "PX2Renderer.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditorEventType.hpp"
#include "PX2GraphicsRoot.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
UIObjectCtrl::UIObjectCtrl ()
{
	mDragIndex = -1;
	mSmallRectSize = 8.0f;

	mIsLeftDown = false;

	mShapeType = ST_NONE;

	mCtrlsGroup = new0 SwitchNode();

	GeoObjFactory factory;

	mRectCtrl = factory.CreateUIRectCtrl(mSmallRectSize);	
	mCrossCtrl = factory.CreateUICrossCtrl();
	
	mCtrlsGroup->AttachChild(new0 Node());
	mCtrlsGroup->AttachChild(mRectCtrl);
	mCtrlsGroup->AttachChild(mCrossCtrl);
}
//----------------------------------------------------------------------------
UIObjectCtrl::~UIObjectCtrl ()
{
	PX2_EW.GoOut(this);
}
//----------------------------------------------------------------------------
void UIObjectCtrl::SetShapeType (ShapeType type)
{
	mShapeType = type;

	mCtrlsGroup->SetActiveChild((int)mShapeType);
	mCtrlsGroup->Update(Time::GetTimeInSeconds(), false);
}
//----------------------------------------------------------------------------
UIObjectCtrl::ShapeType UIObjectCtrl::GetShapeType()
{
	return mShapeType;
}
//----------------------------------------------------------------------------
int UIObjectCtrl::GetDragIndex()
{
	return mDragIndex;
}
//----------------------------------------------------------------------------
PX2::Movable *UIObjectCtrl::GetCtrlsGroup()
{
	return mCtrlsGroup;
}
//----------------------------------------------------------------------------
void UIObjectCtrl::OnEvent (PX2::Event *event)
{
	if (EditES::IsEqual(event, EditES::AddSelect) ||
		EditES::IsEqual(event, EditES::RemoveSelect) ||
		EditES::IsEqual(event, EditES::RemoveAllSelects))
	{
		UpdateOnSelectUI();
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::ObjectTransformChanged) ||
		EditorEventSpace::IsEqual(event, EditorEventSpace::ObjectSizeChanged))
	{
		Object *obj = event->GetData<Object*>();
		if (PX2_SELECTM_E->GetFirstObject() == obj)
		{
			UpdateOnSelectUI();
		}
	}
}
//----------------------------------------------------------------------------
void UIObjectCtrl::UpdateOnSelectUI()
{
	SetShapeType(ST_NONE);

	bool isCross = false;
	Sizef size;
	Float2 pvoit = Float2::ZERO;

	//if (PX2_SELECTM_E->GetNumObjects() > 1) return;

	Object *obj = PX2_SELECTM_E->GetFirstObject();
	if (!obj) return;
	
	Movable *mov = DynamicCast<Movable>(obj);
	if (!mov) return;
	UIFrame *uiFrame = DynamicCast<UIFrame>(mov);

	if (uiFrame)
	{
		isCross = false;
		pvoit = uiFrame->GetPivot();
		size = uiFrame->GetSize();
	}
	else
	{
		SetShapeType(ST_NONE);
		return;
	}

	if (isCross)
	{
		mCrossCtrl->WorldTransformIsCurrent = true;
		mCrossCtrl->WorldTransform = mov->WorldTransform;

		SetShapeType(ST_CROSS);
	}
	else
	{
		float width = size.Width;
		float height = size.Height;

		VertexBufferAccessor vba;
		PolysegmentPtr polySeg = DynamicCast<Polysegment>(mRectCtrl->GetChild(0));
		vba.ApplyTo(polySeg);

		APoint point0 = APoint(0.0f - width*pvoit[0], 0.0f, 0.0f - height*pvoit[1]);
		APoint point1 = APoint(width*(1.0f - pvoit[0]), 0.0f, 0.0f - height*pvoit[1]);
		APoint point2 = APoint(width*(1.0f - pvoit[0]), 0.0f, height*(1.0f - pvoit[1]));
		APoint point3 = APoint(0.0f - width*pvoit[0], 0.0f, height*(1.0f - pvoit[1]));

		vba.Position<Float3>(0) = point0;
		vba.Position<Float3>(1) = point1;
		vba.Position<Float3>(2) = point2;
		vba.Position<Float3>(3) = point3;
		vba.Position<Float3>(4) = point0;
		vba.Color<Float4>(0, 0) = Float4::MakeColor(150, 150, 150, 255);
		vba.Color<Float4>(0, 1) = Float4::MakeColor(150, 150, 150, 255);
		vba.Color<Float4>(0, 2) = Float4::MakeColor(150, 150, 150, 255);
		vba.Color<Float4>(0, 3) = Float4::MakeColor(150, 150, 150, 255);
		vba.Color<Float4>(0, 4) = Float4::MakeColor(150, 150, 150, 255);

		polySeg->UpdateModelSpace(Renderable::GU_MODEL_BOUND_ONLY);		
		Renderer::UpdateAll(polySeg->GetVertexBuffer());

		APoint p0 = APoint(point0.X()-mSmallRectSize, 0.0f, point0.Z()-mSmallRectSize);
		APoint p1 = APoint(point1.X(), 0.0f, point1.Z()-mSmallRectSize);
		APoint p2 = point2;
		APoint p3 = APoint(point3.X()-mSmallRectSize, 0.0f, point3.Z());

		mRectCtrl->GetChild(1)->LocalTransform.SetTranslate(p0);
		mRectCtrl->GetChild(2)->LocalTransform.SetTranslate((p0+p1)/2.0f);
		mRectCtrl->GetChild(3)->LocalTransform.SetTranslate(p1);
		mRectCtrl->GetChild(4)->LocalTransform.SetTranslate((p1+p2)/2.0f);
		mRectCtrl->GetChild(5)->LocalTransform.SetTranslate(p2);
		mRectCtrl->GetChild(6)->LocalTransform.SetTranslate((p2+p3)/2.0f);
		mRectCtrl->GetChild(7)->LocalTransform.SetTranslate(p3);
		mRectCtrl->GetChild(8)->LocalTransform.SetTranslate((p0+p3)/2.0f);

		mRectCtrl->WorldTransformIsCurrent = true;
		mRectCtrl->WorldTransform = mov->WorldTransform;

		SetShapeType(ST_RECT);
	}
}
//----------------------------------------------------------------------------
void UIObjectCtrl::SetDragIndex (int index)
{
	if (mDragIndex == index)
		return;

	mDragIndex = index;
}
//----------------------------------------------------------------------------
void UIObjectCtrl::OnLeftDown(Canvas *canvas, const PickInputData &data)
{
	int index = _GetDragIndex(canvas, data.LogicPos);
	SetDragIndex(index);
	UpdateOnSelectUI();

	mIsLeftDown = true;
}
//----------------------------------------------------------------------------
void UIObjectCtrl::OnLeftUp(Canvas *canvas, const PickInputData &data)
{
	PX2_UNUSED(canvas);
	PX2_UNUSED(data);

	mIsLeftDown = false;
}
//----------------------------------------------------------------------------
void UIObjectCtrl::OnMotion(Canvas *canvas, const PickInputData &data)
{
	if (!mIsLeftDown)
		return;

	int dragIndex = GetDragIndex();
	const Sizef &canvasSize = canvas->GetSize();
	Camera *camera = canvas->GetOverCamera();

	UIFrame *frame = DynamicCast<UIFrame>(PX2_SELECTM_E->GetFirstObject());
	if (!frame) return;

	Float2 anchorHor = frame->GetAnchorHor();
	Float2 anchorParamHor = frame->GetAnchorParamHor();
	Float2 anchorVer = frame->GetAnchorVer();
	Float2 anchorParamVer = frame->GetAnchorParamVer();

	if (anchorHor[0] == anchorHor[1])
	{
		anchorParamHor[0] += data.MoveDelta.X();
		anchorParamHor[1] = anchorParamHor[0];
	}
	else
	{
	}

	if (anchorVer[0] == anchorVer[1])
	{
		anchorParamVer[0] += data.MoveDelta.Z();
		anchorParamVer[1] += anchorParamVer[0];
	}
	else
	{
	}

	frame->SetAnchorHor(anchorHor);
	frame->SetAnchorParamHor(anchorParamHor);
	frame->SetAnchorVer(anchorHor);
	frame->SetAnchorParamVer(anchorParamVer);
	frame->Update(Time::GetTimeInSeconds(), 0.0f);

	UpdateOnSelectUI();

	mCtrlsGroup->Update(Time::GetTimeInSeconds(), 0.0f);
}
//----------------------------------------------------------------------------
int UIObjectCtrl::_GetDragIndex(Canvas *canvas, const PX2::APoint &pos)
{
	Project *proj = Project::GetSingletonPtr();
	if (!proj) return -1;

	const Sizef &canvasSize = canvas->GetSize();
	Camera *camera = canvas->GetOverCamera();

	APoint origin;
	AVector direction;
	camera->GetPickRay(pos.X(), pos.Z(), canvasSize, origin, direction);

	ObjectPtr curSelectObj = PX2_SELECTM_E->GetFirstObject();
	UIFrame *uiFrame = DynamicCast<UIFrame>(curSelectObj);
	if (!uiFrame) return -1;

	PX2::Picker picker;
	PX2::MovablePtr pickedMove = 0;
	picker.Execute(uiFrame, origin, direction, 0.0f, Mathf::MAX_REAL);

	if ((int)picker.Records.size() > 0)
	{
		return 0;
	}
	else
	{
		PX2_SELECTM_E->Clear();

		return -1;
	}

	return -1;
}
//----------------------------------------------------------------------------