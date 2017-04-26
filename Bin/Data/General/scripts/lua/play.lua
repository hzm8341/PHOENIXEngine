-- play.lua

require("Data/General/scripts/lua/language.lua")
require("Data/General/scripts/lua/sample/sample.lua")

function preplay()
	g_AddLanguage()	
	--PX2_APP:NewProject("Data/General/general.px2proj", "General", 0, 960, 600)
end

function play()
	s_SampleCata()
end
