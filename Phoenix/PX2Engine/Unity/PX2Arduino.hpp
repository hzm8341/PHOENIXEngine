// PX2Arduino.hpp

#ifndef PX2ARDUINO_HPP
#define PX2ARDUINO_HPP

#include "PX2UnityPre.hpp"
#include "PX2Object.hpp"
#include "PX2Bluetooth.hpp"
#include "PX2Singleton_NeedNew.hpp"
#include "PX2Serial.hpp"
#include "PX2Serial1.hpp"
#include "PX2Serial2.hpp"

namespace PX2
{
	
	class Serial;

	class PX2_ENGINE_ITEM Arduino : public Singleton<Arduino>
	{
	public:
		Arduino();
		virtual ~Arduino();

		enum Mode
		{
			M_SERIAL,
			M_BLUETOOTH,
			M_MAX_TYPE
		};

		bool Initlize(Mode mode, const std::string &port="", int baudrate = 9600);
		bool IsInitlized();
		void Terminate();
		void Update(float elapsedSeconds);

		Mode GetMode() const;
		Serial2 &GetSerial();

		// arduino used -------------------------
	public:
		void Begin();
		void End();

		// arduino
		void PinMode(int pinVal, bool isOutput=true, bool isA=false);
		void DigitalWrite(int pinVal, bool isHigh=true, bool isA=false);
		void AnalogWrite(int pinVal, int val, bool isA=false);
		int DigitalRead(int pinVal);
		int AnalogRead(int pinVal);

		// server
		void ServerInit(int pin = 10, bool isA = false);
		void Server1Init(int pin = 11, bool isA = false);
		void Server2Init(int pin = 12, bool isA = false);
		void ServerWrite(int val);
		void Server1Write(int val);
		void Server2Write(int val);

		// dist
		void DistInit(int pinTrig, int pinEcho, bool isA);
		void DistTest();
		float GetDist() const;

		// ir
		void IRRecvInit(int pin = 1, bool isAnalog = true);
		void IRSendNEC(int val = 1);
		void IRSendSony(int val = 1);
		int GetIRReceive() const;

		// mp3
		void Mp3Init(int pin0 = 5, int pin1 = 6);
		void Mp3Stop();
		void Mp3Volume(int val = 25);
		void Mp3Play(int index = 1);
		void Mp3Next();

		// vehicle
		void VehicleInit(int pinL0 = 4, int pinL1 = 5, int speedL = 3,
			int pinR0 = 7, int pinR1 = 8, int speedR = 9);
		void VehicleInitSimple();
		void Go(int speed);
		void Back(int speed);
		void Left(int speed);
		void Right(int speed);
		void Stop();

		void LeftRunType(int type);
		void LeftSpeed(int speed);
		void RightRunType(int type);
		void RightSpeed(int speed);

		// laser
		void LaserInit(int pin, bool isAnalog);
		void LaserTurn(bool isOn);

		// lcds
		void LEDInit(int din, int cs, int clk);
		void LEDSetFace(const std::string &faceStr);

		// RGBLight
		void RGBLightInit(int pinR, int pinG, int pinB, bool isAnglog);
		void RGBLight(int r, int g, int b);

	public_internal:
		void _Send(const std::string &str);
		void _SetDist(float dist);
		void _SetIRReceive(int irReceive);
		void _SetDigital(int pin, int val);
		void _SetAnalog(int pin, int val);

		static const int NumDR = 16;
		static const int NumAR = 8;

	private:
		void _Reset();

		Mode mMode;		
		bool mIsBeginArduino;
		std::string mArduinoString;
		std::string mEndStr;

		//Serial mSerial;
		//Serial1 mSerial;
		Serial2 mSerial;

		float mDist;
		int mIRReceive;

		int mDigitalRead[NumDR];
		int mAnalogRead[NumAR];
	};

#define PX2_ARDUINO Arduino::GetSingleton()

}

#endif