-- robot.lua

function ch_Robot()    
    local ui = PX2_PROJ:GetUI()
    
    local frameChaos = UIFrame:New()
    ui:AttachChild(frameChaos)
    frameChaos:SetAnchorHor(0.0, 1.0)
    frameChaos:SetAnchorVer(0.0, 1.0)

    -- blue block 初始化
    PX2BBLOCK_SYS:Initlize()
    PX2_BBM:SetProductTag("Chaos")
    PX2BBLOCK_SYS:setDeviceID(1)
    PX2BBLOCK_SYS:setBluetooth()

    local ctrlScript = ChaosCtrl:New()
    local ctrler = Cast:ToSC(ctrlScript.__object)
	frameChaos:AttachController(ctrler)
	ctrler:ResetPlay()
end