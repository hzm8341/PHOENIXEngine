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

    return uiFrame
end