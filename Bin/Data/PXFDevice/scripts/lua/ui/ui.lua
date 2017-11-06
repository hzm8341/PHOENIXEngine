-- ui.lua

roundSize = 300.0
roundButSize = 250.0
roundPos = 200.0

pxfDevice_Slider0 = nil
pxfDevice_Slider1 = nil
pxfDevice_Slider2 = nil

pxfDistText = nil

function uiMain()
    PX2_ENGINESCENECANVAS:GetClearFlag(true, true, true)
    PX2_ENGINESCENECANVAS:SetClearColor(Float4(0.5, 0.5, 0.5, 1.0))
    
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
    uiRound0:SetScriptHandler("pxfDevice_MainCallabckRound")
    uiRound0:RegistToScriptSystem()

    -- light
    local butFire = UIButton:New("ButFire")
    frame:AttachChild(butFire)
    butFire.LocalTransform:SetTranslateY(-1.0)
	butFire:SetSize(100.0, 100.0)
    butFire:SetAnchorHor(1.0, 1.0)
    butFire:SetAnchorParamHor(-200.0, -200.0)
    butFire:SetAnchorVer(0.0, 0.0)
    butFire:SetAnchorParamVer(200.0, 200.0)
    butFire:SetScriptHandler("pxfDevice_MainCallabckRound")
	butFire:CreateAddText("激光")

    -- slider
    local uiSlider0 = UISlider:New("Slider0")
    frame:AttachChild(uiSlider0)
	uiSlider0:SetSize(300.0, 40.0)
    uiSlider0:SetAnchorHor(1.0, 1.0)
    uiSlider0:SetAnchorParamHor(-200.0, -200.0)
    uiSlider0:SetAnchorVer(1.0, 1.0)
    uiSlider0:SetAnchorParamVer(-200.0, -200.0)
    uiSlider0:SetScriptHandler("pxfDevice_MainCallabckRound")
    uiSlider0:SetSliderLength(60.0)
    uiSlider0:RegistToScriptSystem()
    pxfDevice_Slider0 = uiSlider0

    local uiSlider1 = UISlider:New("Slider1")
    frame:AttachChild(uiSlider1)
	uiSlider1:SetSize(300.0, 40.0)
    uiSlider1:SetAnchorHor(1.0, 1.0)
    uiSlider1:SetAnchorParamHor(-200.0, -200.0)
    uiSlider1:SetAnchorVer(1.0, 1.0)
    uiSlider1:SetAnchorParamVer(-250.0, -250.0)
    uiSlider1:SetScriptHandler("pxfDevice_MainCallabckRound")
    uiSlider1:SetSliderLength(60.0)
    uiSlider1:RegistToScriptSystem()
    pxfDevice_Slider1 = uiSlider1

    local uiSlider2 = UISlider:New("Slider2")
    frame:AttachChild(uiSlider2)
	uiSlider2:SetSize(300.0, 40.0)
    uiSlider2:SetAnchorHor(1.0, 1.0)
    uiSlider2:SetAnchorParamHor(-200.0, -200.0)
    uiSlider2:SetAnchorVer(1.0, 1.0)
    uiSlider2:SetAnchorParamVer(-300.0, -300.0)
    uiSlider2:SetScriptHandler("pxfDevice_MainCallabckRound")
    uiSlider2:SetSliderLength(60.0)
    uiSlider2:RegistToScriptSystem()
    pxfDevice_Slider2 = uiSlider2

    -- dis
    local textDist = UIFText:New()
    frame:AttachChild(textDist)
    pxfDistText = textDist
    textDist:GetText():SetText("距离")
    textDist:SetAnchorHor(0.5, 0.5)
    textDist:SetAnchorVer(1.0, 1.0)
    textDist:SetSize(200, 200)
    textDist:SetAnchorParamVer(-150, -150)
    textDist:GetText():SetFontColor(Float3.WHITE)
    textDist:GetText():SetFontWidthHeight(36, 36)

    PX2_TIMERM:RemoveTimer("DistText")
    PX2_TIMERM:RemoveTimer("DistText1")

    coroutine.wrap(function()
        while pxfIsPlaying do
            PX2_ARDUINO:Begin()
            PX2_ARDUINO:DistTest()
            PX2_ARDUINO:End()
            sleepName(0.6, "DistText")
        end
    end)()

    coroutine.wrap(function()
        while pxfIsPlaying do
            local dist = PX2_ARDUINO:GetDist()
            if nil~=pxfDistText then
                pxfDistText:GetText():SetText("距离:"..dist)
            end
            sleepName(0.3, "DistText1")
        end
    end)()
end

function initPFX()
    coroutine.wrap(function()
        sleep(2.0)
        initArduino()
        sleep(1.0)
        pxfDevice_Slider0:SetPercent(0.5)
        pxfDevice_Slider1:SetPercent(0.5)
        pxfDevice_Slider2:SetPercent(0.0)
    end)()
end

pxf4w_L0 = 4
pxf4w_L1 = 5
pxf4w_LS = 6

pxf4w_R0 = 7
pxf4w_R1 = 8
pxf4w_RS = 9

function initArduino()
    PX2_LOGGER:LogInfo("pfm", "init arduino")

    -- begin
    PX2_ARDUINO:Begin()

    PX2_ARDUINO:PinMode(pxf4w_L0, true)
	PX2_ARDUINO:PinMode(pxf4w_L1, true)
	PX2_ARDUINO:PinMode(pxf4w_LS, true)

    PX2_ARDUINO:PinMode(pxf4w_R0, true)
	PX2_ARDUINO:PinMode(pxf4w_R1, true)
    PX2_ARDUINO:PinMode(pxf4w_RS, true)
    
    PX2_ARDUINO:PinMode(10, true)

    PX2_ARDUINO:ServerInit(1, true)
    PX2_ARDUINO:Server1Init(2, true)
    PX2_ARDUINO:Server2Init(3, true)

    PX2_ARDUINO:DistInit(0, 1, true)

    -- end
    PX2_ARDUINO:End()
end

function moveStop()
    gLastDirSimple = 0

    PX2_ARDUINO:Begin()
    
    -- 左
    PX2_ARDUINO:DigitalWrite(pxf4w_L0, false)
	PX2_ARDUINO:DigitalWrite(pxf4w_L1, false)
	PX2_ARDUINO:AnalogWrite(pxf4w_LS, 0)

    -- 右
    PX2_ARDUINO:DigitalWrite(pxf4w_R0, false)
	PX2_ARDUINO:DigitalWrite(pxf4w_R1, false)
	PX2_ARDUINO:AnalogWrite(pxf4w_RS, 0)

    PX2_ARDUINO:End()
end

function moveF(perc255)
    PX2_ARDUINO:Begin()

    -- 左
    PX2_ARDUINO:DigitalWrite(pxf4w_L0, false)
	PX2_ARDUINO:DigitalWrite(pxf4w_L1, true)
	PX2_ARDUINO:AnalogWrite(pxf4w_LS, 255)

    -- 右
    PX2_ARDUINO:DigitalWrite(pxf4w_R0, true)
	PX2_ARDUINO:DigitalWrite(pxf4w_R1, false)
	PX2_ARDUINO:AnalogWrite(pxf4w_RS, perc255)

    PX2_ARDUINO:End()
end


function moveB(perc255)
    PX2_ARDUINO:Begin()

    -- 左
    PX2_ARDUINO:DigitalWrite(pxf4w_L0, true)
	PX2_ARDUINO:DigitalWrite(pxf4w_L1, false)
	PX2_ARDUINO:AnalogWrite(pxf4w_LS, perc255)

    -- 右
    PX2_ARDUINO:DigitalWrite(pxf4w_R0, false)
	PX2_ARDUINO:DigitalWrite(pxf4w_R1, true)
	PX2_ARDUINO:AnalogWrite(pxf4w_RS, perc255)

    PX2_ARDUINO:End()
end


function turnL(perc255)
    PX2_ARDUINO:Begin()

    -- 左
    PX2_ARDUINO:DigitalWrite(pxf4w_L0, true)
	PX2_ARDUINO:DigitalWrite(pxf4w_L1, false)
	PX2_ARDUINO:AnalogWrite(pxf4w_LS, perc255)

    -- 右
    PX2_ARDUINO:DigitalWrite(pxf4w_R0, true)
	PX2_ARDUINO:DigitalWrite(pxf4w_R1, false)
	PX2_ARDUINO:AnalogWrite(pxf4w_RS, perc255)

    PX2_ARDUINO:End()
end


function turnR(perc255)
    PX2_ARDUINO:Begin()

    -- 左
    PX2_ARDUINO:DigitalWrite(pxf4w_L0, false)
	PX2_ARDUINO:DigitalWrite(pxf4w_L1, true)
	PX2_ARDUINO:AnalogWrite(pxf4w_LS, perc255)

    -- 右
    PX2_ARDUINO:DigitalWrite(pxf4w_R0, false)
	PX2_ARDUINO:DigitalWrite(pxf4w_R1, true)
	PX2_ARDUINO:AnalogWrite(pxf4w_RS, perc255)

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
function pxfDevice_MainCallabckRound(ptr, callType)
    local obj = Cast:ToO(ptr) 
	local name = obj:GetName()	

    if UICT_ROUND_DRAG==callType then

        local distAdjust = 0.1
        if "Round0"==name then
            local dirSimple = obj:GetDragingDirSimple()
            local perc = obj:GetDraggingPercentPiece(4)
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

        if "ButFire"==name then
            PX2_LOGGER:LogInfo("pfm", "fire")

            PX2_ARDUINO:Begin()
            PX2_ARDUINO:DigitalWrite(10, true)
            PX2_ARDUINO:End()
		end

	elseif UICT_RELEASED==callType then
        playFrameNormal(obj)

        if "ButFire"==name then
            PX2_LOGGER:LogInfo("pfm", "fire")

            PX2_ARDUINO:Begin()
            PX2_ARDUINO:DigitalWrite(10, false)
            PX2_ARDUINO:End()
		end

    elseif UICT_RELEASED_NOTPICK==callType then
        playFrameNormal(obj)

    elseif UICT_SLIDERCHANGED==callType then
        if "Slider0"==name then
            local val = obj:GetPercent()
            local valI = 45 + 90 * val

            PX2_ARDUINO:Begin()
            PX2_ARDUINO:ServerWrite(valI)
            PX2_ARDUINO:End()

        elseif "Slider1"==name then
            local val = obj:GetPercent()
            local valI = 40 + 120 * val

            PX2_ARDUINO:Begin()
            PX2_ARDUINO:Server1Write(valI)
            PX2_ARDUINO:End()

        elseif "Slider2"==name then
            local val = obj:GetPercent()
            local valI = 200 * val

            PX2_ARDUINO:Begin()
            PX2_ARDUINO:Server2Write(valI)
            PX2_ARDUINO:End()

        end
	end
end
