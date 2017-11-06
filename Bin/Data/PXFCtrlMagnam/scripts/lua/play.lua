-- play.lua

require("Data/BlueBlock/scripts/lua/start.lua")
require("Data/PXFCtrlMagnam/scripts/lua/language.lua")
require("Data/PXFCtrlMagnam/scripts/lua/sample/ActorCtrl.lua")

function preplay()
	pfm_AddLanguage()	

	PX2_APP:SetShowInfo(true)

	local pltType = PX2_APP:GetPlatformType()
	if Application.PLT_WINDOWS==pltType then		
		local serialPort = ""
		local platTag = PX2_APP:GetPlatformType()
		if Application.PLT_WINDOWS==platTag then
			serialPort = "COM3"
		elseif Application.PLT_LINUX==platTag then
			serialPort = "/dev/ttyUSB0"
		end

        PX2_ARDUINO:Initlize(Arduino.M_SERIAL, serialPort)
        
        coroutine.wrap(function()
            sleep(2.0)
            initArduino()
        end)()
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
	PX2_ENGINECANVAS:SetClearColor(Float4:MakeColor(200, 200, 200, 255))
	PX2_ENGINESCENECANVAS:SetClearColor(Float4:MakeColor(200, 200, 200, 255))
	PX2_ENGINEUICANVAS:SetClearColor(Float4:MakeColor(200, 200, 200, 255))

    uiMain()
    
    PX2_APP:SetShowInfo(true)
end

roundSize = 300.0
roundButSize = 250.0
roundPos = 200.0

g_SliderUp = nil
g_SilderDown = nil

function uiMain()
	-- ui
    local ui = PX2_PROJ:GetUI()
	
	local frame = UIFrame:New()
	ui:AttachChild(frame)
	frame.LocalTransform:SetTranslateY(-1.0)
	frame:SetAnchorHor(0.0, 1.0)
	frame:SetAnchorVer(0.0, 1.0)

    -- rounds
    local roundOutWidth = 600.0
    local roundOutHeight = 500.0

	-- round0
    local roundFrame0 = UIFrame:New()
    frame:AttachChild(roundFrame0)
    roundFrame0.LocalTransform:SetTranslateY(-25.0)
    roundFrame0:SetAnchorHor(0.0, 0.4)
    roundFrame0:SetAnchorVer(0.0, 1.0)
    roundFrame0:SetPivot(0.0, 0.0)
    roundFrame0:SetChildPickOnlyInSizeRange(true)

    local uiRound0 = UIRound:New("Round0")
    roundFrame0:AttachChild(uiRound0)
    uiRound0.LocalTransform:SetTranslateY(-5.0)
    uiRound0:SetAnchorHor(0.0, 0.0)
    uiRound0:SetAnchorVer(0.0, 0.0)
    uiRound0:SetAnchorParamHor(roundPos, roundPos)
    uiRound0:SetAnchorParamVer(roundPos, roundPos)
    uiRound0:SetPivot(0.5, 0.5)
    uiRound0:SetSize(roundSize, roundSize)
    uiRound0:GetButton():SetSize(roundButSize, roundButSize)
    uiRound0:GetButton():SetStateColorDefaultWhite()
    uiRound0:GetButton():GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("Data/PhoenixFrameMagnam/images/main/qiuti.png")
    uiRound0:GetButton():GetPicBoxAtState(UIButtonBase.BS_HOVERED):SetTexture("Data/PhoenixFrameMagnam/images/main/qiuti.png")
    uiRound0:GetButton():GetPicBoxAtState(UIButtonBase.BS_PRESSED):SetTexture("Data/PhoenixFrameMagnam/images/main/qiuti.png")
    uiRound0:GetBack():GetUIPicBox():SetTexture("Data/PhoenixFrameMagnam/images/main/kj_fxj.png")
    uiRound0:SetScriptHandler("pfm_MainCallabckRound")
    uiRound0:RegistToScriptSystem()

	local butLeft = UIButton:New("ButLeft")
    roundFrame0:AttachChild(butLeft)
    butLeft.LocalTransform:SetTranslateY(-1.0)
	butLeft:SetSize(100.0, 60.0)
    butLeft:SetAnchorHor(0.0, 0.0)
    butLeft:SetAnchorParamHor(roundPos-120.0, roundPos-120.0)
    butLeft:SetAnchorVer(0.0, 0.0)
    butLeft:SetAnchorParamVer(roundPos+300.0, roundPos+300.0)
    butLeft:SetScriptHandler("pfm_MainCallabckRound")
	butLeft:CreateAddText("左")

    local butStop = UIButton:New("ButStop")
    roundFrame0:AttachChild(butStop)
    butStop.LocalTransform:SetTranslateY(-1.0)
	butStop:SetSize(100.0, 60.0)
    butStop:SetAnchorHor(0.0, 0.0)
    butStop:SetAnchorParamHor(roundPos+0.0, roundPos+0.0)
    butStop:SetAnchorVer(0.0, 0.0)
    butStop:SetAnchorParamVer(roundPos+300.0, roundPos+300.0)
    butStop:SetScriptHandler("pfm_MainCallabckRound")
	butStop:CreateAddText("停止")

	local butRight = UIButton:New("ButRight")
    roundFrame0:AttachChild(butRight)
    butRight.LocalTransform:SetTranslateY(-1.0)
	butRight:SetSize(100.0, 60.0)
    butRight:SetAnchorHor(0.0, 0.0)
    butRight:SetAnchorParamHor(roundPos+120.0, roundPos+120.0)
    butRight:SetAnchorVer(0.0, 0.0)
    butRight:SetAnchorParamVer(roundPos+300.0, roundPos+300.0)
    butRight:SetScriptHandler("pfm_MainCallabckRound")
	butRight:CreateAddText("右")

	local butFire = UIButton:New("ButFire")
    frame:AttachChild(butFire)
    butFire.LocalTransform:SetTranslateY(-1.0)
	butFire:SetSize(100.0, 100.0)
    butFire:SetAnchorHor(1.0, 1.0)
    butFire:SetAnchorParamHor(-200.0, -200.0)
    butFire:SetAnchorVer(0.0, 0.0)
    butFire:SetAnchorParamVer(200.0, 200.0)
    butFire:SetScriptHandler("pfm_MainCallabckRound")
	butFire:CreateAddText("发射")

    local uiSliderUp = UISlider:New("SliderUP")
    frame:AttachChild(uiSliderUp)
	uiSliderUp:SetSize(300.0, 40.0)
    uiSliderUp:SetAnchorHor(1.0, 1.0)
    uiSliderUp:SetAnchorParamHor(-200.0, -200.0)
    uiSliderUp:SetAnchorVer(1.0, 1.0)
    uiSliderUp:SetAnchorParamVer(-200.0, -200.0)
    uiSliderUp:SetScriptHandler("pfm_MainCallabckRound")
    uiSliderUp:SetSliderLength(60.0)
    uiSliderUp:RegistToScriptSystem()
    g_SliderUp = uiSliderUp

    local uiSliderDown = UISlider:New("SliderDown")
    frame:AttachChild(uiSliderDown)
	uiSliderDown:SetSize(300.0, 40.0)
    uiSliderDown:SetAnchorHor(1.0, 1.0)
    uiSliderDown:SetAnchorParamHor(-200.0, -200.0)
    uiSliderDown:SetAnchorVer(1.0, 1.0)
    uiSliderDown:SetAnchorParamVer(-300.0, -300.0)
    uiSliderDown:SetScriptHandler("pfm_MainCallabckRound")
    uiSliderDown:SetSliderLength(60.0)
    uiSliderDown:RegistToScriptSystem()
    g_SliderDown = uiSliderDown

    UnRegistAllEventFunctions("BluetoothES::OnConnected")
    RegistEventFunction("BluetoothES::OnConnected", function()
        PX2_LOGGER:LogInfo("pfm", "Bluetooth OnConncted")

        coroutine.wrap(function()
            sleep(1.0)
            initArduino()
        end)()
    end)

    if PX2_BLUETOOTH:IsConnected() then
        coroutine.wrap(function()
            sleep(1.0)
            initArduino()
        end)()
    end    
end

function initArduino()
    PX2_LOGGER:LogInfo("pfm", "init arduino")

    -- begin
    -- left front back
    PX2_ARDUINO:PinMode(2, true)
    PX2_ARDUINO:PinMode(3, true) -- pwm
    PX2_ARDUINO:PinMode(4, true)

    PX2_ARDUINO:PinMode(12, true)
    PX2_ARDUINO:PinMode(6, true) -- pwm
    PX2_ARDUINO:PinMode(7, true)

    -- right front back
    PX2_ARDUINO:PinMode(0, true, true)
    PX2_ARDUINO:PinMode(1, true, true)
    PX2_ARDUINO:PinMode(9, true) -- pwm

    PX2_ARDUINO:PinMode(2, true)
    PX2_ARDUINO:PinMode(3, true)
    PX2_ARDUINO:PinMode(10, true) -- pwm

    -- fire
    PX2_ARDUINO:PinMode(8, true)

    -- Server up down
    PX2_ARDUINO:PinMode(5, true, false)
    PX2_ARDUINO:PinMode(11, true, false)
    PX2_ARDUINO:ServerInit(5, false)
    PX2_ARDUINO:Server1Init(11, false)

    -- end
    PX2_ARDUINO:End()

    if nil ~= g_SliderUp then
        g_SliderUp:SetPercent(0.45)
    end
    if nil ~= g_SliderDown then
        g_SliderDown:SetPercent(0.5)
    end
end

function leftSlider()
    gLastDirSimple = 0

    PX2_ARDUINO:Begin()

    -- 左
    -- 进
    PX2_ARDUINO:DigitalWrite(2, true)
    PX2_ARDUINO:AnalogWrite(3, 255)
    PX2_ARDUINO:DigitalWrite(4, false)

    -- 退
    PX2_ARDUINO:DigitalWrite(12, true)
    PX2_ARDUINO:AnalogWrite(6, 255)
    PX2_ARDUINO:DigitalWrite(7, false)

    -- 右
    -- 退
    PX2_ARDUINO:DigitalWrite(2, true, true)
    PX2_ARDUINO:AnalogWrite(10, 255)
    PX2_ARDUINO:DigitalWrite(3, false, true)

    -- 进
    PX2_ARDUINO:DigitalWrite(0, false, true)
    PX2_ARDUINO:AnalogWrite(9, 255)
    PX2_ARDUINO:DigitalWrite(1, true, true)

    PX2_ARDUINO:End()
end

function rightSlider()
    gLastDirSimple = 0

    PX2_ARDUINO:Begin()

    -- 左
    -- 进
    PX2_ARDUINO:DigitalWrite(2, false)
    PX2_ARDUINO:AnalogWrite(3, 255)
    PX2_ARDUINO:DigitalWrite(4, true)

    -- 退
    PX2_ARDUINO:DigitalWrite(12, false)
    PX2_ARDUINO:AnalogWrite(6, 255)
    PX2_ARDUINO:DigitalWrite(7, true)

    -- 右
    -- 退
    PX2_ARDUINO:DigitalWrite(2, false, true)
    PX2_ARDUINO:AnalogWrite(10, 255)
    PX2_ARDUINO:DigitalWrite(3, true, true)

    -- 进
    PX2_ARDUINO:DigitalWrite(0, true, true)
    PX2_ARDUINO:AnalogWrite(9, 255)
    PX2_ARDUINO:DigitalWrite(1, false, true)

    PX2_ARDUINO:End()
end

function moveStop()
    gLastDirSimple = 0

    PX2_ARDUINO:Begin()
    
    -- 左
    -- 进
    PX2_ARDUINO:DigitalWrite(2, false)
    PX2_ARDUINO:AnalogWrite(3, 0)
    PX2_ARDUINO:DigitalWrite(4, false)

    -- 退
    PX2_ARDUINO:DigitalWrite(12, false)
    PX2_ARDUINO:AnalogWrite(6, 0)
    PX2_ARDUINO:DigitalWrite(7, false)

    -- 右
    -- 退
    PX2_ARDUINO:DigitalWrite(2, false, true)
    PX2_ARDUINO:AnalogWrite(10, 0)
    PX2_ARDUINO:DigitalWrite(3, false, true)

    -- 进
    PX2_ARDUINO:DigitalWrite(0, false, true)
    PX2_ARDUINO:AnalogWrite(9, 0)
    PX2_ARDUINO:DigitalWrite(1, false, true)

    PX2_ARDUINO:End()
end

function moveF()
    PX2_ARDUINO:Begin()

    -- 左
    PX2_ARDUINO:DigitalWrite(2, false)
    PX2_ARDUINO:AnalogWrite(3, 255)
    PX2_ARDUINO:DigitalWrite(4, true)

    PX2_ARDUINO:DigitalWrite(12, true)
    PX2_ARDUINO:AnalogWrite(6, 255)
    PX2_ARDUINO:DigitalWrite(7, false)

    -- 右
    PX2_ARDUINO:DigitalWrite(2, true, true)
    PX2_ARDUINO:AnalogWrite(10, 255)
    PX2_ARDUINO:DigitalWrite(3, false, true)

    PX2_ARDUINO:DigitalWrite(0, true, true)
    PX2_ARDUINO:AnalogWrite(9, 255)
    PX2_ARDUINO:DigitalWrite(1, false, true)

    PX2_ARDUINO:End()
end


function moveB()
    PX2_ARDUINO:Begin()

    -- 左
    PX2_ARDUINO:DigitalWrite(2, true)
    PX2_ARDUINO:AnalogWrite(3, 255)
    PX2_ARDUINO:DigitalWrite(4, false)

    PX2_ARDUINO:DigitalWrite(12, false)
    PX2_ARDUINO:AnalogWrite(6, 255)
    PX2_ARDUINO:DigitalWrite(7, true)

    -- 右
    PX2_ARDUINO:DigitalWrite(2, false, true)
    PX2_ARDUINO:AnalogWrite(10, 255)
    PX2_ARDUINO:DigitalWrite(3, true, true)

    PX2_ARDUINO:DigitalWrite(0, false, true)
    PX2_ARDUINO:AnalogWrite(9, 255)
    PX2_ARDUINO:DigitalWrite(1, true, true)

    PX2_ARDUINO:End()
end


function turnL()
    PX2_ARDUINO:Begin()

    -- 左
    PX2_ARDUINO:DigitalWrite(2, true)
    PX2_ARDUINO:AnalogWrite(3, 255)
    PX2_ARDUINO:DigitalWrite(4, false)

    PX2_ARDUINO:DigitalWrite(12, false)
    PX2_ARDUINO:AnalogWrite(6, 255)
    PX2_ARDUINO:DigitalWrite(7, true)

    -- 右
    PX2_ARDUINO:DigitalWrite(2, true, true)
    PX2_ARDUINO:AnalogWrite(10, 255)
    PX2_ARDUINO:DigitalWrite(3, false, true)

    PX2_ARDUINO:DigitalWrite(0, true, true)
    PX2_ARDUINO:AnalogWrite(9, 255)
    PX2_ARDUINO:DigitalWrite(1, false, true)

    PX2_ARDUINO:End()
end


function turnR()
    PX2_ARDUINO:Begin()

    -- 左
    PX2_ARDUINO:DigitalWrite(2, false)
    PX2_ARDUINO:AnalogWrite(3, 255)
    PX2_ARDUINO:DigitalWrite(4, true)

    PX2_ARDUINO:DigitalWrite(12, true)
    PX2_ARDUINO:AnalogWrite(6, 255)
    PX2_ARDUINO:DigitalWrite(7, false)

    -- 右
    PX2_ARDUINO:DigitalWrite(2, false, true)
    PX2_ARDUINO:AnalogWrite(10, 255)
    PX2_ARDUINO:DigitalWrite(3, true, true)

    PX2_ARDUINO:DigitalWrite(0, false, true)
    PX2_ARDUINO:AnalogWrite(9, 255)
    PX2_ARDUINO:DigitalWrite(1, true, true)

    PX2_ARDUINO:End()
end

function playFrameScale(frame)
	local ctrlPlay = frame:GetControllerByName("ScaleCtrlPlay")
	if nil==ctrlPlay then
		ctrlPlay = InterpCurveUniformScaleController:New("ScaleCtrlPlay")
		frame:AttachController(ctrlPlay)
		ctrlPlay:Clear()
		ctrlPlay:AddPoint(0.0, 1.0, ICM_CURVE_AUTO)
		ctrlPlay:AddPoint(0.1, 0.8, ICM_CURVE_AUTO)
	end
	ctrlPlay:ResetPlay()

	local ctrlStop = frame:GetControllerByName("ScaleCtrlStop")
	if nil==ctrlStop then
		ctrlStop = InterpCurveUniformScaleController:New("ScaleCtrlStop")
		frame:AttachController(ctrlStop)
		ctrlStop:Clear()
		ctrlStop:AddPoint(0.0, 0.8, ICM_CURVE_AUTO)
		ctrlStop:AddPoint(0.1, 1.0, ICM_CURVE_AUTO)
	end
	ctrlStop:Stop()
end

function playFrameNormal(frame)
	local ctrlPlay = frame:GetControllerByName("ScaleCtrlPlay")
	if nil~=ctrlPlay then
		ctrlPlay:Stop()
	end

	local ctrlStop = frame:GetControllerByName("ScaleCtrlStop")
	if nil~=ctrlStop then
		ctrlStop:ResetPlay()
	end
end

gLastDirSimple = 0
function pfm_MainCallabckRound(ptr, callType)
    local obj = Cast:ToO(ptr) 
	local name = obj:GetName()	

    if UICT_ROUND_DRAG==callType then

        local distAdjust = 0.1
        if "Round0"==name then
            local dirSimple = obj:GetDragingDirSimple()

            if dirSimple~=gLastDirSimple then
                gLastDirSimple = dirSimple
                
                if 0==dirSimple then
                    moveStop()
                elseif 1==dirSimple then
                    moveF()
                elseif 2==dirSimple then
                    moveB()
                elseif 3==dirSimple then
                    turnL()
                elseif 4==dirSimple then
                    turnR()
                end

            end
        end

    elseif UICT_ROUND_RELEASED==callType then
        if "Round0"==name then
            moveStop()
        end
    elseif UICT_ROUND_RELEASEDNOTPICK==callType then
        if "Round0"==name then
             moveStop()
        end
    elseif UICT_PRESSED==callType then
        playFrameScale(obj)

        if "ButFire"==name then
            PX2_LOGGER:LogInfo("pfm", "fire")

            PX2_ARDUINO:Begin()
            PX2_ARDUINO:DigitalWrite(8, true)
            PX2_ARDUINO:End()
		end

	elseif UICT_RELEASED==callType then
        playFrameNormal(obj)

		if "ButLeft"==name then
            PX2_LOGGER:LogInfo("pfm", "ButLeft")
            leftSlider()

        elseif "ButRight"==name then
            rightSlider()

        elseif "ButStop"==name then
            moveStop()

        elseif "ButFire"==name then
            PX2_LOGGER:LogInfo("pfm", "fire over")

            PX2_ARDUINO:Begin()
            PX2_ARDUINO:DigitalWrite(8, false)
            PX2_ARDUINO:End()
		end

    elseif UICT_RELEASED_NOTPICK==callType then
        playFrameNormal(obj)

    elseif UICT_SLIDERCHANGED==callType then
        if "SliderUP"==name then
            local val = 1.0 - obj:GetPercent()
            local valI = 60 + 180 * val

            PX2_LOGGER:LogInfo("pfm", "SliderUP"..valI)

            PX2_ARDUINO:Begin()
            PX2_ARDUINO:ServerInit(5, false)
            PX2_ARDUINO:ServerWrite(valI)
            PX2_ARDUINO:End()
        elseif "SliderDown"==name then
            local val = obj:GetPercent()
            local valI = 60 + 70 * val

            PX2_LOGGER:LogInfo("pfm", "SliderDown"..valI)

            PX2_ARDUINO:Begin()
            PX2_ARDUINO:Server1Init(11, false)
            PX2_ARDUINO:Server1Write(valI)
            PX2_ARDUINO:End()
        end
	end
end
