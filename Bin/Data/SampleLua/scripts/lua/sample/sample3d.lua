-- sample3d
-- stuff about 3d scene

function s_createsample3d()
	-- ui
    local ui = PX2_PROJ:GetUI()
    
    local frameTouch = UIFrame:New()
    ui:AttachChild(frameTouch)
    frameTouch:SetAnchorHor(0.0, 1.0)
    frameTouch:SetAnchorVer(0.0, 1.0)
    --frameTouch:CreateAddBackgroundPicBox()

    -- scene
    local scene = Scene:New()
    PX2_PROJ:SetScene(scene)

    -- robot
    local nodePXFrame = Node:New("PXFrame")
    scene:AttachChild(nodePXFrame)
    
    local actorScript = ActorCtrl:New({val = 1001, _name="Box"})
    actorScript._val = 1001	
    local actorController = Cast:ToSC(actorScript.__object)
    nodePXFrame:AttachController(actorController)

    -- test val
    for k, v in pairs(gScriptTable) do
        PX2_LOGGER:LogInfo("script_lua", "gScriptTable:"..k)
    end	
    local actorScript1 = gScriptTable[actorController:SelfP()]
    actorScript1._val = 1002
    PX2_LOGGER:LogInfo("script_lua", "ActorCtrl._val:"..actorScript._val)

    -- cam model
    local mainCameraNode = scene:GetMainCameraNode()
    local cameraPlayCtrl = PX2_CREATER:CreateCameraPlayController()
    nodePXFrame:AttachController(cameraPlayCtrl)
    cameraPlayCtrl:SetCameraNode(mainCameraNode)
    cameraPlayCtrl:SetCameraDistance(60.0)
    cameraPlayCtrl:SetCameraDist(30.0, 60.0)
    cameraPlayCtrl:SetTouchSizeNode(frameTouch)
    cameraPlayCtrl:ResetPlay()

    -- voxel
    --[[
    PX2_VOXELM:Initlize(VoxelManager.T_TEX)
    local vs = VoxelSection:New()
    vs:SetMinSize(-3, -3, -1)
    vs:SetMaxSize(3, 3, -1)
    vs:SetDistXY(10)
    vs:SetDistZ(10)
    vs:SetInitMtlType(2)
    scene:AttachChild(vs)
    ]]--

    -- sky
   -- local sky = PX2_CREATER:CreateSkyBox("Data/engine/sky/skybox/thickcloudswater/")
   -- scene:AttachChild(sky)
end