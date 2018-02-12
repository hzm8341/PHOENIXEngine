-- play.lua

require("Data/Chaos/scripts/lua/language.lua")
require("Data/Chaos/scripts/lua/robot.lua")
require("Data/Chaos/scripts/lua/ChaosCtrl.lua")
require("Data/Chaos/scripts/lua/ChaosCommon.lua")
require("Data/Chaos/scripts/lua/ChaosConnect.lua")
require("Data/Chaos/scripts/lua/ChaosSetting.lua")

function preplay()
	PX2_APP:SetShowInfo(true)
	g_AddLanguage()	
	
	--PX2_BLUETOOTH:SetType(Bluetooth.T_2)
	PX2_BLUETOOTH:SetDataProtocolHex(false)
end

function play()
	ch_Robot()
end
