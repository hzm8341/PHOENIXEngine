-- ZERONE.lua

ZERONE_UIFace = nil
ZERONE_IsZERO3DSceneCreated = false
ZERONE_CurSerialOptType = 0 -- 1 car, 2 lidar, 3 axis
ZERONE_IsFireRobot = false

function zo_ZERONE()    
    local ui = PX2_PROJ:GetUI()
    
    local frameZERONE = UIFrame:New()
    ui:AttachChild(frameZERONE)
    frameZERONE:SetAnchorHor(0.0, 1.0)
    frameZERONE:SetAnchorVer(0.0, 1.0)

    zo_CreateUDPServer()

    -- unregist events
    UnRegistAllEventFunctions("SerialES::Open")
    UnRegistAllEventFunctions("SerialES::Close")

    UnRegistAllEventFunctions("AIES::LiDarOpen")
    UnRegistAllEventFunctions("AIES::LiDarClose")

    UnRegistAllEventFunctions("AIES::AxisOpen")
    UnRegistAllEventFunctions("AIES::AxisClose")


    -- lidar
    PX2_ROBOT:CreateLidar()

    -- ui
    local frameUIFface = UIFrame:New()
    frameZERONE:AttachChild(frameUIFface)
    frameUIFface:SetAnchorHor(0.0, 1.0)
    frameUIFface:SetAnchorVer(0.0, 1.0)

    local ctrlScript = ZERONEUIFaceCtrl:New()
    local ctrler = Cast:ToSC(ctrlScript.__object)
	frameUIFface:AttachController(ctrler)
    ctrler:ResetPlay()

    local framePad = zo_PadCtrl()
    frameZERONE:AttachChild(framePad)
    framePad.LocalTransform:SetTranslateY(-20.0)
    framePad:SetAnchorHor(0.0, 1.0)
    framePad:SetAnchorVer(0.0, 1.0)
    framePad:Show(false)
    
    -- event
    UnRegistAllEventFunctions("InputEventSpace::KeyPressed")
    RegistEventFunction("InputEventSpace::KeyPressed", function(keyStr)
        if "KC_0" == keyStr then
            ZERONE_UIFace:SoundPlay(0)
        elseif "KC_1" == keyStr then
            ZERONE_UIFace:SoundPlay(1)
        elseif "KC_2" == keyStr then
            ZERONE_UIFace:SoundPlay(2)
        elseif "KC_3" == keyStr then
            ZERONE_UIFace:SoundPlay(3)
        elseif "KC_4" == keyStr then
            ZERONE_UIFace:SoundPlay(4)
        elseif "KC_5" == keyStr then
            ZERONE_UIFace:SoundPlay(5)
        elseif "KC_6" == keyStr then
            ZERONE_UIFace:SoundPlay(6)
        elseif "KC_LEFT" == keyStr then
            if nil~=ZERONE_UIFace then
                ZERONE_UIFace:MoveControl(1, true)
            end
        elseif "KC_RIGHT" == keyStr then
            if nil~=ZERONE_UIFace then
                ZERONE_UIFace:MoveControl(2, true)
            end
        elseif "KC_UP" == keyStr then
            if nil~=ZERONE_UIFace then
                ZERONE_UIFace:MoveControl(3, true)
            end
        elseif "KC_DOWN" == keyStr then
            if nil~=ZERONE_UIFace then
                ZERONE_UIFace:MoveControl(4, true)
            end
        elseif "KC_SPACE" == keyStr then
            if nil~=ZERONE_UIFace then
                ZERONE_UIFace:MoveControl(0, true)
            end

            zo_SceneAddBox()
        end
    end)
    UnRegistAllEventFunctions("InputEventSpace::KeyReleased")
    RegistEventFunction("InputEventSpace::KeyReleased", function(keyStr)
        if "KC_LEFT" == keyStr then
            if nil~=ZERONE_UIFace then
                ZERONE_UIFace:MoveControl(1, false)
            end
        elseif "KC_RIGHT" == keyStr then
            if nil~=ZERONE_UIFace then
                ZERONE_UIFace:MoveControl(2, false)
            end
        elseif "KC_UP" == keyStr then
            if nil~=ZERONE_UIFace then
                ZERONE_UIFace:MoveControl(3, false)
            end
        elseif "KC_DOWN" == keyStr then
            if nil~=ZERONE_UIFace then
                ZERONE_UIFace:MoveControl(4, false)
            end
        elseif "KC_SPACE" == keyStr then
            if nil~=ZERONE_UIFace then
                ZERONE_UIFace:MoveControl(0, false)
            end
        end
    end)
end

function zo_OnStartUp(useSpeed)
    -- Arduino
    if not ZERONE_IsRobotMotoWith298N then
        PX2_ARDUINO:VehicleInitMotoBoard4567()
        if useSpeed then
            PX2_ARDUINO:VehicleSpeedInit(Arduino.P_2, Arduino.P_8, Arduino.P_3, Arduino.P_9)
        end
    else
        PX2_ARDUINO:VehicleInitMotoBoard298N(Arduino.P_4, Arduino.P_5, Arduino.P_6, Arduino.P_7, Arduino.P_8, Arduino.P_9)
        if useSpeed then
            PX2_ARDUINO:VehicleSpeedInit(Arduino.P_2, Arduino.P_10, Arduino.P_3, Arduino.P_11)
        end
    end

    PX2_ARDUINO:PinMode(Arduino.P_11, Arduino.PM_OUTPUT)
    PX2_ARDUINO:PinMode(Arduino.P_12, Arduino.PM_OUTPUT)
    PX2_ARDUINO:PinMode(Arduino.P_13, Arduino.PM_OUTPUT)
    PX2_ARDUINO:ServerInit(0, Arduino.P_A0)
    
    if ZERONE_IsFireRobot then
        PX2_ARDUINO:ServerInit(1, Arduino.P_A1)
    end

    PX2_VOICESDK:Speak("零一机器人已经启动！")
end

function zo_AppUpdateCallback(appSecondsStr, elapsedSecondsStr)
    if nil~=ZERONE_UDPServer then
        ZERONE_UDPServer:Update(elapsedSecondsStr)
    end
end