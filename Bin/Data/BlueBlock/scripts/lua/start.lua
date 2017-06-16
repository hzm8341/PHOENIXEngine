-- start.lua

require("Data/BlueBlock/scripts/lua/language.lua")
require("Data/BlueBlock/scripts/lua/add_event.lua")
require("Data/BlueBlock/scripts/lua/add_math.lua")
require("Data/BlueBlock/scripts/lua/add_param.lua")
require("Data/BlueBlock/scripts/lua/add_test.lua")
require("Data/BlueBlock/scripts/lua/editor/editor.lua")

function b_Start()
	bb_add_language()
	
	bb_add_event()
	bb_add_math()
	bb_add_param()
	bb_add_test()

	blueblock_editorstart()
end