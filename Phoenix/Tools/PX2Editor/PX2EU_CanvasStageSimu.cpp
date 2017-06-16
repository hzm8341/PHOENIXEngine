// PX2EU_CanvasStageSimu.cpp

#include "PX2EU_CanvasStageSimu.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2EU_ProjectEventController.hpp"
#include "PX2InputEventData.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2Project.hpp"
#include "PX2Application.hpp"
#include "PX2UISizeExtendControl.hpp"
#include "PX2ProjectEvent.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Canvas, EU_CanvasStageSimu);
PX2_IMPLEMENT_STREAM(EU_CanvasStageSimu);
PX2_IMPLEMENT_FACTORY(EU_CanvasStageSimu);
PX2_IMPLEMENT_DEFAULT_STREAM(Canvas, EU_CanvasStageSimu);

//----------------------------------------------------------------------------
EU_CanvasStageSimu::EU_CanvasStageSimu()
{
	CreateUICameraNode();

	SetName("EU_CanvasStageSimu");

	SetAnchorHor(0.0f, 1.0f);
	SetAnchorVer(0.0f, 1.0f);

	SetActivateSelfCtrled(false);

	SetClearFlag(true, true, true);
	GetUICameraNode()->GetCamera()->SetClearFlag(false, false, false);

	PX2_APP.InitlizeDefaultEngineCanvas(this);

	EngineSceneCanvas* sceneCanvas = EngineSceneCanvas::GetSingletonPtr();
	EngineCanvas *uiCanvas = EngineCanvas::GetSingletonPtr();
	sceneCanvas->SetActivateSelfCtrled(false);
	uiCanvas->SetActivateSelfCtrled(false);

	Float4 blackGroundColor = Float4(PX2_UISM.Color_ViewBackground.X(),
		PX2_UISM.Color_ViewBackground.Y(), PX2_UISM.Color_ViewBackground.Z(), 1.0f);
	SetClearColor(blackGroundColor);

	ComeInEventWorld();
}
//----------------------------------------------------------------------------
EU_CanvasStageSimu::~EU_CanvasStageSimu()
{
	GoOutEventWorld();
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::SetActivate(bool act)
{
	Show(act);

	Canvas::SetActivate(act);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnLeftDown(const PickInputData &data)
{
	Canvas::OnLeftDown(data);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnLeftUp(const PickInputData &data)
{
	Canvas::OnLeftUp(data);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnLeftDClick(const PickInputData &data)
{
	Canvas::OnLeftDClick(data);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnMiddleDown(const PickInputData &data)
{
	Canvas::OnMiddleDown(data);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnMiddleUp(const PickInputData &data)
{
	Canvas::OnMiddleUp(data);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnMouseWheel(const PickInputData &data)
{
	Canvas::OnMouseWheel(data);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnRightDown(const PickInputData &data)
{
	Canvas::OnRightDown(data);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnRightUp(const PickInputData &data)
{
	Canvas::OnRightUp(data);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnMotion(const PickInputData &data)
{

	Canvas::OnMotion(data);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::UpdateWorldData(double applicationTime,
	double elapsedTime)
{
	Canvas::UpdateWorldData(applicationTime, elapsedTime);
}
//----------------------------------------------------------------------------