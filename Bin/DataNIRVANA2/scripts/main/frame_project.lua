-- frame_project.lua

function n_CreateFrame_Left_Project()
	local frame = UIFrame:New("FrameLeftProject")
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
	
	local butSyn = UIButton:New("ButSynchronize")
	frameTitle:AttachChild(butSyn)
	butSyn.LocalTransform:SetTranslateY(-1.0)
	butSyn:SetSize(g_n_t.Size_LeftTitleBar-4, g_n_t.Size_LeftTitleBar-4)
	butSyn:SetPivot(1.0, 0.5)
	butSyn:SetAnchorHor(1.0, 1.0)
	butSyn:SetAnchorVer(0.5, 0.5)
	butSyn:SetStateColor(UIButtonBase.BS_NORMAL, Float3.WHITE)
	butSyn:SetStateColor(UIButtonBase.BS_HOVERED, Float3.WHITE)
	butSyn:SetStateColor(UIButtonBase.BS_PRESSED, Float3.WHITE)
	butSyn:SetStateBrightness(UIButtonBase.BS_NORMAL, 1.0)
	butSyn:SetStateBrightness(UIButtonBase.BS_HOVERED, 0.9)
	butSyn:SetStateBrightness(UIButtonBase.BS_PRESSED, 0.7)
	butSyn:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("DataNIRVANA2/images/icons1/synchronize.png")
	butSyn:SetScriptHandler("n_ProjSyn")	
	
	local titleText = UIFText:New()
	frameTitle:AttachChild(titleText)
	titleText.LocalTransform:SetTranslateY(-1.0)
	titleText:SetAnchorHor(0.0, 1.0)
	titleText:SetAnchorParamHor(20.0, 0.0)
	titleText:SetAnchorVer(0.0, 1.0)
	local text = PX2_LM_EDITOR:GetValue("Project")
	titleText:GetText():SetText(text)
	titleText:GetText():SetFontScale(0.8)
	titleText:GetText():SetFontColor(Float3.WHITE)
	titleText:GetText():SetDrawStyle(FD_SHADOW)
	titleText:GetText():SetAligns(TEXTALIGN_LEFT+TEXTALIGN_VCENTER)
	
	local frameProject = EU_ProjectTree:New()
	frame:AttachChild(frameProject)
	frameProject:SetAnchorHor(0.0, 1.0)
	frameProject:SetAnchorVer(0.0, 1.0)
	frameProject:SetAnchorParamVer(0.0, -g_n_t.Size_LeftTitleBar)
	
	return frame
end

function n_ProjSyn(objPtr, callType)
	local obj = Cast:ToO(objPtr)
	local name = obj:GetName()

	local selectResData = PX2_EDIT:GetSelectedResource()
	local resPathname = selectResData.ResPathname

	if UICT_RELEASED == callType then
		if "ButSynchronize" == name then
			local engineClientConnector = PX2_APP:GetEngineClientConnector()
			local isConnected = engineClientConnector:IsConnected()
			if isConnected then
				engineClientConnector:SendAynchronize()
			end
		end
	end
end