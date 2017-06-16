-- language.lua

function bb_add_language()
	PX2_LM_APP:AddItem1("Ctrl", "控制")
	PX2_LM_APP:AddItem1("Event", "事件")
	PX2_LM_APP:AddItem1("Test", "检测")
	PX2_LM_APP:AddItem1("Math", "数学")
	PX2_LM_APP:AddItem1("Param", "变量")
	PX2_LM_APP:AddItem1("Function", "函数")
	PX2_LM_APP:AddItem1("View", "造型")
	PX2_LM_APP:AddItem1("Transform", "方位")
	PX2_LM_APP:AddItem1("System", "系统")
	PX2_LM_APP:AddItem1("Func", "功能")
	PX2_LM_APP:AddItem1("Music", "音乐")

	PX2_LM_APP:AddItem1("AddParam", "添加变量")
	PX2_LM_APP:AddItem1("DeleteParam", "删除变量")
	PX2_LM_APP:AddItem1("AddMusic", "增加音乐")
	PX2_LM_APP:AddItem1("OK", "确定")
	PX2_LM_APP:AddItem1("Cancel", "取消")
	PX2_LM_APP:AddItem1("Close", "关闭")

	PX2_LM_APP:AddItem1("CreateVariable", "创建变量")
	PX2_LM_APP:AddItem1("DeleteVariable", "删除")
	PX2_LM_APP:AddItem1("ReNameVariable", "重命名")
	PX2_LM_APP:AddItem1("InputVariableName", "输入要创建变量的名称")

	PX2_LM_APP:AddItem1("ShowCode", "显示代码")
end