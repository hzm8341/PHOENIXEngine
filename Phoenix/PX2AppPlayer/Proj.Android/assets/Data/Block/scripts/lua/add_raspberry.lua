-- raspberry.lua

function b_addblocks_Raspberry()
	PX2_LOGICM:BeginAddClassFunObj("GPIO", "Export", true)
	PX2_LOGICM:AddInput("gpio", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Raspberry")
	
	PX2_LOGICM:BeginAddClassFunObj("GPIO", "Unexport", true)
	PX2_LOGICM:AddInput("gpio", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Raspberry")
	
	PX2_LOGICM:BeginAddClassFunObj("GPIO", "SetDriection", true)
	PX2_LOGICM:AddInput("gpio", FPT_INT)
	PX2_LOGICM:AddInput("dir", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Raspberry")
	
	PX2_LOGICM:BeginAddClassFunObj("GPIO", "SetValue", true)
	PX2_LOGICM:AddInput("gpio", FPT_INT)
	PX2_LOGICM:AddInput("val", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Raspberry")
	
	PX2_LOGICM:BeginAddClassFunObj("GPIO", "GetValue", true)
	PX2_LOGICM:AddInput("gpio", FPT_INT)
	PX2_LOGICM:AddInput("val", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Raspberry")
end