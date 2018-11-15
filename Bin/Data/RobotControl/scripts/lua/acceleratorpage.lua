-- acceleratorpage.lua

rc_SliderHor = nil
rc_SliderVer = nil

function rc_AcceleratorPage ()
    local uiFrame = UIFrame:New()

	uiFrame:SetAnchorHor(0.0, 1.0)
    uiFrame:SetAnchorVer(0.0, 1.0)
    
    local sliderHor = UISlider:New()
    uiFrame:AttachChild(sliderHor)
    rc_SliderHor = sliderHor
    sliderHor.LocalTransform:SetTranslateY(-2.0)
    sliderHor:SetAnchorParamVer(60.0, 60.0)
    sliderHor:SetSize(300.0, 40.0)
    sliderHor:CreateAddText("Hor")
    sliderHor:GetButSlider():SetSize(60,60)
    sliderHor:SetSliderLength(60)   

    local sliderVer = UISlider:New()
    uiFrame:AttachChild(sliderVer)
    rc_SliderVer = sliderVer
    sliderVer.LocalTransform:SetTranslateY(-2.0)
    sliderVer:SetAnchorParamVer(-60.0, -60.0)
    sliderVer:SetSize(300.0, 40.0)
    sliderVer:CreateAddText("Ver")

    return uiFrame
end

function rc_AcceleratorUpdate(appseconds, elapsedseconds)
    local xPos = PX2_PFSDK:GetAcceleratorX()
    local yPos = PX2_PFSDK:GetAcceleratorY()
    local zPos = PX2_PFSDK:GetAcceleratorZ()

    local percX = 0.5 + (xPos*0.1)*0.5
    local percY = 0.5 + (yPos*0.1)*0.5

    if percX < 0.0 then
        percX = 0.0
    end
    if percX > 1.0 then
        percX = 1.0
    end

    if percY < 0.0 then
        percY = 0.0
    end
    if percY > 1.0 then
        percY = 1.0
    end

    rc_SliderHor:SetPercent(percX, false)
    rc_SliderVer:SetPercent(percY, false)
end