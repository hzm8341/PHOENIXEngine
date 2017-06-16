// PX2Arduino.cpp

#include "PX2Arduino.hpp"
#include "PX2ArduinoMsg.hpp"
using namespace PX2;

const uint8_t START_BYTE = 0x12;
const uint8_t STOP_BYTE = 0x13;
const uint8_t ESCAPE_BYTE = 0x7D;

//---------------------------------------------------------------------------
Arduino::Arduino() :
mMode(M_BLUETOOTH)
{
}
//---------------------------------------------------------------------------
Arduino::~Arduino()
{
	mSerial.Close();
}
//---------------------------------------------------------------------------
void Arduino::SetMode(Mode mode)
{
	mMode = mode;
}
//---------------------------------------------------------------------------
Arduino::Mode Arduino::GetMode() const
{
	return mMode;
}
//---------------------------------------------------------------------------
void Arduino::init(const std::string &port, int baudrate)
{
	mSerial.Init(port, baudrate);
}
//---------------------------------------------------------------------------
void Arduino::terminate()
{
	mSerial.Close();
}
//---------------------------------------------------------------------------
void Arduino::pinMode(Pin pin, PinMode val)
{
	ArduinoMsg msg = ArduinoMsg::CreateMsgPinMode(pin, val);
	_SendMsg(msg);
}
//---------------------------------------------------------------------------
int Arduino::digitalRead(Pin pin)
{
	ArduinoMsg msg = ArduinoMsg::CreateDigitalReadMsg(pin);
	_SendMsg(msg);

	return 0;
}
//---------------------------------------------------------------------------
void Arduino::digitalWrite(Pin pin, PinState state)
{
	ArduinoMsg msg = ArduinoMsg::CreateDigitalWriteMsg(pin, state);
	_SendMsg(msg);
}
//---------------------------------------------------------------------------
int Arduino::analogRead(Pin pin)
{
	ArduinoMsg msg = ArduinoMsg::CreateAnalogReadMsg(pin);
	_SendMsg(msg);

	return 0;
}
//---------------------------------------------------------------------------
void Arduino::analogWrite(Pin pin, int val)
{
	ArduinoMsg msg = ArduinoMsg::CreateAnalogWriteMsg(pin, (int8_t)val);
	_SendMsg(msg);
}
//---------------------------------------------------------------------------
void Arduino::_SendMsg(const ArduinoMsg &msg)
{
	std::string str;
	str.resize(32);
	int strIndex = 0;
	memcpy(&str[strIndex], &START_BYTE, sizeof(uint8_t));
	strIndex += 1;

	for (int i = 0; i < ARDUINO_MAX_PACKET_SIZE; i++)
	{
		if (START_BYTE == msg.mBuffer[i] || STOP_BYTE == msg.mBuffer[i] ||
			ESCAPE_BYTE == msg.mBuffer[i])
		{
			memcpy(&str[strIndex], &ESCAPE_BYTE, sizeof(uint8_t));
			strIndex += 1;
		}

		memcpy(&str[strIndex], &msg.mBuffer[i], sizeof(uint8_t));
		strIndex += 1;
	}

	memcpy(&str[strIndex], &STOP_BYTE, sizeof(uint8_t));
	strIndex += 1;

	std::string strSend = str.substr(0, strIndex);
	if (M_BLUETOOTH == mMode)
	{
		PX2_BLUETOOTH.Send(strSend, false);
	}
	else if (M_SERIAL == mMode)
	{
		if (msg.IsNeedResult())
		{
			mSerial.Send(strSend);
		}
		else
		{
			mSerial.Send(strSend);
		}
	}
}
//---------------------------------------------------------------------------
void Arduino::Update(float elapsedSeconds)
{
	PX2_UNUSED(elapsedSeconds);

	if (mMode == M_SERIAL)
	{
		std::string str;
		str.resize(10);
		mSerial.Receive(str);
		if (!str.empty())
		{
			int a = 0;
		}
	}
}
//---------------------------------------------------------------------------