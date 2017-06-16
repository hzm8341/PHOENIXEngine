-- editor.lua

function blueblock_editorstart()
	PX2_APP:Menu_AddSubItemCatalogue("", "BlueBlock", "BlueBlock")
	PX2_APP:Menu_AddItem("BlueBlock", "CreateBSpriteFrame", "CreateBSpriteFrame", "bb_CreateBSpriteFrame")
	PX2_APP:Menu_AddItem("BlueBlock", "CreateBSpritePicBox", "CreateBSpritePicBox", "bb_CreateBSpritePicBox")
	PX2_APP:Menu_AddItem("BlueBlock", "CreateBSpriteButton", "CreateBSpriteButton", "bb_CreateBSpriteButton")
	PX2_APP:Menu_AddItem("BlueBlock", "CreateBSpriteText", "CreateBSpriteText", "bb_CreateBSpriteText")
	PX2_APP:Menu_AddItem("BlueBlock", "CreateBSpriteEditBox", "CreateBSpriteEditBox", "bb_CreateBSpriteEditBox")
	PX2_APP:Menu_AddItem("BlueBlock", "CreateBSpriteComboBox", "CreateBSpriteComboBox", "bb_CreateBSpriteComboBox")
	PX2_APP:Menu_AddItem("BlueBlock", "CreateBSpriteWebView", "CreateBSpriteWebView", "bb_CreateBSpriteWebView")
	PX2_APP:Menu_AddItem("BlueBlock", "CreateBSpriteRound", "CreateBSpriteRound", "bb_CreateBSpriteRound")

    RegistEventFunction("EditES::AddSelect", function(strData0, strData1, strData2)
		local selectObj = PX2_SELECTM_E:GetFirstObject()
		if nil~=selectObj then
			if "PX2.BBlockScriptGenController" == selectObj:GetRttiType():GetName() then
				selectObj:RegistToScriptSystem()
				PX2_LOGICM:SetSelectLogicObject(selectObj)
			end
		end
	end)
end

function bb_CreateBSpriteFrame()
	local obj = PX2_SELECTM_E:GetFirstObject()
	local frame = Cast:ToNode(obj)
	if nil~=frame then
		local sprite = BBlockSprite:New(BBlockSprite.ST_FRAME)
		frame:AttachChild(sprite)
		sprite:RegistToScriptSystem()
	end
end

function bb_CreateBSpritePicBox()
	local obj = PX2_SELECTM_E:GetFirstObject()
	local frame = Cast:ToNode(obj)
	if nil~=frame then
		local sprite = BBlockSprite:New(BBlockSprite.ST_PICBOX)
		frame:AttachChild(sprite)
		sprite:RegistToScriptSystem()
	end
end

function bb_CreateBSpriteButton()
	local obj = PX2_SELECTM_E:GetFirstObject()
	local frame = Cast:ToNode(obj)
	if nil~=frame then
		local sprite = BBlockSprite:New(BBlockSprite.ST_BUTTON)
		frame:AttachChild(sprite)
		sprite:RegistToScriptSystem()
	end
end

function bb_CreateBSpriteText()
	local obj = PX2_SELECTM_E:GetFirstObject()
	local frame = Cast:ToNode(obj)
	if nil~=frame then
		local sprite = BBlockSprite:New(BBlockSprite.ST_TEXT)
		frame:AttachChild(sprite)
		sprite:RegistToScriptSystem()
	end
end

function bb_CreateBSpriteEditBox()
	local obj = PX2_SELECTM_E:GetFirstObject()
	local frame = Cast:ToNode(obj)
	if nil~=frame then
		local sprite = BBlockSprite:New(BBlockSprite.ST_EDITBOX)
		frame:AttachChild(sprite)
		sprite:RegistToScriptSystem()
	end
end

function bb_CreateBSpriteComboBox()
	local obj = PX2_SELECTM_E:GetFirstObject(BBlockSprite.ST_COMBOXBOX)
	local frame = Cast:ToNode(obj)
	if nil~=frame then
		local sprite = BBlockSprite:New()
		frame:AttachChild(sprite)
		sprite:RegistToScriptSystem()
	end
end

function bb_CreateBSpriteWebView()
	local obj = PX2_SELECTM_E:GetFirstObject()
	local frame = Cast:ToNode(obj)
	if nil~=frame then
		local sprite = BBlockSprite:New(BBlockSprite.ST_WEBVIEW)
		frame:AttachChild(sprite)
		sprite:RegistToScriptSystem()
	end
end

function bb_CreateBSpriteRound()
	local obj = PX2_SELECTM_E:GetFirstObject()
	local frame = Cast:ToNode(obj)
	if nil~=frame then
		local sprite = BBlockSprite:New(BBlockSprite.ST_ROUND)
		frame:AttachChild(sprite)
		sprite:RegistToScriptSystem()
	end
end