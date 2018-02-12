-- ChaosCtrl.lua

g_Chaos = nil
g_ChaosText = nil
g_ChaosTextWidth = 660.0
g_ChaosTextHeight = 200.0

g_IsPlayingMusics = false
g_MusicsPlayIndex = 1

g_ChaosEditBoxName = nil
g_ChaosEditBoxID = nil

g_ChaosFrameSetting = nil
g_ChaosBleList = nil
g_ChaosBleConnect = nil

ch_MT = 0.75
ch_LT = 2.0
ch_LastDelay = 0.8

ChaosCtrl = class(LuaScriptController,
{
    _scriptControl = nil,
    _ctrlable = nil,
    _background = nil,

    _name = "零一机器人",
    _id = 1,

    _circleOut = nil,
    _circleOutCtrl = nil,

    _circleIn = nil,
    _circleInCtrl = nil,

    _circleBtn = nil,
    _circleBtnCtrl = nil,

    _yibackground = nil,

    _text = nil,

    _vlc = nil,

    _btnSetting = nil,
    _btnCamera = nil,
    _isCameraOpen = false,

    _musics = {},
});

function ChaosCtrl:OnAttached()
    self._scriptControl = Cast:ToSC(self.__object)
	self._ctrlable = self._scriptControl:GetControlledable()

    self._ctrlable:SetWidget(false)

    g_Chaos = self

    -- strlable
    self._ctrlable:SetScriptHandlerWidgetPicked("ChaosWidgetPicked")
    self._ctrlable:SetScriptHandlerNodePicked("ChaosFrameSizeNodePicked")
    self._ctrlable:SetScriptHandlerNodeNotPicked("ChaosFrameSizeNodeNotPicked")

    -- background
    local frame = UIFrame:New()
    self._background = frame
    self._ctrlable:AttachChild(frame)
    frame:SetAnchorHor(0.0, 1.0)
    frame:SetAnchorVer(0.0, 1.0)
    frame:CreateAddBackgroundPicBox(true)
    self:SetBackColor(Float3:MakeColor(0, 0, 0))

    -- circle out
    local fPicCircleOut = UIFPicBox:New()
    self._circleOut = fPicCircleOut
    frame:AttachChild(fPicCircleOut)
    fPicCircleOut.LocalTransform:SetTranslateY(-1.0)
    fPicCircleOut:GetUIPicBox():SetTexture("Data/Chaos/images/circle256.png")
    self:SetCircleOutColor(Float3:MakeColor(0, 54, 97))
    self:SetCircleOutSize(300)
    --fPicCircleOut:AutoMakeSizeFixable()
    --fPicCircleOut:SetColorSelfCtrled(true)

    -- circle in
    local fPicCircleIn = UIFPicBox:New()
    self._circleIn = fPicCircleIn
    frame:AttachChild(fPicCircleIn)
    fPicCircleIn.LocalTransform:SetTranslateY(-2.0)
    fPicCircleIn:GetUIPicBox():SetTexture("Data/Chaos/images/circle256.png")
    self:SetCircleInColor(Float3:MakeColor(0, 121, 216))
    self:SetCircleInSize(260)

    -- face btn
    local uiBtn = UIButton:New()
    self._circleBtn = uiBtn
    frame:AttachChild(uiBtn)
    uiBtn.LocalTransform:SetTranslateY(-3.0)
    uiBtn:SetStateColorDefaultWhite()
    uiBtn:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("Data/Chaos/images/circle256.png")
    self:SetFaceColor(Float3.ZERO)
    self:SetFaceSize(200)

    local fPicYi = UIFPicBox:New()
    self._yibackground = fPicYi
    uiBtn:AttachChild(fPicYi)
    fPicYi.LocalTransform:SetTranslateY(-3.0)
    fPicYi:SetColorSelfCtrled(true)
    fPicYi:GetUIPicBox():SetTexture("Data/Chaos/images/yi.png")
    fPicYi:SetAnchorHor(0.0, 1.0)
    fPicYi:SetAnchorVer(0.0, 1.0)
    fPicYi:SetAnchorParamVer(1.0, 4.0)
    fPicYi:SetAlpha(0.2)

    -- text
    local text = UIFText:New()
    self._text = text
    g_ChaosText = text
    frame:AttachChild(text)
    text.LocalTransform:SetTranslateY(-5.0)
    text:GetText():SetFontColor(Float3.WHITE)
    text:GetText():SetFontSize(36)
    text:SetAnchorVer(0.0, 0.0)
    text:SetAnchorParamVer(100.0, 100.0)
    text:SetSize(g_ChaosTextWidth, g_ChaosTextHeight)
    text:GetText():SetAutoWarp(true)
    self:SetText("你好，我是"..self._name)
    text:SetPivot(0.5, 0.5)
    --text:CreateAddBackgroundPicBox(false)

    -- vlc
    _vlc = UIVlc:New()
    frame:AttachChild(_vlc)
    _vlc.LocalTransform:SetTranslateY(-7.0)
    _vlc:SetAnchorHor(0.35, 0.65)
    _vlc:SetAnchorVer(0.75, 1.0)
    _vlc:SetType(UIVlc.T_HARDCAMERA)

    self:CloseCamera()

    -- setting
    self:CreateFrameSetting()

    -- musics
    self:MusicAdd(1, "Data/Chaos/media/music/canon.mp3")
    self:MusicAdd(2, "Data/Chaos/media/music/destination.mp3")
    self:MusicAdd(3, "Data/Chaos/media/music/roadtohappiness.mp3")
    self:MusicAdd(4, "Data/Chaos/media/music/stratus.mp3")
    self:MusicReWrite()
    self:MusicStop()

    -- ctrls
    local ctrlOut = InterpCurveUniformScaleController:New()
    self._circleOutCtrl = ctrlOut
    fPicCircleOut:AttachController(ctrlOut)

    local ctrlIn = InterpCurveUniformScaleController:New()
    self._circleInCtrl = ctrlIn
    fPicCircleIn:AttachController(ctrlIn)

    local ctrlBtn = InterpCurveUniformScaleController:New()
    self._circleBtnCtrl = ctrlBtn
    self._circleBtn:AttachController(ctrlBtn)

    PX2_VOICESDK:Speak("你好，我是混沌机器人")
    PX2_VOICESDK:EnableAutoSpeak(true)
    PX2_VOICESDK:EnableAutoSpeakTTS(true)     

    UnRegistAllEventFunctions("VoiceSDKSpace::SpeakText")
    RegistEventFunction("VoiceSDKSpace::SpeakText", function(txt)  
        --if not g_IsPlayingMusics then
            coroutine.wrap(function()     
                sleep(0.3)
                g_Chaos:SetText(txt)
                local fontWidth = g_ChaosText:GetText():GetTextWidth()
                if fontWidth < (g_ChaosTextWidth-20.0) then
                    g_ChaosText:GetText():SetRectUseage(RU_ALIGNS)
                    g_ChaosText:SetHeight(g_ChaosTextHeight)
                    g_ChaosText:SetAnchorParamVer(g_ChaosTextHeight*0.5, g_ChaosTextHeight*0.5)
                else
                    local numHeight = (fontWidth/g_ChaosTextWidth) * 1.0 + 1
                    local height = numHeight * 40
                    g_ChaosText:GetText():SetRectUseage(RU_CLIPWARP)
                    g_ChaosText:SetHeight(height)
                    if height>g_ChaosTextHeight then
                        g_ChaosText:SetAnchorParamVer(height*0.5, height*0.5)
                    end
                end
            end)()
        --end
    end)  

    UnRegistAllEventFunctions("VoiceSDKSpace::RecognizeResults")
    RegistEventFunction("VoiceSDKSpace::RecognizeResults", function(txt, txtJson)  
        g_Chaos:SetText(txt)
        local fontWidth = g_ChaosText:GetText():GetTextWidth()
        if fontWidth < (g_ChaosTextWidth-20.0) then
            g_ChaosText:GetText():SetRectUseage(RU_ALIGNS)
            g_ChaosText:SetHeight(g_ChaosTextHeight)
            g_ChaosText:SetAnchorParamVer(g_ChaosTextHeight*0.5, g_ChaosTextHeight*0.5)
        else
            local numHeight = (fontWidth/g_ChaosTextWidth) * 1.0 + 1
            local height = numHeight * 40
            g_ChaosText:GetText():SetRectUseage(RU_CLIPWARP)
            g_ChaosText:SetHeight(height)
            if height>g_ChaosTextHeight then
                g_ChaosText:SetAnchorParamVer(height*0.5, height*0.5)
            end
        end

        if "播放音乐" == txt then
            g_IsPlayingMusics = true
            g_Chaos:MusicPlayRandom()
            --PX2_VOICESDK:EnableAutoSpeakTTS(false)            
        elseif "停止音乐"==txt then
            g_IsPlayingMusics = false
            g_Chaos:MusicStop()
            --PX2_VOICESDK:EnableAutoSpeakTTS(true)            
        elseif "上一首"==txt or "上一手"==txt or "上一曲"==txt then
            if g_IsPlayingMusics then
                g_Chaos:MusicBefore()
            end
        elseif "下一首"==txt  or "下一手"==txt or "下一曲"==txt then
            if g_IsPlayingMusics then
                g_Chaos:MusicNext()
            end
        end
    end)  

    coroutine.wrap(function()     
        self:StartUp()
        sleep(ch_LT+ch_LastDelay)
        self:Idle()
    end)()
end

function ChaosCtrl:OnInitUpdate()
end

function ChaosCtrl:OnUpdate()
end

function ChaosCtrl:OnPPlay()
end

function ChaosCtrl:OnPUpdate()
end

-- funs setting
function ChaosCtrl:CreateFrameSetting()
    -- setting btn
    local btnSetting = UIButton:New("BtnSetting")
    self._btnSetting = btnSetting
    self._background:AttachChild(btnSetting)
    btnSetting.LocalTransform:SetTranslateY(-5.0)
    btnSetting:SetAnchorHor(0.0, 0.0)
    btnSetting:SetAnchorVer(1.0, 1.0)
    btnSetting:SetAnchorParamHor(60.0, 60.0)
    btnSetting:SetAnchorParamVer(-60.0, -60.0)
    btnSetting:SetSize(40.0, 40.0)
    btnSetting:SetStateColorDefaultWhite()
    btnSetting:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("Data/Chaos/images/circle.png")
    btnSetting:SetStateColor(UIButtonBase.BS_NORMAL, Float3:MakeColor(0, 121, 216))
    btnSetting:SetStateColor(UIButtonBase.BS_PRESSED, Float3:MakeColor(0, 121, 216))
    btnSetting:SetStateColor(UIButtonBase.BS_HOVERED, Float3:MakeColor(0, 121, 216))
    btnSetting:SetScriptHandler("ch_UICallabck")

    -- text testing
    local textTesting = UIFText:New()
    self._background:AttachChild(textTesting)
    textTesting.LocalTransform:SetTranslateY(-5.0)
    textTesting:GetText():SetFontColor(Float3.WHITE)
    textTesting:GetText():SetFontSize(20)
    textTesting:SetWidth(200)
    textTesting:SetAnchorHor(0.0, 0.0)
    textTesting:SetAnchorVer(1.0, 1.0)
    textTesting:SetPivot(0.0, 0.5)
    textTesting:SetAnchorParamHor(60.0, 60.0)
    textTesting:SetAnchorParamVer(-60.0, -60.0)
    textTesting:GetText():SetText("测试版 v 1.0.0")

    -- cam btn
    local btnCamera = UIButton:New("BtnCamera")
    self._btnCamera = btnCamera
    self._background:AttachChild(btnCamera)
    btnCamera.LocalTransform:SetTranslateY(-5.0)
    btnCamera:SetAnchorHor(1.0, 1.0)
    btnCamera:SetAnchorVer(1.0, 1.0)
    btnCamera:SetAnchorParamHor(-60.0, -60.0)
    btnCamera:SetAnchorParamVer(-60.0, -60.0)
    btnCamera:SetSize(40.0, 40.0)
    btnCamera:SetStateColorDefaultWhite()
    btnCamera:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("Data/Chaos/images/circle.png")
    btnCamera:SetStateColor(UIButtonBase.BS_NORMAL, Float3:MakeColor(0, 121, 216))
    btnCamera:SetStateColor(UIButtonBase.BS_PRESSED, Float3:MakeColor(0, 121, 216))
    btnCamera:SetStateColor(UIButtonBase.BS_HOVERED, Float3:MakeColor(0, 121, 216))
    btnCamera:SetScriptHandler("ch_UICallabck")

    -- frame
	local uiFrameBack, uiFrame, btnClose, titleText = chaos_UICreateDlgCommon(478.0, 324.0, "")
    uiFrame:SetAnchorHor(0.0, 1.0)
	uiFrame:SetAnchorParamHor(80.0, -80.0)
	uiFrame:SetAnchorVer(0.0, 1.0)
    uiFrame:SetAnchorParamVer(80.0, -80.0)
    btnClose:SetScriptHandler("ch_UICallabck")

    -- buts
    local frameTab = UITabFrame:New()
    uiFrame:AttachChild(frameTab)
    frameTab.LocalTransform:SetTranslateY(-1.0)
    frameTab:SetAnchorHor(0.0, 1.0)
    frameTab:SetAnchorVer(0.0, 1.0)
    frameTab:SetAnchorParamVer(0.0, -60.0)
    frameTab:SetTabBarHeight(42.0)
    frameTab:SetTabHeight(42.0)
    frameTab:SetFontColor(Float3.WHITE)

    -- setting
    local frame = ch_SettingFrame()
    frameTab:AddTab("Setting", PX2_LM_APP:GetValue("Setting"), frame)
    local txt = frameTab:GetTabButton("Setting"):GetText()
    ch_UISetTextFont(txt, 16)

    -- ble frame
    local frameBle = ch_Connect()
    frameTab:AddTab("Connect", PX2_LM_APP:GetValue("Connect"), frameBle)
    local txt = frameTab:GetTabButton("Connect"):GetText()
    ch_UISetTextFont(txt, 16)

    frameTab:SetActiveTab("Setting")

    self._frameSetting = uiFrameBack
    g_ChaosFrameSetting = uiFrameBack
    self._background:AttachChild(uiFrameBack)
    uiFrameBack.LocalTransform:SetTranslateY(-10.0)
    g_ChaosFrameSetting:Show(false)
end

-- functions

-- 设置名称
function ChaosCtrl:SetName(name)
    self._name = name
end

function ChaosCtrl:GetName()
    return self._name
end

function ChaosCtrl:SetID(id)
    self._id = id
    PX2BBLOCK_SYS:setDeviceID(id)
end

function ChaosCtrl:GetID()
    return self._id
end

-- 设置背景色
function ChaosCtrl:SetBackColor(color)
    self._background:GetBackgroundPicBox():SetColor(color)
end

-- 设置CircleOut颜色
function ChaosCtrl:SetCircleOutColor(color)
    self._circleOut:SetColor(color)
end
-- 设置CircleOut大小
function ChaosCtrl:SetCircleOutSize(size)
    self._circleOut:SetSize(size, size)
end

-- 设置CircleIn颜色
function ChaosCtrl:SetCircleInColor(color)
    self._circleIn:SetColor(color)
end
-- 设置CircleIn大小
function ChaosCtrl:SetCircleInSize(size)
    self._circleIn:SetSize(size, size)
end

-- 设置Face颜色
function ChaosCtrl:SetFaceColor(color)
    self._circleBtn:SetColor(color)
end
-- 设置Face大小
function ChaosCtrl:SetFaceSize(size)
    self._circleBtn:SetSize(size, size)
end

-- 设置文字
function ChaosCtrl:SetText(text)
    self._text:GetText():SetText(text)
end

-- 待机
function ChaosCtrl:StartUp()
    self._circleOutCtrl:Clear()
    self._circleOutCtrl:AddPoint(0.0, 0.0001, ICM_LINEAR) --ICM_LINEAR ICM_CURVE_AUTO
    self._circleOutCtrl:AddPoint(ch_MT, 1.05, ICM_LINEAR)   
    self._circleOutCtrl:AddPoint(ch_LT, 1.0, ICM_LINEAR)   
    self._circleOutCtrl.MaxTime = ch_LT
    self._circleOutCtrl.Repeat = Controller.RT_CLAMP
    self._circleOutCtrl:SetDelayPlayTime(0.0)
    self._circleOutCtrl:ResetPlay()

    self._circleInCtrl:Clear()
    self._circleInCtrl:AddPoint(0.0, 0.0001, ICM_LINEAR) --ICM_LINEAR ICM_CURVE_AUTO
    self._circleInCtrl:AddPoint(ch_MT, 1.2, ICM_LINEAR)   
    self._circleInCtrl:AddPoint(ch_LT, 1.0, ICM_LINEAR)   
    self._circleInCtrl.MaxTime = ch_LT
    self._circleInCtrl.Repeat = Controller.RT_CLAMP
    self._circleInCtrl:SetDelayPlayTime(0.4)
    self._circleInCtrl:ResetPlay()

    self._circleBtnCtrl:Clear()
    self._circleBtnCtrl:AddPoint(0.0, 0.0001, ICM_LINEAR) --ICM_LINEAR ICM_CURVE_AUTO
    self._circleBtnCtrl:AddPoint(ch_MT, 0.88, ICM_LINEAR)   
    self._circleBtnCtrl:AddPoint(ch_LT, 1.0, ICM_LINEAR)   
    self._circleBtnCtrl.MaxTime = ch_LT
    self._circleBtnCtrl.Repeat = Controller.RT_CLAMP
    self._circleBtnCtrl:SetDelayPlayTime(ch_LastDelay)
    self._circleBtnCtrl:ResetPlay()
end

-- 冰冻
function ChaosCtrl:Freeze()
    self._circleOutCtrl:Clear()
    self._circleOutCtrl:AddPoint(0.0, 1.0, ICM_CURVE_AUTO) --ICM_LINEAR ICM_CURVE_AUTO
    self._circleOutCtrl.MaxTime = 1.0
    self._circleOutCtrl.Repeat = Controller.RT_WRAP
    self._circleOutCtrl:ResetPlay()

    self._circleInCtrl:Clear()
    self._circleInCtrl:AddPoint(0.0, 1.0, ICM_CURVE_AUTO) --ICM_LINEAR ICM_CURVE_AUTO
    self._circleInCtrl.MaxTime = 1.0
    self._circleInCtrl.Repeat = Controller.RT_WRAP
    self._circleInCtrl:ResetPlay()

    self._circleBtnCtrl:Clear()
    self._circleBtnCtrl:AddPoint(0.0, 1.0, ICM_CURVE_AUTO) --ICM_LINEAR ICM_CURVE_AUTO
    self._circleBtnCtrl.MaxTime = 1.0
    self._circleBtnCtrl.Repeat = Controller.RT_WRAP
    self._circleBtnCtrl:ResetPlay()
end

-- 待机
function ChaosCtrl:Idle()
    self._circleOutCtrl:Clear()
    self._circleOutCtrl:AddPoint(0.0, 1.0, ICM_CURVE_AUTO) --ICM_LINEAR ICM_CURVE_AUTO
    self._circleOutCtrl:AddPoint(1.5, 1.05, ICM_CURVE_AUTO)   
    self._circleOutCtrl:AddPoint(3.0, 1.0, ICM_CURVE_AUTO)   
    self._circleOutCtrl.MaxTime = 3.0
    self._circleOutCtrl.Repeat = Controller.RT_WRAP
    self._circleOutCtrl:ResetPlay()

    self._circleInCtrl:Clear()
    self._circleInCtrl:AddPoint(0.0, 1.0, ICM_CURVE_AUTO) --ICM_LINEAR ICM_CURVE_AUTO
    self._circleInCtrl:AddPoint(1.5, 0.9, ICM_CURVE_AUTO)   
    self._circleInCtrl:AddPoint(3.0, 1.0, ICM_CURVE_AUTO)   
    self._circleInCtrl.MaxTime = 3.0
    self._circleInCtrl.Repeat = Controller.RT_WRAP
    self._circleInCtrl:ResetPlay()

    self._circleBtnCtrl:Clear()
    self._circleBtnCtrl:AddPoint(0.0, 1.0, ICM_CURVE_AUTO) --ICM_LINEAR ICM_CURVE_AUTO
    self._circleBtnCtrl:AddPoint(1.5, 0.88, ICM_CURVE_AUTO)   
    self._circleBtnCtrl:AddPoint(3.0, 1.0, ICM_CURVE_AUTO)   
    self._circleBtnCtrl.MaxTime = 3.0
    self._circleBtnCtrl.Repeat = Controller.RT_WRAP
    self._circleBtnCtrl:ResetPlay()
end

-- 兴奋
function ChaosCtrl:Excite()
end

-- 音乐
function ChaosCtrl:MusicAdd(index, musicPath)
    self._musics[index] = musicPath
end

function ChaosCtrl:MusicReWrite()
    for index,value in ipairs(self._musics) do
        local pathStr = value
        local musicName = index..".mp3"

        local dstPath = ResourceManager:GetWriteablePath()..musicName
        if not PX2_RM:IsFileFloderExist(dstPath) then
            PX2_RM:ReWriteFileToWriteablePath(pathStr, musicName)
        end      
    end
end

function ChaosCtrl:MusicPlayRandom()
    local tabSize = table.getn(self._musics)
    g_MusicsPlayIndex = Mathf:IntRandom(1, tabSize+1)   
    self:MusicPlay(g_MusicsPlayIndex)
end

function ChaosCtrl:MusicPlay(index)
    local tabSize = table.getn(self._musics)

    if index>=1 and index<=tabSize then
        local dstPath = ResourceManager:GetWriteablePath()..index..".mp3"
        PX2_SS:PlayMusic(0, dstPath, true, 0.0)
    end
end

function ChaosCtrl:MusicStop()
    g_MusicsPlayIndex = 1
	PX2_SS:PlayMusic(0, nil, true, 0.0)
end

function ChaosCtrl:MusicBefore()
    local tabSize = table.getn(self._musics)
    g_MusicsPlayIndex = g_MusicsPlayIndex - 1
    if g_MusicsPlayIndex < 1 then
        g_MusicsPlayIndex = tabSize
    end
    if g_MusicsPlayIndex > tabSize then
        g_MusicsPlayIndex = 1
    end    
    self:MusicPlay(g_MusicsPlayIndex)
end

function ChaosCtrl:MusicNext()
    local tabSize = table.getn(self._musics)
    g_MusicsPlayIndex = g_MusicsPlayIndex + 1
    if g_MusicsPlayIndex < 1 then
        g_MusicsPlayIndex = tabSize
    end
    if g_MusicsPlayIndex > tabSize then
        g_MusicsPlayIndex = 1
    end    
    self:MusicPlay(g_MusicsPlayIndex)
end

-- camera
function ChaosCtrl:OpenCamera(isFront)
    -- body
    if isFront then
        PX2_HARDCAMERA:OpenCamera(1)
        _vlc:SetHorSpaw(true)
    else
        PX2_HARDCAMERA:OpenCamera(0)
        _vlc:SetHorSpaw(false)
    end

    _vlc:Show(true)

    self._isCameraOpen = true
end

function ChaosCtrl:CloseCamera()
    PX2_HARDCAMERA:CloseCamera()
    _vlc:Show(false)

    self._isCameraOpen = false
end

function ChaosCtrl:IsCameraOpened()
    return self._isCameraOpen
end

-- touch
function ChaosWidgetPicked(ptr)
    local obj = Cast:ToO(ptr)    
end

function ChaosFrameSizeNodePicked(ptr)
    local obj = Cast:ToO(ptr)    
end

function ChaosFrameSizeNodeNotPicked(ptr)
    local obj = Cast:ToO(ptr)    
end


function ch_UICallabck(ptr, callType)
    local obj = Cast:ToO(ptr) 
	local name = obj:GetName()	

    if UICT_PRESSED==callType then
        playFrameScale(obj)
	elseif UICT_RELEASED==callType then
        playFrameNormal(obj)

        if "BtnSetting"==name then
            g_ChaosFrameSetting:Show(true)
            g_ChaosEditBoxName:SetText("".. g_Chaos:GetName())
            g_ChaosEditBoxID:SetText("".. g_Chaos:GetID())
        elseif "BtnCamera"==name then
            if not g_Chaos:IsCameraOpened() then
                g_Chaos:OpenCamera(0)
            else
                g_Chaos:CloseCamera()
            end
        elseif "BtnDlgClose"==name then
            g_ChaosFrameSetting:Show(false)
		end
    elseif UICT_RELEASED_NOTPICK==callType then
        playFrameNormal(obj)
    elseif UICT_ROUND_RELEASEDNOTPICK==callType then
    elseif UICT_CHECKED==callType then
    elseif UICT_DISCHECKED==callType then
	end
end