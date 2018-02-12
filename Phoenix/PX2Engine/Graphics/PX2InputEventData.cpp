// PX2InputEventData.cpp

#include "PX2InputEventData.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
TouchState::TouchState() :
ID(0)
{
}
//----------------------------------------------------------------------------
TouchState::~TouchState()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
InputEventData::InputEventData() :
ViewID(0),
TheEventType(0),
MWheel(0.0f)
{
	KCode = KC_UNASSIGNED;
	MButtonID = MBID_MAX;

	Msg = 0;
	WParam = 0;
	LParam = 0;
}
//----------------------------------------------------------------------------
InputEventData::~InputEventData()
{
}
//----------------------------------------------------------------------------
bool InputEventData::IsKeyEvent() const
{
	return TheEventType == InputEventSpace::KeyPressed ||
		TheEventType == InputEventSpace::KeyReleased;
}
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
CanvasInputData::CanvasInputData() :
TouchID(0),
TheMouseTag(MT_NONE),
Wheel(0.0f),
PickType(UIPT_NONE)
{
}
//-----------------------------------------------------------------------------
CanvasInputData::~CanvasInputData()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
PickInputData::PickInputData()
{
	TouchID = 0;
	Wheel = 0.0f;
}
//----------------------------------------------------------------------------
PickInputData::~PickInputData()
{
}
//----------------------------------------------------------------------------