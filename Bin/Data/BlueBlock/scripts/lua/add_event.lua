-- add_event.lua

function bb_add_event()
	PX2_LOGICM:BeginAddEvent("Event", "onEvent")
	PX2_LOGICM:AddInput("Event", FPT_STRING)
	PX2_LOGICM:AddOutput("EventDo", FPT_LINK)
	PX2_LOGICM:EndAddFun_Event("Event")

	PX2_LOGICM:BeginAddParam("BBlockEventS", FunObject.PT_ENUMSTRING)
	PX2_LOGICM:AddInputString("String", "")
	PX2_LOGICM:AddInputString("UIButtonPressed", "")
	PX2_LOGICM:AddInputString("UIButtonReleased", "")
	PX2_LOGICM:AddInputString("UIButtonReleasedNotPick", "")
	PX2_LOGICM:AddInputString("UIRoundDragChanged", "")
	PX2_LOGICM:AddInputString("VoiceResult", "")
	PX2_LOGICM:AddOutput("val", FPT_STRING)
	PX2_LOGICM:EndAddFun_Param("Event")

--[[
	PX2_LOGICM:BeginAddClassFunObj("BBlockSystem", "getEventObjectName", false, "PX2BBLOCK_SYS")
	PX2_LOGICM:AddOutput("name", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Event")
	
	PX2_LOGICM:BeginAddClassFunObj("BBlockSystem", "getEventDataInt", false, "PX2BBLOCK_SYS")
	PX2_LOGICM:AddOutput("val", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Event")

	PX2_LOGICM:BeginAddClassFunObj("BBlockSystem", "getEventDataString", false, "PX2BBLOCK_SYS")
	PX2_LOGICM:AddOutput("str", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Event")
]]--
end