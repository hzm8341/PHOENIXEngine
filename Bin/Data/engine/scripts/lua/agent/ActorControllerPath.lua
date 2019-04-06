-- ActorControllerPath.lua

ActorControllerPath = class(ActorController,
{
	_name = "ActorControllerPath",
	_direction = 1,
	_path0 = 0,
})

function ActorControllerPath:OnAttached()
	ActorController.OnAttached(self)

	self._agent:SetMaxForce(40.0)
	self._agent:SetMass(20.0)
	self._agent:SetRadius(0.12)
	self._agent:SetPhysicsRadius(0.00001)
	self._agent:SetHeight(0.1)
	self._agent:SetMaxSpeed(0.2)
    self._agent:ResetPlay()
end

function ActorControllerPath:OnInitUpdate()
	local agentPath = AIAgentPath()
	self._path0 = agentPath
	agentPath:AddWayPoint(APoint(0.0, 0.0, 0.0))
	agentPath:AddWayPoint(APoint(0.0, 2.0, 0.0))
	agentPath:AddWayPoint(APoint(1.0, 2.0, 0.0))
	self._agent:SetPath(agentPath)
end

function ActorControllerPath:OnPUpdate()

	local elapsedSeconds = PX2_APP:GetElapsedTime()
	
	-- self
    local position = self._agent:GetPosition()
	local radius = self._agent:GetRadius()  

end