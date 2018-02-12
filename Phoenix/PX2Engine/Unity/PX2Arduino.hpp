// PX2Arduino.hpp

#ifndef PX2ARDUINO_HPP
#define PX2ARDUINO_HPP

#include "PX2UnityPre.hpp"
#include "PX2Object.hpp"
#include "PX2Bluetooth.hpp"
#include "PX2Singleton_NeedNew.hpp"
#include "PX2Serial.hpp"

namespace PX2
{
	
	class PX2_ENGINE_ITEM Arduino : public Singleton<Arduino>
	{
	public:
		Arduino();
		virtual ~Arduino();

		enum Mode
		{
			M_SERIAL,
			M_BLUETOOTH,
			M_WIFI_ROBOT,
			M_MAX_TYPE
		};

		bool Initlize(Mode mode, const std::string &port="", int baudrate = 9600);
		bool InitlizeForRobot(int targetRobotID, int udpPort);
		bool IsInitlized();
		void Terminate();
		void Update(float elapsedSeconds);

		Mode GetMode() const;
		Serial &GetSerial();

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

		// ir
		void IRRecvInit(Pin pin);
		void IRSendSony(int val = 1);
		int GetIRReceive() const;

		// vehicle
		void VehicleInitMotoBoard();
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

		void IRInit(Pin pinR);
		void IRSend(int val);

	public_internal:
		void _Send(const std::string &str);
		void _SetDist(float dist);
		void _SetIRReceive(int irReceive);
		void _SetPinVal(Pin pin, int val);
		void _SetSpeedLR(int left, int right);

		enum OptionType
		{
			OT_PM,
			OT_DW,
			OT_AW,
			OT_RETURN_DR,
			OT_RETURN_AR,
			OT_SVR_I,
			OT_SVR_W,
			OT_DST_I,
			OT_DST_T,
			OT_RETURN_DIST,
			OT_MOTO_I,
			OT_MOTO_RUN,
			OT_MOTO_RUNSIMPLE,
			OT_MOTO_STOP,
			OT_MP3_INIT,
			OT_MP3_PLAY,
			OT_MP3_INDEX,
			OT_MP3_NEXT,
			OT_MP3_STOP,
			OT_MP3_VOLUME,
			OT_IR_INIT,
			OT_IR_SEND,
			OT_RETRUN_IR,
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
		static int _NetStr2Int(const std::string &str);
		static float _NetStr2Float(const std::string &str);
		static DirectionType _NetStr2Dir(const std::string &str);
		static SimpleDirectionType _NetStr2SimpleDir(const std::string &str);

	private:
		void _Reset();

		Mode mMode;
		int mTargetRobotID;
		int mRobotUDPPort;
		std::string mArduinoString;
		std::string mEndStr;

		Serial mSerial;

		float mDist;
		int mIRReceive;

		int mPinValue[P_MAX_TYPE];
		int mSpeed[4];
	};

#define PX2_ARDUINO Arduino::GetSingleton()

}

#endif