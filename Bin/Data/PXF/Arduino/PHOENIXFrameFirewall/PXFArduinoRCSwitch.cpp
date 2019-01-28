// PXFArduinoRCSwitch.cpp

#include "PXFArduino.h"

#if defined PXF_RCSWITCH

//----------------------------------------------------------------------------
void PXFArduino::_InitRCSwitchReceive(int pinTimerIndex)
{
    mRCSwitch.enableReceive(pinTimerIndex); 
}
//----------------------------------------------------------------------------
void PXFArduino::_RCSend(int val)
{
    mRCSwitch.send(val, 24);
}
//----------------------------------------------------------------------------

#endif