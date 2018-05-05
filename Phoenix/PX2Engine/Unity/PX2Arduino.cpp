// PX2Arduino.cpp

#include "PX2Arduino.hpp"
#include "PX2Log.hpp"
#include "PX2StringTokenizer.hpp"
#include "PX2StringHelp.hpp"
#include "PX2UDPServer.hpp"
#include "PX2System.hpp"
#include "PX2ScriptManager.hpp"
using namespace PX2;

const uint8_t START_BYTE = 0x12;
const uint8_t STOP_BYTE = 0x13;
const uint8_t ESCAPE_BYTE = 0x7D;

//----------------------------------------------------------------------------
void _ArduinoProcessStr1(std::string recvVal)
{
	PX2_LOG_INFO("_ProcessStr %s", recvVal.c_str());

	StringTokenizer stk(recvVal, " ");
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
	else if (Arduino::sOptTypeStr[Arduino::OT_RETURN_IR] == cmdStr) 
	{
		int val = StringHelp::StringToInt(paramStr);
		PX2_LOG_INFO("!!!!!!!!!!!!!!!!Recved IR %d", val);

		PX2_ARDUINO._SetIRReceive(val);
	}
	else if (Arduino::sOptTypeStr[Arduino::OT_RETURN_NETID] == cmdStr)
	{
		int val = StringHelp::StringToInt(paramStr);
		PX2_ARDUINO.SetNetID(val);
	}
	else if (Arduino::sOptTypeStr[Arduino::OT_RETURN_MOTOSPD] == cmdStr)
	{
		int speedL = StringHelp::StringToInt(paramStr);
		int speedR = StringHelp::StringToInt(paramStr1);
		PX2_ARDUINO._SetSpeedLR(speedL, speedR);
	}
	else if (Arduino::sOptTypeStr[Arduino::OT_RETURN_HX711] == cmdStr)
	{
		int index = StringHelp::StringToInt(paramStr);
		float val = StringHelp::StringToInt(paramStr1);
		PX2_ARDUINO._SetWeight(index, val);
	}
}
//----------------------------------------------------------------------------
void _Less4Process(std::string recvVal)
{
	if (recvVal.empty())
		return;

	std::string useStr = recvVal.substr(4);
	_ArduinoProcessStr1(useStr);
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
	"35",
	"36"
};
//----------------------------------------------------------------------------
std::string Arduino::PModeStr[PM_MAX_TYPE] = 
{
	"0",
	"1"
};
//---------------------------------------------------------------------------
std::string Arduino::sOptTypeStr[OT_MAX_TYPE] =
{
	"50", //OT_TOGET_NETID
	"51", //OT_RETRUN_NETID
	"0",  //OT_PM
	"1",  //OT_DW
	"2",  //OT_AW
	"3",  //OT_RETURN_DR
	"4",  //OT_RETURN_AR
	"5",  //OT_SVR_I
	"6",  //OT_SVR_W
	"7",  //OT_DST_I
	"8",  //OT_DST_T
	"9",  //OT_RETURN_DIST
	"10", //OT_MOTO_I
	"11", //OT_MOTO_RUN
	"12", //OT_MOTO_RUNSIMPLE
	"13", //OT_MOTO_STOP
	"14", //OT_MOTO_I_SPD
	"15", //OT_RETURN_MOTOSPD
	"16", //OT_MOTO_I_DRIVER4567
	"17", //OT_MOTO_I_DRIVER298N
	"18", //OT_MP3_INIT
	"19", //OT_MP3_PLAY
	"20", //OT_MP3_INDEX
	"21", //OT_MP3_NEXT
	"22", //OT_MP3_STOP
	"23", //OT_MP3_VOLUME
	"24", //OT_IR_INIT
	"25", //OT_IR_SEND
	"26", //OT_RETURN_IR
	"27", //OT_HX711_I
	"28", //OT_HX711_TEST
	"29", //OT_RETURN_HX711
	"500", //OT_INTERNAL_LIGHT
	"501", //OT_LIGHT
	"502", //OT_SEGMENT
	"503", //OT_MOTO
	"504" //OT_DISTTEST
};
//---------------------------------------------------------------------------
std::string Arduino::sDirectionTypeStr[DT_MAX_TYPE] =
{
	"0",
	"1",
	"2"
};
//---------------------------------------------------------------------------
std::string Arduino::sSimpleDirectionTypeStr[SDT_MAX_TYPE] =
{
	"0",
	"1",
	"2",
	"3",
	"4",
};
//---------------------------------------------------------------------------
void Arduino::_SetDist(float dist)
{
	if (dist > 500)
		return;

	mDist = dist;

	_OnCallback(ART_RECT_DIST, (int)mDist);
}
//---------------------------------------------------------------------------
void Arduino::_SetIRReceive(int irReceive)
{
	mIRReceive = irReceive;

	_OnCallback(ART_RECV_IR, mIRReceive);
}
//---------------------------------------------------------------------------
void Arduino::_SetPinVal(Pin pin, int val)
{
	if (0 <= pin && pin < P_MAX_TYPE)
		mPinValue[pin] = val;
}
//---------------------------------------------------------------------------
void Arduino::_SetWeight(int index, float weight)
{
	if (0 <= index && index < 4)
	{
		mWeight[index] = weight;
	}
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
mNetID(0),
mTargetRobotID(0),
mRobotUDPPort(0),
mTcpPort(9000),
mDist(0.0f),
mIRReceive(0),
mServer(0)
{
	mEndStr = "\n";

	mSerial.AddCMDCallback(_Less4Process);

	Reset();
}
//---------------------------------------------------------------------------
Arduino::~Arduino()
{
	if (mSerial.IsOpened())
	{
		mSerial.Close();
	}

	if (mServer)
	{
		mServer->Shutdown();
		mServer = 0;
	}
}
//---------------------------------------------------------------------------
Arduino::Mode Arduino::GetMode() const
{
	return mMode;
}
//---------------------------------------------------------------------------
bool Arduino::AddArduinoReceiveCallbacks(ArduinoReceiveCallback callback)
{
	if (IsHasArduinoReceiveCallback(callback))
		return false;

	mCallbacks.push_back(callback);

	return true;
}
//---------------------------------------------------------------------------
bool Arduino::IsHasArduinoReceiveCallback(ArduinoReceiveCallback callback) const
{
	for (int i = 0; i < (int)mCallbacks.size(); i++)
	{
		if (callback == mCallbacks[i])
			return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool Arduino::AddScriptHandler(const std::string &handler)
{
	for (int i = 0; i < (int)mRecvHandlers.size(); i++)
	{
		if (handler == mRecvHandlers[i])
			return false;
	}

	mRecvHandlers.push_back(handler);
	return true;
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

	Reset();

	if (M_SERIAL == mMode)
	{
		if (0 == mSerial.Open(port, baudrate))
		{
			mSerial.AddCMDCallback(_Less4Process);

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
		PX2_BLUETOOTH.AddCMDCallback(_Less4Process);
		PX2_LOG_INFO("Arduino Initlize BLUETOOTH");
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
static int _DoConnect(ClientConnector *conn, const char *ip, int port, 
	const char *servername)
{
	if (conn->ConnectNB(ip, (int16_t)port) < 0)
	{
		printf("connect %s failed\n", servername);
		return -1;
	}
	else printf("connect %s begin...\n", servername);

	int times = 0;
	while (conn->GetConnectState() == CONNSTATE_TRYCONNECT)
	{
		if (times > 10)
			return - 1;

		times++;

		System::SleepSeconds(0.02f);
		if (conn->Update(0.0f) < 0)
		{
			printf("connect %s failed\n", servername);
			return -1;
		}
	}

	if (conn->GetConnectState() == CONNSTATE_INIT)
	{
		printf("connect %s failed\n", servername);
		return -1;
	}
	else printf("connected\n");

	return 0;
}
//---------------------------------------------------------------------------
static std::string _sNetRecvStr;
//---------------------------------------------------------------------------
void _ClientConnectorRecvCallback(const std::string &recvStr)
{
	if (recvStr.empty())
		return;

	std::string cmdStr;
	int index = 0;
	for (index = 0; index < (int)recvStr.size(); index++)
	{
		char chara = recvStr[index];
		if ('\r' == chara)
		{
			continue;
		}
		else if ('\n' == chara)
		{
			if (!recvStr.empty())
			{
				_Less4Process(_sNetRecvStr);
				_sNetRecvStr.clear();
			}
		}
		else
		{
			_sNetRecvStr += chara;
		}
	}
}
//---------------------------------------------------------------------------
bool Arduino::InitlizeWifiTCP(const std::string &ip, int port)
{
	mMode = M_WIFI_TCP;

	if (mConnector)
	{
		mConnector->Disconnect();
		mConnector = 0;
	}

	mTcpIP = ip;
	mTcpPort = port;
	mConnector = new0 ClientConnector(2);
	mConnector->AddRecvCallback(_ClientConnectorRecvCallback);
	int connectRet = _DoConnect(mConnector, mTcpIP.c_str(), port, "");
	if (0 != connectRet)
	{
		PX2_LOG_INFO("DoConnect failed.");
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool Arduino::InitlizeEmpty()
{
	mMode = M_EMPTY;

	return true;
}
//---------------------------------------------------------------------------
bool Arduino::InitlizeServer(Server *server)
{
	mMode = M_WIFI_SERVER;
	mServer = server;

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
	else if (M_WIFI_TCP == mMode)
	{
		return (mConnector->GetConnectState() == CONNSTATE_CONNECTED);
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

	if (mConnector)
	{
		mConnector->Disconnect();
		mConnector = 0;
	}
}
//---------------------------------------------------------------------------
void Arduino::Reset()
{
	mDist = 0.0f;
	mIRReceive = 0;

	for (int i = 0; i < P_MAX_TYPE; i++)
	{
		mPinValue[i] = 0;
	}

	for (int i = 0; i < 4; i++)
	{
		mSpeed[i] = 0;
	}

	for (int i = 0; i < 4; i++)
	{
		mWeight[i] = 0.0f;
	}

	PX2_BLUETOOTH.AddCMDCallback(_Less4Process);
}
//---------------------------------------------------------------------------
void Arduino::_OnCallback(ArduinoRectType type, int value)
{
	for (int i = 0; i < (int)mCallbacks.size(); i++)
	{
		if (mCallbacks[i])
		{
			mCallbacks[i](type, value);
		}
	}

	for (int i = 0; i < (int)mRecvHandlers.size(); i++)
	{
		if (!mRecvHandlers[i].empty())
		{
			PX2_SC_LUA->CallFunction(mRecvHandlers[i], this, (int)type);
		}
	}
}
//---------------------------------------------------------------------------
void Arduino::_OnToSendCallback(const std::string &str)
{
	for (int i = 0; i < (int)mToSendCallbacks.size(); i++)
	{
		if (mToSendCallbacks[i])
		{
			mToSendCallbacks[i](str);
		}
	}
}
//---------------------------------------------------------------------------
void Arduino::SendToGetNetID()
{
	std::string opStr = sOptTypeStr[OT_TOGET_NETID];
	std::string sendStr = opStr;

	_Send(sendStr + mEndStr);
}
//---------------------------------------------------------------------------
void Arduino::SetNetID(int id)
{
	mNetID = id;
}
//---------------------------------------------------------------------------
int Arduino::GetNetID() const
{
	return mNetID;
}
//---------------------------------------------------------------------------
void Arduino::Update(float elapsedSeconds)
{
	PX2_UNUSED(elapsedSeconds);

	if (mSerial.IsOpened())
	{
		mSerial.Update(elapsedSeconds);
	}

	if (mConnector)
	{
		mConnector->Update(elapsedSeconds);
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
	int type = (int)dt;
	return StringHelp::IntToString(type);
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
	else if ("A6" == str)
		return Arduino::P_A6;

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
	int type = (int)dt;
	return StringHelp::IntToString(type);
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
void Arduino::VehicleInitMotoBoard4567()
{
	std::string sendStr = sOptTypeStr[OT_MOTO_I_DRIVER4567];

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::VehicleInitMotoBoard298N(Pin pinLA, Pin pinLB, Pin pinLS, 
	Pin pinRA, Pin pinRB, Pin pinRS)
{
	std::string sendStr = sOptTypeStr[OT_MOTO_I_DRIVER298N];

	sendStr += " " + _Pin2Str(pinLA) + " " + _Pin2Str(pinLB) + ' ' + _Pin2Str(pinLS) +
		" " + _Pin2Str(pinRA) + " " + _Pin2Str(pinRB) + ' ' + _Pin2Str(pinRS);

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::VehicleSpeedInit(Pin pinLA, Pin pinLB, Pin pinRA, Pin pinRB)
{
	std::string sendStr = sOptTypeStr[OT_MOTO_I_SPD];

	sendStr += " " + _Pin2Str(pinLA) + " " + _Pin2Str(pinLB) + 
		" " + _Pin2Str(pinRA) + " " + _Pin2Str(pinRB);

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
int Arduino::GetIRReceive() const
{
	return mIRReceive;
}
//----------------------------------------------------------------------------
void Arduino::WeightInit(int i, Pin pinOut, Pin pinClk)
{
	if (0 <= i && i < 4)
	{
		std::string sendStr = sOptTypeStr[OT_HX711_I];
		sendStr += " " + StringHelp::IntToString(i) + " " + _Pin2Str(pinOut) + 
			" " + _Pin2Str(pinClk);

		_Send(sendStr + mEndStr);
	}
}
//----------------------------------------------------------------------------
void Arduino::WeightTest(int i)
{
	if (0 <= i && i < 4)
	{
		std::string sendStr = sOptTypeStr[OT_HX711_TEST];
		sendStr += " " + StringHelp::IntToString(i);

		_Send(sendStr + mEndStr);
	}
}
//----------------------------------------------------------------------------
float Arduino::GetWeight(int i)
{
	if (0 <= i && i < 4)
	{
		return mWeight[i];
	}

	return 0.0f;
}
//----------------------------------------------------------------------------
bool Arduino::AddArduinoToSendCallback(ArduinoToSendCallback callback)
{
	if (IsHasArduinoToSendCallback(callback))
		return false;

	mToSendCallbacks.push_back(callback);

	return true;
}
//----------------------------------------------------------------------------
bool Arduino::IsHasArduinoToSendCallback(ArduinoToSendCallback callback) const
{
	for (int i = 0; i < (int)mToSendCallbacks.size(); i++)
	{
		if (callback == mToSendCallbacks[i])
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
const std::string &Arduino::GetLastSendString()
{
	return 	mLastSendString;
}
//----------------------------------------------------------------------------
void Arduino::MCSegmentSet(int pin, int val)
{
	std::string sendStr = sOptTypeStr[OT_SEGMENT];
	sendStr += " " + _Int2Str(pin) + " " + StringHelp::IntToString(val);

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::MCMoto(int pin, int speed)
{
	std::string sendStr = sOptTypeStr[OT_MOTO];
	sendStr += " " + _Int2Str(pin) + " " + StringHelp::IntToString(speed);

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::MCTestDist(int pin)
{
	std::string sendStr = sOptTypeStr[OT_DISTTEST];
	sendStr += " " + _Int2Str(pin);

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::_Send(const std::string &cmdStr)
{
	std::string lastCmdStr = "0000" + cmdStr;

	int allLength = 2 + cmdStr.length();
	*(unsigned short *)(&lastCmdStr[0]) = (unsigned short)allLength; // length
	*(unsigned short *)(&lastCmdStr[2]) = (unsigned short)2; // GeneralServerMsgID

	mLastSendString = lastCmdStr;

	if (M_SERIAL == mMode)
	{
		mSerial.Write(lastCmdStr);
	}
	else if (M_BLUETOOTH == mMode)
	{
		PX2_BLUETOOTH.Send(lastCmdStr);
	}
	else if (M_WIFI_ROBOT == mMode)
	{
		if (0 != mRobotUDPPort)
		{
			SocketAddress sktAddr("255.255.255.255", (int16_t)mRobotUDPPort);
			std::string sendStr = StringHelp::IntToString(mRobotUDPPort) + "$" +
				std::string("rs") + "$" + StringHelp::IntToString(mTargetRobotID)
				+ "$" + lastCmdStr;

			DatagramSocket udpSocket;
			udpSocket.SetBroadcast(true);
			udpSocket.SendTo(sendStr.c_str(), sendStr.length(), sktAddr);
		}
	}
	else if (M_WIFI_TCP == mMode)
	{
		if (mConnector && !lastCmdStr.empty())
		{
			mConnector->GetSocket().SendBytes(lastCmdStr.c_str(), (int)lastCmdStr.length());
		}
	}
	else if (M_WIFI_SERVER == mMode)
	{
		if (0 != mNetID)
		{
			if (mServer && !cmdStr.empty())
			{
				// 2 is GeneralServerMsgID
				mServer->SendMsgToClientBuffer(mNetID, 2, cmdStr.c_str(),
					cmdStr.length());
			}
		}
		else
		{
			PX2_LOG_INFO("NetID should not be 0");
		}
	}

	_OnToSendCallback(lastCmdStr);
}
//----------------------------------------------------------------------------