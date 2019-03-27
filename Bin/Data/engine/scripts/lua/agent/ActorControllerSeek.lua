-- ActorControllerSeek.lua

ActorControllerSeek = class(ActorController,
{
	_name = "ActorControllerSeek",
})

function ActorControllerSeek:OnAttached()
	ActorController.OnAttached(self)

	self._agent:SetMaxForce(100.0)
	self._agent:SetMass(10.0)
	self._agent:SetRadius(0.15)
	self._agent:SetPhysicsRadius(0.1)
	self._agent:SetHeight(0.5)
	self._agent:SetMaxSpeed(0.8)

	self._agent:SetPosition(APoint(0.0, 3.0, 0.0))

	self._agent:SetTarget(APoint(0.0, 3.0, 0.0))
	self._agent:SetTargetRadius(0.1);
    self._agent:ResetPlay()
end