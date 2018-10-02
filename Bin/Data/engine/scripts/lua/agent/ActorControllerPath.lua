-- ActorControllerPath.lua

ActorControllerPath = class(ActorController,
{
	_name = "ActorControllerPath",
	_direction = 1,
})

function ActorControllerPath:OnAttached()
	ActorController.OnAttached(self)

	self._agent:SetRadius(0.8)
    self._agent:ResetPlay()
end

function ActorControllerPath:OnInitUpdate()
	if 1 == self._direction then
		local agentPath = AIAgentPath()
		agentPath:AddPoint(APoint(0.0, 0.0, 0.0))
		agentPath:AddPoint(APoint(30.0, 0.0, 0.0))
		agentPath:AddPoint(APoint(30.0, 30.0, 0.0))
		agentPath:AddPoint(APoint(0.0, 30.0, 0.0))
		agentPath:ConfigPoints(0.5, true)
		self._agent:SetPath(agentPath)
	elseif 2 == self._direction then
		local agentPath = AIAgentPath()
		agentPath:AddPoint(APoint(0.0, 30.0, 0.0))
		agentPath:AddPoint(APoint(30.0, 30.0, 0.0))
		agentPath:AddPoint(APoint(30.0, 0.0, 0.0))
		agentPath:AddPoint(APoint(0.0, 0.0, 0.0))
		agentPath:ConfigPoints(0.5, true)
		self._agent:SetPath(agentPath)
	end
end

function ActorControllerPath:OnPUpdate()

	local elapsedSeconds = PX2_APP:GetElapsedTime()
	
	-- self
    local position = self._agent:GetPosition()
	local radius = self._agent:GetRadius()
    
	-- follow path
	local followForce = self._agent:ForceToFollowPath(1.25)
	followForce:Normalize()
	local stayForce = self._agent:ForceToStayOnPath(0.5)
	stayForce:Normalize()
	local wanderForce = self._agent:ForceToWander(elapsedSeconds*1000.0)
	wanderForce:Normalize()
	
	local followForceAll0 = followForce:Add(stayForce:Dot(0.25))
	local followForceAll1 = followForceAll0:Add(wanderForce:Dot(0.25))
	
	-- avoid
	local avoidAgentForce = self._agent:ForceToAvoidAgents(3.5)
    local avoidObjectForce = self._agent:ForceToAvoidObjects(3.5)
	local avoidanceMultiplier = 3
	local agentForce = avoidAgentForce:Dot(avoidanceMultiplier)
	local objForce = avoidObjectForce:Dot(avoidanceMultiplier)
	
	-- all force
	local steeringForces = followForceAll1
	local force0 = followForceAll1:Add(agentForce)
	steeringForces = force0:Add(objForce)
	
    local targetSpeed = 3;
    -- Accelerate pathing agents to a minimum speed.
    if (self._agent:GetSpeed() < targetSpeed) then
        local speedForce = self._agent:ForceToTargetSpeed(targetSpeed)
		speedForce:Normalize()
        steeringForces = steeringForces:Add(speedForce)
    end
	
	Agent_ApplyPhysicsSteeringForce(self._agent, steeringForces, elapsedSeconds)
	Agent_ClampHorizontalSpeed(self._agent)
end