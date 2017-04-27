-- frame_market.lua

function n_CreateFrame_Left_Market()
	local frame = UIFrame:New()
	frame:SetAnchorHor(0.0, 1.0)
	frame:SetAnchorVer(0.0, 1.0)
	
	-- title
	local frameTitle = UIFrame:New()
	frame:AttachChild(frameTitle)
	frameTitle.LocalTransform:SetTranslateY(-1.0)
	frameTitle:SetAnchorHor(0.0, 1.0)
	frameTitle:SetAnchorVer(1.0, 1.0)
	frameTitle:SetPivot(0.5, 1.0)
	frameTitle:SetSize(0.0, g_n_t.Size_LeftTitleBar)
	
	local titleText = UIFText:New()
	frameTitle:AttachChild(titleText)
	titleText.LocalTransform:SetTranslateY(-1.0)
	titleText:SetAnchorHor(0.0, 1.0)
	titleText:SetAnchorParamHor(20.0, 0.0)
	titleText:SetAnchorVer(0.0, 1.0)
	local text = PX2_LM_EDITOR:GetValue("Market")
	titleText:GetText():SetText(text)
	titleText:GetText():SetFontScale(0.8)
	titleText:GetText():SetFontColor(Float3.WHITE)
	titleText:GetText():SetDrawStyle(FD_SHADOW)
	titleText:GetText():SetAligns(TEXTALIGN_LEFT+TEXTALIGN_VCENTER)
	
	local webFrame = UIWebFrame:New()
	frame:AttachChild(webFrame)
	webFrame:SetAnchorHor(0.0, 1.0)
	webFrame:SetAnchorVer(0.0, 1.0)
	webFrame:SetAnchorParamVer(0.0, -g_n_t.Size_LeftTitleBar)
	webFrame:LoadURL("http://manykit.ydmh5.com")
	webFrame:SetUpdateToTex(true)
		
	return frame
end