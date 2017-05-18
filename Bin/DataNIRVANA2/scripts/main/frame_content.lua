-- frame_content.lua

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
function n_CreateFrame_ContentFrame()
    RegistEventFunction("EditorEventSpace::OpenContentRes", function(path, filename, outExtention)
		if "lua"==outExtention then
			local frameNew = n_CreateFrame_Content(path, filename, outExtention)
			n_g_FrameContentLogicTab:AddTab(path, filename, frameNew) 
			n_g_FrameContentLogicTab:SetActiveTab(path)
		end
	end)

	local frame = UIFrame:New()
	frame:SetAnchorHor(0.0, 1.0)
	frame:SetAnchorVer(0.0, 1.0)
	frame:SetAnchorParamHor(g_n_t.Size_LeftBar+g_n_t.Size_Left, 0.0)
	frame:SetAnchorParamVer(g_n_t.Size_StatusBar, 0.0)

	local frameTab = UITabFrame:New()
	n_g_FrameContentTab = frameTab
	frame:AttachChild(frameTab)
	frameTab:SetTabBarHeight(28)
	frameTab:SetTabHeight(28)
	frameTab:SetScriptHandler("n_ContentTableCallback")

	frameTab:AddTab("Welcome", PX2_LM_EDITOR:GetValue("WelcomeToUse"), n_CreateFrame_Welcome())
	frameTab:AddTab("Stage", PX2_LM_EDITOR:GetValue("Stage"), n_CreateFrame_SceneUI())
	frameTab:AddTab("Logic", PX2_LM_EDITOR:GetValue("Logic"), n_CreateFrame_Logic())
	frameTab:AddTab("Simu", PX2_LM_EDITOR:GetValue("Ply"), n_CreateFrame_Play())

	frameTab:SetActiveTab("Welcome")
	
	return frame
end

function n_CreateFrame_SceneUI()
	local frame = EU_StageFrame:New()
	frame:SetAnchorHor(0.0, 1.0)
	frame:SetAnchorVer(0.0, 1.0)
	return frame
end

function n_CreateFrame_Logic()
	local frame = UIFrame:New()
	frame:SetAnchorHor(0.0, 1.0)
	frame:SetAnchorVer(0.0, 1.0)

	local tabFrame = UITabFrame:New()
	frame:AttachChild(tabFrame)
	n_g_FrameContentLogicTab = tabFrame
	tabFrame:SetLayoutPos(UITabFrame.LPT_BOTTOM)
	tabFrame:SetAnchorHor(0.0, 1.0)
	tabFrame:SetAnchorVer(0.0, 1.0)
	tabFrame:SetTabBarHeight(25)
	tabFrame:SetTabHeight(25)
	if nil~=UIBBlockCataFrame then
		tabFrame:AddTab("BlueBlock", PX2_LM_EDITOR:GetValue("BlueBlock"), n_CreateFrame_BlueBlock())
	end
	if nil~=UIBluePrintFrame then
		tabFrame:AddTab("BluePrint", PX2_LM_EDITOR:GetValue("BluePrint"), n_CreateFrame_BluePrint())
	end
	tabFrame:SetActiveTab("BlueBlock")

	return frame
end

-- BlueBlock
n_g_FrameBlueBlockFrame = nil
n_g_FrameBlueBlockCodeEditor = nil
n_g_FrameBlueBlockCodeView = nil
n_g_FrameBlueBlockSplitter = nil
function n_BlueBlock_ShowCodeView(isShow)
	if isShow then
		n_BlueBlock_Callback(n_g_FrameBlueBlockSplitter, UICT_SPLITTER_DRAGING)
	else
		n_g_FrameBlueBlockCodeEditor:SetAnchorHor(0.0, 1.0)
		n_g_FrameBlueBlockCodeEditor:SetAnchorParamHor(0.0, 0.0)
	end

	n_g_FrameBlueBlockCodeView:Show(isShow)
	n_g_FrameBlueBlockSplitter:Show(isShow)
end
function n_BlueBlock_Callback(objPtr, callType)
	local obj = Cast:ToO(objPtr)
	local name = obj:GetName()
	if UICT_RELEASED==callType then
		if "ButShowCode" == name then
			local isShow = n_g_FrameBlueBlockCodeView:IsShow()
			n_BlueBlock_ShowCodeView(not isShow)
		end
	elseif UICT_SPLITTER_DRAGING==callType then
		local splitter = obj
		
		local spHalfWidth = splitter:GetWidth() * 0.5
		local blueBlockWidth = n_g_FrameBlueBlockFrame:GetWidth()

		local left = splitter:GetUserDataPointer("Left")
		local leftFrame = Cast:ToO(left)
		local right = splitter:GetUserDataPointer("Right")
		local rightFrame = Cast:ToO(right)
		local anchorParamHor = splitter:GetAnchorParamHor():X()
		
		leftFrame:SetAnchorHor(0.0, 0.0)
		leftFrame:SetPivot(0.0, 0.5)
		leftFrame:SetSize(anchorParamHor-spHalfWidth, 0.0)

		rightFrame:SetAnchorHor(0.0, 1.0)
		rightFrame:SetAnchorParamHor(anchorParamHor+spHalfWidth, 0.0)
	end
end
function n_CreateFrame_BlueBlock()
	local frame = UIFrame:New()
	n_g_FrameBlueBlockFrame = frame
	frame:SetAnchorHor(0.0, 1.0)
	frame:SetAnchorVer(0.0, 1.0)

	local codeViewWidth = 400.0

	-- block editor
	local frameBlockEditor = UIFrame:New()
	n_g_FrameBlueBlockCodeEditor = frameBlockEditor
	frame:AttachChild(frameBlockEditor)
	frameBlockEditor:SetAnchorVer(0.0, 1.0)

	local leftSize = 320.0
	local leftCataheight = 160.0
	local cataFrme = UIBBlockCataFrame:New()
	frameBlockEditor:AttachChild(cataFrme)
	cataFrme:SetCataType(UIBBlockCataFrame.CT_NORMAL)
	cataFrme:CreateCataButs()
	cataFrme:SetPivot(0.0, 1.0)
	cataFrme:SetAnchorHor(0.0, 0.0)
	cataFrme:SetAnchorVer(1.0, 1.0)
	cataFrme:SetAnchorParamVer(0.0, 0.0)
	cataFrme:SetSize(leftSize, leftCataheight)

	local butShowCode = UIButton:New("ButShowCode")
	cataFrme:AttachChild(butShowCode)
	butShowCode.LocalTransform:SetTranslateY(-5.0)
	butShowCode:SetAnchorHor(0.0, 1.0)
	butShowCode:SetAnchorVer(0.0, 0.0)
	butShowCode:SetSize(0.0, 20.0)
	butShowCode:SetPivot(0.5, 0.0)
	local showCodeText = PX2_LM_EDITOR:GetValue("ShowCode")
	butShowCode:CreateAddText(showCodeText)
	butShowCode:SetScriptHandler("n_BlueBlock_Callback")

	local editFrame = UIBBlockEdit:New()
	frameBlockEditor:AttachChild(editFrame)
	editFrame:SetAnchorHor(0.0, 1.0)
	editFrame:SetAnchorVer(0.0, 1.0)
	editFrame:SetAnchorParamHor(leftSize, 0.0)

	local toolFrame = UIBBlockEditToolFrame:New()
	frameBlockEditor:AttachChild(toolFrame)
	toolFrame.LocalTransform:SetTranslateY(-15.0)
	toolFrame:SetAnchorHor(0.0, 1.0)
	toolFrame:SetAnchorVer(1.0, 1.0)
	toolFrame:SetSize(0.0, 40.0)
	toolFrame:SetPivot(0.5, 1.0)
	
	local blocksCanvas = Canvas:New()
	frameBlockEditor:AttachChild(blocksCanvas)
	blocksCanvas.LocalTransform:SetTranslateY(-2.0)
	blocksCanvas:CreateUICameraNode()
	blocksCanvas:SetWidth(leftSize)
	blocksCanvas:SetAnchorHor(0.0, 0.0)
	blocksCanvas:SetAnchorParamHor(0.0, 0.0)
	blocksCanvas:SetAnchorVer(0.0, 1.0)
	blocksCanvas:SetAnchorParamVer(0.0, -leftCataheight)
	blocksCanvas:SetPivot(0.0, 0.5)
	blocksCanvas:SetClearColor(Float4:MakeColor(80, 80, 80, 255))

	local blocksFrame = UIBBlockPanels:New()
	blocksCanvas:AttachChild(blocksFrame)
	blocksFrame.LocalTransform:SetTranslateY(-2.0)
	blocksFrame:SetAnchorHor(0.0, 1.0)
	blocksFrame:SetAnchorVer(0.0, 1.0)

	local splitter = UISplitterFrame:New()
	n_g_FrameBlueBlockSplitter = splitter
	frame:AttachChild(splitter)
	splitter.LocalTransform:SetTranslateY(-10.0)
	splitter:SetHor(false)
	splitter:SetAnchorHor(0.0, 0.0)
	splitter:SetAnchorParamHor(900, 900)
	splitter:SetAnchorVer(0.0, 1.0)
	splitter:SetAnchorParamVer(0.0, 0.0)
	splitter:SetScriptHandler("n_BlueBlock_Callback")

	-- code view
	local codeView = EU_ContentFrame:New()
	frame:AttachChild(codeView)
	n_g_FrameBlueBlockCodeView = codeView
	codeView.LocalTransform:SetTranslateY(-10.0)
	codeView:SetName("CodeView")
	codeView:SetAnchorHor(0.0, 1.0)
	codeView:SetAnchorVer(0.0, 1.0)
	codeView:SetContString("--empty")
	codeView:SetContAcceptKeyboardInput(false)

	splitter:SetUserDataPointer("Left", frameBlockEditor)
	splitter:SetUserDataPointer("Right", codeView)
	n_BlueBlock_Callback(splitter, UICT_SPLITTER_DRAGING)

	n_BlueBlock_ShowCodeView(false)

	return frame
end

-- BlurPrint
n_g_FrameBluePrintFrame = nil
function n_CreateFrame_BluePrint()
	local frame = UIFrame:New()
	n_g_FrameBluePrintFrame = frame
	frame:SetAnchorHor(0.0, 1.0)
	frame:SetAnchorVer(0.0, 1.0)

	local printFrame = UIBluePrintFrame:New()
	frame:AttachChild(printFrame)
	printFrame.LocalTransform:SetTranslateY(-1.0)
	printFrame:SetAnchorHor(0.0, 1.0)
	printFrame:SetAnchorVer(0.0, 1.0)

	return frame
end

function n_CreateFrame_Play()
	local frame = EU_SimuFrame:New()
	frame:SetAnchorHor(0.0, 1.0)
	frame:SetAnchorVer(0.0, 1.0)
	return frame
end
