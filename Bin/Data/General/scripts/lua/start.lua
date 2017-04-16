-- start.lua

require("Data/General/scripts/lua/language.lua")
require("Data/General/scripts/lua/sample/sample.lua")

function prestart()
	g_AddLanguage()	
	PX2_APP:NewProject("Data/General/general.px2proj", "General", 0, 960, 600)
end

function start()
	s_SampleCata()
end
