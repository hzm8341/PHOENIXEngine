-- frame_res.lua

-- left_res
function n_LeftProjectSplitterCallback(objPtr, callType)
	local splitter = Cast:ToO(objPtr)
	local ptrResTree = splitter:GetUserDataPointer("ResCanvas")
	local resTree = Cast:ToO(ptrResTree)
	local contentObj = splitter:GetUserDataPointer("ContentFrame")
	local contentFrame = Cast:ToO(contentObj)
	
	local name = splitter:GetName()
	if UICT_SPLITTER_DRAGING==callType then
		if "SplitterLeft" == name then
			local anchorParamVer = splitter:GetAnchorParamVer():X()
			resTree:SetAnchorParamVer(anchorParamVer+4.0, -g_n_t.Size_LeftTitleBar)
			contentFrame:SetSize(0.0, anchorParamVer-4.0)
		end
	end
end

function n_ResButCallback(objPtr, callType)
	local obj = Cast:ToO(objPtr)
	local name = obj:GetName()

	local selectResData = PX2_EDIT:GetSelectedResource()
	local resPathname = selectResData.ResPathname

	if UICT_RELEASED == callType then
		if "ButOpenIn" == name then
			PX2_EDIT:OpenResIn(resPathname)
		elseif "ButOpenOut" == name then
			PX2_EDIT:OpenResOut(resPathname)
		elseif "ButRefresh" == name then
			PX2_EDIT:BroadCastEditorEventRefreshRes()
		elseif "ButUp" == name then
			PX2_EDIT:BroadCastEditorEventUp()
		elseif "ButDown" == name then
			PX2_EDIT:BroadCastEditorEventDown()
		end
	end
end

function n_CreateFrame_Left_Res()
	local frame = UIFrame:New("FrameLeftRes")
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
	local text = PX2_LM_EDITOR:GetValue("ResourceManager")
	titleText:GetText():SetText(text)
	titleText:GetText():SetFontScale(0.8)
	titleText:GetText():SetFontColor(Float3.WHITE)
	titleText:GetText():SetDrawStyle(FD_SHADOW)
	titleText:GetText():SetAligns(TEXTALIGN_LEFT+TEXTALIGN_VCENTER)

	local butRefresh = UIButton:New("ButRefresh")
	frameTitle:AttachChild(butRefresh)
	butRefresh:SetSize(g_n_t.Size_LeftTitleBar-4, g_n_t.Size_LeftTitleBar-4)
	butRefresh:SetPivot(1.0, 0.5)
	butRefresh:SetAnchorHor(1.0, 1.0)
	butRefresh:SetAnchorVer(0.5, 0.5)
	butRefresh:SetStateColor(UIButtonBase.BS_NORMAL, Float3.WHITE)
	butRefresh:SetStateColor(UIButtonBase.BS_HOVERED, Float3.WHITE)
	butRefresh:SetStateColor(UIButtonBase.BS_PRESSED, Float3.WHITE)
	butRefresh:SetStateBrightness(UIButtonBase.BS_NORMAL, 1.0)
	butRefresh:SetStateBrightness(UIButtonBase.BS_HOVERED, 0.9)
	butRefresh:SetStateBrightness(UIButtonBase.BS_PRESSED, 0.7)
	butRefresh:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("DataNIRVANA2/images/icons1/refresh.png")
	butRefresh:SetScriptHandler("n_ResButCallback")
	
	-- res canvas
	local resCanvas = Canvas:New("CanvasRes")
	resCanvas:CreateUICameraNode()
	frame:AttachChild(resCanvas)
	resCanvas.LocalTransform:SetTranslateY(-1.0)
	resCanvas:SetAnchorHor(0.0, 1.0)
	resCanvas:SetAnchorVer(0.0, 1.0)
	resCanvas:SetAnchorParamVer(400.0, -g_n_t.Size_LeftTitleBar)
	resCanvas:SetClearColor(Float4:MakeColor(37, 37, 38, 255))
	resCanvas:RegistToScriptSystem()
	
	local resTree = EU_ResTree:New()
	resCanvas:AttachChild(resTree)
	resTree:SetAnchorHor(0.0, 1.0)
	resTree:SetAnchorVer(0.0, 1.0)
	
	-- splitter
	local splitter = UISplitterFrame:New("SplitterLeft")
	frame:AttachChild(splitter)
	splitter.LocalTransform:SetTranslateY(-1.0)
	splitter:SetSize(0.0, 4.0)
	splitter:SetAnchorHor(0.0, 1.0)
	splitter:SetAnchorParamHor(0.0, 0.0)
	splitter:SetAnchorVer(0.0, 0.0)
	splitter:SetAnchorParamVer(400.0, 400.0)
	splitter:RegistToScriptSystem()
	splitter:SetScriptHandler("n_LeftProjectSplitterCallback")
	
	-- grid canvas
	local frameContent = UIFrame:New()
	frame:AttachChild(frameContent)
	frameContent.LocalTransform:SetTranslateY(-1.0)
	frameContent:SetAnchorHor(0.0, 1.0)
	frameContent:SetAnchorParamHor(0.0, 0.0)
	frameContent:SetAnchorVer(0.0, 0.0)
	frameContent:SetPivot(0.5, 0.0)
	frameContent:SetSize(0.0, 400.0)

	local toolBarHeight = g_n_t.Size_ToolBar

	-- tool bar
	local frameToolBar = UIFrame:New()
	frameContent:AttachChild(frameToolBar)
	frameToolBar:SetAnchorHor(0.0, 1.0)
	frameToolBar:SetAnchorVer(1.0, 1.0)
	frameToolBar:SetPivot(0.5, 1.0)
	frameToolBar:SetSize(0.0, toolBarHeight)

	-- tool bar buts
	local butOpenIn = UIButton:New("ButOpenIn")
	frameToolBar:AttachChild(butOpenIn)
	butOpenIn:SetSize(toolBarHeight-4, toolBarHeight-4)
	butOpenIn:SetPivot(0.0, 0.5)
	butOpenIn:SetAnchorHor(0.0, 0.0)
	butOpenIn:SetAnchorVer(0.5, 0.5)
	butOpenIn:SetStateColor(UIButtonBase.BS_NORMAL, Float3.WHITE)
	butOpenIn:SetStateColor(UIButtonBase.BS_HOVERED, Float3.WHITE)
	butOpenIn:SetStateColor(UIButtonBase.BS_PRESSED, Float3.WHITE)
	butOpenIn:SetStateBrightness(UIButtonBase.BS_NORMAL, 1.0)
	butOpenIn:SetStateBrightness(UIButtonBase.BS_HOVERED, 0.9)
	butOpenIn:SetStateBrightness(UIButtonBase.BS_PRESSED, 0.7)
	butOpenIn:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("DataNIRVANA2/images/icons1/openin.png")
	butOpenIn:SetScriptHandler("n_ResButCallback")

	local butOpenOut = UIButton:New("ButOpenOut")
	frameToolBar:AttachChild(butOpenOut)
	butOpenOut:SetSize(toolBarHeight-4, toolBarHeight-4)
	butOpenOut:SetPivot(0.0, 0.5)
	butOpenOut:SetAnchorParamHor(toolBarHeight, toolBarHeight)
	butOpenOut:SetAnchorHor(0.0, 0.0)
	butOpenOut:SetAnchorVer(0.5, 0.5)
	butOpenOut:SetStateColor(UIButtonBase.BS_NORMAL, Float3.WHITE)
	butOpenOut:SetStateColor(UIButtonBase.BS_HOVERED, Float3.WHITE)
	butOpenOut:SetStateColor(UIButtonBase.BS_PRESSED, Float3.WHITE)
	butOpenOut:SetStateBrightness(UIButtonBase.BS_NORMAL, 1.0)
	butOpenOut:SetStateBrightness(UIButtonBase.BS_HOVERED, 0.9)
	butOpenOut:SetStateBrightness(UIButtonBase.BS_PRESSED, 0.7)
	butOpenOut:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("DataNIRVANA2/images/icons1/openout.png")
	butOpenOut:SetScriptHandler("n_ResButCallback")

	local butUp = UIButton:New("ButUp")
	frameToolBar:AttachChild(butUp)
	butUp:SetSize(toolBarHeight-4, toolBarHeight-4)
	butUp:SetPivot(1.0, 0.5)
	butUp:SetAnchorParamHor(-toolBarHeight, -toolBarHeight)
	butUp:SetAnchorHor(1.0, 1.0)
	butUp:SetAnchorVer(0.5, 0.5)
	butUp:SetStateColor(UIButtonBase.BS_NORMAL, Float3.WHITE)
	butUp:SetStateColor(UIButtonBase.BS_HOVERED, Float3.WHITE)
	butUp:SetStateColor(UIButtonBase.BS_PRESSED, Float3.WHITE)
	butUp:SetStateBrightness(UIButtonBase.BS_NORMAL, 1.0)
	butUp:SetStateBrightness(UIButtonBase.BS_HOVERED, 0.9)
	butUp:SetStateBrightness(UIButtonBase.BS_PRESSED, 0.7)
	butUp:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("DataNIRVANA2/images/icons1/up.png")
	butUp:SetScriptHandler("n_ResButCallback")

	local butDown = UIButton:New("ButDown")
	frameToolBar:AttachChild(butDown)
	butDown:SetSize(toolBarHeight-4, toolBarHeight-4)
	butDown:SetPivot(1.0, 0.5)
	butDown:SetAnchorHor(1.0, 1.0)
	butDown:SetAnchorVer(0.5, 0.5)
	butDown:SetStateColor(UIButtonBase.BS_NORMAL, Float3.WHITE)
	butDown:SetStateColor(UIButtonBase.BS_HOVERED, Float3.WHITE)
	butDown:SetStateColor(UIButtonBase.BS_PRESSED, Float3.WHITE)
	butDown:SetStateBrightness(UIButtonBase.BS_NORMAL, 1.0)
	butDown:SetStateBrightness(UIButtonBase.BS_HOVERED, 0.9)
	butDown:SetStateBrightness(UIButtonBase.BS_PRESSED, 0.7)
	butDown:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("DataNIRVANA2/images/icons1/down.png")
	butDown:SetScriptHandler("n_ResButCallback")

	local gridCanvas = Canvas:New("CanvasGrid")
	gridCanvas:CreateUICameraNode()
	frameContent:AttachChild(gridCanvas)
	gridCanvas:SetAnchorHor(0.0, 1.0)
	gridCanvas:SetAnchorVer(0.0, 1.0)
	gridCanvas:SetAnchorParamVer(0.0, -toolBarHeight)

	gridCanvas:SetClearColor(Float4:MakeColor(37, 37, 38, 255))
	gridCanvas:RegistToScriptSystem()
	
	local gridFrame = EU_ResGridFrame:New()
	gridCanvas:AttachChild(gridFrame)
	gridFrame.LocalTransform:SetTranslateY(-1.0)
	gridFrame:SetAnchorHor(0.0, 1.0)
	gridFrame:SetAnchorVer(0.0, 1.0)
	gridFrame:RegistToScriptSystem()
	
	splitter:SetUserDataPointer("ResCanvas", resCanvas)
	splitter:SetUserDataPointer("ContentFrame", frameContent)
	
	n_LeftProjectSplitterCallback(splitter, UICT_SPLITTER_DRAGING)
		
	return frame
end
