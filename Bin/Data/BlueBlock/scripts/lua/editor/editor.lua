-- editor.lua

function editorstart()
	PX2_APP:Menu_AddSubItemCatalogue("", "BlueBlock", "BlueBlock")
	PX2_APP:Menu_AddItem("BlueBlock", "CreateBlueBlockScriptCtrl", "CreateBlueBlockScriptCtrl", "b_CreateBlueBlockScriptCtrl")

    RegistEventFunction("EditES::AddSelect", function(strData0, strData1, strData2)
		local selectObj = PX2_SELECTM_E:GetFirstObject()
		if nil~=selectObj then
			selectObj:RegistToScriptSystem()
			if "PX2.BBlockScriptGenController" == selectObj:GetRttiType():GetName() then
				PX2_LOGICM:SetSelectObject(selectObj)
			end
		end
	end)
end

function b_CreateBlueBlockScriptCtrl()
	local scGenCtrl = BBlockScriptGenController:New()
	local obj = PX2_SELECTM_E:GetFirstObject()
	obj:RegistToScriptSystem()
	obj:AttachController(scGenCtrl)
	scGenCtrl:ResetPlay()
end