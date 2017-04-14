-- start.lua

require("Data/Block/scripts/lua/language.lua")
require("Data/Block/scripts/lua/resource.lua")

require("Data/Block/scripts/lua/add_arduino.lua")
require("Data/Block/scripts/lua/add_event.lua")
require("Data/Block/scripts/lua/add_look.lua")
require("Data/Block/scripts/lua/add_math.lua")
require("Data/Block/scripts/lua/add_media.lua")
require("Data/Block/scripts/lua/add_param.lua")
require("Data/Block/scripts/lua/add_raspberry.lua")
require("Data/Block/scripts/lua/add_test.lua")
require("Data/Block/scripts/lua/add_transform.lua")
require("Data/Block/scripts/lua/add_func.lua")


function prestart()
	b_AddLanguage()
	b_AddLanguageProgram()
	
	b_addblocks_Arduino()
	b_addblocks_Raspberry()
	b_addblocks_Events()
	b_Addblocks_Math()
	b_Addblocks_Params()
	b_Addblocks_ParamsCreated()
	b_Addblocks_Tests()
	b_addblocks_Media()	
	b_addblocks_Look()
	b_Addblocks_Transform()
	b_addblocks_Func()
	b_addblocks_FuncStage()
end

function start()

end