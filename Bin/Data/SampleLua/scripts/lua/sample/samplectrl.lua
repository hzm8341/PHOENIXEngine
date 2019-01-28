-- samplectrl.lua

function s_createsamplectrl(parent)
    local frame = UIFrame:New()
    parent:AttachChild(frame)

	local picBox = frame:CreateAddBackgroundPicBox(true)
    frame.LocalTransform:SetTranslateY(-2)
	frame:SetAnchorHor(0.0, 1.0)
	frame:SetAnchorVer(0.0, 1.0)
	frame:SetAnchorParamHor(25.0, -25.0)
	frame:SetAnchorParamVer(25.0, -100.0)
    frame:SetWidget(true)
    picBox:SetAlpha(0.6)
    picBox:UseAlphaBlend(true)

    local uiText = UIFText:New()
    frame:AttachChild(uiText)
    uiText.LocalTransform:SetTranslateY(-2.0)
    smapleglobals.TextCameraAddr = uiText
    uiText:GetText():SetText("IP")
    uiText:GetText():SetFontColor(Float3.BLACK)
	uiText:GetText():SetFontWidthHeight(20, 20)
	uiText:SetWidth(400.0)
	uiText:SetHeight(300.0)
    uiText:SetAnchorParamVer(10.0, 10.0)

    local btnConnect = UIButton:New("BtnConnect")
    frame:AttachChild(btnConnect)
	btnConnect.LocalTransform:SetTranslateY(-2.0)
	btnConnect:SetSize(200.0, 30.0)
    btnConnect:SetAnchorParamVer(-15.0, -15.0)
    btnConnect:CreateAddText("Connect")
    btnConnect:SetScriptHandler("s_SampleCtrlCallback")

    local btnRefresh = UIButton:New("BtnRefresh")
    frame:AttachChild(btnRefresh)
	btnRefresh.LocalTransform:SetTranslateY(-2.0)
    btnRefresh:SetSize(30.0, 30.0)
    btnRefresh:SetAnchorParamHor(130.0, 130.0)
    btnRefresh:SetAnchorParamVer(-15.0, -15.0)
    btnRefresh:CreateAddText("Ref")
    btnRefresh:SetScriptHandler("s_SampleCtrlCallback")

    local frameVedio = nil
    local platType = PX2_APP:GetPlatformType()
    if Application.PLT_WINDOWS == platType then
        frameVedio = UIVlc:New()
        frame:AttachChild(frameVedio)
        frameVedio:SetType(UIVlc.T_VLC)
        smapleglobals.FrameVLC = frameVedio
    elseif Application.PLT_ANDROID == platType then
        frameVedio = UIWebFrame:New()
        frame:AttachChild(frameVedio)
        frameVedio:SetUpdateToTex(true)
        frameVedio:ShowNativeView(false)
        smapleglobals.FrameWebFrame = frameVedio
    end
    frameVedio.LocalTransform:SetTranslateY(-0.1)
    frameVedio:SetAnchorHor(0.0, 1.0)
    frameVedio:SetAnchorParamHor(20.0, -20.0)
    frameVedio:SetAnchorVer(0.0, 1.0)
    frameVedio:SetAnchorParamVer(20.0, -20.0)
    frameVedio:SetPivot(0.5, 0.5)

    local frameLeft = UIRound:New("RoundCtrl")
    frame:AttachChild(frameLeft)
    frameLeft.LocalTransform:SetTranslateY(-2.0)
    frameLeft:SetAnchorHor(0.25, 0.25)
    frameLeft:SetAnchorVer(0.25, 0.25)
    frameLeft:SetSize(300.0, 300.0)
    frameLeft:GetButton():SetSize(150.0, 150.0)
    frameLeft:RegistToScriptSystem()
    frameLeft:SetScriptHandler("s_SampleCtrlCallback")

    local frameRight = UIRound:New("ServerCtrl")
    frame:AttachChild(frameRight)
    frameRight.LocalTransform:SetTranslateY(-2.0)
    frameRight:SetAnchorHor(0.75, 0.75)
    frameRight:SetAnchorVer(0.25, 0.25)
    frameRight:SetSize(300.0, 300.0)
    frameRight:GetButton():SetSize(150.0, 150.0)
    frameRight:RegistToScriptSystem()
    frameRight:SetScriptHandler("s_SampleCtrlCallback")

    PX2_APP:CreateEngineUDPServerEditor()

    s_RefreshDevice()

    return frame
end

UnRegistAllEventFunctions("EngineNetES::EngineClientUDPInfoChanged")
RegistEventFunction("EngineNetES::EngineClientUDPInfoChanged", function()
    s_RefreshDevice()
end)
function s_RefreshDevice()
    if nil~=smapleglobals.TextCameraAddr then
        smapleglobals.TextCameraAddr:GetText():SetText("")
        local numInfos = PX2_APP:GetNumUDPNetInfo()
        for i=1,numInfos,1 do
            local info = PX2_APP:GetUDPNetInfo(i-1)
            if UDPNetInfo.T_CAMERA==info.TheType then
                local txt = info.IP
                smapleglobals.CameraIP = txt
                smapleglobals.TextCameraAddr:GetText():SetText(txt)
            end
        end
    end
end

function s_CamConnect(ip)
    if nil~=smapleglobals.FrameVLC then
        smapleglobals.FrameVLC:StopVLC()
        local allAddr = "http://"..ip..":8080/?action=stream"
        smapleglobals.FrameVLC:StartVLC(allAddr)
    end

    if nil~=smapleglobals.FrameWebFrame then
        local allAddr = "http://"..ip..":8080/javascript_simple_fullscreen.html"
        smapleglobals.FrameWebFrame:LoadURL(allAddr)
        smapleglobals.FrameWebFrame:Show(true)
    end
end

pc_g_IsPressedLeft0 = false
pc_g_IsPressedLeft1 = false
pc_g_IsPressedRight0 = false
pc_g_IsPressedRight1 = false

local pc_SpeedAdjustGo = 1.0
local pc_SpeedAdjustTurn = 1.0
local pc_LastLeftType = 0
local pc_LastLeftSpeed = 0.0
local pc_LastRightType = 0
local pc_LastRightSpeed = 0.0

function s_SampleCtrlCallback(objPtr, callType)
	local obj = Cast:ToO(objPtr)
	
	local name = obj:GetName()
	if UICT_PRESSED==callType then

    elseif UICT_RELEASED==callType then
        if "BtnConnect"==name then
            s_CamConnect(smapleglobals.CameraIP)
        elseif "BtnRefresh"==name then
            s_RefreshDevice()
        end
    elseif UICT_RELEASED_NOTPICK==callType then
        --
    elseif UICT_ROUND_DRAG == callType then
        if "RoundCtrl" == name then      
            local leftMoveType = obj:GetDragingLeftMoveType()
            local leftMoveSpeed = obj:GetDragingLeftMoveSpeed()
            local rightMoveType = obj:GetDragingRightMoveType()
            local rightMoveSpeed = obj:GetDragingRightMoveSpeed()
            if leftMoveType == rightMoveType then
                leftMoveSpeed = leftMoveSpeed * pc_SpeedAdjustGo
                rightMoveSpeed = rightMoveSpeed * pc_SpeedAdjustGo
            else
                leftMoveSpeed = leftMoveSpeed * pc_SpeedAdjustTurn
                rightMoveSpeed = rightMoveSpeed * pc_SpeedAdjustTurn
            end

            if pc_LastLeftType~=leftMoveType or pc_LastLeftSpeed ~=leftMoveSpeed then
                local str = "left ".. leftMoveType .. " " .. leftMoveSpeed

                DatagramSocket:Bradcast(11139, str)

                pc_LastLeftType = leftMoveType
                pc_LastLeftSpeed = leftMoveSpeed
            end
            if pc_LastRightType~=rightMoveType or pc_LastRightSpeed ~=rightMoveSpeed then
                local str = "right ".. rightMoveType .. " " .. rightMoveSpeed

                DatagramSocket:Bradcast(11139, str)

                --PX2_ARDUINO:Run(1, rightMoveType, rightMoveSpeed)

                pc_LastRightType = rightMoveType
                pc_LastRightSpeed = rightMoveSpeed
            end
        end
    elseif UICT_ROUND_RELEASED == callType then
        if "RoundCtrl" == name then      
            --PX2_ARDUINO:Run(0, 0, 0)
            --PX2_ARDUINO:Run(1, 0, 0)

            local str = "left ".. 0 .. " " .. 0
            DatagramSocket:Bradcast(11139, str)
            local str = "right ".. 0 .. " " .. 0
            DatagramSocket:Bradcast(11139, str)

            pc_LastLeftType = 0
            pc_LastLeftSpeed = 0.0
            pc_LastRightType = 0
            pc_LastRightSpeed = 0.0
        end
    elseif UICT_ROUND_RELEASEDNOTPICK == callType then
        if "RoundCtrl" == name then      
            --PX2_ARDUINO:Run(0, 0, 0)
            --PX2_ARDUINO:Run(1, 0, 0)

            local str = "left ".. 0 .. " " .. 0
            DatagramSocket:Bradcast(11139, str)
            local str = "right ".. 0 .. " " .. 0
            DatagramSocket:Bradcast(11139, str)

            pc_LastLeftType = 0
            pc_LastLeftSpeed = 0.0
            pc_LastRightType = 0
            pc_LastRightSpeed = 0.0
        end
	end
end