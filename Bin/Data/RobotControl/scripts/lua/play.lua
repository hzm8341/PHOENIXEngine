--play.lua

require("Data/RobotControl/scripts/lua/language.lua")
require("Data/RobotControl/scripts/lua/homepage.lua")
require("Data/RobotControl/scripts/lua/gamepadpage.lua")
require("Data/RobotControl/scripts/lua/acceleratorpage.lua")
require("Data/RobotControl/scripts/lua/voicepage.lua")
require("Data/RobotControl/scripts/lua/connect.lua")
require("Data/RobotControl/scripts/lua/bluetooth.lua")
require("Data/RobotControl/scripts/lua/common.lua")

function engine_project_preplay() 
    PX2_APP:SetShowInfo(false)
    PX2_BLUETOOTH:SetDataProtocolHex(false)
    rc_AddLanguage()
end

function engine_project_play()
    rc_Play()
end

function engine_project_update(appseconds, elapsedseconds) 
    rc_AcceleratorUpdate(appseconds, elapsedseconds)
end

function engine_project_cmd(cmd, param0, param1, param2) 
end

rc_ConnectFrame = nil
rc_FrameHome = nil
rc_FramePad = nil
rc_FrameAxis = nil
rc_FrameVoice = nil
rc_SpeakText = nil

rc_TextWidth = 660.0
rc_TextHeight = 200.0

PageType = {
    PT_HOME = 0,
    PT_CTRL = 1,
    PT_AXIS = 2,
    PT_VOICE = 3,
    PT_MAX_TYPE = 4,
}
rc_ThePageType = PageType.PT_HOME

function rc_UISetTextFont(text, fontSize)
	text:SetFont("Data/engine/font.ttf", fontSize, fontSize)
end

local cornorBtnPos = 70.0

function rc_Play()
    PX2_ENGINECANVAS:SetClearColor(Float4:MakeColor(63, 72, 204, 255))
    PX2_ENGINESCENECANVAS:SetClearColor(Float4:MakeColor(63, 72, 204, 255))

    local ui = PX2_PROJ:GetUI()
    local frameRC = UIFrame:New()
    ui:AttachChild(frameRC)
    frameRC:SetAnchorHor(0.0, 1.0)
    frameRC:SetAnchorVer(0.0, 1.0)

    local btnConnect = UIButton:New("BtnConnect")
    frameRC:AttachChild(btnConnect)
    btnConnect.LocalTransform:SetTranslateY(-50.0)
    btnConnect:SetAnchorHor(1.0, 1.0)
    btnConnect:SetAnchorVer(1.0, 1.0)
    btnConnect:SetAnchorParamHor(-cornorBtnPos, -cornorBtnPos)
    btnConnect:SetAnchorParamVer(-cornorBtnPos, -cornorBtnPos)
    btnConnect:SetSize(60.0, 60.0)
    btnConnect:SetScriptHandler("rc_UICallabck")
    btnConnect:SetStateColorDefaultWhite()
    btnConnect:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("Data/RobotControl/images/bluetooth.png")

    local btnReturn = UIButton:New("BtnReturn")
    frameRC:AttachChild(btnReturn)
    btnReturn.LocalTransform:SetTranslateY(-50.0)
    btnReturn:SetAnchorHor(0.0, 0.0)
    btnReturn:SetAnchorVer(1.0, 1.0)
    btnReturn:SetAnchorParamHor(cornorBtnPos, cornorBtnPos)
    btnReturn:SetAnchorParamVer(-cornorBtnPos, -cornorBtnPos)
    btnReturn:SetSize(60.0, 60.0)
    btnReturn:SetScriptHandler("rc_UICallabck")
    btnReturn:SetStateColorDefaultWhite()
    btnReturn:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("Data/RobotControl/images/return.png")

    local cntFrame = rc_Connect()
    frameRC:AttachChild(cntFrame)
    rc_ConnectFrame = cntFrame
    cntFrame.LocalTransform:SetTranslateY(-100.0)
    cntFrame:SetAnchorHor(0.0, 1.0)
    cntFrame:SetAnchorVer(0.0, 1.0)
    cntFrame:Show(false)

    local frameHome = rc_FrameHomePage()
    frameRC:AttachChild(frameHome)
    rc_FrameHome = frameHome
    rc_FrameHome.LocalTransform:SetTranslateY(-1.0)
    rc_FrameHome:SetAnchorHor(0.0, 1.0)
    rc_FrameHome:SetAnchorVer(0.0, 1.0)
    rc_FrameHome:Show(true)

    local framePad = rc_FramePadPage()
    frameRC:AttachChild(framePad)
    rc_FramePad = framePad
    framePad.LocalTransform:SetTranslateY(-1.0)
    framePad:SetAnchorHor(0.0, 1.0)
    framePad:SetAnchorVer(0.0, 1.0)
    framePad:Show(false)

    local frameAcceler = rc_AcceleratorPage()
    frameRC:AttachChild(frameAcceler)
    rc_FrameAxis = frameAcceler
    frameAcceler.LocalTransform:SetTranslateY(-1.0)
    frameAcceler:SetAnchorHor(0.0, 1.0)
    frameAcceler:SetAnchorVer(0.0, 1.0)
    frameAcceler:Show(false)

    local frameVoice = rc_VoicePage()
    frameRC:AttachChild(frameVoice)
    rc_FrameVoice = frameVoice
    frameVoice.LocalTransform:SetTranslateY(-1.0)
    frameVoice:SetAnchorHor(0.0, 1.0)
    frameVoice:SetAnchorVer(0.0, 1.0)
    frameVoice:Show(false)

    PX2_VOICESDK:EnableAutoSpeak(false)
    PX2_VOICESDK:EnableAutoSpeakTTS(true)    

    UnRegistAllEventFunctions("VoiceSDKSpace::RecognizeResults")
    RegistEventFunction("VoiceSDKSpace::RecognizeResults", function(txt, txtJson)
        PX2_LOGGER:LogInfo("RobotControl", txt)

        rc_SpeakText:GetText():SetText(txt)
        local fontWidth = rc_SpeakText:GetText():GetTextWidth()
        if fontWidth < (rc_TextWidth-20.0) then
            rc_SpeakText:GetText():SetRectUseage(RU_ALIGNS)
            rc_SpeakText:SetHeight(rc_TextHeight)
            rc_SpeakText:SetAnchorParamVer(rc_TextHeight*0.5, rc_TextHeight*0.5)
        else
            local numHeight = (fontWidth/rc_TextWidth) * 1.0 + 1
            local height = numHeight * 40
            rc_SpeakText:GetText():SetRectUseage(RU_CLIPWARP)
            rc_SpeakText:SetHeight(height)
            if height>rc_TextHeight then
                rc_SpeakText:SetAnchorParamVer(height*0.5, height*0.5)
            end
        end

        PX2_VOICESDK:Speak(""..txt)

    end)

    UnRegistAllEventFunctions("VoiceSDKSpace::SpeakText")
    RegistEventFunction("VoiceSDKSpace::SpeakText", function(txt) 
    end)

    PX2_PFSDK:StartAccelerator()
    PX2_PFSDK:RegistAccelerator()
end

function rc_UICallabck(ptr, callType)
    local obj = Cast:ToO(ptr) 
	local name = obj:GetName()	

    if UICT_PRESSED==callType then
        playFrameScale(obj)
        
        if "BtnVoiceRecording"==name then
            PX2_VOICESDK:StartVoiceListening()
            PX2_LOGGER:LogInfo("RobotControl", "start voice")
        end
	elseif UICT_RELEASED==callType then
        playFrameNormal(obj)

        if "BtnConnect" == name then
            rc_ConnectFrame:Show(true)
        elseif "BtnDlgClose" == name then
            rc_ConnectFrame:Show(false)
        elseif "BtnCtrl" == name then
            rc_ThePageType = PageType.PT_CTRL

            rc_FrameHome:Show(false)
            rc_FramePad:Show(false)
            rc_FrameAxis:Show(false)
            rc_FrameVoice:Show(false)
            rc_FramePad:Show(true)
        elseif "BtnAxis"==name then
            rc_ThePageType = PageType.PT_AXIS

            rc_FrameHome:Show(false)
            rc_FramePad:Show(false)
            rc_FrameAxis:Show(false)
            rc_FrameVoice:Show(false)
            rc_FrameAxis:Show(true)
        elseif "BtnVoice"==name then
            rc_ThePageType = PageType.PT_VOICE

            rc_FrameHome:Show(false)
            rc_FramePad:Show(false)
            rc_FrameAxis:Show(false)
            rc_FrameVoice:Show(false)
            rc_FrameVoice:Show(true)
        elseif "BtnReturn"==name then

            if PageType.PT_HOME ~= rc_ThePageType then
                rc_FrameHome:Show(true)
                rc_FramePad:Show(false)
                rc_FrameAxis:Show(false)
                rc_FrameVoice:Show(false)

                rc_RobotCtrlLeave()

                rc_ThePageType = PageType.PT_HOME
            end
        elseif "BtnVoiceRecording"==name then
            PX2_VOICESDK:EndVoiceListening()
            PX2_LOGGER:LogInfo("RobotControl", "end voice")
        end
    elseif UICT_CHECKED==callType then  
    elseif UICT_DISCHECKED==callType then
    elseif UICT_RELEASED_NOTPICK==callType then
        playFrameNormal(obj)
    elseif UICT_ROUND_RELEASEDNOTPICK==callType then
    elseif UICT_COMBOBOX_CHOOSED==callType then 
	end
end

function rc_RobotCtrlLeave()
    PX2_ARDUINO:Run(0, Arduino.DT_NONE, 0)
    PX2_ARDUINO:Run(1, Arduino.DT_NONE, 0)
end