-- add_param.lua

function b_Addblocks_Params()
	PX2_LOGICM:BeginAddFunObj("setInt")
	PX2_LOGICM:AddInput("variable", FPT_INT)
	PX2_LOGICM:AddInput("val", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Param")
	
	PX2_LOGICM:BeginAddFunObj("setFloat")
	PX2_LOGICM:AddInput("variable", FPT_FLOAT)
	PX2_LOGICM:AddInput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Param")
	
	PX2_LOGICM:BeginAddFunObj("setChar")
	PX2_LOGICM:AddInput("variable", FPT_CHAR)
	PX2_LOGICM:AddInput("val", FPT_CHAR)
	PX2_LOGICM:EndAddFun_General("Param")
	
	PX2_LOGICM:BeginAddFunObj("setString")
	PX2_LOGICM:AddInput("variable", FPT_STRING)
	PX2_LOGICM:AddInput("val", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Param")
	
	PX2_LOGICM:BeginAddFunObj("setBool")
	PX2_LOGICM:AddInput("variable", FPT_BOOL)
	PX2_LOGICM:AddInput("val", FPT_BOOL)
	PX2_LOGICM:EndAddFun_General("Param")
	
	PX2_LOGICM:BeginAddFunObj("setObject")
	PX2_LOGICM:AddInput("variable", FPT_POINTER)
	PX2_LOGICM:AddInput("val", FPT_POINTER)
	PX2_LOGICM:EndAddFun_General("Param")
	
	-- const
	PX2_LOGICM:BeginAddParam("HIGH", FunObject.PT_CONST)
	PX2_LOGICM:AddInputInt("val", 1)
	PX2_LOGICM:EndAddFun_Param("Param")
	
	PX2_LOGICM:BeginAddParam("LOW", FunObject.PT_CONST)
	PX2_LOGICM:AddInputInt("val", 0)
	PX2_LOGICM:EndAddFun_Param("Param")
	
	PX2_LOGICM:BeginAddParam("TRUE", FunObject.PT_CONST)
	PX2_LOGICM:AddInputBool("val", true)
	PX2_LOGICM:EndAddFun_Param("Param")
	
	PX2_LOGICM:BeginAddParam("FALSE", FunObject.PT_CONST)
	PX2_LOGICM:AddInputBool("val", false)
	PX2_LOGICM:EndAddFun_Param("Param")	
	
	PX2_LOGICM:BeginAddParam("iValue", FunObject.PT_VALUE)
	PX2_LOGICM:AddInputInt("val", 0)
	PX2_LOGICM:EndAddFun_Param("Param")
	
	PX2_LOGICM:BeginAddParam("fValue", FunObject.PT_VALUE)
	PX2_LOGICM:AddInputFloat("val", 0.0)
	PX2_LOGICM:EndAddFun_Param("Param")
	
	PX2_LOGICM:BeginAddParam("cValue", FunObject.PT_VALUE)
	PX2_LOGICM:AddInputChar("val", 65)
	PX2_LOGICM:EndAddFun_Param("Param")
	
	PX2_LOGICM:BeginAddParam("strValue", FunObject.PT_VALUE)
	PX2_LOGICM:AddInputString("val", "abc")
	PX2_LOGICM:EndAddFun_Param("Param")
	
	PX2_LOGICM:BeginAddParam("ParamsInt", FunObject.PT_VARIABLESELECT)
	PX2_LOGICM:AddOutput("val", FPT_INT)
	PX2_LOGICM:EndAddFun_Param("Param")
	
	PX2_LOGICM:BeginAddParam("ParamsFloat", FunObject.PT_VARIABLESELECT)
	PX2_LOGICM:AddOutput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_Param("Param")
	
	PX2_LOGICM:BeginAddParam("ParamsChar", FunObject.PT_VARIABLESELECT)
	PX2_LOGICM:AddOutput("val", FPT_CHAR)
	PX2_LOGICM:EndAddFun_Param("Param")
	
	PX2_LOGICM:BeginAddParam("ParamsBool", FunObject.PT_VARIABLESELECT)
	PX2_LOGICM:AddOutput("val", FPT_CHAR)
	PX2_LOGICM:EndAddFun_Param("Param")
	
	PX2_LOGICM:BeginAddParam("ParamsString", FunObject.PT_VARIABLESELECT)
	PX2_LOGICM:AddOutput("val", FPT_STRING)
	PX2_LOGICM:EndAddFun_Param("Param")
end

function b_Addblocks_ParamsCreated()
	-- variable
	PX2_LOGICM:BeginAddParam("iVariable", FunObject.PT_VARIABLE)
	PX2_LOGICM:AddInputInt("val", 0)
	PX2_LOGICM:EndAddFun_Param("ParamCreated")
	
	PX2_LOGICM:BeginAddParam("fVariable", FunObject.PT_VARIABLE)
	PX2_LOGICM:AddInputFloat("val", 0.0)
	PX2_LOGICM:EndAddFun_Param("ParamCreated")	
	
	PX2_LOGICM:BeginAddParam("cVariable", FunObject.PT_VARIABLE)
	PX2_LOGICM:AddInputChar("val", 65)
	PX2_LOGICM:EndAddFun_Param("ParamCreated")
	
	PX2_LOGICM:BeginAddParam("strVariable", FunObject.PT_VARIABLE)
	PX2_LOGICM:AddInputString("val", "defstring")
	PX2_LOGICM:EndAddFun_Param("ParamCreated")
	
	PX2_LOGICM:BeginAddParam("objVariable", FunObject.PT_VARIABLE)
	PX2_LOGICM:AddInputObj("val")
	PX2_LOGICM:EndAddFun_Param("ParamCreated")
end