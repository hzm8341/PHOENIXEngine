-- common.lua

function ad_UISetTextFont(text, fontSize)
	text:SetFont("Data/engine/font.ttf", fontSize, fontSize)
end

function ad_UICreateDlgCommon(frameWidth, frameHeight, titleText)
	local uiFrameBack = UIFrame:New()
	uiFrameBack.LocalTransform:SetTranslateY(-2.0)
	local backPic = uiFrameBack:CreateAddBackgroundPicBox(true, Float3:MakeColor(0, 0, 0))
	backPic:SetAlpha(0.4)
	backPic:UseAlphaBlend(true)
	backPic:SetFakeTransparent(false)
	uiFrameBack:SetWidget(true)
	uiFrameBack:SetAnchorHor(0.0, 1.0)
    uiFrameBack:SetAnchorVer(0.0, 1.0)
    
	local uiFrame = UIFrame:New()
	uiFrameBack:AttachChild(uiFrame)
	local picBox = uiFrame:CreateAddBackgroundPicBox(true, Float3:MakeColor(255, 255, 255))
	picBox:SetTexture("Data/AIDoor/images/background.png")
	picBox:SetPicBoxType(UIPicBox.PBT_NINE)
	picBox:SetTexCornerSize(4.0, 4.0, 4.0, 4.0)
	picBox:UseAlphaBlend(true)
	uiFrame:SetWidget(true)
	uiFrame:SetAnchorHor(0.5, 0.5)
	uiFrame:SetAnchorVer(0.5, 0.5)
	uiFrame:SetSize(frameWidth, frameHeight)
    uiFrame.LocalTransform:SetTranslateY(-2.0)
    
    local textTitle = UIFText:New("TextTitle")
	uiFrame:AttachChild(textTitle)
	textTitle.LocalTransform:SetTranslateY(-1.0)
	textTitle:SetAnchorHor(0.0, 1.0)
	textTitle:SetAnchorVer(1.0, 1.0)
	textTitle:SetAnchorParamVer(-80.0, -80.0)
	textTitle:SetHeight(100.0)
	textTitle:GetText():SetText(titleText)
	ad_UISetTextFont(textTitle:GetText(), 48)

	local btnClose = UIButton:New("BtnDlgClose")
	uiFrame:AttachChild(btnClose)
	btnClose.LocalTransform:SetTranslateY(-1.0)
	btnClose:SetStateColorDefaultWhite()
	btnClose:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("Data/AIDoor/images/close.png")	
	btnClose:AutoMakeSizeFixable()
	btnClose:SetSize(50, 50)
	btnClose:SetAnchorHor(1.0, 1.0)
	btnClose:SetAnchorVer(1.0, 1.0)
	btnClose:SetPivot(1.0, 1.0)

	return uiFrameBack, uiFrame, btnClose, textTitle
end