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

		void Initlize(Mode mode, const std::string &port="", int baudrate = 9600);
		void Terminate();
		void Update(float elapsedSeconds);

		Mode GetMode() const;

	private:

		Serial mSerial;
		Mode mMode;
		
		bool mIsCombining;
		std::string mCombingStr;
	};

#define PX2_ARDUINO Arduino::GetSingleton()

}

#endif