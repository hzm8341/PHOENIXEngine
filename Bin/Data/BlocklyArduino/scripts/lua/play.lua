-- play.lua

require("Data/BlocklyArduino/scripts/lua/language.lua")
require("Data/BlocklyArduino/scripts/lua/language_ansi.lua")

function preplay()
	PX2_APP:SetShowInfo(false)
	g_AddLanguage()
	g_AddLanguage_ANSI()
end

g_cs_WebView = nil
function play()
	PX2_PROJ:SetSizeSameWithScreen(true)

	local idFile = PX2_GR:GetMainWindow():AddMenuMain( "File" )
	local idSub = PX2_GR:GetMainWindow():AddMenuSub(idFile, PX2_LM_APP:GetValue("New"), "newXML")
	local idSub = PX2_GR:GetMainWindow():AddMenuSub(idFile, PX2_LM_APP:GetValue("LoadXML"), "loadXML")
	local idSub = PX2_GR:GetMainWindow():AddMenuSub(idFile, PX2_LM_APP:GetValue("SaveXML"), "saveXML")
	local idSub = PX2_GR:GetMainWindow():AddMenuSub(idFile, PX2_LM_APP:GetValue("SaveArduino"), "saveArduino")
	PX2_GR:GetMainWindow():AddMenuSpearater(idFile)
	local idSub = PX2_GR:GetMainWindow():AddMenuSub(idFile, PX2_LM_APP:GetValue("Exit"), "exitApp")
	local idArduino = PX2_GR:GetMainWindow():AddMenuMain("Arduino")
	PX2_GR:GetMainWindow():AddMenuSub(idArduino, PX2_LM_APP:GetValue("ArduinoReset"),  "arduinoReset" )
	PX2_GR:GetMainWindow():AddMenuSub(idArduino, PX2_LM_APP:GetValue("ArduinoUpLoad"),  "arduinoUpLoad" )

	PX2_GR:GetMainWindow():MaxSize(true)
	
	local ui = PX2_PROJ:GetUI()

	
	PX2_ENGINECANVAS:SetClearColor(Float4:MakeColor(255, 255, 255, 255))
	PX2_ENGINESCENECANVAS:SetClearColor(Float4:MakeColor(255, 255, 255, 255))
	PX2_ENGINEUICANVAS:SetClearColor(Float4:MakeColor(255, 255, 255, 255))
	
	local uiFrame = UIFrame:New()
	ui:AttachChild(uiFrame)
	uiFrame:SetAnchorHor(0.0, 1.0)
	uiFrame:SetAnchorVer(0.0, 1.0)
	
	local picBoxBottom = 25.0
	local uiFPicBoxBottom = UIFPicBox:New()
	uiFrame:AttachChild(uiFPicBoxBottom)
	uiFPicBoxBottom:SetAnchorHor(0.0, 1.0)
	uiFPicBoxBottom:SetAnchorVer(0.0, 0.0)
	uiFPicBoxBottom:SetPivot(0.5, 0.0)
	uiFPicBoxBottom:SetHeight(picBoxBottom)
	uiFPicBoxBottom:GetUIPicBox():SetTexture("Data/engine/white.png")
	uiFPicBoxBottom:SetColor(Float3:MakeColor(0, 122, 204))


	local webView = UIWebFrame:New()
	g_cs_WebView = webView
	uiFrame:AttachChild(webView)
	webView:SetAnchorHor(0.0, 1.0)
	webView:SetAnchorVer(0.0, 1.0)
	webView:SetAnchorParamVer(picBoxBottom, 0.0)
	webView:LoadURL("file:///Data/BlocklyArduino/blockly/apps/codeschool/index_local.html")
	webView:SetUpdateToTex(true)
	webView:SetAcceptKeyboardInput(true)
	
end

function newXML()
	g_cs_WebView:EvaluateJS("direct_discard()")
end

function loadXML()
	PX2_GR:GetMainWindow():OpenFileDlg(".xml", "onLoadXML")
end

function onLoadXML(ptr, filename)
	local strBuf = PX2_RM:LoadBuffer(filename, true)
	local str = Base64:Encode( strBuf )

	g_cs_WebView:EvaluateJS("net_onSetXMLContent(\"" ..str.. "\")")
end

function saveXML()
	PX2_GR:GetMainWindow():SaveFileDlg(".xml", "onSaveXML")
end

function onSaveXML(ptr, filename)
	g_cs_WebView:EvaluateJS("net_saveXML(\"" ..filename.. "\")")
end

function saveArduino()
	PX2_GR:GetMainWindow():SaveFileDlg(".ino", "onSaveArduino")
end

function onSaveArduino(ptr, filename)
	g_cs_WebView:EvaluateJS("net_saveCode(\"" ..filename.. "\")")
end

function exitApp()
	PX2_APP:SetQuit(true)
end

function arduinoReset()

end

function arduinoUpLoad()

end