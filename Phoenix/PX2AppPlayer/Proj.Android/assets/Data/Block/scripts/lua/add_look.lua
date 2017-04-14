-- add_look.lua

function b_addblocks_Look()	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setName", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("str", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("View")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "getName", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddOutput("str", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("View")

	PX2_LOGICM:BeginAddClassFunObj("BActor", "show", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("var", FPT_BOOL)
	PX2_LOGICM:EndAddFun_General("View")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "isShow", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddOutput("var", FPT_BOOL)
	PX2_LOGICM:EndAddFun_General("View")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "playLook", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("var", FPT_BOOL)
	PX2_LOGICM:EndAddFun_General("View")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "isPlayingLook", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddOutput("var", FPT_BOOL)
	PX2_LOGICM:EndAddFun_General("View")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setLookPlaySpeed", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("var", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("View")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "say", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("str", FPT_STRING)
	PX2_LOGICM:AddInput("voice", FPT_BOOL)
	PX2_LOGICM:EndAddFun_General("View")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setText", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("str", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("View")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "getText", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddOutput("str", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("View")
end