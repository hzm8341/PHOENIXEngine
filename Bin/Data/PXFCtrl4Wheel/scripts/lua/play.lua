-- play.lua

require("Data/BlueBlock/scripts/lua/start.lua")
require("Data/PXFCtrl4Wheel/scripts/lua/language.lua")
require("Data/PXFCtrl4Wheel/scripts/lua/sample/ActorCtrl.lua")

function preplay()
	pfm_AddLanguage()	

    local pltType = PX2_APP:GetPlatformType()
    if Application.PLT_WINDOWS==pltType then
        --PX2_ARDUINO:Initlize(Arduino.M_SERIAL, "COM9")
    else
        --PX2_ARDUINO:Initlize(Arduino.M_BLUETOOTH)
    end

    initArduino()
end

function play()
	PX2_ENGINECANVAS:SetClearColor(Float4:MakeColor(200, 200, 200, 255))
	PX2_ENGINESCENECANVAS:SetClearColor(Float4:MakeColor(200, 200, 200, 255))
	PX2_ENGINEUICANVAS:SetClearColor(Float4:MakeColor(200, 200, 200, 255))
	
	PX2_BLUETOOTH:SetWriteServiceID("0000ffe0-0000-1000-8000-00805f9b34fb")
	PX2_BLUETOOTH:SetWriteCharaID("0000ffe1-0000-1000-8000-00805f9b34fb")
	PX2_BLUETOOTH:SetReadServiceID("0000ffe0-0000-1000-8000-00805f9b34fb")
	PX2_BLUETOOTH:SetReadCharaID("0000ffe1-0000-1000-8000-00805f9b34fb")
	PX2_BLUETOOTH:SetType(Bluetooth.T_2)
	PX2_BLUETOOTH:SetDataProtocolHex(false)

    uiMain()
    
    PX2_APP:SetShowInfo(true)
end

roundSize = 300.0
roundButSize = 250.0
roundPos = 200.0

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

    if PX2_BLUETOOTH:IsConnected() then
        coroutine.wrap(function()
            initArduino()
            sleep(1.0)
            g_SliderUp:SetPercent(0.45)
            g_SliderDown:SetPercent(0.5)
        end)()
    end    
end

pxf4w_L0 = 6
pxf4w_L1 = 9

pxf4w_R0 = 10
pxf4w_R1 = 11


function initArduino()
    PX2_LOGGER:LogInfo("pfm", "init arduino")

    -- begin
    PX2_ARDUINO:Begin()

    PX2_ARDUINO:PinMode(pxf4w_L0, true)
    PX2_ARDUINO:PinMode(pxf4w_L1, true)

    PX2_ARDUINO:PinMode(pxf4w_R0, true)
    PX2_ARDUINO:PinMode(pxf4w_R1, true)

    -- end
    PX2_ARDUINO:End()
end

function moveStop()
    gLastDirSimple = 0

    PX2_ARDUINO:Begin()
    
    -- 左
    PX2_ARDUINO:AnalogWrite(pxf4w_L0, 0)
    PX2_ARDUINO:AnalogWrite(pxf4w_L1, 0)

    -- 右
    PX2_ARDUINO:AnalogWrite(pxf4w_R0, 0)
    PX2_ARDUINO:AnalogWrite(pxf4w_R1, 0)


    PX2_ARDUINO:End()
end

function moveF(perc255)
    PX2_ARDUINO:Begin()

    -- 左
    PX2_ARDUINO:AnalogWrite(pxf4w_L0, perc255)
    PX2_ARDUINO:AnalogWrite(pxf4w_L1, 0)

    -- 右
    PX2_ARDUINO:AnalogWrite(pxf4w_R0, 0)
    PX2_ARDUINO:AnalogWrite(pxf4w_R1, perc255)


    PX2_ARDUINO:End()
end


function moveB(perc255)
    PX2_ARDUINO:Begin()

    -- 左
    PX2_ARDUINO:AnalogWrite(pxf4w_L0, 0)
    PX2_ARDUINO:AnalogWrite(pxf4w_L1, perc255)

    -- 右
    PX2_ARDUINO:AnalogWrite(pxf4w_R0, perc255)
    PX2_ARDUINO:AnalogWrite(pxf4w_R1, 0)


    PX2_ARDUINO:End()
end


function turnL(perc255)
    PX2_ARDUINO:Begin()

    -- 左
    PX2_ARDUINO:AnalogWrite(pxf4w_L0, 0)
    PX2_ARDUINO:AnalogWrite(pxf4w_L1, perc255)

    -- 右
    PX2_ARDUINO:AnalogWrite(pxf4w_R0, 0)
    PX2_ARDUINO:AnalogWrite(pxf4w_R1, perc255)


    PX2_ARDUINO:End()
end


function turnR(perc255)
    PX2_ARDUINO:Begin()

    -- 左
    PX2_ARDUINO:AnalogWrite(pxf4w_L0, perc255)
    PX2_ARDUINO:AnalogWrite(pxf4w_L1, 0)

    -- 右
    PX2_ARDUINO:AnalogWrite(pxf4w_R0, perc255)
    PX2_ARDUINO:AnalogWrite(pxf4w_R1, 0)


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
gLastSpeed = 0
function pfm_MainCallabckRound(ptr, callType)
    local obj = Cast:ToO(ptr) 
	local name = obj:GetName()	

    if UICT_ROUND_DRAG==callType then

        local distAdjust = 0.1
        if "Round0"==name then
            local dirSimple = obj:GetDragingDirSimple()
            local perc = obj:GetDraggingPercentPiece(5)
            local perc255 = 255.0 * perc

            if dirSimple~=gLastDirSimple or gLastSpeed~=perc255 then
                gLastDirSimple = dirSimple
                gLastSpeed = perc255
                
                if 0==dirSimple then
                    moveStop()
                elseif 1==dirSimple then
                    moveF(perc255)
                elseif 2==dirSimple then
                    moveB(perc255)
                elseif 3==dirSimple then
                    turnL(perc255)
                elseif 4==dirSimple then
                    turnR(perc255)
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

	elseif UICT_RELEASED==callType then
        playFrameNormal(obj)

    elseif UICT_RELEASED_NOTPICK==callType then
        playFrameNormal(obj)
	end
end
