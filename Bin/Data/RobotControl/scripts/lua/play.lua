--play.lua

require("Data/RobotControl/scripts/lua/language.lua")
require("Data/RobotControl/scripts/lua/homepage.lua")
require("Data/RobotControl/scripts/lua/gamepadpage.lua")
require("Data/RobotControl/scripts/lua/axispage.lua")
require("Data/RobotControl/scripts/lua/voicepage.lua")
require("Data/RobotControl/scripts/lua/connect.lua")
require("Data/RobotControl/scripts/lua/bluetooth.lua")
require("Data/RobotControl/scripts/lua/common.lua")

function engine_project_preplay() 
    PX2_APP:SetShowInfo(true)
    PX2_BLUETOOTH:SetDataProtocolHex(false)
    rc_AddLanguage()
end

function engine_project_play()
    rc_Play()
end

function engine_project_update(appseconds, elapsedseconds) 
end

function engine_project_cmd(cmd, param0, param1, param2) 
end

rc_ConnectFrame = nil
rc_FrameHome = nil
rc_FramePad = nil
rc_FrameAxis = nil
rc_FrameVoice = nil

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
    btnConnect:CreateAddText("Cnt")
    btnConnect:SetScriptHandler("rc_UICallabck")

    local btnReturn = UIButton:New("BtnReturn")
    frameRC:AttachChild(btnReturn)
    btnReturn.LocalTransform:SetTranslateY(-50.0)
    btnReturn:SetAnchorHor(0.0, 0.0)
    btnReturn:SetAnchorVer(1.0, 1.0)
    btnReturn:SetAnchorParamHor(cornorBtnPos, cornorBtnPos)
    btnReturn:SetAnchorParamVer(-cornorBtnPos, -cornorBtnPos)
    btnReturn:SetSize(60.0, 60.0)
    btnReturn:CreateAddText("Cnt")
    btnReturn:SetScriptHandler("rc_UICallabck")

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

    local frameAxis = rc_AxisPage()
    frameRC:AttachChild(frameAxis)
    rc_FrameAxis = frameAxis
    frameAxis.LocalTransform:SetTranslateY(-1.0)
    frameAxis:SetAnchorHor(0.0, 1.0)
    frameAxis:SetAnchorVer(0.0, 1.0)
    frameAxis:Show(false)

    local frameVoice = rc_VoicePage()
    frameRC:AttachChild(frameVoice)
    rc_FrameVoice = frameVoice
    frameVoice.LocalTransform:SetTranslateY(-1.0)
    frameVoice:SetAnchorHor(0.0, 1.0)
    frameVoice:SetAnchorVer(0.0, 1.0)
    frameVoice:Show(false)
end

function rc_UICallabck(ptr, callType)
    local obj = Cast:ToO(ptr) 
	local name = obj:GetName()	

    if UICT_PRESSED==callType then
        playFrameScale(obj)
	elseif UICT_RELEASED==callType then
        playFrameNormal(obj)

        if "BtnConnect" == name then
            rc_ConnectFrame:Show(true)
        elseif "BtnDlgClose" == name then
            rc_ConnectFrame:Show(false)
        elseif "BtnCtrl" == name then
            rc_FrameHome:Show(false)
            rc_FramePad:Show(false)
            rc_FrameAxis:Show(false)
            rc_FrameVoice:Show(false)
            rc_FramePad:Show(true)
        elseif "BtnShake"==name then
            rc_FrameHome:Show(false)
            rc_FramePad:Show(false)
            rc_FrameAxis:Show(false)
            rc_FrameVoice:Show(false)
            rc_FrameAxis:Show(true)
        elseif "BtnVoice"==name then
            rc_FrameHome:Show(false)
            rc_FramePad:Show(false)
            rc_FrameAxis:Show(false)
            rc_FrameVoice:Show(false)
            rc_FrameVoice:Show(true)
        end
    elseif UICT_CHECKED==callType then  
    elseif UICT_DISCHECKED==callType then
    elseif UICT_RELEASED_NOTPICK==callType then
        playFrameNormal(obj)
    elseif UICT_ROUND_RELEASEDNOTPICK==callType then
    elseif UICT_COMBOBOX_CHOOSED==callType then 
	end
end