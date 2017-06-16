// PX2Arduino.hpp

#ifndef PX2ARDUINO_HPP
#define PX2ARDUINO_HPP

#include "PX2UnityPre.hpp"
#include "PX2Object.hpp"
#include "PX2Serial.hpp"
#include "PX2Bluetooth.hpp"
#include "PX2Singleton_NeedNew.hpp"

namespace PX2
{

	class ArduinoMsg;

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
		void SetMode(Mode mode);
		Mode GetMode() const;

		enum Pin
		{
			PIN_0 = 0,
			PIN_1 = 1,
			PIN_2 = 2,
			PIN_3 = 3,
			PIN_4 = 4,
			PIN_5 = 5,
			PIN_6 = 6,
			PIN_7 = 7,
			PIN_8 = 8,
			PIN_9 = 9,
			PIN_10 = 10,
			PIN_11 = 11,
			PIN_12 = 12,
			PIN_13 = 13,
			A_0 = 14,
			A_1 = 15,
			A_2 = 16,
			A_3 = 17,
			A_4 = 18,
			A_5 = 19,
			PIN_MAX_TYPE
		};

		enum PinMode
		{
			INPUT = 0,
			OUTPUT = 1
		};

		enum PinState
		{
			LOW = 0,
			HIGH = 127
		};

		void init(const std::string &port, int baudrate=9600);
		void terminate();

		void pinMode(Pin pin, PinMode mode);

		int digitalRead(Pin pin);
		void digitalWrite(Pin pin, PinState state);

		int analogRead(Pin pin);
		void analogWrite(Pin pin, int val);

		void Update(float elapsedSeconds);

	private:
		void _SendMsg(const ArduinoMsg &msg);

		Serial mSerial;
		Mode mMode;
	};

#define PX2_ARDUINO Arduino

}

#endif