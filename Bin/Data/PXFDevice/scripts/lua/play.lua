-- play.lua

require("Data/BlueBlock/scripts/lua/start.lua")
require("Data/PXFDevice/scripts/lua/language.lua")
require("Data/PXFDevice/scripts/lua/server.lua")
require("Data/PXFDevice/scripts/lua/ui/ui.lua")

pxfIsPlaying = false
pxfDistText = nil

function preplay()
	PX2_APP:SetShowInfo(true)
	p_g_AddLanguage()

	pxfDistText = nil

	local pltType = PX2_APP:GetPlatformType()
	if Application.PLT_WINDOWS==pltType then		
		local serialPort = "COM7"
		local platTag = PX2_APP:GetPlatformType()
		if Application.PLT_WINDOWS==platTag then
			serialPort = "COM7"
		elseif Application.PLT_LINUX==platTag then
			serialPort = "/dev/ttyUSB0"
		end

		PX2_ARDUINO:Initlize(Arduino.M_SERIAL, serialPort)
	else
		PX2_BLUETOOTH:SetWriteServiceID("0000ffe0-0000-1000-8000-00805f9b34fb")
		PX2_BLUETOOTH:SetWriteCharaID("0000ffe2-0000-1000-8000-00805f9b34fb")
		PX2_BLUETOOTH:SetReadServiceID("0000ffe0-0000-1000-8000-00805f9b34fb")
		PX2_BLUETOOTH:SetReadCharaID("0000ffe1-0000-1000-8000-00805f9b34fb")
		PX2_BLUETOOTH:SetType(Bluetooth.T_4)
		PX2_BLUETOOTH:SetDataProtocolHex(false)	

        PX2_ARDUINO:Initlize(Arduino.M_BLUETOOTH)
    end
end

function play()
	pxfIsPlaying = true

	--[[
	PX2_VOXELM:Initlize()	
	PX2_APP:NewScene()
	local scene = PX2_PROJ:GetScene()
	
	local section = VoxelSection:New()
	section:SetDistXY(10)
	section:SetMinSize(-1, -1, 0)
	section:SetMaxSize(0, 0, 0)
	scene:AttachChild(section)	
	scene:GetMainCameraNode().LocalTransform:SetTranslate(APoint(0, 0, 25))
	scene:GetMainCameraNode():LookAt(APoint(0, 0, 0), AVector.UNIT_Y)
	]]--

	-- ui
	uiMain()

	local pltType = PX2_APP:GetPlatformType()
	if Application.PLT_WINDOWS==pltType then	
        initPFX()
	end

	UnRegistAllEventFunctions("BluetoothES::OnConnected")
    RegistEventFunction("BluetoothES::OnConnected", function()
        PX2_LOGGER:LogInfo("pfm", "Bluetooth OnConncted")

        coroutine.wrap(function()
			initPFX()
        end)()
    end)
	if PX2_BLUETOOTH:IsConnected() then
        initPFX()
    end
	
	-- music
	--local musicName = "flog.mp3"
	--PX2_RM:ReWriteFileToWriteablePath("Data/PXFDevice/media/music/"..musicName, musicName)
	--local dstPath = ResourceManager:GetWriteablePath()..musicName
	--PX2_SS:PlayMusic(0, dstPath, true, 0.0)
end


