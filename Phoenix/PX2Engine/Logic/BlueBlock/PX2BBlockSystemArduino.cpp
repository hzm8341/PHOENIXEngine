// PX2BBlockSystemArduino.cpp

#include "PX2BBlockSystem.hpp"
#include "PX2Log.hpp"
#include "PX2Arduino.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
void BBlockSystem::pinMode(Pin pin, PMode mode)
{
	PX2_ARDUINO.PinMode((Arduino::Pin)pin, (Arduino::PMode)mode);
}
//----------------------------------------------------------------------------
void BBlockSystem::digitalWrite(Pin pin, bool isHigh)
{
	PX2_ARDUINO.DigitalWrite((Arduino::Pin)pin, isHigh);
}
//----------------------------------------------------------------------------
void BBlockSystem::analogWrite(Pin pin, int val)
{
	PX2_ARDUINO.AnalogWrite((Arduino::Pin)pin, val);
}
//----------------------------------------------------------------------------
int BBlockSystem::digitalRead(Pin pin)
{
	return PX2_ARDUINO.DigitalRead((Arduino::Pin)pin);
}
//----------------------------------------------------------------------------
int BBlockSystem::analogRead(Pin pin)
{
	return PX2_ARDUINO.AnalogRead((Arduino::Pin)pin);
}
//----------------------------------------------------------------------------
void BBlockSystem::serverInit(int index, Pin pin)
{
	PX2_ARDUINO.ServerInit(index, (Arduino::Pin)pin);
}
//----------------------------------------------------------------------------
void BBlockSystem::serverWrite(int index, int val)
{
	PX2_ARDUINO.ServerWrite(index, val);
}
//----------------------------------------------------------------------------
void BBlockSystem::distInit(Pin pinTrig, Pin pinEcho)
{
	PX2_ARDUINO.DistInit((Arduino::Pin)pinTrig, (Arduino::Pin)pinEcho);
}
//----------------------------------------------------------------------------
void BBlockSystem::distTest()
{
	PX2_ARDUINO.DistTest();
}
//----------------------------------------------------------------------------
float BBlockSystem::getDist() const
{
	return PX2_ARDUINO.GetDist();
}
//----------------------------------------------------------------------------
void BBlockSystem::vehicleInitMotoBoard()
{
	PX2_ARDUINO.VehicleInitMotoBoard();
}
//----------------------------------------------------------------------------
void BBlockSystem::vehicleInitMotoBoard4567()
{
	PX2_ARDUINO.VehicleInitMotoBoard4567();
}
//----------------------------------------------------------------------------
void BBlockSystem::vehicleRun(int motoIndex, DirectionType type, int speed)
{
	PX2_ARDUINO.Run(motoIndex, (Arduino::DirectionType)type, speed);
}
//----------------------------------------------------------------------------
void BBlockSystem::vehicleRunSimple(SimpleDirectionType dt, int speed)
{
	PX2_ARDUINO.Run((Arduino::SimpleDirectionType)dt, speed);
}
//----------------------------------------------------------------------------
int BBlockSystem::vehicleGetSpeed(int motoIndex) const
{
	return PX2_ARDUINO.GetSpeed(motoIndex);
}
//----------------------------------------------------------------------------
void BBlockSystem::vehicleStop()
{
	PX2_ARDUINO.Stop();
}
//----------------------------------------------------------------------------
void BBlockSystem::vehicleSpeedInit(Pin pinLA, Pin pinLB, Pin pinRA, Pin pinRB)
{
	PX2_ARDUINO.VehicleSpeedInit((Arduino::Pin)pinLA, (Arduino::Pin)pinLB, 
		(Arduino::Pin)pinRA, (Arduino::Pin)pinRB);
}
//----------------------------------------------------------------------------
void BBlockSystem::mp3Init(Pin pinR, Pin pinT)
{
	PX2_ARDUINO.MP3Init((Arduino::Pin)pinR, (Arduino::Pin)pinT);
}
//----------------------------------------------------------------------------
void BBlockSystem::mp3Play()
{
	PX2_ARDUINO.MP3Play();
}
//----------------------------------------------------------------------------
void BBlockSystem::mp3PlayNext()
{
	PX2_ARDUINO.MP3PlayNext();
}
//----------------------------------------------------------------------------
void BBlockSystem::mp3PlayAtIndex(int index)
{
	PX2_ARDUINO.MP3PlayAtIndex(index);
}
//----------------------------------------------------------------------------
void BBlockSystem::mp3SetVolume(int volume)
{
	PX2_ARDUINO.MP3SetVolume(volume);
}
//----------------------------------------------------------------------------
void BBlockSystem::mp3Stop()
{
	PX2_ARDUINO.MP3Stop();
}
//----------------------------------------------------------------------------
void BBlockSystem::irSend(int val)
{
	PX2_ARDUINO.IRSend(val);
}
//----------------------------------------------------------------------------
void BBlockSystem::irRecvInit(Pin pinReceive)
{
	PX2_ARDUINO.IRInit((Arduino::Pin)pinReceive);
}
//----------------------------------------------------------------------------
int BBlockSystem::getIRReceive() const
{
	return PX2_ARDUINO.GetIRReceive();
}
//----------------------------------------------------------------------------