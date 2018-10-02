-- ZERONEScene.lua

function zo_Scene()
    ZERONE_IsZERO3DSceneCreated = true
 
    -- start slam
    --PX2_ROBOT:StartShareMemory()

    -- new scene
    PX2_APP:NewScene()
    local scene = PX2_PROJ:GetScene()
    scene:ResetPlay()

    -- new root node
    local nodeScene = Node:New("SceneFrame")
    scene:AttachChild(nodeScene)

    --[[
    -- for test not useful
    for k, v in pairs(gScriptTable) do
        PX2_LOGGER:LogInfo("script_lua", "gScriptTable:"..k)
    end	
    local actorScript1 = gScriptTable[actorController:SelfP()]
    actorScript1._val = 1002
    PX2_LOGGER:LogInfo("script_lua", "ActorCtrl._val:"..actorCtrlScript._val)
    ]]--

    -- cam model
    local mainCameraNode = scene:GetMainCameraNode()
    local cameraPlayCtrl = PX2_CREATER:CreateCameraPlayController()
    nodeScene:AttachController(cameraPlayCtrl)
    cameraPlayCtrl:SetCameraNode(mainCameraNode)
    cameraPlayCtrl:SetCameraDistance(40.0)
    cameraPlayCtrl:SetCameraDist(5.0, 60.0)
    cameraPlayCtrl:ResetPlay()

    -- cam touchFrame
    local ui = PX2_PROJ:GetUI()
    local frameTouch = UIFrame:New()
    ui:AttachChild(frameTouch)
    frameTouch:SetAnchorHor(0.0, 1.0)
    frameTouch:SetAnchorVer(0.0, 1.0)
    cameraPlayCtrl:SetTouchSizeNode(frameTouch)
    
    -- actor control
    local followerActorAgent = nil


    -- seek
    for i=1,10,1 do
        local actor = PX2_CREATER:CreateActor()
        scene:AttachChild(actor)
        local movBox = PX2_CREATER:CreateMovable_Box()
        actor:AttachChild(movBox)
        
		local script = ActorControllerSeek:New()
        local scriptCtrl = Cast:ToSC(script.__object)
        actor:AttachController(scriptCtrl)
        scriptCtrl:ResetPlay()
    end

	--[[
    -- path
    for i=1,2,1 do
        local actor = PX2_CREATER:CreateActor()
        scene:AttachChild(actor)
        local movBox = PX2_CREATER:CreateMovable_Box()
        actor:AttachChild(movBox)
        local script = ActorControllerPath:New()
        if 1==i then
            followerActorAgent = actor:GetAIAgent()
        end
        if 1<=i and i<=1 then
            script._direction = 1
        else
            script._direction = 2
        end
        local scriptCtrl = Cast:ToSC(script.__object)
        actor:AttachController(scriptCtrl)
        scriptCtrl:ResetPlay()
    end

    -- follower
    if nil~=followerActorAgent then
        for i=1,4,1 do
            local actor = PX2_CREATER:CreateActor()
            scene:AttachChild(actor)
            local movBox = PX2_CREATER:CreateMovable_Box()
            actor:AttachChild(movBox)
            local script = ActorControllerFollower:New()
            script._leader = followerActorAgent

            local scriptCtrl = Cast:ToSC(script.__object)
            actor:AttachController(scriptCtrl)
            scriptCtrl:ResetPlay()
        end     
    end
	]]--

    -- actor rect
    local actorRect = PX2_CREATER:CreateActor_InfinitePlane()
    scene:AttachChild(actorRect)
    actorRect.LocalTransform:SetTranslateZ(-0.2)

    --[[
    -- voxel
    PX2_VOXELM:Initlize(VoxelManager.T_TEX)
    local vs = VoxelSection:New()
    vs:SetMinSize(-5, -5, 0)
    vs:SetMaxSize(5, 5, 0)
    vs:SetDistXY(10)
    vs:SetDistZ(10)
    vs:SetInitMtlType(0)
    scene:AttachChild(vs)
    PX2_ROBOT:SetVoxelSection(vs)
    ]]--

    -- sky
    --local sky = PX2_CREATER:CreateSkyBox("Data/engine/sky/skybox/thickcloudswater/")
    --scene:AttachChild(sky)
end

function zo_SceneAddBox()
    local scene = PX2_PROJ:GetScene()

    local actor = PX2_CREATER:CreateActorBox()
    scene:AttachChild(actor)
    actor:GetAIAgentBase():SetPosition(APoint(0.5, 0.5, 10.0))
    actor:GetAIAgentBase():ResetPlay()
end