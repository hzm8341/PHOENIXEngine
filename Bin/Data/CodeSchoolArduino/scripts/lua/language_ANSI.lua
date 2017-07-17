-- language_ansi.lua

function g_AddLanguage_ANSI()
	PX2_LM_APP:AddItem1("File", "文件")
	PX2_LM_APP:AddItem1("New", "新建")
	PX2_LM_APP:AddItem1("LoadXML", "加载")
	PX2_LM_APP:AddItem1("SaveXML", "保存")
	PX2_LM_APP:AddItem1("SaveArduino", "存储为Arduino")
	PX2_LM_APP:AddItem1("Exit", "退出")
	
	PX2_LM_APP:AddItem1("ArduinoReset", "重置")
	PX2_LM_APP:AddItem1("ArduinoUpLoad", "上传")
end