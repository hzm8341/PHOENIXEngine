-- start.lua

PX2_SC_LUA:CallFile("DataNIRVANA2/scripts/globals.lua")
PX2_SC_LUA:CallFile("DataNIRVANA2/scripts/language.lua")
PX2_SC_LUA:CallFile("DataNIRVANA2/scripts/languagePre.lua")
PX2_SC_LUA:CallFile("DataNIRVANA2/scripts/functions.lua")
PX2_SC_LUA:CallFile("DataNIRVANA2/scripts/main/frame_main.lua")
PX2_SC_LUA:CallFile("DataNIRVANA2/scripts/main/frame_project.lua")
PX2_SC_LUA:CallFile("DataNIRVANA2/scripts/main/frame_res.lua")
PX2_SC_LUA:CallFile("DataNIRVANA2/scripts/main/frame_timeline.lua")
PX2_SC_LUA:CallFile("DataNIRVANA2/scripts/main/frame_market.lua")
PX2_SC_LUA:CallFile("DataNIRVANA2/scripts/main/frame_inspector.lua")
PX2_SC_LUA:CallFile("DataNIRVANA2/scripts/main/frame_content.lua")
PX2_SC_LUA:CallFile("DataNIRVANA2/scripts/main/frame_run.lua")
PX2_SC_LUA:CallFile("DataNIRVANA2/scripts/main/menu.lua")
PX2_SC_LUA:CallFile("DataNIRVANA2/scripts/main/menufunction.lua")
PX2_SC_LUA:CallFile("DataNIRVANA2/scripts/blueprint/blueprint.lua")

function n_EditOnEvent(entType)
	n_project:onEvent(entType)
end

function naPreStart()
	n_AddLanguagePre()
end

function naStart()
	n_AddLanguage()
	n_CreateMainMenu()
	n_CreatMainWindow()
end