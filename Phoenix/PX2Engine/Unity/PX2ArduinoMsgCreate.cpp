// PX2ArduinoMsgCreate.cpp

#include "PX2ArduinoMsg.hpp"
using namespace PX2;

//---------------------------------------------------------------------------
ArduinoMsg ArduinoMsg::CreateMessageFromPacket(const std::string &packet)
{
	ArduinoMsg result;
	result.SetData((const uint8_t*)packet.c_str(), 8);

	return result;
}
//---------------------------------------------------------------------------
ArduinoMsg ArduinoMsg::CreateMsgPinMode(Arduino::Pin pin,
	Arduino::PinMode mode)
{
	ArduinoMsg msg;
	msg.SetCMD(ArduinoMsg::PIN_MODE);
	msg.AddByteValue((int8_t)pin);
	msg.AddByteValue((int8_t)mode);
	return msg;
}
//---------------------------------------------------------------------------
ArduinoMsg ArduinoMsg::CreateDigitalReadMsg(Arduino::Pin pin)
{
	ArduinoMsg msg;
	msg.SetNeedResult(true);
	msg.SetCMD(ArduinoMsg::DIGITAL_READ);
	msg.AddByteValue((int8_t)pin);
	return msg;
}
//---------------------------------------------------------------------------
ArduinoMsg ArduinoMsg::CreateDigitalReadMsgResult(Arduino::Pin pin, int8_t val)
{
	ArduinoMsg msg;
	msg.SetCMD(ArduinoMsg::DIGITAL_READ_RESULT);
	msg.AddByteValue((int8_t)pin);
	msg.AddByteValue((int8_t)val);
	return msg;
}
//---------------------------------------------------------------------------
ArduinoMsg ArduinoMsg::CreateDigitalWriteMsg(Arduino::Pin pin,
	Arduino::PinState state)
{
	ArduinoMsg msg;
	msg.SetCMD(ArduinoMsg::DIGITAL_WRITE);
	msg.AddByteValue((int8_t)pin);
	msg.AddByteValue((int8_t)state);
	return msg;
}
//---------------------------------------------------------------------------
ArduinoMsg ArduinoMsg::CreateAnalogReadMsg(Arduino::Pin pin)
{
	ArduinoMsg msg;
	msg.SetNeedResult(true);
	msg.SetCMD(ArduinoMsg::ANALOG_READ);
	msg.AddByteValue((int8_t)pin);
	return msg;
}
//---------------------------------------------------------------------------
ArduinoMsg ArduinoMsg::CreateAnalogReadMsgResult(Arduino::Pin pin, int8_t val)
{
	ArduinoMsg msg;
	msg.SetCMD(ArduinoMsg::ANALOG_READ_RESULT);
	msg.AddByteValue((int8_t)pin);
	msg.AddByteValue((int8_t)val);
	return msg;
}
//---------------------------------------------------------------------------
ArduinoMsg ArduinoMsg::CreateAnalogWriteMsg(Arduino::Pin pin, int8_t val)
{
	ArduinoMsg msg;
	msg.SetCMD(ArduinoMsg::ANALOG_WRITE);
	msg.AddByteValue((int8_t)pin);
	msg.AddByteValue(val);
	return msg;
}
//---------------------------------------------------------------------------