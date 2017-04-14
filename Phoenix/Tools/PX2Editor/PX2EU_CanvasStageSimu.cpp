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
	if (PX2EU_MAN.GetNumCombos() > 0)
		return;

	Show(act);

	Canvas::SetActivate(act);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnLeftDown(const APoint &sceenPos, const APoint &logicPos)
{
	if (PX2EU_MAN.GetNumCombos() > 0)
		return;

	Canvas::OnLeftDown(sceenPos, logicPos);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnLeftUp(const APoint &sceenPos, const APoint &logicPos)
{
	if (PX2EU_MAN.GetNumCombos() > 0)
		return;

	Canvas::OnLeftUp(sceenPos, logicPos);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnLeftDClick(const APoint &sceenPos, const APoint &logicPos)
{
	if (PX2EU_MAN.GetNumCombos() > 0)
		return;

	Canvas::OnLeftDClick(sceenPos, logicPos);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnMiddleDown(const APoint &sceenPos, const APoint &logicPos)
{
	if (PX2EU_MAN.GetNumCombos() > 0)
		return;

	Canvas::OnMiddleDown(sceenPos, logicPos);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnMiddleUp(const APoint &sceenPos, const APoint &logicPos)
{
	if (PX2EU_MAN.GetNumCombos() > 0)
		return;

	Canvas::OnMiddleUp(sceenPos, logicPos);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnMouseWheel(const APoint &sceenPos, const APoint &logicPos, float delta)
{
	if (PX2EU_MAN.GetNumCombos() > 0)
		return;

	Canvas::OnMouseWheel(sceenPos, logicPos, delta);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnRightDown(const APoint &sceenPos, const APoint &logicPos)
{
	if (PX2EU_MAN.GetNumCombos() > 0)
		return;

	Canvas::OnRightDown(sceenPos, logicPos);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnRightUp(const APoint &sceenPos, const APoint &logicPos)
{
	if (PX2EU_MAN.GetNumCombos() > 0)
		return;

	Canvas::OnRightUp(sceenPos, logicPos);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::OnMotion(const APoint &sceenPos, const APoint &logicPos)
{
	if (PX2EU_MAN.GetNumCombos() > 0)
		return;

	Canvas::OnMotion(sceenPos, logicPos);
}
//----------------------------------------------------------------------------
void EU_CanvasStageSimu::UpdateWorldData(double applicationTime,
	double elapsedTime)
{
	Canvas::UpdateWorldData(applicationTime, elapsedTime);
}
//----------------------------------------------------------------------------