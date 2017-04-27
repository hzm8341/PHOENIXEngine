-- start.lua

require("Data/BlueBlock/scripts/lua/language.lua")

require("Data/BlueBlock/scripts/lua/add_event.lua")
require("Data/BlueBlock/scripts/lua/add_math.lua")
require("Data/BlueBlock/scripts/lua/add_param.lua")
require("Data/BlueBlock/scripts/lua/add_raspberry.lua")
require("Data/BlueBlock/scripts/lua/add_test.lua")
require("Data/BlueBlock/scripts/lua/editor/editor.lua")

function b_Start()
	b_AddLanguageProgram()
	b_addblocks_Events()
	b_Addblocks_Math()
	b_Addblocks_Params()
	b_Addblocks_Tests()
	b_addblocks_Raspberry()
	editorstart()
end