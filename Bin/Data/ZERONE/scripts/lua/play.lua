-- play.lua

require("Data/ZERONE/scripts/lua/language.lua")
require("Data/ZERONE/scripts/lua/ZERONE.lua")
require("Data/ZERONE/scripts/lua/ZERONECommon.lua")
require("Data/ZERONE/scripts/lua/ZERONEConnectBleSerial.lua")
require("Data/ZERONE/scripts/lua/ZERONEConnectLidar.lua")
require("Data/ZERONE/scripts/lua/ZERONEConnectDevice.lua")
require("Data/ZERONE/scripts/lua/ZERONESetting.lua")
require("Data/ZERONE/scripts/lua/ZERONEScene.lua")
require("Data/ZERONE/scripts/lua/ZERONERobotCtrl.lua")
require("Data/ZERONE/scripts/lua/ZERONEActorAgentCtrl.lua")
require("Data/ZERONE/scripts/lua/ZERONEServer.lua")
require("Data/ZERONE/scripts/lua/ZERONEUIFaceCtrl.lua")
require("Data/ZERONE/scripts/lua/ZERONEUIPadCtrl.lua")

function engine_project_preplay()
	PX2_APP:SetShowInfo(true)
	zo_AddLanguage()	

	PX2_BLUETOOTH:SetDataProtocolHex(false)
end

function engine_project_play()
	zo_ZERONE()
end

function engine_project_update(appseconds, elapsedseconds)
	zo_AppUpdateCallback(appseconds, elapsedseconds)
end

-- cmds default called by PHOENIXEngine
function engine_project_cmd(cmd, param0, param1, param2)
	if "robot" == cmd then
		ZERONE_CurSerialOptType = 1
		PX2_ARDUINO:Initlize(Arduino.M_SERIAL, param0)
	elseif "lidar"==cmd then
		ZERONE_CurSerialOptType = 2
		PX2_ROBOT:LidarOpen(param0, 115200)
	elseif "1"==cmd then
		-- left
		if nil~=ZERONE_UIFace then
			ZERONE_UIFace:MoveControl(1, false)
		end
	elseif "2"==cmd then
		-- right
		if nil~=ZERONE_UIFace then
			ZERONE_UIFace:MoveControl(2, false)
		end
	elseif "3"==cmd then
		-- up
		if nil~=ZERONE_UIFace then
			ZERONE_UIFace:MoveControl(3, false)
		end
	elseif "4"==cmd then
		-- down
		if nil~=ZERONE_UIFace then
			ZERONE_UIFace:MoveControl(4, false)
		end
	elseif "0"==cmd then
		if nil~=ZERONE_UIFace then
			ZERONE_UIFace:MoveControl(0, false)
		end
	end
end