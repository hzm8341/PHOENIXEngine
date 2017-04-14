-- add_transform.lua

function b_Addblocks_Transform()
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setPostion", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("posX", FPT_FLOAT)
	PX2_LOGICM:AddInput("posY", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setAnchorHor", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("a", FPT_FLOAT)
	PX2_LOGICM:AddInput("b", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setAnchorParamHor", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("a", FPT_FLOAT)
	PX2_LOGICM:AddInput("b", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setAnchorVer", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("a", FPT_FLOAT)
	PX2_LOGICM:AddInput("b", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setAnchorParamVer", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("a", FPT_FLOAT)
	PX2_LOGICM:AddInput("b", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setPvoit", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("a", FPT_FLOAT)
	PX2_LOGICM:AddInput("b", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setSize", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setSizeWidthHeight", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("width", FPT_FLOAT)
	PX2_LOGICM:AddInput("height", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setRotateXYZ", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("x", FPT_FLOAT)
	PX2_LOGICM:AddInput("y", FPT_FLOAT)
	PX2_LOGICM:AddInput("z", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setRotateX", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setRotateY", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setRotateZ", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "getRotateX", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddOutput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "getRotateY", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddOutput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")	
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "getRotateZ", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddOutput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setScale", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "getScale", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddOutput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setScaleXZ", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("x", FPT_FLOAT)
	PX2_LOGICM:AddInput("z", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setScaleX", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setScaleX", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "getScaleX", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddOutput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "getScaleZ", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddOutput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "move", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("x", FPT_FLOAT)
	PX2_LOGICM:AddInput("y", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "addRotate", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("degree", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "addScale", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("val", FPT_FLOAT)
	PX2_LOGICM:EndAddFun_General("Transform")	
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "setLayer", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddInput("val", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Transform")
	
	PX2_LOGICM:BeginAddClassFunObj("BActor", "getLayer", false)
	PX2_LOGICM:AddInput("obj", FPT_POINTER_THIS)
	PX2_LOGICM:AddOutput("val", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Transform")
end