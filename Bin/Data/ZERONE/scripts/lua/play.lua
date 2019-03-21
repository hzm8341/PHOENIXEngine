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

rc_Arduino = nil

function engine_project_preplay()
	PX2_APP:SetShowInfo(true)
	zo_AddLanguage()	

	PX2_BLUETOOTH:SetDataProtocolHex(false)
end

function engine_project_play()
	Robot:InitlizeSlam2D()
	zo_ZERONE()

	-- on raspberry we use linux
	local platType = PX2_APP:GetPlatformType()
	if Application.PLT_LINUX==platType then
		PX2_GR:SendGeneralEvent("autoconnectlidar", 2.0)
	end
end

function engine_project_update(appseconds, elapsedseconds)
	zo_AppUpdateCallback(appseconds, elapsedseconds)
end

function startForRaspberryLidarSender()
	PX2_ROBOT:GetLidar():SetLiDarType(LiDar.LT_III)
	PX2_ROBOT:SetRoleType(Robot.RT_MASTER_ONLY_SENDLIDAR)

		local serial = Serial()
    serial:UpdatePortList()
    local numPorts = serial:GetNumPorts()
    for i=0, numPorts-1 do
			local portStr = serial:GetPort(i)
			local portDesc = serial:GetPortDesc(i)

			PX2_ROBOT:LidarOpen(portStr, 230400)
    end  
end

UnRegistAllEventFunctions("GraphicsES::GeneralString")
RegistEventFunction("GraphicsES::GeneralString", function(str)
	if "autoconnectlidar"==str then
		startForRaspberryLidarSender()
	end
end)

-- cmds default called by PHOENIXEngine
function engine_project_cmd(cmd, param0, param1, param2)
	if "robot" == cmd then
		ZERONE_CurSerialOptType = 1
		rc_Arduino:Initlize(Arduino.M_SERIAL, param0)
		PX2_LOGGER:LogInfo("ZERONE", "robot arduino initlized")
	elseif "lidar"==cmd then
		ZERONE_CurSerialOptType = 2
		local lidarType = PX2_ROBOT:GetLidar():GetLiDarType()
		if LiDar.LT_III ==lidarType then
			PX2_ROBOT:LidarOpen(param0, 230400)
		else
			PX2_ROBOT:LidarOpen(param0, 115200)
		end
        PX2_LOGGER:LogInfo("ZERONE", "lidar opened")
	elseif "raspberry"==cmd then
		PX2_ROBOT:GetLidar():SetLiDarType(LiDar.LT_III)
		PX2_ROBOT:SetRoleType(Robot.RT_MASTER_ONLY_SENDLIDAR)
		PX2_LOGGER:LogInfo("ZERONE", "raspberry")
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