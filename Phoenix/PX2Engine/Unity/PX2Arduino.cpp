// PX2Arduino.cpp

#include "PX2Arduino.hpp"
#include "PX2Log.hpp"
#include "PX2StringTokenizer.hpp"
#include "PX2StringHelp.hpp"
using namespace PX2;

const uint8_t START_BYTE = 0x12;
const uint8_t STOP_BYTE = 0x13;
const uint8_t ESCAPE_BYTE = 0x7D;

//----------------------------------------------------------------------------
void _ArduinoProcessStr(std::string recvVal0)
{
	std::string recvStr;
	for (int i = 0; i < (int)recvVal0.size(); i++)
	{
		if ('\r' == recvVal0[i])
		{
		}
		else if ('\n' == recvStr[i])
		{
		}
		else
		{
			recvStr += recvVal0[i];
		}
	}

	PX2_LOG_INFO("_ProcessStr %s", recvStr.c_str());

	StringTokenizer stk(recvStr, " ");
	std::string cmdStr;
	std::string paramStr;
	std::string paramStr1;

	if (stk.Count() > 0)
		cmdStr = stk[0];
	if (stk.Count() > 1)
		paramStr = stk[1];
	if (stk.Count() > 2)
		paramStr1 = stk[2];

	if ("dist" == cmdStr)
	{
		float dist = StringHelp::StringToFloat(paramStr);
		PX2_ARDUINO._SetDist(dist);
	}
	else if ("irr_r" == cmdStr)
	{
		int val = StringHelp::StringToInt(paramStr);
		PX2_ARDUINO._SetIRReceive(val);
	}
	else if ("dr" == cmdStr)
	{
		int pin = StringHelp::StringToInt(paramStr);
		int val = StringHelp::StringToInt(paramStr1);
		PX2_ARDUINO._SetDigital(pin, val);
	}
	else if ("ar" == cmdStr)
	{
		int pin = StringHelp::StringToInt(paramStr);
		int val = StringHelp::StringToInt(paramStr1);
		PX2_ARDUINO._SetAnalog(pin, val);
	}
}
//----------------------------------------------------------------------------
void _ArduinoSerialBluetoothReceiveCallback(std::string recvVal)
{
	PX2_LOG_INFO("Recv Cmd:%s", recvVal.c_str());
	if (!recvVal.empty())
	{
		_ArduinoProcessStr(recvVal);
	}
}
//---------------------------------------------------------------------------
void Arduino::_SetDist(float dist)
{
	if (dist > 500)
		return;

	mDist = dist;
}
//---------------------------------------------------------------------------
void Arduino::_SetIRReceive(int irReceive)
{
	mIRReceive = irReceive;
}
//---------------------------------------------------------------------------
void Arduino::_SetDigital(int pin, int val)
{
	if (0 <= pin && pin < NumDR)
		mDigitalRead[pin] = val;
}
//---------------------------------------------------------------------------
void Arduino::_SetAnalog(int pin, int val)
{
	if (0 <= pin && pin < NumAR)
		mAnalogRead[pin] = val;
}
//---------------------------------------------------------------------------
Arduino::Arduino() :
mMode(M_BLUETOOTH),
mIsBeginArduino(false),
mDist(0.0f),
mIRReceive(0)
{
	mEndStr = "\n";

	mSerial.AddReceiveCallback(_ArduinoSerialBluetoothReceiveCallback);

	_Reset();
}
//---------------------------------------------------------------------------
Arduino::~Arduino()
{
	if (mSerial.IsOpened())
	{
		mSerial.Close();
	}
}
//---------------------------------------------------------------------------
Arduino::Mode Arduino::GetMode() const
{
	return mMode;
}
//---------------------------------------------------------------------------
Serial2 &Arduino::GetSerial()
{
	return mSerial;
}
//---------------------------------------------------------------------------
bool Arduino::Initlize(Mode mode, const std::string &port, int baudrate)
{
	mMode = mode;

	_Reset();

	if (M_SERIAL == mMode)
	{
		if (0 == mSerial.Open(port, baudrate))
		{
			mSerial.StartThread();
			mSerial.AddReceiveCallback(_ArduinoSerialBluetoothReceiveCallback);

			return true;
		}
		else
		{
			PX2_LOG_ERROR("Serial open failed.");
			return false;
		}
	}
	else if (M_BLUETOOTH == mMode)
	{
		/*_*/
		PX2_BLUETOOTH.AddReceiveCallback(_ArduinoSerialBluetoothReceiveCallback);
	}

	return true;
}
//---------------------------------------------------------------------------
bool Arduino::IsInitlized()
{
	if (M_SERIAL == mMode)
	{
		return mSerial.IsOpened();
	}
	else if (M_BLUETOOTH == mMode)
	{
		return PX2_BLUETOOTH.IsConnected();
	}

	return true;
}
//---------------------------------------------------------------------------
void Arduino::Terminate()
{
	if (mSerial.IsOpened())
	{
		mSerial.Close();
	}

	mSerial.EndThread();
}
//---------------------------------------------------------------------------
void Arduino::_Reset()
{
	mDist = 0.0f;

	for (int i = 0; i < NumDR; i++)
	{
		mDigitalRead[i] = 0;
	}

	for (int i = 0; i < NumAR; i++)
	{
		mAnalogRead[i] = 0;
	}
}
//---------------------------------------------------------------------------
void Arduino::Update(float elapsedSeconds)
{
	PX2_UNUSED(elapsedSeconds);

	if (mSerial.IsOpened())
	{
		mSerial.Update(elapsedSeconds);
	}
}
//---------------------------------------------------------------------------
void Arduino::Begin()
{
	PX2_LOG_INFO("Begin");
	mIsBeginArduino = true;
	mArduinoString = "";
}
//----------------------------------------------------------------------------
void Arduino::End()
{
	int adjustLength = 18;
	if (!mArduinoString.empty())
	{
		if ((int)mArduinoString.size() > adjustLength)
		{
			PX2_LOG_INFO("arduinoEnd %s", mArduinoString.c_str());

			StringTokenizer stk(mArduinoString, ";");
			std::string strSend;
			std::string strSendTemp;

			for (int i = 0; i < stk.Count(); i++)
			{
				strSendTemp += (stk[i] + ";");

				if ((int)strSendTemp.length() > adjustLength)
				{
					strSend += mEndStr;
					_Send(strSend);

					strSendTemp = (stk[i] + ";");
					strSend = strSendTemp;
				}
				else
				{
					strSend = strSendTemp;
				}
			}

			if (!strSend.empty())
			{
				_Send(strSend + mEndStr);
			}
		}
		else
		{
			PX2_LOG_INFO("arduinoEnd %s", mArduinoString.c_str());

			if (!mArduinoString.empty())
				_Send(mArduinoString + mEndStr);
		}
	}
	mArduinoString = "";
	mIsBeginArduino = false;
}
//----------------------------------------------------------------------------
void Arduino::PinMode(int pinVal, bool isOutput, bool isA)
{
	std::string opStr = "pM";
	std::string pinStr; 
	if (!isA)
		pinStr = StringHelp::IntToString(pinVal);
	else
		pinStr = "A" + StringHelp::IntToString(pinVal);
	int iMode = isOutput ? 1 : 0;
	std::string modeStr = StringHelp::IntToString(iMode);
	std::string sendStr = opStr + " " + pinStr + " " + modeStr;

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::DigitalWrite(int pinVal, bool isHigh, bool isA)
{
	std::string opStr = "dW";
	std::string pinStr;
	if (!isA)
		pinStr = StringHelp::IntToString(pinVal);
	else
		pinStr = "A" + StringHelp::IntToString(pinVal);
	int iMode = isHigh ? 1 : 0;
	std::string modeStr = StringHelp::IntToString(iMode);
	std::string sendStr = opStr + " " + pinStr + " " + modeStr;

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::AnalogWrite(int pinVal, int val, bool isA)
{
	std::string opStr = "aW";
	std::string pinStr;
	if (!isA)
		pinStr = StringHelp::IntToString(pinVal);
	else
		pinStr = "A" + StringHelp::IntToString(pinVal);
	std::string modeStr = StringHelp::IntToString(val);
	std::string sendStr = opStr + " " + pinStr + " " + modeStr;

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
int Arduino::DigitalRead(int pinVal)
{
	if (0 <= pinVal && pinVal < NumDR)
		return mDigitalRead[pinVal];
	return 0;
}
//----------------------------------------------------------------------------
int Arduino::AnalogRead(int pinVal)
{
	if (0 <= pinVal && pinVal < NumAR)
		return mAnalogRead[pinVal];
	return 0;
}
//----------------------------------------------------------------------------
void Arduino::LEDInit(int din, int cs, int clk)
{
	std::string sendStr = "lcdset " + StringHelp::IntToString(din) + " "
		+ StringHelp::IntToString(cs) + " " +
		StringHelp::IntToString(clk);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::LEDSetFace(const std::string &faceStr)
{
	std::string sendStr = "lcd " + faceStr;

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::RGBLightInit(int pinR, int pinG, int pinB, bool isAnglog)
{
	std::string sendStr;
	if (isAnglog)
	{
		sendStr = "cl s d" +
			StringHelp::IntToString(pinR) + " " +
			StringHelp::IntToString(pinG) + " " +
			StringHelp::IntToString(pinB);
	}
	else
	{
		sendStr = "cl s a" +
			StringHelp::IntToString(pinR) + " " +
			StringHelp::IntToString(pinG) + " " +
			StringHelp::IntToString(pinB);
	}

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::RGBLight(int r, int g, int b)
{
	std::string sendStr;
	sendStr = "clc " +
		StringHelp::IntToString(r) + " " +
		StringHelp::IntToString(g) + " " +
		StringHelp::IntToString(b);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::VehicleInit(int pinL0, int pinL1, int speedL,
	int pinR0, int pinR1, int speedR)
{
	std::string sendStr = "v s " +
		StringHelp::IntToString(pinL0) + " " +
		StringHelp::IntToString(pinL1) + " " +
		StringHelp::IntToString(speedL) + " " +
		StringHelp::IntToString(pinR0) + " " +
		StringHelp::IntToString(pinR1) + " " +
		StringHelp::IntToString(speedR);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::VehicleInitSimple()
{
	std::string sendStr = "v ss";

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::Go(int speed)
{
	std::string sendStr = std::string("m l g") + ";";
	sendStr += std::string("m r g") + ";";
	sendStr += std::string("s l ") + StringHelp::IntToString(speed) + ";";
	sendStr += std::string("s r ") + StringHelp::IntToString(speed);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::LaserInit(int pin, bool isAnalog)
{
	std::string sendStr;
	if (!isAnalog)
	{
		sendStr = std::string("lt s d ") + StringHelp::IntToString(pin);
	}
	else
	{
		sendStr = std::string("lt s a ") + StringHelp::IntToString(pin);
	}

	if (!mIsBeginArduino)
	{
		sendStr += mEndStr;
		_Send(sendStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::LaserTurn(bool isOn)
{
	std::string sendStr;
	if (isOn)
		sendStr = std::string("lt on");
	else
		sendStr = std::string("lt off");

	if (!mIsBeginArduino)
	{
		sendStr += mEndStr;
		_Send(sendStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::Back(int speed)
{
	std::string sendStr;
	sendStr += std::string("m l b") + ";";
	sendStr += std::string("m r b") + ";";
	sendStr += std::string("s l ") + StringHelp::IntToString(speed) + ";";
	sendStr += std::string("s r ") + StringHelp::IntToString(speed);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::Left(int speed)
{
	std::string sendStr;
	sendStr += std::string("m l b") + ";";
	sendStr += std::string("m r g") + ";";
	sendStr += std::string("s l ") + StringHelp::IntToString(speed) + ";";
	sendStr += std::string("s r ") + StringHelp::IntToString(speed);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::Right(int speed)
{
	std::string sendStr;
	sendStr += std::string("m l g") + ";";
	sendStr += std::string("m r b") + ";";
	sendStr += std::string("s l ") + StringHelp::IntToString(speed) + ";";
	sendStr += std::string("s r ") + StringHelp::IntToString(speed);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::Stop()
{
	std::string sendStr;
	sendStr += std::string("m l s") + ";";
	sendStr += std::string("m r s") + ";";
	sendStr += std::string("s l ") + StringHelp::IntToString(0) + ";";
	sendStr += std::string("s r ") + StringHelp::IntToString(0);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::LeftRunType(int type)
{
	std::string sendStr;
	if (0 == type)
		sendStr = std::string("m l s");
	else if (1 == type)
		sendStr = std::string("m l g");
	else if (2 == type)
		sendStr = std::string("m l b");

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::LeftSpeed(int speed)
{
	std::string sendStr = std::string("s l ") +
		StringHelp::IntToString(speed);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::RightRunType(int type)
{
	std::string sendStr;
	if (0 == type)
		sendStr = std::string("m r s");
	else if (1 == type)
		sendStr = std::string("m r g");
	else if (2 == type)
		sendStr = std::string("m r b");

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::RightSpeed(int speed)
{
	std::string sendStr = std::string("s r ") + StringHelp::IntToString(speed);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::DistInit(int pinTrig, int pinEcho, bool isA)
{
	std::string sendStr = std::string("distSet ");
	if (!isA)
	{
		sendStr += "d ";
	}
	else
	{
		sendStr += "a ";
	}

	sendStr += StringHelp::IntToString(pinTrig) + " " +
		StringHelp::IntToString(pinEcho);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::DistTest()
{
	std::string sendStr = std::string("distTest");

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
float Arduino::GetDist() const
{
	return mDist;
}
//----------------------------------------------------------------------------
void Arduino::ServerInit(int pin, bool isA)
{
	std::string sendStr = std::string("svrI ") + StringHelp::IntToString(pin);
	if (isA)
	{
		sendStr = std::string("svrIA ") + StringHelp::IntToString(pin);
	}

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::Server1Init(int pin, bool isA)
{
	std::string sendStr = std::string("svr1I ") + StringHelp::IntToString(pin);
	if (isA)
	{
		sendStr = std::string("svr1IA ") + StringHelp::IntToString(pin);
	}

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::Server2Init(int pin, bool isA)
{
	std::string sendStr = std::string("svr2I ") + StringHelp::IntToString(pin);
	if (isA)
	{
		sendStr = std::string("svr2IA ") + StringHelp::IntToString(pin);
	}

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::ServerWrite(int val)
{
	std::string sendStr = std::string("svr ") + StringHelp::IntToString(val);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::Server1Write(int val)
{
	std::string sendStr = std::string("svr1 ") + StringHelp::IntToString(val);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::Server2Write(int val)
{
	std::string sendStr = std::string("svr2 ") + StringHelp::IntToString(val);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::Mp3Init(int pin0, int pin1)
{
	std::string sendStr = std::string("mp3 ") +
		StringHelp::IntToString(pin0) + " " + StringHelp::IntToString(pin1);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::Mp3Stop()
{
	std::string sendStr = std::string("mp3s");

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::Mp3Volume(int val)
{
	std::string sendStr = std::string("mp3vo ") + StringHelp::IntToString(val);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::Mp3Play(int index)
{
	std::string sendStr = std::string("mp3i ") +
		StringHelp::IntToString(index);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::Mp3Next()
{
	std::string sendStr = std::string("mp3n");

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::IRRecvInit(int pin, bool isAnalog)
{
	std::string sendStr;
	if (!isAnalog)
	{
		sendStr = std::string("irr d ") + StringHelp::IntToString(pin);
	}
	else
	{
		sendStr = std::string("irr a ") + StringHelp::IntToString(pin);
	}

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::IRSendNEC(int val)
{
	std::string sendStr = std::string("irr_nec ") + StringHelp::IntToString(val);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
void Arduino::IRSendSony(int val)
{
	std::string sendStr = std::string("irr_sony ") + StringHelp::IntToString(val);

	if (!mIsBeginArduino)
	{
		_Send(sendStr + mEndStr);
	}
	else
	{
		mArduinoString += sendStr + ";";
	}
}
//----------------------------------------------------------------------------
int Arduino::GetIRReceive() const
{
	return mIRReceive;
}
//----------------------------------------------------------------------------
void Arduino::_Send(const std::string &str)
{
	if (M_SERIAL == mMode)
	{
		mSerial.Write(str);
	}
	else if (M_BLUETOOTH == mMode)
	{
		PX2_BLUETOOTH.Send(str);
	}
}
//----------------------------------------------------------------------------