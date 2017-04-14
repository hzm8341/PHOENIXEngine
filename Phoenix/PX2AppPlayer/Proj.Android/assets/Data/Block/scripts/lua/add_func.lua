-- add_func.lua

function b_addblocks_Func()	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "getDragingDirX", false, "", "Round")
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddOutput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "getDragingDirY", false, "", "Round")
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddOutput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "getDragingDirSimple", false, "", "Round")
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddOutput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "getDragingPercent", false, "", "Round")
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddOutput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "addChooseString", false, "", "ComboBox")
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("val", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "chooseString", false, "", "ComboBox")
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("val", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "chooseIndex", false, "", "ComboBox")
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("val", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "getChooseString", false, "", "ComboBox")
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddOutput("val", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "getChooseIndex", false, "", "ComboBox")
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddOutput("val", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Func")
end

function b_addblocks_FuncStage()
	PX2_LOGICM:BeginAddClassFunObj("Stage", "getActorByName", false, "Stage")
	PX2_LOGICM:AddInput("name", FPT_STRING)
	PX2_LOGICM:AddOutput("actor", FPT_POINTER)
	PX2_LOGICM:EndAddFun_General("Func")	
	
	PX2_LOGICM:BeginAddClassFunObj("Stage", "log", false, "Stage")
	PX2_LOGICM:AddInput("str", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("coroutine", "yield", false, "coroutine")
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("coroutine", "yield", false, "coroutine")
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("Stage", "systemSleep", false, "Stage")
	PX2_LOGICM:AddInput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddFunObj("print")
	PX2_LOGICM:AddInput("str", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddFunObj("sleep")
	PX2_LOGICM:AddInput("seconds", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("Stage", "stringToInt", false, "Stage")
	PX2_LOGICM:AddInput("str", FPT_STRING)
	PX2_LOGICM:AddOutput("val", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("Stage", "stringToFloat", false, "Stage")
	PX2_LOGICM:AddInput("str", FPT_STRING)
	PX2_LOGICM:AddOutput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("Stage", "intToString", false, "Stage")
	PX2_LOGICM:AddInput("val", FPT_INT)
	PX2_LOGICM:AddOutput("str", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("Stage", "floatToString", false, "Stage")
	PX2_LOGICM:AddInput("val", FPT_FLOAT)
	PX2_LOGICM:AddOutput("str", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("Stage", "getStringParam", false, "Stage")
	PX2_LOGICM:AddInput("str", FPT_STRING)
	PX2_LOGICM:AddInput("index", FPT_INT)
	PX2_LOGICM:AddOutput("str", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("Stage", "netSendString", false, "Stage")
	PX2_LOGICM:AddInput("str", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("Stage", "bluetoothSendString", false, "Stage")
	PX2_LOGICM:AddInput("str", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("Stage", "voiceStart", false, "Stage")
	PX2_LOGICM:EndAddFun_General("Func")
	
	PX2_LOGICM:BeginAddClassFunObj("Stage", "voiceEnd", false, "Stage")
	PX2_LOGICM:EndAddFun_General("Func")
end