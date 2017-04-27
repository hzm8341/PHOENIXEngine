-- frame_content.lua

function n_CreateFrame_Welcome1()
	local frame = UIFrame:New()
	frame:SetAnchorHor(0.0, 1.0)
	frame:SetAnchorVer(0.0, 1.0)

	local webFrame = UIWebFrame:New()
	frame:AttachChild(webFrame)
	webFrame:SetAnchorHor(0.0, 1.0)
	webFrame:SetAnchorVer(0.0, 1.0)
	webFrame:SetUpdateToTex(true)
	webFrame:LoadURL("file:///DataNIRVANA2/web/index.html")

	return frame
end

function n_CreateFrame_Welcome()
	local frameWelcome = UIFrame:New()
	frameWelcome:SetAnchorHor(0.0, 1.0)
	frameWelcome:SetAnchorVer(0.0, 1.0)
	
	local canvas = Canvas:New()
	canvas:CreateUICameraNode()
	frameWelcome:AttachChild(canvas)
	canvas:SetClearColor(Float4(g_n_t.Color_MainAUI:X(), g_n_t.Color_MainAUI:Y(), g_n_t.Color_MainAUI:Z(), 1.0))
	canvas:SetAnchorHor(0.0, 1.0)
	canvas:SetAnchorVer(0.0, 1.0)

	local frameLeft = UIFrame:New()
	canvas:AttachChild(frameLeft)
	frameLeft:SetAnchorHor(0.0, 1.0)
	frameLeft:SetAnchorParamHor(230.0, 0.0)
	frameLeft:SetAnchorVer(0.0, 1.0)

	local fPicBoxLogo = UIFPicBox:New()
	frameLeft:AttachChild(fPicBoxLogo)
	fPicBoxLogo.LocalTransform:SetTranslateY(-1.0)
	fPicBoxLogo:SetPivot(1.0, 1.0)
	fPicBoxLogo:SetAnchorHor(0.0, 0.0)
	fPicBoxLogo:SetAnchorParamHor(-40.0, -40.0)
	fPicBoxLogo:SetAnchorVer(1.0, 1.0)
	fPicBoxLogo:SetAnchorParamVer(-130.0, -130.0)
	fPicBoxLogo:GetUIPicBox():SetTexture("DataNIRVANA2/images/logo/phoenix.png")
	fPicBoxLogo:SetSize(100, 100)

	local titleText = UIFText:New()
	frameLeft:AttachChild(titleText)
	titleText:SetAnchorHor(0.0, 1.0)
	titleText:SetAnchorVer(1.0, 1.0)
	titleText:SetAnchorParamVer(-140.0, -140.0)
	titleText:SetPivot(0.0, 1.0)
	titleText:SetSize(0.0, 50.0)
	titleText:GetText():SetFontWidthHeight(32, 32)
	titleText:GetText():SetFontColor(g_n_t.Color_FontBlue1)
	titleText:GetText():SetAligns(TEXTALIGN_LEFT+TEXTALIGN_TOP)
	titleText:GetText():SetText("Hello, 欢迎使用PhoenixIOT！")

	local titleTextDesc = UIFText:New()
	frameLeft:AttachChild(titleTextDesc)
	titleTextDesc:SetAnchorHor(0.0, 1.0)
	titleTextDesc:SetAnchorVer(1.0, 1.0)
	titleTextDesc:SetAnchorParamVer(-200.0, -180.0)
	titleTextDesc:SetPivot(0.0, 1.0)
	titleTextDesc:SetSize(0.0, 50.0)
	titleTextDesc:GetText():SetFontScale(0.9)
	titleTextDesc:GetText():SetFontColor(g_n_t.Color_Font)
	titleTextDesc:GetText():SetAligns(TEXTALIGN_LEFT+TEXTALIGN_TOP)
	titleTextDesc:GetText():SetText("基于Lua的开源跨平台IOT系统方案，从0开始开发部署你的机器人")

	-- project
	local frameProj = UIFrame:New()
	frameLeft:AttachChild(frameProj)
	frameProj:SetAnchorHor(0.0, 0.0)
	frameProj:SetAnchorVer(1.0, 1.0)
	frameProj:SetAnchorParamVer(-300.0, -300.0)
	frameProj:SetSize(100, 200.0)
	frameProj:SetPivot(0.0, 1.0)
	--frameProj:CreateAddBackgroundPicBox(true)

	local fText = UIFText:New()
	frameProj:AttachChild(fText)
	fText.LocalTransform:SetTranslateY(-1.0)
	fText:SetSize(100, 40.0)
	fText:SetPivot(0.0, 0.0)
	fText:SetAnchorHor(0.0, 0.0)
	fText:SetAnchorVer(1.0, 1.0)
	fText:GetText():SetAligns(TEXTALIGN_LEFT+TEXTALIGN_VCENTER)
	fText:GetText():SetFontWidthHeight(22, 22)
	fText:GetText():SetFontColor(g_n_t.Color_Font)
	fText:GetText():SetText("开始")

	local butRectentPos = -10.0
	for i=1,2,1 do
		local but = UIButton:New()
		frameProj:AttachChild(but)
		but.LocalTransform:SetTranslateY(-1.0)
		but:SetStateColor(UIButtonBase.BS_NORMAL, g_n_t.Color_MainAUI)
		but:SetAnchorHor(0.0, 0.0)
		but:SetAnchorVer(1.0, 1.0)
		but:SetPivot(0.0, 0.5)
		but:SetAnchorParamVer(butRectentPos, butRectentPos)
		but:SetSize(100.0, 20.0)
		butRectentPos = butRectentPos-25.0

		local text = "新建项目"
		if 1==i then
			text = "新建项目"
		elseif 2==i then
			text = "打开项目"
		end
		local fText = but:CreateAddText(text)
		fText:SetAnchorParamHor(3, 10.0)
		fText:GetText():SetFontColor(g_n_t.Color_FontBlue)
		fText:GetText():SetAligns(TEXTALIGN_LEFT+TEXTALIGN_VCENTER)
	end

	-- recently
	local frameRecent = UIFrame:New()
	frameLeft:AttachChild(frameRecent)
	frameRecent:SetAnchorHor(0.0, 0.0)
	frameRecent:SetAnchorVer(1.0, 1.0)
	frameRecent:SetAnchorParamVer(-420.0, -420.0)
	frameRecent:SetSize(100, 200.0)
	frameRecent:SetPivot(0.0, 1.0)

	local fText = UIFText:New()
	frameRecent:AttachChild(fText)
	fText.LocalTransform:SetTranslateY(-1.0)
	fText:SetSize(100, 40.0)
	fText:SetPivot(0.0, 0.0)
	fText:SetAnchorHor(0.0, 0.0)
	fText:SetAnchorVer(1.0, 1.0)
	fText:GetText():SetAligns(TEXTALIGN_LEFT+TEXTALIGN_VCENTER)
	fText:GetText():SetFontWidthHeight(22, 22)
	fText:GetText():SetFontColor(g_n_t.Color_Font)
	fText:GetText():SetText("最近")

	local butRectentPos = -10.0
	for i=1,0,1 do
		local but = UIButton:New()
		frameRecent:AttachChild(but)
		but.LocalTransform:SetTranslateY(-1.0)
		but:SetStateColor(UIButtonBase.BS_NORMAL, g_n_t.Color_MainAUI)
		but:SetAnchorHor(0.0, 0.0)
		but:SetAnchorVer(1.0, 1.0)
		but:SetPivot(0.0, 0.5)
		but:SetAnchorParamVer(butRectentPos, butRectentPos)
		but:SetSize(100.0, 20.0)
		butRectentPos = butRectentPos-25.0

		local text = "产品文档"
		if 1==i then
			text = "产品文档"
		end
		local fText = but:CreateAddText(text)
		fText:SetAnchorParamHor(3.0, 10.0)
		fText:GetText():SetFontColor(g_n_t.Color_FontBlue)
		fText:GetText():SetAligns(TEXTALIGN_LEFT+TEXTALIGN_VCENTER)
	end

	-- help
	local frameHelp = UIFrame:New()
	frameLeft:AttachChild(frameHelp)
	frameHelp:SetAnchorHor(0.0, 0.0)
	frameHelp:SetAnchorVer(1.0, 1.0)
	frameHelp:SetAnchorParamVer(-540.0, -540.0)
	frameHelp:SetSize(100, 200.0)
	frameHelp:SetPivot(0.0, 1.0)
	--frameHelp:CreateAddBackgroundPicBox(true)

	local fText = UIFText:New()
	frameHelp:AttachChild(fText)
	fText.LocalTransform:SetTranslateY(-1.0)
	fText:SetSize(100, 40.0)
	fText:SetPivot(0.0, 0.0)
	fText:SetAnchorHor(0.0, 0.0)
	fText:SetAnchorVer(1.0, 1.0)
	fText:GetText():SetAligns(TEXTALIGN_LEFT+TEXTALIGN_VCENTER)
	fText:GetText():SetFontWidthHeight(22, 22)
	fText:GetText():SetFontColor(g_n_t.Color_Font)
	fText:GetText():SetText("帮助")

	local butHelpPos = -10.0
	for i=1,4,1 do
		local but = UIButton:New()
		frameHelp:AttachChild(but)
		but.LocalTransform:SetTranslateY(-1.0)
		but:SetStateColor(UIButtonBase.BS_NORMAL, g_n_t.Color_MainAUI)
		but:SetAnchorHor(0.0, 0.0)
		but:SetAnchorVer(1.0, 1.0)
		but:SetPivot(0.0, 0.5)
		but:SetAnchorParamVer(butHelpPos, butHelpPos)
		but:SetSize(100.0, 20.0)
		butHelpPos = butHelpPos-25.0

		local text = "产品文档"
		if 1==i then
			text = "产品文档"
		elseif 2==i then
			text = "视频教程"
		elseif 3==i then
			text = "GitHub"
		elseif 4==i then
			text = "ManyKit"
		end
		local fText = but:CreateAddText(text)
		fText:SetAnchorParamHor(3.0, 10.0)
		fText:GetText():SetFontColor(g_n_t.Color_FontBlue)
		fText:GetText():SetAligns(TEXTALIGN_LEFT+TEXTALIGN_VCENTER)
	end

	-- lience
	local textStr = nil
	textStr = "".." 	引擎PX2Engine，PX2AppPlayer，以Boost Software License进行发布。\n\n"
	textStr = textStr.."编辑器PX2Editor Nirvana以GPL协议进行发布。\n\n"
	textStr = textStr.." 	在Boost协议下，你拥有非常宽松的政策，可以自由修改引擎核心，甚至可以形\n\n"
	textStr = textStr.."成自己的一个版本；在GPL协议下，你不可以引用编辑器的代码形成一个商业\n\n"
	textStr = textStr.."版本，必須也是以GPL协议进行开源发布。\n"	

	local fText = UIFText:New()
	frameLeft:AttachChild(fText)
	fText.LocalTransform:SetTranslateY(-1.0)
	fText:GetText():SetText(textStr)
	fText:SetAnchorHor(0.0, 0.0)
	fText:SetAnchorVer(1.0, 1.0)
	fText:SetAnchorParamVer(-720, -720)
	fText:SetPivot(0.0, 1.0)
	fText:SetSize(600, 400)
	fText:GetText():SetRectUseage(UIText.RU_CLIPWARP)
	fText:GetText():SetFontScale(0.75)
	fText:GetText():SetFontColor(g_n_t.Color_Font)
	fText:GetText():SetAligns(TEXTALIGN_LEFT+TEXTALIGN_TOP)

	-- news
	local frameNews = UIFrame:New()
	canvas:AttachChild(frameNews)
	frameNews.LocalTransform:SetTranslateY(-1.0)
	frameNews:SetAnchorHor(0.55, 1.0)
	frameNews:SetAnchorParamHor(0.0, -240.0)
	frameNews:SetAnchorVer(0.0, 1.0)
	frameNews:SetAnchorParamVer(100.0, -300.0)
	--frameNews:CreateAddBackgroundPicBox()

	local fText = UIFText:New()
	frameNews:AttachChild(fText)
	fText.LocalTransform:SetTranslateY(-1.0)
	fText:SetSize(100, 40.0)
	fText:SetPivot(0.0, 0.0)
	fText:SetAnchorHor(0.0, 0.0)
	fText:SetAnchorVer(1.0, 1.0)
	fText:GetText():SetAligns(TEXTALIGN_LEFT+TEXTALIGN_VCENTER)
	fText:GetText():SetFontWidthHeight(22, 22)
	fText:GetText():SetFontColor(g_n_t.Color_Font)
	fText:GetText():SetText("快速链接")

	local newsPos = -10.0
	for i=1,7,1 do
		local frame = UIFrame:New()
		frameNews:AttachChild(frame)
		frame:CreateAddBackgroundPicBox(true, Float3:MakeColor(50, 50, 50))
		frame.LocalTransform:SetTranslateY(-1.0)
		frame:SetAnchorHor(0.0, 1.0)
		frame:SetAnchorVer(1.0, 1.0)
		frame:SetPivot(0.5, 1.0)
		frame:SetAnchorParamVer(newsPos, newsPos)
		frame:SetSize(0.0, 70.0)
		newsPos = newsPos-80.0
	end
	
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
	tabFrame:AddTab("BluePrint", PX2_LM_EDITOR:GetValue("BluePrint"), UIFrame:New())
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

	local leftSize = 80.0

	local cataFrme = UIBBlockCataFrame:New()
	frameBlockEditor:AttachChild(cataFrme)
	cataFrme:SetPivot(0.0, 0.5)
	cataFrme:SetAnchorHor(0.0, 0.0)
	cataFrme:SetAnchorVer(0.0, 1.0)
	cataFrme:SetAnchorParamVer(0.0, 0.0)
	cataFrme:SetSize(leftSize, 0.0)

	local butShowCode = UIButton:New("ButShowCode")
	cataFrme:AttachChild(butShowCode)
	butShowCode.LocalTransform:SetTranslateY(-5.0)
	butShowCode:SetAnchorHor(0.0, 1.0)
	butShowCode:SetAnchorVer(0.0, 0.0)
	butShowCode:SetSize(0.0, 30.0)
	butShowCode:SetPivot(0.5, 0.0)
	butShowCode:CreateAddText("ShowCode")
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

	local blocksFrame = UIBBlockPanels:New()
	frameBlockEditor:AttachChild(blocksFrame)
	blocksFrame.LocalTransform:SetTranslateY(-10.0)
	blocksFrame:SetAnchorHor(0.0, 0.0)
	blocksFrame:SetAnchorParamHor(leftSize, leftSize)
	blocksFrame:SetAnchorParamVer(0.0, 0.0)
	blocksFrame:SetAnchorVer(0.0, 1.0)
	blocksFrame:SetPivot(0.0, 0.5)

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

function n_CreateFrame_Play()
	local frame = EU_SimuFrame:New()
	frame:SetAnchorHor(0.0, 1.0)
	frame:SetAnchorVer(0.0, 1.0)
	return frame
end
