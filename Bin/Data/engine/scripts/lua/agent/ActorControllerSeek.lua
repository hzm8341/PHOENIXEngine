-- ActorControllerSeek.lua

ActorControllerSeek = class(ActorController,
{
	_name = "ActorControllerSeek",
})

function ActorControllerSeek:OnAttached()
	ActorController.OnAttached(self)

	self._agent:SetPosition(APoint(-1.0, 0.0, 0.0))
	self._agent:SetTarget(APoint(-10, 0.0, 0.0))
	self._agent:SetTargetRadius(1.5);
    self._agent:ResetPlay()
end