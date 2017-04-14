-- add_event.lua

function b_addblocks_Events()
	PX2_LOGICM:BeginAddClassFunObj("Stage", "sendEvent", false, "Stage")
	PX2_LOGICM:AddInputString("str", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Event")
	
	PX2_LOGICM:BeginAddEvent("Event", "onEvent")
	PX2_LOGICM:AddInput("Event", FPT_STRING)
	PX2_LOGICM:AddOutput("EventDo", FPT_LINK)
	PX2_LOGICM:EndAddFun_Event("Event")

	PX2_LOGICM:BeginAddParam("EventS", FunObject.PT_ENUMSTRING)
	PX2_LOGICM:AddInputString("String", "")
	PX2_LOGICM:AddInputString("NetClientConnected", "")
	PX2_LOGICM:AddInputString("NetClientDisConnected", "")
	PX2_LOGICM:AddInputString("NetClientReceived", "")
	PX2_LOGICM:AddInputString("NetServerOnConnect", "")
	PX2_LOGICM:AddInputString("NetServerOnDisConnect", "")
	PX2_LOGICM:AddInputString("NetServerOnMsgReceive", "")
	PX2_LOGICM:AddInputString("UIButtonPressed", "")
	PX2_LOGICM:AddInputString("UIButtonReleased", "")
	PX2_LOGICM:AddInputString("UIButtonReleasedNotPick", "")
	PX2_LOGICM:AddInputString("UIRoundDragChanged", "")
	PX2_LOGICM:AddInputString("VoiceResult", "")
	PX2_LOGICM:AddOutput("val", FPT_STRING)
	PX2_LOGICM:EndAddFun_Param("Event")
	
	PX2_LOGICM:BeginAddClassFunObj("Stage", "getEventObjectName", false, "Stage")
	PX2_LOGICM:AddOutput("name", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Event")
	
	PX2_LOGICM:BeginAddClassFunObj("Stage", "getEventDataInt", false, "Stage")
	PX2_LOGICM:AddOutput("val", FPT_INT)
	PX2_LOGICM:EndAddFun_General("Event")

	PX2_LOGICM:BeginAddClassFunObj("Stage", "getEventDataString", false, "Stage")
	PX2_LOGICM:AddOutput("str", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Event")
end