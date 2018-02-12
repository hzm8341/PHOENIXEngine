-- language.lua

function g_AddLanguage()
	PX2_LM_APP:Clear()
	PX2_LM_APP:AddItem1("General", "通用")
	PX2_LM_APP:AddItem1("UI", "界面")
	PX2_LM_APP:AddItem1("About", "关于")
	
	PX2_LM_APP:AddItem1("Cancel", "取消")
	PX2_LM_APP:AddItem1("OK", "确定")

	PX2_LM_APP:AddItem1("Setting", "设置")

	PX2_LM_APP:AddItem1("Name", "名字")

	PX2_LM_APP:AddItem1("Bluetooth", "蓝牙")
	PX2_LM_APP:AddItem1("Connect", "连接")
	PX2_LM_APP:AddItem1("DisConnect", "断开")
	PX2_LM_APP:AddItem1("Scan", "扫描")
	PX2_LM_APP:AddItem1("SignDegree", "信号强度")
end