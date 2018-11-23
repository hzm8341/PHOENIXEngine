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
    sliderHor:GetButSlider():SetStateColorDefaultWhite()
    sliderHor:GetFPicBoxBack():GetUIPicBox():SetPicBoxType(UIPicBox.PBT_NINE)
    sliderHor:GetFPicBoxBack():GetUIPicBox():SetTexCornerSize(12,12,12,12)        
    sliderHor:GetFPicBoxBack():GetUIPicBox():SetTexture("Data/RobotControl/images/directctrl/slider0.png")
    sliderHor:GetButSlider():GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("Data/RobotControl/images/directctrl/slider1.png")
    sliderHor.LocalTransform:SetTranslateY(-2.0)
    sliderHor:SetAnchorParamVer(60.0, 60.0)
    sliderHor:SetSliderLength(60)    
    sliderHor:SetHeight(60.0)
    sliderHor:SetWidth(300.0)
    local text = sliderHor:CreateAddText("Hor")
    text:GetText():SetFontColor(Float3.WHITE)
    text:SetAnchorParamVer(-40.0, -40.0)
    sliderHor:GetButSlider():SetSize(60,60)


    local sliderVer = UISlider:New()
    uiFrame:AttachChild(sliderVer)
    rc_SliderVer = sliderVer
    sliderVer:GetButSlider():SetStateColorDefaultWhite()
    sliderVer:GetFPicBoxBack():GetUIPicBox():SetPicBoxType(UIPicBox.PBT_NINE)
    sliderVer:GetFPicBoxBack():GetUIPicBox():SetTexCornerSize(12,12,12,12)      
    sliderVer:GetFPicBoxBack():GetUIPicBox():SetTexture("Data/RobotControl/images/directctrl/slider0.png")
    sliderVer:GetButSlider():GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("Data/RobotControl/images/directctrl/slider1.png")
    sliderVer.LocalTransform:SetTranslateY(-2.0)
    sliderVer:SetAnchorParamVer(-60.0, -60.0)
    sliderVer:SetSliderLength(60)    
    sliderVer:SetHeight(60.0)
    sliderVer:SetWidth(300.0)
    local text = sliderVer:CreateAddText("Ver")
    text:GetText():SetFontColor(Float3.WHITE)
    text:SetAnchorParamVer(-40.0, -40.0)
    sliderVer:GetButSlider():SetSize(60,60)

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