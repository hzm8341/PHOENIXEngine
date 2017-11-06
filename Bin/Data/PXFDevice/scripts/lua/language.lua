-- language.lua

function p_g_AddLanguage()
	PX2_LM_APP:Clear()
	PX2_LM_APP:AddItem1("General", "通用")
	PX2_LM_APP:AddItem1("UI", "界面")
	PX2_LM_APP:AddItem1("About", "关于")
end