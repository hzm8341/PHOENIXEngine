-- voicepage.lua

function rc_VoicePage ()
    local uiFrame = UIFrame:New()

	uiFrame:SetAnchorHor(0.0, 1.0)
    uiFrame:SetAnchorVer(0.0, 1.0)
    
    local btnVoice = UIButton:New("BtnVoiceRecording")
    uiFrame:AttachChild(btnVoice)
    btnVoice.LocalTransform:SetTranslateY(-1.0)
    btnVoice:SetAnchorHor(0.5, 0.5)
    btnVoice:SetAnchorVer(0.5, 0.5)
    btnVoice:SetSize(200.0, 200.0)
    btnVoice:SetScriptHandler("rc_UICallabck")
    btnVoice:SetStateColorDefaultWhite()
    btnVoice:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("Data/RobotControl/images/voice.png")

    local text = UIFText:New()
    rc_SpeakText = text
    uiFrame:AttachChild(text)
    text.LocalTransform:SetTranslateY(-5.0)
    text:GetText():SetFontColor(Float3.WHITE)
    text:GetText():SetFontSize(36)
    text:SetAnchorVer(0.0, 0.0)
    text:SetAnchorParamVer(100.0, 100.0)
    text:SetSize(rc_TextWidth, rc_TextHeight)
    text:GetText():SetAutoWarp(true)
    text:GetText():SetText("你可以按着按钮说话")
    text:SetPivot(0.5, 0.5)

    return uiFrame
end