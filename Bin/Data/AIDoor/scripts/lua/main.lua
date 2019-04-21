-- main.lua

AIDoor_MainUI = nil
function ui_Main()
    local ui = PX2_PROJ:GetUI()
    
    local frameAll = UIFrame:New()
    ui:AttachChild(frameAll)
    AIDoor_MainUI = frameAll
    frameAll:SetAnchorHor(0.0, 1.0)
    frameAll:SetAnchorVer(0.0, 1.0)

    local butVisit = UIButton:New("BtnVisit")
    frameAll:AttachChild(butVisit)
    butVisit.LocalTransform:SetTranslateY(-2.0)
    butVisit:SetSize(300.0, 300.0)
    butVisit:SetAnchorHor(0.5,0.5)
    butVisit:SetAnchorVer(0.5,0.5)
    butVisit:SetAnchorParamHor(-200.0, -200.0)
    butVisit:SetAnchorParamVer(0, 0)
    butVisit:SetScriptHandler("aidoor_UICallback")
    butVisit:CreateAddText("拜访")

    local butCompany = UIButton:New("BtnCompany")
    frameAll:AttachChild(butCompany)
    butCompany.LocalTransform:SetTranslateY(-2.0)
    butCompany:SetSize(300.0, 300.0)
    butCompany:SetAnchorHor(0.5,0.5)
    butCompany:SetAnchorVer(0.5,0.5)
    butCompany:SetAnchorParamHor(200.0, 200.0)
    butCompany:SetAnchorParamVer(0, 0)
    butCompany:SetScriptHandler("aidoor_UICallback")
    butCompany:CreateAddText("企业宣传")
end

function aidoor_UICallback(ptr,callType)
    local obj=Cast:ToO(ptr)
    local name=obj:GetName()
    if UICT_PRESSED==callType then
        PX2_GR:PlayScale(obj)
    elseif UICT_RELEASED ==callType then
        PX2_GR:PlayNormal(obj)
        if "BtnVisit" == name then
            ui_Visit()
        elseif "BtnCompany" == name then
            ui_Company()
        end
    elseif UICT_RELEASED_NOTPICK == callType then
        PX2_GR:PlayNormal(obj)
    elseif UICT_CHECKED == callType then
    elseif UICT_DISCHECKED == callType then
    end
end

function ui_Visit()
    AIDoor_MainUI:DetachAllChildren()

    local uiFrameBack, uiFrame, btnClose, titleText = ad_UICreateDlgCommon(478.0, 324.0, "")
    uiFrame:SetAnchorHor(0.0, 1.0)
	uiFrame:SetAnchorParamHor(80.0, -80.0)
	uiFrame:SetAnchorVer(0.0, 1.0)
    uiFrame:SetAnchorParamVer(80.0, -80.0)
    btnClose:SetScriptHandler("aidoor_UICallback")

    AIDoor_MainUI:AttachChild(uiFrameBack)
end

function  ui_Company()

end