-- ActorControllerPuresure.lua

ActorControllerPuresure = class(ActorController,
{
	_name = "ActorControllerPuresure",
})

function ActorControllerPuresure:OnPUpdate()
	-- need do it to clear
	--collectgarbage("collect")
end