-- start.lua

require("Data/General/scripts/lua/language.lua")

function prestart()
	g_AddLanguage()	
	PX2_APP:NewProject("Data/General/general.px2proj", "General", 0, 960, 600)
end

function start()
	Sample()
end

function Sample()
	-- scene
	local scene = Scene:New()
	PX2_PROJ:SetScene(scene)
	local box = PX2_CREATER:CreateMovable_Box()
	box.LocalTransform:SetUniformScale(6.0)
	scene:AttachChild(box)
	
	-- ui
	local ui = PX2_PROJ:GetUI()
	
	local fPicBox = UIFPicBox:New()
	ui:AttachChild(fPicBox)
	
	local but = UIButton:New()
	ui:AttachChild(but)
	but.LocalTransform:SetTranslateY(-1.0)
	
	ui:GetFirstCamera():SetClearFlag(false, true, true)
	
	-- another canvas
	local canvas = Canvas:New()
	ui:AttachChild(canvas)
	canvas:CreateUICameraNode()
	canvas:SetAnchorHor(0.1, 0.4)
	canvas:SetAnchorVer(0.1, 0.4)
	canvas:SetClearFlag(true, true, true)
	canvas:SetClearColor(Float4(1.0, 0.0, 1.0, 1.0))
	
	local but = UIButton:New()
	canvas:AttachChild(but)
	but.LocalTransform:SetTranslateY(-1.0)
	but:SetAnchorHor(0.1, 0.4)
	but:SetAnchorVer(0.1, 0.4)
end