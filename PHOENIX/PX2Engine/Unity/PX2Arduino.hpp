// PX2Arduino.hpp

#ifndef PX2ARDUINO_HPP
#define PX2ARDUINO_HPP

#include "PX2UnityPre.hpp"
#include "PX2Object.hpp"
#include "PX2Bluetooth.hpp"
#include "PX2Singleton_NeedNew.hpp"
#include "PX2Serial.hpp"
#include "PX2NetClientConnector.hpp"
#include "PX2NetServer.hpp"
#include "PX2Timestamp.hpp"

namespace PX2
{

	typedef void(*ArduinoToSendCallback) (const std::string &callback);

	const int Arduino_SocketTCP_MsgID = 7;

	enum ArduinoRectType
	{
		ART_RECT_DIST,
		ART_RECV_IR,
		ART_MAXZ_TYPE
	};
	typedef void(*ArduinoReceiveCallback) (ArduinoRectType type, int val);

	#define NUMDISTMAT 6
	
	class PX2_ENGINE_ITEM Arduino : public Object, public Singleton<Arduino>
	{
	public:
		Arduino();
		virtual ~Arduino();

		enum Mode
		{
			M_SERIAL,
			M_BLUETOOTH,
			M_SOCKETUDP_Broadcast,
			M_ESP_SOCKETTCP_Connector, // ESP8266
			M_SOCKETTCP_Connector, // SocketTCP_MsgID
			M_EMPTY,
			M_MAX_TYPE
		};

		void Reset();
		bool Initlize(Mode mode, const std::string &port="", int baudrate = 9600);
		bool InitlizeSocketUDP_Broadcast(int targetRobotID, int udpPort);
		bool InitlizeESPSocketTCP_Connector(const std::string &ip = "192.168.4.1", int port = 8888);
		bool InitlizeSocketTCP_Connector(ClientConnector *clientConnector);
		bool InitlizeEmpty();
		bool IsInitlized();
		void Terminate();

		void Update(float elapsedSeconds);

		void SendToGetNetID();
		void SetNetID(int id);
		int GetNetID() const;

		Mode GetMode() const;
		Serial &GetSerial();

		bool AddArduinoReceiveCallbacks(ArduinoReceiveCallback callback);
		bool IsHasArduinoReceiveCallback(ArduinoReceiveCallback callback) const;
		bool AddScriptHandler(const std::string &handler);

		// arduino used -------------------------
	public:
		enum Pin
		{
			P_0 = 0,
			P_1,
			P_2,
			P_3,
			P_4,
			P_5,
			P_6,
			P_7,
			P_8,
			P_9,
			P_10,
			P_11,
			P_12,
			P_13,
			P_A0,
			P_A1,
			P_A2,
			P_A3,
			P_A4,
			P_A5,
			P_A6,
			P_MAX_TYPE
		};

		enum PMode
		{
			PM_INPUT,
			PM_OUTPUT,
			PM_MAX_TYPE
		};
		static std::string PinStr[P_MAX_TYPE];
		static std::string PModeStr[PM_MAX_TYPE];

		void PinMode(Pin pin, PMode mode);
		void DigitalWrite(Pin pin, bool isHigh = true);
		void AnalogWrite(Pin pin, int val);
		int DigitalRead(Pin pin);
		int AnalogRead(Pin pin);

		// server
		void ServerInit(int i, Pin pin);
		void ServerWrite(int i, int val);

		// dist
		void DistInit(Pin pinTrig, Pin pinEcho);
		void DistTest();
		float GetDist() const;

		// vehicle
		void VehicleInitMotoBoard();
		void VehicleInitMotoBoard4567();
		void VehicleInitMotoBoard298N(Pin pinLA, Pin pinLB, Pin pinLS, Pin pinRA, Pin pinRB, Pin pinRS);
		// pinLA D2
		// pinRA D3
		void VehicleSpeedInit(Pin pinLA, Pin pinLB, Pin pinRA, Pin pinRB);
		enum DirectionType
		{
			DT_NONE,
			DT_FORWARD,
			DT_BACKWARD,
			DT_MAX_TYPE
		};
		static std::string sDirectionTypeStr[DT_MAX_TYPE];

		enum SimpleDirectionType
		{
			SDT_NONE,
			SDT_FORWARD,
			SDT_BACKWARD,
			SDT_LEFT,
			SDT_RIGHT,
			SDT_MAX_TYPE
		};
		static std::string sSimpleDirectionTypeStr[SDT_MAX_TYPE];

		void Run(int motoIndex, DirectionType type, int speed);
		void Run(SimpleDirectionType dt, int speed);
		int GetSpeed(int motoIndex) const;
		void Stop();

		void MP3Init(Pin pinR, Pin pinT);
		void MP3Play();
		void MP3PlayNext();
		void MP3PlayAtIndex(int index);
		void MP3SetVolume(int volume);
		void MP3Stop();

		void IRInit(Pin pinReceive);
		void IRSend(int val);
		int GetIRReceive() const;

		void WeightInit(int i, Pin pinOut, Pin pinClk);
		void WeightTest(int i);
		float GetWeight(int i);

		void DistMatInit(int i, Pin pinTrig, Pin pinEcho);
		float GetMatDist(int i) const;

		void AxisInit();
		float AxisGetYAxis() const;
		float AxisGetXAxis() const;
		float AxisGetZAxis() const;
		float AxisGetPitch() const;
		float AxisGetRoll() const;
		float AxisGetYaw() const;

		bool AddArduinoToSendCallback(ArduinoToSendCallback callback);
		bool IsHasArduinoToSendCallback(ArduinoToSendCallback callback) const;

		const std::string &GetLastSendContentString() const;
		const std::string &GetLastSendString() const;

	public_internal:
		void _Send(const std::string &str);
		void _SetDist(float dist);
		void _SetIRReceive(int irReceive);
		void _SetPinVal(Pin pin, int val);
		void _SetWeight(int index, float weight);
		void _SetSpeedLR(int left, int right);
		void _SetDistMat(int index, float val);
		void _SetAxis(unsigned long timeMilliseconds, float yAxis, float xAxis, float zAxis, float pitch,
			float roll, float yaw);

		enum OptionType
		{
			OT_TOGET_NETID, // phoenixframe
			OT_RETURN_NETID,
			OT_PM,
			OT_DW,
			OT_AW,
			OT_RETURN_DR,
			OT_RETURN_AR,
			OT_SVR_I,
			OT_SVR_W,
			OT_DST_I,
			OT_DST_T, // ·ÏÆú
			OT_RETURN_DIST,
			OT_MOTO_I,
			OT_MOTO_RUN,
			OT_MOTO_RUNSIMPLE,
			OT_MOTO_STOP,
			OT_MOTO_I_SPD,
			OT_RETURN_MOTOSPD,
			OT_MOTO_I_DRIVER4567,
			OT_MOTO_I_DRIVER298N,
			OT_MP3_INIT,
			OT_MP3_PLAY,
			OT_MP3_INDEX,
			OT_MP3_NEXT,
			OT_MP3_STOP,
			OT_MP3_VOLUME,
			OT_IR_INIT,
			OT_IR_SEND,
			OT_RETURN_IR,
			OT_HX711_I,
			OT_HX711_TEST,
			OT_RETURN_HX711,
			OT_DSTMAT_I,
			OT_RETURN_DSTMAT,
			OT_AXIS_I,
			OT_RETURN_AXIS,
			OT_SET_TIME,
			OT_MC_INTERNAL_LIGHT, // makerclock
			OT_MC_LIGHT,
			OT_MC_SEGMENT,
			OT_MC_MOTO,
			OT_MC_DISTTEST,
			OT_MB_MOTO,	// mbot
			OT_MB_SEND,
			OT_MB_BUZZER,
			OT_MAX_TYPE
		};
		static std::string sOptTypeStr[OT_MAX_TYPE];

		static std::string _Pin2Str(Pin pin);
		static std::string _PinMode2Str(PMode pm);
		static std::string _Bool2Str(bool bVal);
		static std::string _Int2Str(int val);
		static std::string _DirectionType2Str(DirectionType dt);
		static std::string _SimpleDirectionType2Str(SimpleDirectionType dt);

		static Pin _NetStr2Pin(const std::string &str);
		static PMode _NetStr2PinMode(const std::string &str);
		static bool _NetStr2Bool(const std::string &str);
		static bool _HighLow2Bool(const std::string &str);
		static int _NetStr2Int(const std::string &str);
		static float _NetStr2Float(const std::string &str);
		static DirectionType _NetStr2Dir(const std::string &str);
		static SimpleDirectionType _NetStr2SimpleDir(const std::string &str);

		class PX2_ENGINE_ITEM AxisObj
		{
		public:
			AxisObj();
			~AxisObj();

			bool IsValied;
			Timestamp TStamp;
			float AX;
			float AY;
			float AZ;
			float P;
			float R;
			float Y;
		};

		std::vector<AxisObj> &GetAxisObjs();
		AxisObj GetCurAxisObj();

	private:
		void _OnCallback(ArduinoRectType type, int value);
		void _OnToSendCallback(const std::string &str);
		void _SetTime();

		bool mIsBlockLoopDoBreak;
		int mBlockLoopUpdateTimes;

		std::vector<ArduinoReceiveCallback> mCallbacks;
		std::vector<std::string> mRecvHandlers;

		std::vector<ArduinoToSendCallback> mToSendCallbacks;

		Mode mMode;
		int mNetID;
		int mTargetRobotID;
		int mRobotUDPPort;
		std::string mTcpIP;
		int mTcpPort;

		bool mIsEverSetTime;
		float mEverSetTime;
		Timestamp mArduinoSetTime;

		std::string mEndStr;

		Serial mSerial;
		ClientConnectorPtr mConnector;
		Server *mServer;

		float mDist;
		int mIRReceive;

		float mWeight[4];

		int mPinValue[P_MAX_TYPE];
		int mSpeed[4];

		std::string mLastSendContentString;
		std::string mLastSendString;

		float mDistMat[NUMDISTMAT];

		std::vector<AxisObj> mAxisObjs;
		AxisObj mCurAxisObj;
		float mYAxis;
		float mXAxis;
		float mZAxis;
		float mPitch;
		float mRoll;
		float mYaw;

		// makeblock
	public:
		void MCSegmentSet(int pin, int val);
		void MCMoto(int pin, int speed);
		void MCTestDist(int pin);

		// mbot
	public:
		void MBotInit();
		void MBotMoto(int leftRight, int speed);
		
		void MBotIRSend(int val);
		int MBotIRGetReceivedValue();

		void MBotIRBuzzer(bool on);
		void MBotIsButtonPressed() const;
		int MBotGetLightSensorValue() const;
	};

#define PX2_ARDUINO Arduino::GetSingleton()

}

#endif