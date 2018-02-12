// PX2Arduino.cpp

#include "PX2Arduino.hpp"
#include "PX2Log.hpp"
#include "PX2StringTokenizer.hpp"
#include "PX2StringHelp.hpp"
#include "PX2UDPServer.hpp"
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
	std::string paramStr2;

	if (stk.Count() > 0)
		cmdStr = stk[0];
	if (stk.Count() > 1)
		paramStr = stk[1];
	if (stk.Count() > 2)
		paramStr1 = stk[2];
	if (stk.Count() > 3)
		paramStr2 = stk[3];

	if (Arduino::sOptTypeStr[Arduino::OT_RETURN_DIST] == cmdStr)
	{
		float dist = StringHelp::StringToFloat(paramStr);
  		PX2_ARDUINO._SetDist(dist);
	}
	else if (Arduino::sOptTypeStr[Arduino::OT_RETURN_DR] == cmdStr)
	{
		int pin = StringHelp::StringToInt(paramStr);
		int val = StringHelp::StringToInt(paramStr1);
		PX2_ARDUINO._SetPinVal((Arduino::Pin)(Arduino::P_0 + pin), val);
 	}
	else if (Arduino::sOptTypeStr[Arduino::OT_RETURN_AR] == cmdStr)
	{
		int pin = StringHelp::StringToInt(paramStr);
		int val = StringHelp::StringToInt(paramStr1);
		PX2_ARDUINO._SetPinVal((Arduino::Pin)(Arduino::P_0 + pin), val);
	}
	else if (Arduino::sOptTypeStr[Arduino::OT_RETRUN_IR] == cmdStr)
	{
		int val = StringHelp::StringToInt(paramStr);
		PX2_ARDUINO._SetIRReceive(val);
	}
	//else if ("sp" == cmdStr)
	//{
	//	int speedL = StringHelp::StringToInt(paramStr);
	//	int speedR = StringHelp::StringToInt(paramStr1);
	//	PX2_ARDUINO._SetSpeedLR(speedL, speedR);
	//}
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
//----------------------------------------------------------------------------
std::string Arduino::PinStr[P_MAX_TYPE] = 
{
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"10",
	"11",
	"12",
	"13",
	"30",
	"31",
	"32",
	"33",
	"34",
	"35"
};
//----------------------------------------------------------------------------
std::string Arduino::PModeStr[PM_MAX_TYPE] = 
{
	"i",
	"o"
};

//---------------------------------------------------------------------------
std::string Arduino::sOptTypeStr[OT_MAX_TYPE] =
{
	"pm",
	"dw",
	"aw",
	"dr_re",
	"ar_re",
	"svr_i",
	"svr_w",
	"dst_i",
	"dst_t",
	"dst_re",
	"mo_i",
	"mo_r",
	"mo_rs",
	"mo_s",
	"mp3_i",
	"mp3_p",
	"mp3_id",
	"mp3_n",
	"mp3_s",
	"mp3_v",
	"ir_i",
	"ir_se",
	"ir_re"
};
//---------------------------------------------------------------------------
std::string Arduino::sDirectionTypeStr[DT_MAX_TYPE] =
{
	"n",
	"f",
	"b"
};
//---------------------------------------------------------------------------
std::string Arduino::sSimpleDirectionTypeStr[SDT_MAX_TYPE] =
{
	"n",
	"f",
	"b",
	"l",
	"r",
};
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
void Arduino::_SetPinVal(Pin pin, int val)
{
	if (0 <= pin && pin < P_MAX_TYPE)
		mPinValue[pin] = val;
}
//---------------------------------------------------------------------------
void Arduino::_SetSpeedLR(int left, int right)
{
	mSpeed[0] = left;
	mSpeed[1] = right;
}
//---------------------------------------------------------------------------
Arduino::Arduino() :
mMode(M_BLUETOOTH),
mTargetRobotID(0),
mRobotUDPPort(0),
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
Serial &Arduino::GetSerial()
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
bool Arduino::InitlizeForRobot(int targetRobotID, int udpPort)
{
	mMode = M_WIFI_ROBOT;
	mTargetRobotID = targetRobotID;
	mRobotUDPPort = udpPort;

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

	for (int i = 0; i < P_MAX_TYPE; i++)
	{
		mPinValue[i] = 0;
	}

	for (int i = 0; i < 4; i++)
	{
		mSpeed[i] = 0;
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
//----------------------------------------------------------------------------
std::string Arduino::_Pin2Str(Pin pin)
{
	return PinStr[pin];
}
//----------------------------------------------------------------------------
std::string Arduino::_PinMode2Str(PMode pm)
{
	return PModeStr[pm];
}
//----------------------------------------------------------------------------
std::string Arduino::_Bool2Str(bool bVal)
{
	return bVal ? "1" : "0";
}
//----------------------------------------------------------------------------
std::string Arduino::_Int2Str(int val)
{
	return StringHelp::IntToString(val);
}
//----------------------------------------------------------------------------
std::string Arduino::_DirectionType2Str(DirectionType dt)
{
	if (dt == DT_FORWARD)
		return "f";
	else if (dt == DT_BACKWARD)
		return "b";

	return "n";
}
//----------------------------------------------------------------------------
Arduino::Pin Arduino::_NetStr2Pin(const std::string &str)
{
	if ("0" == str)
		return Arduino::P_0;
	else if ("1" == str)
		return Arduino::P_1;
	else if ("2" == str)
		return Arduino::P_2;
	else if ("3" == str)
		return Arduino::P_3;
	else if ("4" == str)
		return Arduino::P_4;
	else if ("5" == str)
		return Arduino::P_5;
	else if ("6" == str)
		return Arduino::P_6;
	else if ("7" == str)
		return Arduino::P_7;
	else if ("8" == str)
		return Arduino::P_8;
	else if ("9" == str)
		return Arduino::P_9;
	else if ("10" == str)
		return Arduino::P_10;
	else if ("11" == str)
		return Arduino::P_11;
	else if ("12" == str)
		return Arduino::P_12;
	else if ("13" == str)
		return Arduino::P_13;
	else if ("A0" == str)
		return Arduino::P_A0;
	else if ("A1" == str)
		return Arduino::P_A1;
	else if ("A2" == str)
		return Arduino::P_A2;
	else if ("A3" == str)
		return Arduino::P_A3;
	else if ("A4" == str)
		return Arduino::P_A4;
	else if ("A5" == str)
		return Arduino::P_A5;

	return Arduino::P_0;
}
//----------------------------------------------------------------------------
Arduino::PMode Arduino::_NetStr2PinMode(const std::string &str)
{
	if ("input" == str)
		return Arduino::PM_INPUT;

	return Arduino::PM_OUTPUT;
}
//----------------------------------------------------------------------------
bool Arduino::_NetStr2Bool(const std::string &str)
{
	return str=="true" ? true : false;
}
//----------------------------------------------------------------------------
int Arduino::_NetStr2Int(const std::string &str)
{
	return StringHelp::StringToInt(str);
}
//----------------------------------------------------------------------------
float Arduino::_NetStr2Float(const std::string &str)
{
	return StringHelp::StringToFloat(str);
}
 //----------------------------------------------------------------------------
 Arduino::DirectionType Arduino::_NetStr2Dir(const std::string &str)
 {
	 if ("none" == str)
	 {
		 return DT_NONE;
	 }
	 if ("forward" == str)
	 {
		 return DT_FORWARD;
	 }
	 else if ("backward" == str)
	 {
		 return DT_BACKWARD;
	 }

	 return DT_NONE;
 }
 //----------------------------------------------------------------------------
 Arduino::SimpleDirectionType Arduino::_NetStr2SimpleDir(const std::string &str)
 {
	 if ("none" == str)
	 {
		 return SDT_NONE;
	 }
	 if ("forward" == str)
	 {
		 return SDT_FORWARD;
	 }
	 else if ("backward" == str)
	 {
		 return SDT_BACKWARD;
	 }
	 else if ("left" == str)
	 {
		 return SDT_LEFT;
	 }
	 else if ("right" == str)
	 {
		 return SDT_RIGHT;
	 }

	 return SDT_NONE;
 }
//----------------------------------------------------------------------------
std::string Arduino::_SimpleDirectionType2Str(SimpleDirectionType dt)
{
	if (dt == SDT_FORWARD)
		return "f";
	else if (dt == SDT_BACKWARD)
		return "b";
	else if (dt == SDT_LEFT)
		return "l";
	else if (dt == SDT_RIGHT)
		return "r";

	return "n";
}
//----------------------------------------------------------------------------
void Arduino::PinMode(Pin pin, PMode mode)
{
	std::string opStr = sOptTypeStr[OT_PM];
	std::string pinStr = _Pin2Str(pin);
	std::string valStr = _PinMode2Str(mode);

	std::string sendStr = opStr + " " + pinStr + " " + valStr;

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::DigitalWrite(Pin pin, bool isHigh)
{
	_SetPinVal(pin, isHigh ? 1 : 0);

	std::string opStr = sOptTypeStr[OT_DW];
	std::string pinStr = _Pin2Str(pin);
	std::string valStr = _Bool2Str(isHigh);

	std::string sendStr = opStr + " " + pinStr + " " + valStr;

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::AnalogWrite(Pin pin, int val)
{
	_SetPinVal(pin, val);

	std::string opStr = sOptTypeStr[OT_AW];
	std::string pinStr = _Pin2Str(pin);
	std::string valStr = _Int2Str(val);

	std::string sendStr = opStr + " " + pinStr + " " + valStr;

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
int Arduino::DigitalRead(Pin pin)
{
	return mPinValue[pin]>0 ? 1:0;
}
//----------------------------------------------------------------------------
int Arduino::AnalogRead(Pin pin)
{
	return mPinValue[pin];
}
//----------------------------------------------------------------------------
void Arduino::VehicleInitMotoBoard()
{
	std::string sendStr = sOptTypeStr[OT_MOTO_I];

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::Run(int motoIndex, DirectionType dt, int speed)
{
	if (0 <= motoIndex && motoIndex < 2)
	{
		std::string optStr = sOptTypeStr[OT_MOTO_RUN];
		std::string sendStr = optStr + " " + _Int2Str(motoIndex) + " " +
			_DirectionType2Str(dt) + " " +
			_Int2Str(speed);
		
		_Send(sendStr + mEndStr);
	}
}
//----------------------------------------------------------------------------
void Arduino::Run(SimpleDirectionType dt, int speed)
{
	std::string optStr = sOptTypeStr[OT_MOTO_RUNSIMPLE];
	std::string sendStr = optStr + " " + 
		_SimpleDirectionType2Str(dt) + " " +
		_Int2Str(speed);

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
int Arduino::GetSpeed(int motoIndex) const
{
	if (0 <= motoIndex && motoIndex<4)
		return mSpeed[motoIndex];

	return 0;
}
//----------------------------------------------------------------------------
void Arduino::Stop()
{
	std::string sendStr = sOptTypeStr[OT_MOTO_STOP];

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::MP3Init(Pin pinR, Pin pinT)
{
	std::string opStr = sOptTypeStr[OT_MP3_INIT];
	std::string pinRStr = _Pin2Str(pinR);
	std::string pinTStr = _Pin2Str(pinT);

	std::string sendStr = opStr + " " + pinRStr + " " + pinTStr;

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::MP3Play()
{
	std::string opStr = sOptTypeStr[OT_MP3_PLAY];

	_Send(opStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::MP3PlayNext()
{
	std::string opStr = sOptTypeStr[OT_MP3_NEXT];

	_Send(opStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::MP3PlayAtIndex(int index)
{
	std::string opStr = sOptTypeStr[OT_MP3_INDEX];
	std::string indexStr = _Int2Str(index);

	std::string sendStr = opStr + " " + indexStr;

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::MP3SetVolume(int volume)
{
	std::string opStr = sOptTypeStr[OT_MP3_VOLUME];
	std::string volumeStr = _Int2Str(volume);

	std::string sendStr = opStr + " " + volumeStr;

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::MP3Stop()
{
	std::string opStr = sOptTypeStr[OT_MP3_STOP];

	_Send(opStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::IRInit(Pin pinR)
{
	std::string opStr = sOptTypeStr[OT_IR_INIT];
	std::string pinRStr = _Pin2Str(pinR);
	std::string sendStr = opStr + " " + pinRStr;

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::IRSend(int val)
{
	std::string opStr = sOptTypeStr[OT_IR_SEND];
	std::string sendStr = opStr + " " + _Int2Str(val);

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::DistInit(Pin pinTrig, Pin pinEcho)
{
	std::string sendStr = sOptTypeStr[OT_DST_I];

	sendStr += " " + _Pin2Str(pinTrig) + " " + _Pin2Str(pinEcho);

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::DistTest()
{
	std::string sendStr = sOptTypeStr[OT_DST_T];

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
float Arduino::GetDist() const
{
	return mDist;
}
//----------------------------------------------------------------------------
void Arduino::ServerInit(int i, Pin pin)
{
	if (0 <= i && i < 3)
	{
		std::string sendStr = sOptTypeStr[OT_SVR_I];
		sendStr += " " + StringHelp::IntToString(i) + " " + _Pin2Str(pin);

		_Send(sendStr + mEndStr);
	}
}
//----------------------------------------------------------------------------
void Arduino::ServerWrite(int i, int val)
{
	if (0 <= i && i < 3)
	{
		std::string sendStr = sOptTypeStr[OT_SVR_W] + " " +
			StringHelp::IntToString(i) + " " +
			StringHelp::IntToString(val);

		_Send(sendStr + mEndStr);
	}
}
//----------------------------------------------------------------------------
void Arduino::IRRecvInit(Pin pin)
{
}
//----------------------------------------------------------------------------
void Arduino::IRSendSony(int val)
{
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
	else if (M_WIFI_ROBOT == mMode)
	{
		if (0 != mRobotUDPPort)
		{
			SocketAddress sktAddr("255.255.255.255", (int16_t)mRobotUDPPort);
			std::string sendStr = StringHelp::IntToString(mRobotUDPPort) + "$" +
				std::string("rs") + "$" + StringHelp::IntToString(mTargetRobotID)
				+ "$" + str;

			DatagramSocket udpSocket;
			udpSocket.SetBroadcast(true);
			udpSocket.SendTo(sendStr.c_str(), sendStr.length(), sktAddr);
		}
	}
}
//----------------------------------------------------------------------------