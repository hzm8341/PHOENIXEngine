-- add_media.lua

function b_addblocks_Media()
	PX2_LOGICM:BeginAddClassFunObj("Stage", "playMusic", false, "Stage")
	PX2_LOGICM:AddInput("musicStr", FPT_STRING)
	PX2_LOGICM:EndAddFun_General("Media")
	
	PX2_LOGICM:BeginAddClassFunObj("Stage", "stopMusic", false, "Stage")
	PX2_LOGICM:EndAddFun_General("Media")
	
	PX2_LOGICM:BeginAddParam("Musics", FunObject.PT_VALUESELECT)
	PX2_LOGICM:AddOutput("val", FPT_STRING)
	PX2_LOGICM:EndAddFun_Param("Media")
end
