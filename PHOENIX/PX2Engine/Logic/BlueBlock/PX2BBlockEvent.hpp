// PX2BEvent.hpp

#ifndef PX2BEVENT_HPP
#define PX2BEVENT_HPP

#include "PX2BBlockPre.hpp"
#include "PX2EventSystem.hpp"
#include "PX2EventSpace.hpp"
#include "PX2Event.hpp"

namespace PX2
{

	PX2_DECLARE_EVENT_BEGIN(PX2_ENGINE_ITEM BBlockEventS)
	PX2_EVENT(Play)
	PX2_EVENT(Stop)
	PX2_EVENT(String)
	PX2_EVENT(UIButtonPressed)
	PX2_EVENT(UIButtonReleased)
	PX2_EVENT(UIButtonReleasedNotPick)
	PX2_EVENT(UIRoundDragChanged)
	PX2_EVENT(UISliderChanged)
	PX2_EVENT(VoiceResult)
	PX2_EVENT(BluetoothReceive)
	PX2_EVENT(IRReceive)
	PX2_DECLARE_EVENT_END(BBlockEventS)

}

#endif