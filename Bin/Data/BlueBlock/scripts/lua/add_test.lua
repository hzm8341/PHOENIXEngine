-- add_test.lua

function b_Addblocks_Tests()
	-- float
	PX2_LOGICM:BeginAddFunObj(">_float")
	PX2_LOGICM:AddInput("a", FPT_FLOAT)
	PX2_LOGICM:AddInput("b", FPT_FLOAT)
	PX2_LOGICM:AddOutput("out", FPT_BOOL)
	PX2_LOGICM:EndAddFun_Operator("Test")
	
	PX2_LOGICM:BeginAddFunObj(">=_float")
	PX2_LOGICM:AddInput("a", FPT_FLOAT)
	PX2_LOGICM:AddInput("b", FPT_FLOAT)
	PX2_LOGICM:AddOutput("out", FPT_BOOL)
	PX2_LOGICM:EndAddFun_Operator("Test")
	
	PX2_LOGICM:BeginAddFunObj("<_float")
	PX2_LOGICM:AddInput("a", FPT_FLOAT)
	PX2_LOGICM:AddInput("b", FPT_FLOAT)
	PX2_LOGICM:AddOutput("out", FPT_BOOL)
	PX2_LOGICM:EndAddFun_Operator("Test")
	
	PX2_LOGICM:BeginAddFunObj("<=_float")
	PX2_LOGICM:AddInput("a", FPT_FLOAT)
	PX2_LOGICM:AddInput("b", FPT_FLOAT)
	PX2_LOGICM:AddOutput("out", FPT_BOOL)
	PX2_LOGICM:EndAddFun_Operator("Test")
	
	PX2_LOGICM:BeginAddFunObj("==_float")
	PX2_LOGICM:AddInput("a", FPT_FLOAT)
	PX2_LOGICM:AddInput("b", FPT_FLOAT)
	PX2_LOGICM:AddOutput("out", FPT_BOOL)
	PX2_LOGICM:EndAddFun_Operator("Test")
	
	PX2_LOGICM:BeginAddFunObj("!=_float")
	PX2_LOGICM:AddInput("a", FPT_FLOAT)
	PX2_LOGICM:AddInput("b", FPT_FLOAT)
	PX2_LOGICM:AddOutput("out", FPT_BOOL)
	PX2_LOGICM:EndAddFun_Operator("Test")
	
	-- int
	PX2_LOGICM:BeginAddFunObj(">_int")
	PX2_LOGICM:AddInput("a", FPT_INT)
	PX2_LOGICM:AddInput("b", FPT_INT)
	PX2_LOGICM:AddOutput("out", FPT_BOOL)
	PX2_LOGICM:EndAddFun_Operator("Test")
	
	PX2_LOGICM:BeginAddFunObj(">=_int")
	PX2_LOGICM:AddInput("a", FPT_INT)
	PX2_LOGICM:AddInput("b", FPT_INT)
	PX2_LOGICM:AddOutput("out", FPT_BOOL)
	PX2_LOGICM:EndAddFun_Operator("Test")
	
	PX2_LOGICM:BeginAddFunObj("<_int")
	PX2_LOGICM:AddInput("a", FPT_INT)
	PX2_LOGICM:AddInput("b", FPT_INT)
	PX2_LOGICM:AddOutput("out", FPT_BOOL)
	PX2_LOGICM:EndAddFun_Operator("Test")
	
	PX2_LOGICM:BeginAddFunObj("<=_int")
	PX2_LOGICM:AddInput("a", FPT_INT)
	PX2_LOGICM:AddInput("b", FPT_INT)
	PX2_LOGICM:AddOutput("out", FPT_BOOL)
	PX2_LOGICM:EndAddFun_Operator("Test")
	
	PX2_LOGICM:BeginAddFunObj("==_int")
	PX2_LOGICM:AddInput("a", FPT_INT)
	PX2_LOGICM:AddInput("b", FPT_INT)
	PX2_LOGICM:AddOutput("out", FPT_BOOL)
	PX2_LOGICM:EndAddFun_Operator("Test")
	
	PX2_LOGICM:BeginAddFunObj("!=_int")
	PX2_LOGICM:AddInput("a", FPT_INT)
	PX2_LOGICM:AddInput("b", FPT_INT)
	PX2_LOGICM:AddOutput("out", FPT_BOOL)
	PX2_LOGICM:EndAddFun_Operator("Test")
	
	-- string
	PX2_LOGICM:BeginAddFunObj("==_string")
	PX2_LOGICM:AddInput("a", FPT_STRING)
	PX2_LOGICM:AddInput("b", FPT_STRING)
	PX2_LOGICM:AddOutput("out", FPT_BOOL)
	PX2_LOGICM:EndAddFun_Operator("Test")
	
	PX2_LOGICM:BeginAddFunObj("!=_string")
	PX2_LOGICM:AddInput("a", FPT_STRING)
	PX2_LOGICM:AddInput("b", FPT_STRING)
	PX2_LOGICM:AddOutput("out", FPT_BOOL)
	PX2_LOGICM:EndAddFun_Operator("Test")
end
