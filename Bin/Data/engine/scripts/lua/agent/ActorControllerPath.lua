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
	-- if 1 == self._direction then
	-- 	local agentPath = AIAgentPath()
	-- 	self._path0 = agentPath
	-- 	agentPath:AddPoint(APoint(0.0, 0.0, 0.0))
	-- 	agentPath:AddPoint(APoint(0.0, 2.0, 0.0))
	-- 	agentPath:AddPoint(APoint(1.0, 2.0, 0.0))
	-- 	agentPath:ConfigPoints(0.05, false)
	-- 	self._agent:SetPath(agentPath)
	-- 	self._curPath = 0

	-- 	local agentPath1 = AIAgentPath()
	-- 	agentPath1:AddPoint(APoint(1.0, 2.0, 0.0))
	-- 	agentPath1:AddPoint(APoint(0.0, 2.0, 0.0))
	-- 	agentPath1:AddPoint(APoint(0.0, 0.0, 0.0))
	-- 	agentPath1:ConfigPoints(0.05, false)
	-- 	self._path1 = agentPath1
	-- elseif 2 == self._direction then
	-- 	local agentPath = AIAgentPath()
	-- 	agentPath:AddPoint(APoint(0.0, 10.0, 0.0))
	-- 	agentPath:AddPoint(APoint(10.0, 10.0, 0.0))
	-- 	agentPath:AddPoint(APoint(10.0, 0.0, 0.0))
	-- 	agentPath:AddPoint(APoint(0.0, 0.0, 0.0))
	-- 	agentPath:ConfigPoints(0.05, true)
	-- 	self._agent:SetPath(agentPath)
	-- end
end

function ActorControllerPath:OnPUpdate()

	local elapsedSeconds = PX2_APP:GetElapsedTime()
	
	-- self
    local position = self._agent:GetPosition()
	local radius = self._agent:GetRadius()  

end