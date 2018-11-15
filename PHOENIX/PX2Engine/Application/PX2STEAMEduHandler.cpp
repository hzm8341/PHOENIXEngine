// PX2STEAMEduHandler.cpp

#include "PX2STEAMEdu.hpp"
#include "PX2DateTime.hpp"
#include "PX2Base64.hpp"
#include "PX2StringTokenizer.hpp"
#include "PX2FileIO.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2Arduino.hpp"
#include "PX2STEAMEdu.hpp"
#include "PX2WebSocket.hpp"
#include "PX2NetException.hpp"
#include "PX2PlatformSDK.hpp"
#include "PX2ScopedCS.hpp"
#include "PX2Application.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
STEAMEduHandlerFactory::STEAMEduHandlerFactory()
{
}
//----------------------------------------------------------------------------
HTTPRequestHandler * STEAMEduHandlerFactory::CreateRequestHandler(
	const HTTPServerRequest &request)
{
	if (request.find("Upgrade") != request.end() && Icompare(request["Upgrade"], "websocket") == 0)
		return new0 WebSocketRequestHandler;
	else
	{
		return new0 Snap_RequestHandler();
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
Snap_RequestHandler::Snap_RequestHandler()
{
	mMCPins.push_back(std::pair<std::string, std::string>("10", "11")); // 1
	mMCPins.push_back(std::pair<std::string, std::string>("9", "3")); // 2
	mMCPins.push_back(std::pair<std::string, std::string>("13", "12")); // 3
	mMCPins.push_back(std::pair<std::string, std::string>("2", "8")); // 4
	mMCPins.push_back(std::pair<std::string, std::string>("0", "1")); // 5
	mMCPins.push_back(std::pair<std::string, std::string>("A3", "A2")); // 6
	mMCPins.push_back(std::pair<std::string, std::string>("A1", "A6")); // 7
	mMCPins.push_back(std::pair<std::string, std::string>("A0", "A7")); // 8
	mMCPins.push_back(std::pair<std::string, std::string>("6", "7")); // 9
	mMCPins.push_back(std::pair<std::string, std::string>("4", "5")); // 10
}
//----------------------------------------------------------------------------
Snap_RequestHandler::~Snap_RequestHandler()
{
}
//----------------------------------------------------------------------------
void _StrToPin(const std::string &paramStr, int &pin, bool &isA)
{
	if ('a' == paramStr[0] || 'A' == paramStr[0])
	{
		isA = true;
		std::string subStr = paramStr.substr(1, paramStr.length() - 1);
		pin = StringHelp::StringToInt(subStr);
	}
	else
	{
		pin = StringHelp::StringToInt(paramStr);
	}
}
//----------------------------------------------------------------------------
void Snap_RequestHandler::HandleRequest(HTTPServerRequest& request,
	HTTPServerResponse& response)
{
	ScopedCS cs(&Application::ThreadUpdateMutex);

	// ÔÊÐí¿çÓò!
	std::string url = request.GetURI();

	StringTokenizer stkQuestion(url, "?");
	if (stkQuestion.Count() > 1)
	{
		int outLength = 0;
		std::string valStr = Base64::Decode(stkQuestion[1], outLength);
		StringTokenizer stkEqual(valStr, "$");

		std::string cmdStr;
		std::string contentStr;
		if (stkEqual.Count() > 0)
			cmdStr = stkEqual[0];
		if (stkEqual.Count() > 1)
			contentStr = stkEqual[1];

		bool findLib = (std::string::npos != cmdStr.find("libraries"));
		bool findBlockly = (std::string::npos != cmdStr.find("blockly_"));

		if (findLib)
		{
			response.add("Access-Control-Allow-Origin", "*");
			std::string path = "Data/CodeSnap/codesnap/www/" + cmdStr;
			response.SendFile(path, "file");
		}
		else if ("Costumes/COSTUMES" == cmdStr)
		{
			response.add("Access-Control-Allow-Origin", "*");
			response.SendFile("Data/CodeSnap/codesnap/www/Costumes/", "file");
		}
		else if ("tools.xml" == cmdStr)
		{
			response.add("Access-Control-Allow-Origin", "*");
			response.SendFile("Data/CodeSnap/codesnap/www/tools.xml", "file");
		}
		else if ("device" == cmdStr)
		{
			if ("list" == contentStr)
			{
				std::string sendCnt;

				Serial serial;
				auto lst = serial.GetPortList();
				for (int i = 0; i < (int)lst.size(); i++)
				{
					sendCnt += lst[i];

					if (i != (int)(lst.size() - 1))
						sendCnt += "_";
				}

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << sendCnt;

				return;
			}
			else
			{
				std::string strParam0;
				std::string strParam1;
				std::string strParam2;

				StringTokenizer stk_(contentStr, "_");
				if (stk_.Count() > 0)
					strParam0 = stk_[0];
				if (stk_.Count() > 1)
					strParam1 = stk_[1];
				if (stk_.Count() > 2)
					strParam2 = stk_[2];

				if ("connect" == strParam0)
				{
					PX2_ARDUINO.Terminate();
					PX2_ARDUINO.Initlize(Arduino::M_SERIAL, strParam1, 9600);

					response.add("Access-Control-Allow-Origin", "*");
					std::ostream& ostr = response.Send();

					if (PX2_ARDUINO.IsInitlized())
						ostr << "suc";
					else
						ostr << "failed";

					return;
				}
				else if ("connectwifi" == strParam0)
				{
					PX2_ARDUINO.Terminate();
					PX2_ARDUINO.InitlizeESPSocketTCP_Connector();

					response.add("Access-Control-Allow-Origin", "*");
					std::ostream& ostr = response.Send();

					if (PX2_ARDUINO.IsInitlized())
						ostr << "suc";
					else
						ostr << "failed";

					return;
				}
				else if ("disconnect" == strParam0)
				{
					PX2_ARDUINO.Terminate();

					response.add("Access-Control-Allow-Origin", "*");
					std::ostream& ostr = response.Send();
					ostr << "suc";

					return;
				}
			}
		}
		else if ("phoenix" == cmdStr)
		{
			std::string strParam0;
			StringTokenizer stk_(contentStr, ",");
			if (stk_.Count() > 0)
				strParam0 = stk_[0];

			if ("777" == strParam0)
			{
				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "abcdefg";
			}
			else if ("1001" == strParam0)
			{
				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << PX2_PFSDK.RinGUN_GetCMD();
			}
			else if ("1002" == strParam0)
			{
				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << PX2_PFSDK.RinGun_GetPosX();
			}
			else if ("1003" == strParam0)
			{
				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << PX2_PFSDK.RinGun_GetPosY();
			}
			else if ("1004" == strParam0)
			{
				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << PX2_PFSDK.RinGun_IsFiring();
			}
		}
		else if ("arduino" == cmdStr)
		{
			std::string strParam0;
			std::string strParam1;
			std::string strParam2;
			std::string strParam3;
			std::string strParam4;
			std::string strParam5;
			std::string strParam6;
			std::string strParam7;
			std::string strParam8;
			std::string strParam9;
			std::string strParam10;

			StringTokenizer stk_(contentStr, ",");
			if (stk_.Count() > 0)
				strParam0 = stk_[0];
			if (stk_.Count() > 1)
				strParam1 = stk_[1];
			if (stk_.Count() > 2)
				strParam2 = stk_[2];
			if (stk_.Count() > 3)
				strParam3 = stk_[3];
			if (stk_.Count() > 4)
				strParam4 = stk_[4];
			if (stk_.Count() > 5)
				strParam5 = stk_[5];
			if (stk_.Count() > 6)
				strParam6 = stk_[6];
			if (stk_.Count() > 7)
				strParam7 = stk_[7];
			if (stk_.Count() > 8)
				strParam8 = stk_[8];
			if (stk_.Count() > 9)
				strParam9 = stk_[9];
			if (stk_.Count() > 10)
				strParam10 = stk_[10];

			//OT_PM,
			//OT_DW,
			//OT_AW,
			//OT_RETURN_DR,
			//OT_RETURN_AR,
			//OT_SVR_I,
			//OT_SVR_W,
			//OT_DST_I,
			//OT_DST_T,
			//OT_RETURN_DIST,
			//OT_MOTO_I,
			//OT_MOTO_RUN,
			//OT_MOTO_RUNSIMPLE,
			//OT_MOTO_STOP,

			if (Arduino::sOptTypeStr[Arduino::OT_PM] == strParam0)
			{
				Arduino::Pin pin = Arduino::_NetStr2Pin(strParam1);
				Arduino::PMode pm = Arduino::_NetStr2PinMode(strParam2);

				PX2_ARDUINO.PinMode(pin, pm);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_DW] == strParam0)
			{
				Arduino::Pin pin = Arduino::_NetStr2Pin(strParam1);
				bool val = Arduino::_HighLow2Bool(strParam2);

				PX2_ARDUINO.DigitalWrite(pin, val);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_AW] == strParam0)
			{
				Arduino::Pin pin = Arduino::_NetStr2Pin(strParam1);
				int val = Arduino::_NetStr2Int(strParam2);

				PX2_ARDUINO.AnalogWrite(pin, val);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_RETURN_DR] == strParam0)
			{
				Arduino::Pin pin = Arduino::_NetStr2Pin(strParam1);
				int val = PX2_ARDUINO.DigitalRead(pin);


				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << val;
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_RETURN_AR] == strParam0)
			{
				Arduino::Pin pin = Arduino::_NetStr2Pin(strParam1);
				int val = PX2_ARDUINO.AnalogRead(pin);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << val;
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_SVR_I] == strParam0)
			{
				int svrIndex = Arduino::_NetStr2Int(strParam1);
				Arduino::Pin pin = Arduino::_NetStr2Pin(strParam2);

				PX2_ARDUINO.ServerInit(svrIndex, pin);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_SVR_W] == strParam0)
			{
				int svrIndex = Arduino::_NetStr2Int(strParam1);
				int val = Arduino::_NetStr2Int(strParam2);

				PX2_ARDUINO.ServerWrite(svrIndex, val);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_DST_I] == strParam0)
			{
				Arduino::Pin pinTrigger = Arduino::_NetStr2Pin(strParam1);
				Arduino::Pin pinEcho = Arduino::_NetStr2Pin(strParam2);

				PX2_ARDUINO.DistInit(pinTrigger, pinEcho);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_DST_T] == strParam0)
			{
				PX2_ARDUINO.DistTest();

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_RETURN_DIST] == strParam0)
			{
				PX2_ARDUINO.DistTest();
				float dst = PX2_ARDUINO.GetDist();

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << dst;
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_MOTO_I] == strParam0)
			{
				PX2_ARDUINO.VehicleInitMotoBoard();

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_MOTO_RUN] == strParam0)
			{
				int mi = Arduino::_NetStr2Int(strParam1);
				Arduino::DirectionType dt = Arduino::_NetStr2Dir(strParam2);
				int speed = Arduino::_NetStr2Int(strParam3);
				PX2_ARDUINO.Run(mi, dt, speed);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_MOTO_RUNSIMPLE] == strParam0)
			{
				Arduino::SimpleDirectionType sdt = Arduino::_NetStr2SimpleDir(strParam1);
				int speed = Arduino::_NetStr2Int(strParam2);
				PX2_ARDUINO.Run(sdt, speed);

   				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_MOTO_STOP] == strParam0)
			{
				PX2_ARDUINO.Stop();

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_MOTO_I_SPD] == strParam0)
			{
				Arduino::Pin pin0 = Arduino::_NetStr2Pin(strParam1);
				Arduino::Pin pin1 = Arduino::_NetStr2Pin(strParam2);
				Arduino::Pin pin2 = Arduino::_NetStr2Pin(strParam3);
				Arduino::Pin pin3 = Arduino::_NetStr2Pin(strParam4);
				PX2_ARDUINO.VehicleSpeedInit(pin0, pin1, pin2, pin3);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_RETURN_MOTOSPD] == strParam0)
			{
				int index = Arduino::_NetStr2Int(strParam1);
				int speed = PX2_ARDUINO.GetSpeed(index);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << speed;
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_MOTO_I_DRIVER4567] == strParam0)
			{
				PX2_ARDUINO.VehicleInitMotoBoard4567();

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_MOTO_I_DRIVER298N] == strParam0)
			{
				Arduino::Pin pinL0 = Arduino::_NetStr2Pin(strParam1);
				Arduino::Pin pinL1 = Arduino::_NetStr2Pin(strParam2);
				Arduino::Pin pinLS = Arduino::_NetStr2Pin(strParam3);
				Arduino::Pin pinR0 = Arduino::_NetStr2Pin(strParam4);
				Arduino::Pin pinR1 = Arduino::_NetStr2Pin(strParam5);
				Arduino::Pin pinRS = Arduino::_NetStr2Pin(strParam6);

				PX2_ARDUINO.VehicleInitMotoBoard298N(pinL0, pinL1, pinLS, pinR0, pinR1, pinRS);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_MP3_INIT] == strParam0)
			{
				Arduino::Pin pinR = Arduino::_NetStr2Pin(strParam1);
				Arduino::Pin pinT = Arduino::_NetStr2Pin(strParam2);

				PX2_ARDUINO.MP3Init(pinR, pinT);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_MP3_PLAY] == strParam0)
			{
				PX2_ARDUINO.MP3Play();

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_MP3_INDEX] == strParam0)
			{
				int index = Arduino::_NetStr2Int(strParam1);
				PX2_ARDUINO.MP3PlayAtIndex(index);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_MP3_NEXT] == strParam0)
			{
				PX2_ARDUINO.MP3PlayNext();

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_MP3_STOP] == strParam0)
			{
				PX2_ARDUINO.MP3Stop();

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_MP3_VOLUME] == strParam0)
			{
				int volume = Arduino::_NetStr2Int(strParam1);
				PX2_ARDUINO.MP3SetVolume(volume);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_IR_INIT] == strParam0)
			{
				Arduino::Pin pin = Arduino::_NetStr2Pin(strParam1);
				PX2_ARDUINO.IRInit(pin);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_IR_SEND] == strParam0)
			{
				int val = Arduino::_NetStr2Int(strParam1);
				PX2_ARDUINO.IRSend(val);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_HX711_I] == strParam0)
			{
				int index = Arduino::_NetStr2Int(strParam1);
				Arduino::Pin pinOut = Arduino::_NetStr2Pin(strParam2);
				Arduino::Pin pinClk = Arduino::_NetStr2Pin(strParam3);
				PX2_ARDUINO.WeightInit(index, pinOut, pinClk);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_HX711_TEST] == strParam0)
			{
				int index = Arduino::_NetStr2Int(strParam1);
				PX2_ARDUINO.WeightTest(index);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_RETURN_HX711] == strParam0)
			{
				int index = Arduino::_NetStr2Int(strParam1);
				float val = PX2_ARDUINO.GetWeight(index);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << val;
			}
		}
		else if ("makerclock" == cmdStr)
		{
			std::string strParam0;
			std::string strParam1;
			std::string strParam2;
			std::string strParam3;
			std::string strParam4;
			std::string strParam5;
			std::string strParam6;
			std::string strParam7;
			std::string strParam8;
			std::string strParam9;
			std::string strParam10;

			StringTokenizer stk_(contentStr, ",");
			if (stk_.Count() > 0)
				strParam0 = stk_[0];
			if (stk_.Count() > 1)
				strParam1 = stk_[1];
			if (stk_.Count() > 2)
				strParam2 = stk_[2];
			if (stk_.Count() > 3)
				strParam3 = stk_[3];
			if (stk_.Count() > 4)
				strParam4 = stk_[4];
			if (stk_.Count() > 5)
				strParam5 = stk_[5];
			if (stk_.Count() > 6)
				strParam6 = stk_[6];
			if (stk_.Count() > 7)
				strParam7 = stk_[7];
			if (stk_.Count() > 8)
				strParam8 = stk_[8];
			if (stk_.Count() > 9)
				strParam9 = stk_[9];
			if (stk_.Count() > 10)
				strParam10 = stk_[10];

			if (Arduino::sOptTypeStr[Arduino::OT_MC_INTERNAL_LIGHT] == strParam0)
			{
				int mcPin = 3;
				std::string strPin0 = mMCPins[mcPin - 1].first;
				std::string strPin1 = mMCPins[mcPin - 1].second;
				Arduino::Pin pin0 = Arduino::_NetStr2Pin(strPin0);
				Arduino::Pin pin1 = Arduino::_NetStr2Pin(strPin1);

				bool val = Arduino::_NetStr2Bool(strParam1);

				PX2_ARDUINO.PinMode(pin0, Arduino::PM_OUTPUT);
				PX2_ARDUINO.DigitalWrite(pin0, val);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_MC_LIGHT] == strParam0)
			{
				int mcPin = Arduino::_NetStr2Int(strParam1);
				bool isHigh = Arduino::_NetStr2Bool(strParam2);

				std::string strPin0 = mMCPins[mcPin - 1].first;
				std::string strPin1 = mMCPins[mcPin - 1].second;
				Arduino::Pin pin0 = Arduino::_NetStr2Pin(strPin0);
				Arduino::Pin pin1 = Arduino::_NetStr2Pin(strPin1);

				PX2_ARDUINO.PinMode(pin0, Arduino::PM_OUTPUT);
				PX2_ARDUINO.DigitalWrite(pin0, isHigh);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_MC_SEGMENT] == strParam0)
			{
				int mcPin = Arduino::_NetStr2Int(strParam1);
				int val = Arduino::_NetStr2Int(strParam2);

				PX2_ARDUINO.MCSegmentSet(mcPin, val);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_MC_MOTO] == strParam0)
			{
				int mcPin = Arduino::_NetStr2Int(strParam1);
				int val = Arduino::_NetStr2Int(strParam2);

				int pin = 9;
				if (1 == mcPin)
					pin = 9;
				else if (2 == mcPin)
					pin = 10;

				PX2_ARDUINO.MCMoto(pin, val);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_MC_DISTTEST] == strParam0)
			{
				int mcPin = Arduino::_NetStr2Int(strParam1);

				PX2_ARDUINO.MCTestDist(mcPin);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "suc";
			}
			else if (Arduino::sOptTypeStr[Arduino::OT_RETURN_DIST] == strParam0)
			{
				float dst = PX2_ARDUINO.GetDist();

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << dst;
			}
		}
		else if (findBlockly)
		{
			std::string strParam0;
			std::string strParam1;
			std::string strParam2;

			StringTokenizer stk_(cmdStr, "_");
			if (stk_.Count() > 0)
				strParam0 = stk_[0];
			if (stk_.Count() > 1)
				strParam1 = stk_[1];
			if (stk_.Count() > 2)
				strParam2 = stk_[2];

			std::string valStrCMD = strParam1;
			std::string valStrFilename = strParam2;

			// blockly
			if ("uploadArduino" == valStrCMD)
			{
				std::string writeablePath = ResourceManager::GetWriteablePath();

				std::string dstFilename = valStrFilename;
				std::string dstDir = dstFilename + "/";
				std::string dstFile = dstFilename + ".ino";
				PX2_RM.CreateFloder(writeablePath, dstDir);

				std::string dstFloderFilename = writeablePath + dstDir + dstFile;

				FileIO::Save(dstFloderFilename, false,
					contentStr.length(), contentStr.c_str());

				PX2_STEAMEDU.OpenArduino(dstFloderFilename);

				response.add("Access-Control-Allow-Origin", "*");
				std::ostream& ostr = response.Send();
				ostr << "";
			}
		}
		else
		{
			assertion(false, "can not go to here0");
		}
	}
	else
	{
		assertion(false, "can not go to here1");
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
WebSocketRequestHandler::WebSocketRequestHandler()
{

}
//----------------------------------------------------------------------------
WebSocketRequestHandler::~WebSocketRequestHandler()
{

}
//----------------------------------------------------------------------------
void WebSocketRequestHandler::HandleRequest(HTTPServerRequest& request,
	HTTPServerResponse& response)
{
	WebSocket ws(request, response);

	char buffer[1024];
	int flags;
	int n;
	do
	{
		n = ws.receiveFrame(buffer, sizeof(buffer), flags);
		if (n > 0)
		{
			ws.sendFrame(buffer, n, flags);
		}
	} while (n > 0 && (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE);
}
//----------------------------------------------------------------------------