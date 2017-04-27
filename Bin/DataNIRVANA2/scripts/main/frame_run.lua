-- frame_run.lua

function n_PlayButCallback(objPtr, callType)
	local but = Cast:ToO(objPtr)
	local name = but:GetName()
	if UICT_RELEASED==callType then
		if "ButSimu" == name then
			PX2_APP:Play(Application.PT_SIMULATE)
		elseif "ButRun" == name then
			PX2_APP:Play(Application.PT_PLAY)
		elseif "ButRunInWindow" == name then
			PX2_EDIT:BroadCastEditorEventPlayInWindow()
		end
	end
end

function n_CreateFrame_Left_Run()
	local frame = UIFrame:New()
	frame:SetAnchorHor(0.0, 1.0)
	frame:SetAnchorVer(0.0, 1.0)
	
	-- title
	local titleHeight = g_n_t.Size_LeftTitleBar
	local frameTitle = UIFrame:New()
	frame:AttachChild(frameTitle)
	frameTitle.LocalTransform:SetTranslateY(-1.0)
	frameTitle:SetAnchorHor(0.0, 1.0)
	frameTitle:SetAnchorVer(1.0, 1.0)
	frameTitle:SetPivot(0.5, 1.0)
	frameTitle:SetSize(0.0, titleHeight)
	
	local titleText = UIFText:New()
	frameTitle:AttachChild(titleText)
	titleText.LocalTransform:SetTranslateY(-1.0)
	titleText:SetAnchorHor(0.0, 1.0)
	titleText:SetAnchorParamHor(20.0, 0.0)
	titleText:SetAnchorVer(0.0, 1.0)
	local text = PX2_LM_EDITOR:GetValue("Run")
	titleText:GetText():SetText(text)
	titleText:GetText():SetFontScale(0.8)
	titleText:GetText():SetFontColor(Float3.WHITE)
	titleText:GetText():SetDrawStyle(FD_SHADOW)
	titleText:GetText():SetAligns(TEXTALIGN_LEFT+TEXTALIGN_VCENTER)

	local butMinus = 4
	
	-- run
	local butPlayInWindow = UIButton:New("ButRunInWindow")
	frameTitle:AttachChild(butPlayInWindow)
	butPlayInWindow.LocalTransform:SetTranslateY(-1.0)
	butPlayInWindow:SetAnchorHor(1.0, 1.0)
	butPlayInWindow:SetAnchorParamHor(-titleHeight*0.5, -titleHeight*0.5)
	butPlayInWindow:SetAnchorVer(0.5, 0.5)
	butPlayInWindow:SetSize(titleHeight-butMinus, titleHeight-butMinus)	
	butPlayInWindow:SetStateColor(UIButtonBase.BS_NORMAL, Float3.WHITE)
	butPlayInWindow:SetStateColor(UIButtonBase.BS_HOVERED, Float3.WHITE)
	butPlayInWindow:SetStateColor(UIButtonBase.BS_PRESSED, Float3.WHITE)	
	butPlayInWindow:SetStateBrightness(UIButtonBase.BS_NORMAL, 1.0)
	butPlayInWindow:SetStateBrightness(UIButtonBase.BS_HOVERED, 1.2)
	butPlayInWindow:SetStateBrightness(UIButtonBase.BS_PRESSED, 1.0)
	butPlayInWindow:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("DataNIRVANA2/images/icons1/runinwindow.png")
	butPlayInWindow:SetScriptHandler("n_PlayButCallback")

	local butPlay = UIButton:New("ButRun")
	frameTitle:AttachChild(butPlay)
	butPlay.LocalTransform:SetTranslateY(-1.0)
	butPlay:SetAnchorHor(1.0, 1.0)
	butPlay:SetAnchorParamHor(-titleHeight*1.5, -titleHeight*1.5)
	butPlay:SetAnchorVer(0.5, 0.5)
	butPlay:SetSize(titleHeight-butMinus, titleHeight-butMinus)	
	butPlay:SetStateColor(UIButtonBase.BS_NORMAL, Float3.WHITE)
	butPlay:SetStateColor(UIButtonBase.BS_HOVERED, Float3.WHITE)
	butPlay:SetStateColor(UIButtonBase.BS_PRESSED, Float3.WHITE)	
	butPlay:SetStateBrightness(UIButtonBase.BS_NORMAL, 1.0)
	butPlay:SetStateBrightness(UIButtonBase.BS_HOVERED, 1.2)
	butPlay:SetStateBrightness(UIButtonBase.BS_PRESSED, 1.0)
	butPlay:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("DataNIRVANA2/images/icons1/run.png")
	butPlay:SetScriptHandler("n_PlayButCallback")

	local butSimu = UIButton:New("ButSimu")
	frameTitle:AttachChild(butSimu)
	butSimu.LocalTransform:SetTranslateY(-1.0)
	butSimu:SetAnchorHor(1.0, 1.0)
	butSimu:SetAnchorParamHor(-titleHeight*2.5, -titleHeight*2.5)
	butSimu:SetAnchorVer(0.5, 0.5)
	butSimu:SetSize(titleHeight-butMinus, titleHeight-butMinus)	
	butSimu:SetStateColor(UIButtonBase.BS_NORMAL, Float3.WHITE)
	butSimu:SetStateColor(UIButtonBase.BS_HOVERED, Float3.WHITE)
	butSimu:SetStateColor(UIButtonBase.BS_PRESSED, Float3.WHITE)	
	butSimu:SetStateBrightness(UIButtonBase.BS_NORMAL, 1.0)
	butSimu:SetStateBrightness(UIButtonBase.BS_HOVERED, 1.2)
	butSimu:SetStateBrightness(UIButtonBase.BS_PRESSED, 1.0)
	butSimu:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("DataNIRVANA2/images/icons1/simu.png")
	butSimu:SetScriptHandler("n_PlayButCallback")
	
	local editBoxHeight = 22.0
	local editBox = UIEditBox:New()
	frame:AttachChild(editBox)
	editBox.LocalTransform:SetTranslateY(-1.0)
	editBox:SetSize(0.0, editBoxHeight)
	editBox:SetAnchorHor(0.0, 1.0)
	editBox:SetAnchorParamHor(0.0, -0.0)
	editBox:SetAnchorVer(1.0, 1.0)
	editBox:SetAnchorParamVer(-titleHeight-editBoxHeight*0.5, -titleHeight-editBoxHeight*0.5)
	
	local butConnectHeight = 26.0
	local butConnect = UIButton:New("ButConnect")
	frame:AttachChild(butConnect)
	butConnect.LocalTransform:SetTranslateY(-1.0)
	butConnect:SetSize(butConnectHeight, butConnectHeight)
	butConnect:SetPivot(0.5, 0.5)
	butConnect:SetAnchorHor(0.0, 1.0)
	butConnect:SetAnchorParamHor(0.0, -0.0)
	butConnect:SetAnchorVer(1.0, 1.0)
	butConnect:SetAnchorParamVer(-titleHeight-editBoxHeight-butConnectHeight*0.5, -titleHeight-editBoxHeight-butConnectHeight*0.5)
	butConnect:CreateAddText(PX2_LM_EDITOR:GetValue("ConnectToServer"), Float3.WHITE)
	
	-- console
	local consoleFrame = EU_ConcoleFrame:New()
	frame:AttachChild(consoleFrame)
	consoleFrame.LocalTransform:SetTranslateY(-1.0)
	consoleFrame:SetAnchorHor(0.0, 1.0)
	consoleFrame:SetAnchorVer(0.0, 1.0)
	consoleFrame:SetAnchorParamVer(0.0, -titleHeight-editBoxHeight-butConnectHeight-10)
	
	return frame
end
