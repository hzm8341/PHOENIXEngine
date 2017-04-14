-- arduino.lua


function b_addblocks_Arduino()
	PX2_LOGICM:BeginAddFunObj("pinMode")
	PX2_LOGICM:AddInput("pin", FPT_INT)
	PX2_LOGICM:AddInput("mode", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Arduino")
	
	PX2_LOGICM:BeginAddFunObj("digitalWrite")
	PX2_LOGICM:AddInput("pin", FPT_INT)
	PX2_LOGICM:AddInput("value", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Arduino")
	
	PX2_LOGICM:BeginAddFunObj("digitalRead")
	PX2_LOGICM:AddInput("pin", FPT_INT)
	PX2_LOGICM:AddOutput("value", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Arduino")
	
	PX2_LOGICM:BeginAddFunObj("analogRead")
	PX2_LOGICM:AddInput("pin", FPT_INT)
	PX2_LOGICM:AddOutput("value", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Arduino")
	
	PX2_LOGICM:BeginAddFunObj("analogWrite")
	PX2_LOGICM:AddInput("pin", FPT_INT)
	PX2_LOGICM:AddInput("value", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Arduino")
	
	PX2_LOGICM:BeginAddFunObj("delay")
	PX2_LOGICM:AddInput("value", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Arduino")
	
	PX2_LOGICM:BeginAddFunObj("println")
	PX2_LOGICM:AddInput("strval", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Arduino")
	
	PX2_LOGICM:BeginAddClassFunObj("Serial", "available", false, "Serial")
	PX2_LOGICM:AddOutput("val", FPT_BOOL)
	PX2_LOGICM:EndAddFun_General("Arduino")
	
	PX2_LOGICM:BeginAddClassFunObj("Serial", "read", false, "Serial")
	PX2_LOGICM:AddOutput("val", FPT_CHAR)
	PX2_LOGICM:EndAddFun_General("Arduino")
end