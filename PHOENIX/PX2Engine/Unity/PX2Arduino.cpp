// PX2Arduino.cpp

#include "PX2Arduino.hpp"
#include "PX2Log.hpp"
#include "PX2StringTokenizer.hpp"
#include "PX2StringHelp.hpp"
#include "PX2UDPServer.hpp"
#include "PX2System.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2Math.hpp"
#include "PX2System.hpp"
using namespace PX2;

const uint8_t START_BYTE = 0x12;
const uint8_t STOP_BYTE = 0x13;
const uint8_t ESCAPE_BYTE = 0x7D;

//----------------------------------------------------------------------------
void _ArduinoProcessStr1(std::string recvVal)
{
	StringTokenizer stk(recvVal, " ");
	std::string cmdStr;
	std::string paramStr;
	std::string paramStr1;
	std::string paramStr2;
	std::string paramStr3;
	std::string paramStr4;
	std::string paramStr5;
	std::string paramStr6;

	if (stk.Count() > 0)
		cmdStr = stk[0];
	if (stk.Count() > 1)
		paramStr = stk[1];
	if (stk.Count() > 2)
		paramStr1 = stk[2];
	if (stk.Count() > 3)
		paramStr2 = stk[3];
	if (stk.Count() > 4)
		paramStr3 = stk[4];
	if (stk.Count() > 5)
		paramStr4 = stk[5];
	if (stk.Count() > 6)
		paramStr5 = stk[6];
	if (stk.Count() > 7)
		paramStr6 = stk[7];

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
		float val = (float)StringHelp::StringToInt(paramStr1);
		PX2_ARDUINO._SetWeight(index, val);
	}
	else if (Arduino::sOptTypeStr[Arduino::OT_RETURN_DSTMAT] == cmdStr)
	{
		int index = StringHelp::StringToInt(paramStr);
		float val = (float)StringHelp::StringToInt(paramStr1);
		PX2_ARDUINO._SetDistMat(index, val);
	}
	else if (Arduino::sOptTypeStr[Arduino::OT_RETURN_AXIS] == cmdStr)
	{
		unsigned long time = (unsigned long)atol(paramStr.c_str());
		float yAxis = StringHelp::StringToFloat(paramStr1);
		float xAxis = StringHelp::StringToFloat(paramStr2);
		float zAxis = StringHelp::StringToFloat(paramStr3);
		float pitch = StringHelp::StringToFloat(paramStr4);
		float roll = StringHelp::StringToFloat(paramStr5);
		float yaw = StringHelp::StringToFloat(paramStr6);

		//yAxis = 0.0f;
		//xAxis = 0.0f;
		//zAxis = 0.0f;
		//pitch = 0.0f;
		//roll = 0.0f;
		//yaw = 0.0f;

		PX2_ARDUINO._SetAxis(time, yAxis, xAxis, zAxis, pitch, roll, yaw);
	}
}
//----------------------------------------------------------------------------
void Arduino::_SetAxis(unsigned long timeMilliseconds, float yAxis, float xAxis, 
	float zAxis, float pitch, float roll, float yaw)
{
	mYAxis = yAxis;
	mXAxis = xAxis;
	mZAxis = zAxis;
	mPitch = pitch;
	mRoll = roll;
	mYaw = yaw;

	int iNum = (int)Mathf::Floor(Mathf::FAbs(mYaw) / 180.0f);
	if (mYaw >= 0.0f)
	{
		if (iNum % 2 == 0)
			mYaw = mYaw - iNum*180.0f;
		else
			mYaw = -(180.0f - (mYaw - iNum*180.0f));
	}
	else
	{
		if (iNum % 2 == 0)
			mYaw = mYaw + iNum*180.0f;
		else
			mYaw = 180.0f + (mYaw + iNum*180.0f);
	}

	AxisObj axisObj;
	axisObj.TStamp = mArduinoSetTime + Timestamp::TimeDiff(timeMilliseconds*Timespan::MILLISECONDS);
	axisObj.IsValied = true;
	axisObj.AX = mXAxis;
	axisObj.AY = mYAxis;
	axisObj.AZ = mZAxis;
	axisObj.P = mPitch;
	axisObj.R = mRoll;
	axisObj.Y = mYaw;
	mCurAxisObj = axisObj;
	mAxisObjs.push_back(axisObj);
	Timestamp::TimeVal t = axisObj.TStamp.EpochMicroseconds();

	//PX2_LOG_INFO("Time: %I64d, %d, %d, %d, %d, %d, %d ", (int64_t)timeMilliseconds, (int)mXAxis, (int)mYAxis, (int)mZAxis, (int)mPitch, (int)mRoll, (int)mYaw);

	if (mAxisObjs.size() > 60)
	{
		std::vector<AxisObj> axisObj;
		for (int i = 10; i < (int)mAxisObjs.size(); i++)
		{
			axisObj.push_back(mAxisObjs[i]);
		}
		mAxisObjs = axisObj;
	}
}
//----------------------------------------------------------------------------
void _Less4Process(std::string recvVal)
{
	if (recvVal.empty())
		return;

	if (recvVal.length() < 4)
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
	"30", //OT_DSTMAT_I,
	"31", //OT_RETURN_DSTMAT,
	"32", //OT_AXIS_I,
	"33", //OT_RETURN_AXIS
	"34", //OT_SET_TIME
	"500", //OT_MC_INTERNAL_LIGHT
	"501", //OT_MC_LIGHT
	"502", //OT_MC_SEGMENT
	"503", //OT_MC_MOTO
	"504", //OT_MC_DISTTEST
	"601", //OT_MB_MOTO
	"602", //OT_MB_SEND
	"603" //OT_MB_BUZZER
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

	mIsBlockLoopDoBreak = true;
	mBlockLoopUpdateTimes = 0;
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

	mIsBlockLoopDoBreak = true;
	mBlockLoopUpdateTimes = 0;
}
//---------------------------------------------------------------------------
void Arduino::_SetWeight(int index, float weight)
{
	if (0 <= index && index < 4)
	{
		mWeight[index] = weight;
	}

	mIsBlockLoopDoBreak = true;
	mBlockLoopUpdateTimes = 0;
}
//---------------------------------------------------------------------------
void Arduino::_SetDistMat(int index, float val)
{
	if (0 <= index && index < NUMDISTMAT)
	{
		mDistMat[index] = val;
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
mIsBlockLoopDoBreak(true),
mBlockLoopUpdateTimes(0),
mMode(M_BLUETOOTH),
mNetID(0),
mTargetRobotID(0),
mRobotUDPPort(0),
mTcpPort(9000),
mDist(0.0f),
mIRReceive(0),
mServer(0),
mYAxis(0.0f),
mXAxis(0.0f),
mZAxis(0.0f),
mPitch(0.0f),
mRoll(0.0f),
mYaw(0.0f),
mIsEverSetTime(false),
mEverSetTime(0.0f)
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
bool Arduino::InitlizeSocketUDP_Broadcast(int targetRobotID, int udpPort)
{
	Reset();

	mMode = M_SOCKETUDP_Broadcast;
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
bool Arduino::InitlizeESPSocketTCP_Connector(const std::string &ip, int port)
{
	Reset();

	mMode = M_ESP_SOCKETTCP_Connector;

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
bool Arduino::InitlizeSocketTCP_Connector(ClientConnector *clientConnector)
{
	Reset();

	mMode = M_SOCKETTCP_Connector;

	if (mConnector)
	{
		mConnector->Disconnect();
		mConnector = 0;
	}

	mConnector = clientConnector;

	return true;
}
//---------------------------------------------------------------------------
bool Arduino::InitlizeEmpty()
{
	Reset();

	mMode = M_EMPTY;

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
	else if (M_ESP_SOCKETTCP_Connector == mMode)
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
	mIsBlockLoopDoBreak = true;
	mBlockLoopUpdateTimes = 0;

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

	for (int i = 0; i < NUMDISTMAT; i++)
	{
		mDistMat[i] = 0;
	}

	Bluetooth *bth = Bluetooth::GetSingletonPtr();
	if (bth)
	{
		bth->AddCMDCallback(_Less4Process);
	}

	mIsEverSetTime = false;
	mEverSetTime = 0.0f;
}
//----------------------------------------------------------------------------
void Arduino::_SetTime()
{
	std::string opStr = sOptTypeStr[OT_SET_TIME];
	std::string sendStr = opStr;

	_Send(sendStr + mEndStr);
	mArduinoSetTime = Timestamp();
}
//----------------------------------------------------------------------------
Arduino::AxisObj::AxisObj()
{
	IsValied = false;

	AX = 0.0f;
	AY = 0.0f;
	AZ = 0.0f;
	P = 0.0f;
	R = 0.0f;
	Y = 0.0f;
}
//----------------------------------------------------------------------------
Arduino::AxisObj::~AxisObj()
{
}
//---------------------------------------------------------------------------
std::vector<Arduino::AxisObj> &Arduino::GetAxisObjs()
{
	return mAxisObjs;
}
//---------------------------------------------------------------------------
Arduino::AxisObj Arduino::GetCurAxisObj()
{
	return mCurAxisObj;
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

		if (!mIsEverSetTime)
		{
			mEverSetTime += elapsedSeconds;
			if (mEverSetTime > 2.0f)
			{
				_SetTime();
				mIsEverSetTime = true;
			}
		}
	}

	if (mConnector)
	{
		mConnector->Update(elapsedSeconds);

		if (CONNSTATE_CONNECTED == mConnector->GetConnectState())
		{
			if (!mIsEverSetTime)
			{
				_SetTime();
				mIsEverSetTime = true;
			}
		}
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
	if ("P_0" == str)
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
bool Arduino::_HighLow2Bool(const std::string &str)
{
	return str=="high" ? true : false;
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
	 if ("go" == str)
	 {
		 return SDT_FORWARD;
	 }
	 else if ("back" == str)
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
	std::string opStr = sOptTypeStr[OT_RETURN_DR];
	std::string pinStr = _Pin2Str(pin);

	std::string sendStr = opStr + " " + pinStr;

	_Send(sendStr + mEndStr);

	mIsBlockLoopDoBreak = false;

	while (!mIsBlockLoopDoBreak && mBlockLoopUpdateTimes<1000)
	{
		Update(0.001f);
		System::SleepSeconds(0.001f);
		mBlockLoopUpdateTimes++;

	}

	return mPinValue[pin]>0 ? 1:0;
}
//----------------------------------------------------------------------------
int Arduino::AnalogRead(Pin pin)
{
	std::string opStr = sOptTypeStr[OT_RETURN_AR];
	std::string pinStr = _Pin2Str(pin);

	std::string sendStr = opStr + " " + pinStr;

	_Send(sendStr + mEndStr);

	mIsBlockLoopDoBreak = false;

	while (!mIsBlockLoopDoBreak && mBlockLoopUpdateTimes < 1000)
	{
		Update(0.001f);
		System::SleepSeconds(0.001f);
		mBlockLoopUpdateTimes++;
	}

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

	mIsBlockLoopDoBreak = false;

	while (!mIsBlockLoopDoBreak && mBlockLoopUpdateTimes < 1000)
	{
		Update(0.001f);
		System::SleepSeconds(0.001f);
		mBlockLoopUpdateTimes++;
	}
}
//----------------------------------------------------------------------------
float Arduino::GetDist() const
{
	return mDist;
}
//----------------------------------------------------------------------------
void Arduino::ServerInit(int i, Pin pin)
{
	if (0 <= i && i < 5)
	{
		std::string sendStr = sOptTypeStr[OT_SVR_I];
		sendStr += " " + StringHelp::IntToString(i) + " " + _Pin2Str(pin);

		_Send(sendStr + mEndStr);
	}
}
//----------------------------------------------------------------------------
void Arduino::ServerWrite(int i, int val)
{
	if (0 <= i && i < 5)
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
void Arduino::DistMatInit(int i, Pin pinTrig, Pin pinEcho)
{
	std::string sendStr = sOptTypeStr[OT_DSTMAT_I];

	sendStr += StringHelp::IntToString(i) + " " + _Pin2Str(pinTrig) + " " 
		+ _Pin2Str(pinEcho);

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
float Arduino::GetMatDist(int i) const
{
	if (0 <= i && i < NUMDISTMAT)
	{
		return mDistMat[i];
	}

	return 0.0f;
}
//----------------------------------------------------------------------------
void Arduino::AxisInit()
{
	mYAxis = 0.0f;
	mXAxis = 0.0f;
	mZAxis = 0.0f;
	mPitch = 0.0f;
	mRoll = 0.0f;
	mYaw = 0.0f;

	std::string sendStr = sOptTypeStr[OT_AXIS_I];

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
float Arduino::AxisGetYAxis() const
{
	return mYAxis;
}
//----------------------------------------------------------------------------
float Arduino::AxisGetXAxis() const
{
	return mXAxis;
}
//----------------------------------------------------------------------------
float Arduino::AxisGetZAxis() const
{
	return mZAxis;
}
//----------------------------------------------------------------------------
float Arduino::AxisGetPitch() const
{
	return mPitch;
}
//----------------------------------------------------------------------------
float Arduino::AxisGetRoll() const
{
	return mRoll;
}
//----------------------------------------------------------------------------
float Arduino::AxisGetYaw() const
{
	return mYaw;
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
const std::string &Arduino::GetLastSendContentString() const
{
	return mLastSendContentString;
}
//----------------------------------------------------------------------------
const std::string &Arduino::GetLastSendString() const
{
	return 	mLastSendString;
}
//----------------------------------------------------------------------------
void Arduino::MCSegmentSet(int pin, int val)
{
	std::string sendStr = sOptTypeStr[OT_MC_SEGMENT];
	sendStr += " " + _Int2Str(pin) + " " + StringHelp::IntToString(val);

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::MCMoto(int pin, int speed)
{
	std::string sendStr = sOptTypeStr[OT_MC_MOTO];
	sendStr += " " + _Int2Str(pin) + " " + StringHelp::IntToString(speed);

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::MCTestDist(int pin)
{
	std::string sendStr = sOptTypeStr[OT_MC_DISTTEST];
	sendStr += " " + _Int2Str(pin);

	_Send(sendStr + mEndStr);
}
//----------------------------------------------------------------------------
void Arduino::MBotInit()
{

}
//----------------------------------------------------------------------------
void Arduino::MBotMoto(int leftRight, int speed)
{
}
//----------------------------------------------------------------------------
void Arduino::MBotIRSend(int val)
{
}
//----------------------------------------------------------------------------
void Arduino::MBotIRBuzzer(bool on)
{
}
//----------------------------------------------------------------------------
void Arduino::MBotIsButtonPressed() const
{
}
//----------------------------------------------------------------------------
int Arduino::MBotGetLightSensorValue() const
{
	return 0;
}
//----------------------------------------------------------------------------
void Arduino::_Send(const std::string &cmdStr)
{
	mLastSendContentString = cmdStr;
	std::string lastCmdStr = "0000" + cmdStr;
	mLastSendString = lastCmdStr;

	if (M_SERIAL == mMode)
	{
		mSerial.Write(lastCmdStr);
	}
	else if (M_BLUETOOTH == mMode)
	{
		PX2_BLUETOOTH.Send(lastCmdStr);
	}
	else if (M_SOCKETUDP_Broadcast == mMode)
	{
		int allLength = 2 + cmdStr.length();
		*(unsigned short *)(&lastCmdStr[0]) = (unsigned short)allLength; // length
		*(unsigned short *)(&lastCmdStr[2]) = (unsigned short)2; // GeneralServerMsgID

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
	else if (M_ESP_SOCKETTCP_Connector == mMode)
	{
		if (mConnector && !lastCmdStr.empty())
		{
			mConnector->GetSocket().SendBytes(lastCmdStr.c_str(), (int)lastCmdStr.length());
		}
	}
	else if (M_SOCKETTCP_Connector == mMode)
	{
		if (mConnector && !mLastSendContentString.empty())
		{
			mConnector->SendMsgToServerBuffer(Arduino_SocketTCP_MsgID,
				mLastSendContentString.c_str(),
				(int)mLastSendContentString.length());
			//mConnector->Update(0.0f);
		}
	}

	_OnToSendCallback(lastCmdStr);
}
//----------------------------------------------------------------------------