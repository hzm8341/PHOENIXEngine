-- play.lua

require("Data/SampleLua/scripts/lua/language.lua")
require("Data/SampleLua/scripts/lua/sample/sample.lua")
require("Data/SampleLua/scripts/lua/sample/ActorCtrl.lua")

function preplay()
	sampleLua_AddLanguage()	
end

function play()
	sampleLua_Sample()
end
