// PX2Arduino.cpp

#include "PX2Arduino.hpp"
#include "PX2Log.hpp"
using namespace PX2;

const uint8_t START_BYTE = 0x12;
const uint8_t STOP_BYTE = 0x13;
const uint8_t ESCAPE_BYTE = 0x7D;

//---------------------------------------------------------------------------
Arduino::Arduino() :
mMode(M_BLUETOOTH),
mIsCombining(false)
{
	mMode = M_BLUETOOTH;
}
//---------------------------------------------------------------------------
Arduino::~Arduino()
{
	if (M_SERIAL == mMode)
		mSerial.Close();
}
//---------------------------------------------------------------------------
Arduino::Mode Arduino::GetMode() const
{
	return mMode;
}
//---------------------------------------------------------------------------
void Arduino::Initlize(Mode mode, const std::string &port, int baudrate)
{
	mMode = mode;

	if (M_SERIAL == mMode)
		mSerial.Init(port, baudrate);
}
//---------------------------------------------------------------------------
void Arduino::Terminate()
{
	if (M_SERIAL == mMode)
		mSerial.Close();
}
//---------------------------------------------------------------------------
void Arduino::Update(float elapsedSeconds)
{
	PX2_UNUSED(elapsedSeconds);

	if (M_SERIAL == mMode)
	{
		std::string str;
		str.resize(10);
		mSerial.Receive(str);
		if (!str.empty())
		{
			//int a = 0;
		}
	}
}
//---------------------------------------------------------------------------