-- sampleFunctions.lua

function s_createsamplefunctions(parentFrame)
    local frame = UIFrame:New()
    parentFrame:AttachChild(frame)
	local picBox = frame:CreateAddBackgroundPicBox(true)
    frame.LocalTransform:SetTranslateY(-2)
	frame:SetAnchorHor(0.0, 1.0)
	frame:SetAnchorVer(0.0, 1.0)
	frame:SetAnchorParamHor(25.0, -25.0)
	frame:SetAnchorParamVer(25.0, -100.0)
    frame:SetWidget(true)
    picBox:SetAlpha(0.6)
    picBox:UseAlphaBlend(true)
    
    return frame
end

function s_SampleFunctionsCallback(objPtr, callType)
	local obj = Cast:ToO(objPtr)
	
	local name = obj:GetName()
	if UICT_PRESSED==callType then

    elseif UICT_RELEASED==callType then
        if "ButEngineSample"==name then
            smapleglobals.FrameUIFrame:Show(not smapleglobals.FrameUIFrame:IsShow())
        elseif "ButSnap"==name then
            PX2_APP:RunFile("http://www.manykit.com/codeplay/#/snap")
        elseif "ButFunctions"==name then
            smapleglobals.FrameFunctions:Show(not smapleglobals.FrameFunctions:IsShow())
        elseif "ButCtrl"==name then
            smapleglobals.FrameCtrl:Show(not smapleglobals.FrameCtrl:IsShow())
        end
	elseif UICT_RELEASED_NOTPICK==callType then
		if "ButUI" == name then
            smapleglobals.FrameUIFrame:Show(not smapleglobals.FrameUIFrame:IsShow())
        end
	end
end