-- ActorControllerPath.lua

ActorControllerPath = class(ActorController,
{
	_name = "ActorControllerPath",
	_direction = 1,
	_path0 = 0,
	_path1 = 0,
	_curPath = -1,
})

function ActorControllerPath:OnAttached()
	ActorController.OnAttached(self)

	self._agent:SetMaxForce(10.0)
	self._agent:SetMass(2.0)
	self._agent:SetRadius(0.15)
	self._agent:SetPhysicsRadius(0.001)
	self._agent:SetHeight(0.1)
	self._agent:SetMaxSpeed(0.2)
    self._agent:ResetPlay()
end

function ActorControllerPath:OnInitUpdate()
	if 1 == self._direction then
		local agentPath = AIAgentPath()
		self._path0 = agentPath
		agentPath:AddPoint(APoint(0.0, 0.0, 0.0))
		agentPath:AddPoint(APoint(0.0, 2.0, 0.0))
		agentPath:AddPoint(APoint(2, 2.0, 0.0))
		agentPath:ConfigPoints(0.05, false)
		self._agent:SetPath(agentPath)
		self._curPath = 0

		local agentPath1 = AIAgentPath()
		agentPath1:AddPoint(APoint(2, 2.0, 0.0))
		agentPath1:AddPoint(APoint(0.0, 2.0, 0.0))
		agentPath1:AddPoint(APoint(0.0, 0.0, 0.0))
		agentPath1:ConfigPoints(0.05, false)
		self._path1 = agentPath1
	elseif 2 == self._direction then
		local agentPath = AIAgentPath()
		agentPath:AddPoint(APoint(0.0, 10.0, 0.0))
		agentPath:AddPoint(APoint(10.0, 10.0, 0.0))
		agentPath:AddPoint(APoint(10.0, 0.0, 0.0))
		agentPath:AddPoint(APoint(0.0, 0.0, 0.0))
		agentPath:ConfigPoints(0.05, true)
		self._agent:SetPath(agentPath)
	end
end

function ActorControllerPath:OnPUpdate()

	local elapsedSeconds = PX2_APP:GetElapsedTime()
	
	-- self
    local position = self._agent:GetPosition()
	local radius = self._agent:GetRadius()
    
	-- follow path
	local followForce = self._agent:ForceToFollowPath(3)
	followForce:Normalize()
	local followForce1 = followForce:Dot(1.0)

	local stayForce = self._agent:ForceToStayOnPath(3)
	stayForce:Normalize()
	-- local wanderForce = self._agent:ForceToWander(elapsedSeconds*1000.0)
	-- wanderForce:Normalize()
	
	local followForceAll0 = followForce1:Add(stayForce:Dot(1.0))
	--local followForceAll1 = followForceAll0:Add(wanderForce:Dot(0.25))
	local followForceAll1 = followForceAll0
	
	-- avoid
	local avoidAgentForce = self._agent:ForceToAvoidAgents(2.5)
    local avoidObjectForce = self._agent:ForceToAvoidObjects(2.5)
	local avoidanceMultiplier = 1.0
	local agentForce = avoidAgentForce:Dot(avoidanceMultiplier)
	local objForce = avoidObjectForce:Dot(avoidanceMultiplier)
	
	-- all force
	local steeringForces = followForceAll1
	local force0 = followForceAll1:Add(agentForce)
	steeringForces = force0:Add(objForce)

	local isPathOver0 = true
	local isPathOver1 = true

	if 0 == self._curPath then
	 	isPathOver0 = self._path0:IsPathOver(position)
	 	if isPathOver0 then
	 		self._agent:SetPath(self._path1)
	 		self._curPath = 1
	 	end
	end
	if 1 == self._curPath then
	 	isPathOver1 = self._path1:IsPathOver(position)
	 	if isPathOver1 then
	 		self._agent:SetPath(self._path0)
	 		self._curPath = 0
	 	end
	end

	if 0 == self._curPath and not isPathOver0 then
		local targetSpeed = 0.2;
		-- Accelerate pathing agents to a minimum speed.
		if (self._agent:GetSpeed() < targetSpeed) then
			local speedForce = self._agent:ForceToTargetSpeed(targetSpeed)
			steeringForces = steeringForces:Add(speedForce)
		end
	end
		
	if 1 == self._curPath and not isPathOver1 then
	 	local targetSpeed = 0.2;
	 	-- Accelerate pathing agents to a minimum speed.
	 	if (self._agent:GetSpeed() < targetSpeed) then
	 		local speedForce = self._agent:ForceToTargetSpeed(targetSpeed)
	 		steeringForces = steeringForces:Add(speedForce)
	 	end
	end
	
	Agent_ApplyPhysicsSteeringForce(self._agent, steeringForces, elapsedSeconds)
	Agent_ClampHorizontalSpeed(self._agent)
end