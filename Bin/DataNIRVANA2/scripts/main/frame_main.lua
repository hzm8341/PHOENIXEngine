-- frame_main.lua

-- globals
n_g_FrameMain = nil
n_g_FrameMainStatus = nil
n_g_FrameMainLeftBar = nil
n_g_FrameMainLeftCanvas = nil
n_g_SplitterLeft = nil
n_g_FrameMainLeft_Res = nil
n_g_FrameMainLeft_Project = nil
n_g_FrameMainLeft_Run = nil
n_g_FrameMainLeft_Inspector = nil
n_g_FrameMainLeft_TimeLine = nil
n_g_FrameMainLeft_Market = nil
n_g_FrameMainContent = nil
n_g_FrameContentTab = nil
n_g_FrameContentLogicTab = nil

-- mainfram
function n_CreateMainFrame()
	local mainFrame = UIFrame:New()
	mainFrame:SetAnchorHor(0.0, 1.0)
	mainFrame:SetAnchorVer(0.0, 1.0)
	
	return mainFrame
end

-- status
function n_CreateFrame_StatusBar()
	local frame = UIFrame:New()
	frame:CreateAddBackgroundPicBox(true, g_n_t.Color_StatusBar)
	frame:SetSize(0.0, g_n_t.Size_StatusBar)
	frame:SetAnchorHor(0.0, 1.0);
	frame:SetAnchorVer(0.0, 0.0);
	frame:SetPivot(0.5, 0.0)
	return frame
end

-- left bar
function n_LeftBarButCallback(objPtr, callType)
	local butObj = Cast:ToO(objPtr)
	
	local name = butObj:GetName()
	if UICT_RELEASED==callType then
		n_Left_Show(name)
	end
end
function n_CreateFrame_LeftBar()
	local frame = UIFrame:New()
	frame:CreateAddBackgroundPicBox(true, g_n_t.Color_LeftBar)
	frame:SetSize(g_n_t.Size_LeftBar, 0.0)
	frame:SetPivot(0.0, 0.5)
	frame:SetAnchorHor(0.0, 0.0);
	frame:SetAnchorVer(0.0, 1.0);
	frame:SetAnchorParamVer(g_n_t.Size_StatusBar, 0.0);
	
	local posButY = -g_n_t.Size_LeftBar * 0.5
	for i=1, 6, 1 do
		local but = UIButton:New()
		frame:AttachChild(but)
		but:SetAnchorHor(0.5, 0.5)
		but:SetAnchorVer(1.0, 1.0)
		but:SetAnchorParamVer(posButY, posButY)
		local strPath = "DataNIRVANA2/images/icons1/res.png"
		local name = ""
		if 1==i then
			strPath = "DataNIRVANA2/images/icons1/res.png"
			name = "Res"
		elseif 2==i then
			strPath = "DataNIRVANA2/images/icons1/project.png"
			name = "Project"
		elseif 3==i then
			strPath = "DataNIRVANA2/images/icons1/inspector.png"
			name = "Inspector" 
		elseif 4==i then
			strPath = "DataNIRVANA2/images/icons1/timeline.png"
			name = "TimeLine"
		elseif 5==i then
			strPath = "DataNIRVANA2/images/icons1/run.png"
			name = "Run"
		elseif 6==i then
			strPath = "DataNIRVANA2/images/icons1/store.png"
			name = "Market" 
		end
		local fPicBox = UIFPicBox:New()
		but:AttachChild(fPicBox)
		fPicBox.LocalTransform:SetTranslateY(-2.0)		
		fPicBox:GetUIPicBox():SetTexture(strPath)
		fPicBox:SetSize(30.0, 30.0)
		but:SetName(name)
		but:SetStateColor(UIButtonBase.BS_NORMAL, g_n_t.Color_LeftBar)
		but:SetStateColor(UIButtonBase.BS_HOVERED, g_n_t.Color_LeftBar)
		but:SetStateColor(UIButtonBase.BS_PRESSED, g_n_t.Color_LeftBar)
		but:SetStateBrightness(UIButtonBase.BS_NORMAL, 1.0)
		but:SetStateBrightness(UIButtonBase.BS_HOVERED, 1.2)
		but:SetStateBrightness(UIButtonBase.BS_PRESSED, 1.0)
		but:SetSize(g_n_t.Size_LeftBarBut, g_n_t.Size_LeftBarBut)
		but:SetScriptHandler("n_LeftBarButCallback")
		posButY = posButY - (g_n_t.Size_LeftBar+10)
	end
	
	return frame
end

-- left
function n_CreateFrame_LeftCanvas()
	local canvas = Canvas:New()
	canvas:SetPivot(0.0, 0.5)
	canvas:SetAnchorHor(0.0, 0.0)
	canvas:SetAnchorParamHor(g_n_t.Size_LeftBar, 0.0)
	canvas:SetAnchorVer(0.0, 1.0)
	canvas:SetAnchorParamVer(g_n_t.Size_StatusBar, 0.0)
	canvas:SetSize(g_n_t.Size_Left, 0.0)
	canvas:CreateUICameraNode()
	canvas:SetClearColor(Float4(g_n_t.Color_Left:X(), g_n_t.Color_Left:Y(), g_n_t.Color_Left:Z(), 1.0))
	
	return canvas
end

function n_Left_Show(name)
	n_g_FrameMainLeft_Project:Show(false)
	n_g_FrameMainLeft_Res:Show(false)
	n_g_FrameMainLeft_Run:Show(false)
	n_g_FrameMainLeft_Inspector:Show(false)
	n_g_FrameMainLeft_TimeLine:Show(false)
	n_g_FrameMainLeft_Market:Show(false)

	if "Project"==name then
		n_g_FrameMainLeft_Project:Show(true)
	elseif "Res"==name then
		n_g_FrameMainLeft_Res:Show(true)
	elseif "Inspector"==name then
		n_g_FrameMainLeft_Inspector:Show(true)
	elseif "TimeLine"==name then
		n_g_FrameMainLeft_TimeLine:Show(true)
	elseif "Run"==name then
		n_g_FrameMainLeft_Run:Show(true)
	elseif "Market"==name then
		n_g_FrameMainLeft_Market:Show(true)
	end	
end


-- create mainwindow
function n_CreatMainWindow()
	local mainWindow = PX2_GR:GetMainWindow()
	local mainCanvas = mainWindow:GetMainCanvas()
	mainCanvas:SetClearColor(Float4(g_n_t.Color_MainAUI:X(), g_n_t.Color_MainAUI:Y(), g_n_t.Color_MainAUI:Z(), 1.0))
	
	n_g_FrameMain = n_CreateMainFrame()	
	mainCanvas:AttachChild(n_g_FrameMain)
	
	n_g_FrameMainStatus = n_CreateFrame_StatusBar()
	n_g_FrameMain:AttachChild(n_g_FrameMainStatus)
	
	n_g_FrameMainLeftBar = n_CreateFrame_LeftBar()
	n_g_FrameMain:AttachChild(n_g_FrameMainLeftBar)
	
	n_g_FrameMainLeftCanvas = n_CreateFrame_LeftCanvas()	
	n_g_FrameMainLeft_Project = n_CreateFrame_Left_Project()
	n_g_FrameMainLeft_Res = n_CreateFrame_Left_Res()
	n_g_FrameMainLeft_Inspector = n_CreateFrame_Left_Inspector()
	n_g_FrameMainLeft_TimeLine = n_CreateFrame_Left_TimeLine()
	n_g_FrameMainLeft_Run = n_CreateFrame_Left_Run()	
	n_g_FrameMainLeft_Market = n_CreateFrame_Left_Market()
	
	n_g_FrameMainLeftCanvas:AttachChild(n_g_FrameMainLeft_Project)
	n_g_FrameMainLeftCanvas:AttachChild(n_g_FrameMainLeft_Res)
	n_g_FrameMainLeftCanvas:AttachChild(n_g_FrameMainLeft_Inspector)
	n_g_FrameMainLeftCanvas:AttachChild(n_g_FrameMainLeft_TimeLine)
	n_g_FrameMainLeftCanvas:AttachChild(n_g_FrameMainLeft_Run)
	n_g_FrameMainLeftCanvas:AttachChild(n_g_FrameMainLeft_Market)
	n_Left_Show("Res")
	
	n_g_FrameMain:AttachChild(n_g_FrameMainLeftCanvas)
	
	n_g_FrameMainContent = n_CreateFrame_ContentFrame()
	n_g_FrameMain:AttachChild(n_g_FrameMainContent)

	n_g_SplitterLeft = UISplitterFrame:New()
	n_g_FrameMain:AttachChild(n_g_SplitterLeft)
	n_g_SplitterLeft.LocalTransform:SetTranslateY(-10.0)
	n_g_SplitterLeft:SetHor(false)
	n_g_SplitterLeft:SetAnchorVer(0.0, 1.0)
	n_g_SplitterLeft:SetAnchorParamVer(g_n_t.Size_StatusBar, 0.0)
	n_g_SplitterLeft:SetScriptHandler("n_LeftSplitterCallback")
	n_g_SplitterLeft:SetName("SplitterLeft")
	n_g_SplitterLeft:SetUserDataPointer("LeftCanvas", n_g_FrameMainLeftCanvas)
	n_g_SplitterLeft:SetUserDataPointer("RightContent", n_g_FrameMainContent)
	n_g_SplitterLeft:SetAnchorParamHor(g_n_t.Size_Left, g_n_t.Size_Left)
	local spHalfWidth = n_g_SplitterLeft:GetSize().Width * 0.5
	n_g_SplitterLeft:SetDragRange(Float2(g_n_t.Size_LeftBar+spHalfWidth, 1200))

	n_LeftSplitterCallback(n_g_SplitterLeft, UICT_SPLITTER_DRAGING)
end

function n_LeftSplitterCallback(objPtr, callType)
	local splitter = Cast:ToO(objPtr)
	local left = splitter:GetUserDataPointer("LeftCanvas")
	local leftFrame = Cast:ToO(left)
	local right = splitter:GetUserDataPointer("RightContent")
	local rightFrame = Cast:ToO(right)
	
	local name = splitter:GetName()
	local spHalfWidth = splitter:GetSize().Width * 0.5
	if UICT_SPLITTER_DRAGING==callType then
		if "SplitterLeft" == name then
			local anchorParamHor = splitter:GetAnchorParamHor():X()
			leftFrame:SetSize(anchorParamHor-g_n_t.Size_LeftBar-spHalfWidth, 0.0)
			rightFrame:SetAnchorParamHor(anchorParamHor+spHalfWidth, 0.0)
		end
	end
end