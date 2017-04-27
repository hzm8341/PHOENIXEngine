-- add_event.lua

function b_addblocks_Events()
	PX2_LOGICM:BeginAddEvent("Event", "onEvent")
	PX2_LOGICM:AddInput("Event", FPT_STRING)
	PX2_LOGICM:AddOutput("EventDo", FPT_LINK)
	PX2_LOGICM:EndAddFun_Event("Event")

	PX2_LOGICM:BeginAddParam("EditES", FunObject.PT_ENUMSTRING)
	PX2_LOGICM:AddInputString("AddSelect", "")
	PX2_LOGICM:AddInputString("RemoveSelect", "")
	PX2_LOGICM:AddInputString("RemoveAllSelects", "")
	PX2_LOGICM:AddInputString("PushUnDo", "")
	PX2_LOGICM:AddInputString("UnDo", "")
	PX2_LOGICM:AddInputString("ReDo", "")
	PX2_LOGICM:AddInputString("NoUnDo", "")
	PX2_LOGICM:AddInputString("NoReDo", "")
	PX2_LOGICM:AddOutput("val", FPT_STRING)
	PX2_LOGICM:EndAddFun_Param("Event")
	
	--PX2_LOGICM:BeginAddClassFunObj("Stage", "getEventObjectName", false, "Stage")
	--PX2_LOGICM:AddOutput("name", FPT_STRING)
	--PX2_LOGICM:EndAddFun_General("Event")
	
	--PX2_LOGICM:BeginAddClassFunObj("Stage", "getEventDataInt", false, "Stage")
	--PX2_LOGICM:AddOutput("val", FPT_INT)
	--PX2_LOGICM:EndAddFun_General("Event")

	--PX2_LOGICM:BeginAddClassFunObj("Stage", "getEventDataString", false, "Stage")
	--PX2_LOGICM:AddOutput("str", FPT_STRING)
	--PX2_LOGICM:EndAddFun_General("Event")
end