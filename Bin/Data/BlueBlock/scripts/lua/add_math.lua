-- add_math.lua

function b_Addblocks_Math()
	PX2_LOGICM:BeginAddFunObj("+")
	PX2_LOGICM:AddInput("a", FPT_FLOAT)
	PX2_LOGICM:AddInput("b", FPT_FLOAT)
	PX2_LOGICM:AddOutput("out", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_Operator("Math")
	
	PX2_LOGICM:BeginAddFunObj("-")
	PX2_LOGICM:AddInput("a", FPT_FLOAT)
	PX2_LOGICM:AddInput("b", FPT_FLOAT)
	PX2_LOGICM:AddOutput("out", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_Operator("Math")
	
	PX2_LOGICM:BeginAddFunObj("*")
	PX2_LOGICM:AddInput("a", FPT_FLOAT)
	PX2_LOGICM:AddInput("b", FPT_FLOAT)
	PX2_LOGICM:AddOutput("out", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_Operator("Math")
	
	PX2_LOGICM:BeginAddFunObj("/")
	PX2_LOGICM:AddInput("a", FPT_FLOAT)
	PX2_LOGICM:AddInput("b", FPT_FLOAT)
	PX2_LOGICM:AddOutput("out", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_Operator("Math")
	
	PX2_LOGICM:BeginAddFunObj("!")
	PX2_LOGICM:AddInput("b", FPT_BOOL)
	PX2_LOGICM:AddOutput("out", FPT_BOOL)
	PX2_LOGICM:EndAddFun_Operator("Math")
	
	PX2_LOGICM:BeginAddFunObj("&&")
	PX2_LOGICM:AddInput("a", FPT_BOOL)
	PX2_LOGICM:AddInput("b", FPT_BOOL)
	PX2_LOGICM:AddOutput("out", FPT_BOOL)
	PX2_LOGICM:EndAddFun_Operator("Math")
	
	PX2_LOGICM:BeginAddFunObj("||")
	PX2_LOGICM:AddInput("a", FPT_BOOL)
	PX2_LOGICM:AddInput("b", FPT_BOOL)
	PX2_LOGICM:AddOutput("out", FPT_BOOL)
	PX2_LOGICM:EndAddFun_Operator("Math")

	PX2_LOGICM:BeginAddFunObj("abs")
	PX2_LOGICM:AddInput("val", FPT_FLOAT)
	PX2_LOGICM:AddOutput("absval", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Math")

	PX2_LOGICM:BeginAddFunObj("sin")
	PX2_LOGICM:AddInput("degree", FPT_FLOAT)
	PX2_LOGICM:AddOutput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Math")
	
	PX2_LOGICM:BeginAddFunObj("cos")
	PX2_LOGICM:AddInput("degree", FPT_FLOAT)
	PX2_LOGICM:AddOutput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Math")
end