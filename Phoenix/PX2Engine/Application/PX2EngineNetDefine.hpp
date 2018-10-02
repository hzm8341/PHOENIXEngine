// PX2EngineNetDefine.hpp

#ifndef PX2ENGINENETDEFINE_HPP
#define PX2ENGINENETDEFINE_HPP

#include "PX2CorePre.hpp"
#include "PX2Arduino.hpp"

namespace PX2
{

	const int EngineServerMsgID = 3;
	const int EngineServerSendMapInfoMsgID = 4;
	const int EngineServerSendMapMsgID = 5;
	const int EngineServerSendMapEndMsgID = 6;

	const int EngineServerArduinoMsgID = Arduino_SocketTCP_MsgID;

	const float EngineClientHeartTime = 5.0f;
	const int EngineServerPort = 9907;
	const float EngineServerHeartTime = 20.0f;

	const int EngineUDPPortClient = 9908;
	const int EngineUDPPortServerEditor = 9909;
	const float EngineUDPSendInfoTime = 1.0f;

	const int EngineUDPPortHttp = 9919;

	const std::string CMD_EngineUDPInfoTag = "myudpinfo";
	const std::string CMD_EngineUDPInfoCamera = "camera";
	const std::string CMD_EngineUDPConnectMeStr = "connectme";
	const std::string CMD_PushProject = "pushproject";
	const std::string CMD_LoadProject = "loadproject";
	const std::string CMD_CloseProject = "closeproject";

}

#endif