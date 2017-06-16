// PX2ArduinoDefine.hpp

#ifndef PX2ARDUINODEFINE_HPP
#define PX2ARDUINODEFINE_HPP

#include "PX2UnityPre.hpp"
#include "PX2Arduino.hpp"

namespace PX2
{

#define ARDUINO_MAX_PACKET_SIZE 16

	class PX2_ENGINE_ITEM ArduinoMsg
	{
	public:
		ArduinoMsg();
		~ArduinoMsg();

		std::string ToString() const;

		void SetSourceAddress(uint8_t address);
		uint8_t GetSourceAddress() const;

		void SetTargetAddress(uint8_t address);
		uint8_t GetTargetAddress() const;

		void SetFrameNum(uint8_t num);
		int GetFrameNum() const;

		void SetLength(uint8_t length);
		int GetLength() const;

		enum CMDType
		{
			PIN_MODE = 2,
			DIGITAL_READ = 4,
			DIGITAL_WRITE = 3,
			ANALOG_REFERENCE = 6,
			ANALOG_READ = 7,
			ANALOG_WRITE = 9,
			TONE = 10,
			NO_TONE = 11,
			PULSE_IN = 12,
			PING = 66,
			ATTACH_INTERRUPT = 21,
			DETACH_INTERRUPT = 22,
			EEPROM__READ = 31,
			EEPROM__SYNC__WRITE = 34,
			EEPROM__WRITE = 33,
			DIGITAL_READ_RESULT = 5,
			ANALOG_READ_RESULT = 8,
			PULSE_IN_RESULT = 13,
			PONG = 67,
			INTERRUPT_NOTIFICATION = 23,
			EEPROM__VALUE = 32,
			EEPROM__WRITE__ACK = 35
		};
		void SetCMD(CMDType cmd);
		CMDType GetCMD() const;

		void AddByteValue(int8_t v);
		void AddShortValue(int16_t v);
		void AddIntValue(int32_t v);

		void SetData(const uint8_t *data, uint8_t length);

		void SetParamData(const uint8_t *data, uint8_t length);
		uint8_t *GetParamData() const;

		void SetNeedResult(bool isResult);
		bool IsNeedResult() const;

		static ArduinoMsg CreateMessageFromPacket(const std::string &packet);

		static ArduinoMsg CreateMsgPinMode(Arduino::Pin pin, Arduino::PinMode mode);
		static ArduinoMsg CreateDigitalReadMsg(Arduino::Pin pin);
		static ArduinoMsg CreateDigitalReadMsgResult(Arduino::Pin pin, int8_t val);
		static ArduinoMsg CreateDigitalWriteMsg(Arduino::Pin pin, Arduino::PinState state);
		static ArduinoMsg CreateAnalogReadMsg(Arduino::Pin pin);
		static ArduinoMsg CreateAnalogReadMsgResult(Arduino::Pin pin, int8_t val);
		static ArduinoMsg CreateAnalogWriteMsg(Arduino::Pin pin, int8_t val);

		uint8_t mBuffer[ARDUINO_MAX_PACKET_SIZE];

	private:
		int8_t mSetValueIndex;
		bool mIsNeedResult;
	};

}

#endif