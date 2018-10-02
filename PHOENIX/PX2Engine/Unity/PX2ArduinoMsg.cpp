// PX2ArduinoMsg.cpp

#include "PX2ArduinoMsg.hpp"
#include "PX2StringHelp.hpp"
#include "PX2Math.hpp"
#include "PX2Memory.hpp"
using namespace PX2;

//---------------------------------------------------------------------------
ArduinoMsg::ArduinoMsg() :
mSetValueIndex(5),
mIsNeedResult(false)
{
	memset(mBuffer, 0, ARDUINO_MAX_PACKET_SIZE);
}
//---------------------------------------------------------------------------
ArduinoMsg::~ArduinoMsg()
{

}
//---------------------------------------------------------------------------
std::string ArduinoMsg::ToString() const
{
	std::string result = "";
	for (int i = 0; i < ARDUINO_MAX_PACKET_SIZE; i++) 
	{
		result += StringHelp::IntToString((int)mBuffer[i]); +' ';
	}
	return result;
}
//---------------------------------------------------------------------------
void ArduinoMsg::SetSourceAddress(uint8_t address)
{
	mBuffer[0] = address;
}
//---------------------------------------------------------------------------
uint8_t ArduinoMsg::GetSourceAddress() const
{
	return mBuffer[0];
}
//---------------------------------------------------------------------------
void ArduinoMsg::SetTargetAddress(uint8_t address)
{
	mBuffer[1] = address;
}
//---------------------------------------------------------------------------
uint8_t ArduinoMsg::GetTargetAddress() const
{
	return mBuffer[1];
}
//---------------------------------------------------------------------------
void ArduinoMsg::SetFrameNum(uint8_t num)
{
	mBuffer[2] = num;
}
//---------------------------------------------------------------------------
int ArduinoMsg::GetFrameNum() const
{
	return mBuffer[2];
}
//---------------------------------------------------------------------------
void ArduinoMsg::SetLength(uint8_t length)
{
	if (length > 10) length = 10;
	mBuffer[3] = length;
}
//---------------------------------------------------------------------------
int ArduinoMsg::GetLength() const
{
	return mBuffer[3];
}
//---------------------------------------------------------------------------
void ArduinoMsg::SetCMD(CMDType cmd)
{
	mBuffer[4] = (uint8_t)cmd;
}
//---------------------------------------------------------------------------
ArduinoMsg::CMDType ArduinoMsg::GetCMD() const
{
	return (CMDType)mBuffer[4];
}
//---------------------------------------------------------------------------
void ArduinoMsg::AddByteValue(int8_t v)
{
	mBuffer[mSetValueIndex] = v;
	mSetValueIndex += (uint8_t)sizeof(int8_t);
}
//---------------------------------------------------------------------------
void ArduinoMsg::AddShortValue(int16_t v)
{
	memcpy(&mBuffer[mSetValueIndex], &v, sizeof(int16_t));
	mSetValueIndex += (uint8_t)sizeof(int16_t);
}
//---------------------------------------------------------------------------
void ArduinoMsg::AddIntValue(int32_t v)
{
	memcpy(&mBuffer[mSetValueIndex], &v, sizeof(int32_t));
	mSetValueIndex += (int32_t)sizeof(int32_t);
}
//---------------------------------------------------------------------------
void ArduinoMsg::SetData(const uint8_t *data, uint8_t length)
{
	memcpy(mBuffer, data, length);
	mSetValueIndex = 5;
}
//---------------------------------------------------------------------------
void ArduinoMsg::SetParamData(const uint8_t *data, uint8_t length)
{
	if (length > 10)
		length = 10;

	memcpy(&mBuffer[5], data, length);
	SetLength(length);
}
//---------------------------------------------------------------------------
uint8_t *ArduinoMsg::GetParamData() const
{
	uint8_t *result = new1<uint8_t>(GetLength());
	memcpy(result, &mBuffer[5], GetLength());

	return result;
}
//---------------------------------------------------------------------------
void ArduinoMsg::SetNeedResult(bool isResult)
{
	mIsNeedResult = isResult;
}
//---------------------------------------------------------------------------
bool ArduinoMsg::IsNeedResult() const
{
	return mIsNeedResult;
}
//---------------------------------------------------------------------------