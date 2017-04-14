-- mainedit.lua

-- main aui
function n_MainAuiCallback(objPtr, callType)
	local tabObj = Cast:ToO(objPtr)
	
	local name = tabObj:GetName()
	if UICT_TABFRAME_SETACTIVE==callType then

	end
end

function n_CreateFrame_Welcome()
	local frameWelcome = UIFrame:New()
	frameWelcome:SetAnchorHor(0.0, 1.0)
	frameWelcome:SetAnchorVer(0.0, 1.0)
	
	local canvas = Canvas:New()
	canvas:CreateUICameraNode()
	frameWelcome:AttachChild(canvas)
	canvas:GetUICameraNode():GetCamera():SetClearColor(Float4(g_n_t.Color_MainAUI:X(), g_n_t.Color_MainAUI:Y(), g_n_t.Color_MainAUI:Z(), 1.0))
	canvas:SetAnchorHor(0.0, 1.0)
	canvas:SetAnchorVer(0.0, 1.0)
	
	local uiPicBox = UIFPicBox:New()
	canvas:AttachChild(uiPicBox)
	uiPicBox.LocalTransform:SetTranslateY(-1.0)
	uiPicBox:GetUIPicBox():SetTexture("DataNIRVANA2/images/welcome.png")
	uiPicBox:MakeSizeWithTex()
	
	return frameWelcome
end

function n_CreateFrame_Content(path, name, outExtention)
	local frame = EU_ContentFrame:New()
	frame:SetName(name)
	frame:SetAnchorHor(0.0, 1.0)
	frame:SetAnchorVer(0.0, 1.0)
	
	if "lua"==outExtention or "txt"==outExtention or "xml"==outExtention then
		frame:SetCont(EU_ContentFrame.CT_TEXT, path)
	elseif "png" == outExtention then
		frame:SetCont(EU_ContentFrame.CT_PREVIEW, path)
	elseif "px2obj" == outExtention then
		frame:SetCont(EU_ContentFrame.CT_PREVIEW, path)
	end
	
	return frame
end

function n_ContentTableCallback(objPtr, callType)
	local tableObj = Cast:ToO(objPtr)
	
	local activeTablePath = tableObj:GetActiveTab()
	if UICT_TABFRAME_SETACTIVE==callType then
		PX2_EDIT:SetActivateOpenedFile(activeTablePath)
	end
end
function n_CreateFrame_ContentTable()
    RegistEventFunction("EditorEventSpace::OpenContentRes", function(path, filename, outExtention)
		local frameNew = n_CreateFrame_Content(path, filename, outExtention)
		n_g_FrameContentTab:AddTab(path, filename, frameNew) 
		n_g_FrameContentTab:SetActiveTab(path)
	end)

	local frame = UITabFrame:New()
	frame:SetTabBarHeight(28)
	frame:SetTabHeight(28)
	frame:SetScriptHandler("n_ContentTableCallback")

	frame:AddTab("Welcome", PX2_LM_EDITOR:GetValue("WelcomeToUse"), n_CreateFrame_Welcome())

	frame:SetActiveTab("Welcome")
	
	return frame
end
