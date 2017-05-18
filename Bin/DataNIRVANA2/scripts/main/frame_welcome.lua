-- frame_content.lua

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
	frameLeft:SetAnchorParamHor(200.0, 0.0)
	frameLeft:SetAnchorVer(0.0, 1.0)

	local fPicBoxLogo = UIFPicBox:New()
	frameLeft:AttachChild(fPicBoxLogo)
	fPicBoxLogo.LocalTransform:SetTranslateY(-1.0)
	fPicBoxLogo:SetPivot(1.0, 1.0)
	fPicBoxLogo:SetAnchorHor(0.0, 0.0)
	fPicBoxLogo:SetAnchorParamHor(-40.0, -40.0)
	fPicBoxLogo:SetAnchorVer(1.0, 1.0)
	fPicBoxLogo:SetAnchorParamVer(-120.0, -120.0)
	fPicBoxLogo:GetUIPicBox():SetTexture("DataNIRVANA2/images/logo/phoenix.png")
	fPicBoxLogo:SetSize(100, 100)

	local titleText = UIFText:New()
	frameLeft:AttachChild(titleText)
	titleText:SetAnchorHor(0.0, 1.0)
	titleText:SetAnchorVer(1.0, 1.0)
	titleText:SetAnchorParamVer(-130.0, -130.0)
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
	titleTextDesc:SetAnchorParamVer(-180.0, -180.0)
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
	frameNews:SetAnchorHor(0.5, 1.0)
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
	for i=1,6,1 do
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