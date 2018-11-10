-- bluetooth.lua

rc_BleList = nil

function rc_BluetoothSerial()
    local uiFrame = UIFrame:New()

	uiFrame:SetAnchorHor(0.0, 1.0)
	uiFrame:SetAnchorVer(0.0, 1.0)

    local list = UIList:New("ListBluetooth")
    uiFrame:AttachChild(list)
    list.LocalTransform:SetTranslateY(-2.0)
    list:SetAnchorHor(0.0, 1.0)
    list:SetAnchorParamHor(50.0, -50.0)
    list:SetAnchorVer(0.0, 1.0)
    list:SetAnchorParamVer(100.0, -50.0)
    list:SetItemHeight(60.0)
    list:SetSliderSize(30.0)
    list:SetItemBackColor(Float3(0.7, 0.7, 0.7))
    list:SetReleasedDoSelect(true)
    list:SetFontSize(24)
    rc_BleList = list

    local btnLeft = UIButton:New("BtnDlgLeft")
    uiFrame:AttachChild(btnLeft)
    btnLeft.LocalTransform:SetTranslateY(-1.0)
    btnLeft:SetSize(150, 50)
    btnLeft:SetAnchorHor(0.5, 0.5)
    btnLeft:SetAnchorParamHor(-120.0, -120.0)
    btnLeft:SetAnchorVer(0.0, 0.0)
    btnLeft:SetAnchorParamVer(60.0, 60.0)
    btnLeft:SetSize(180, 60)
    btnLeft:SetStateColor(UIButtonBase.BS_HOVERED, Float3:MakeColor(255, 255, 255))
    btnLeft:SetStateColor(UIButtonBase.BS_NORMAL, Float3:MakeColor(255, 255, 255))
    btnLeft:SetStateColor(UIButtonBase.BS_PRESSED, Float3:MakeColor(190, 190, 190))
    btnLeft:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("Data/RobotControl/images/btnblue.png")
    btnLeft:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetPicBoxType(UIPicBox.PBT_NINE)
    local fText = btnLeft:CreateAddText(""..PX2_LM_APP:GetValue("Scan"))
    rc_UISetTextFont(fText:GetText(), 32)
    btnLeft:SetScriptHandler("zo_ButBluetoothSerialFrameCallabck")

	local btnRight = UIButton:New("BtnDlgRight")
	uiFrame:AttachChild(btnRight)
	btnRight.LocalTransform:SetTranslateY(-1.0)
	btnRight:SetSize(150, 50)
	btnRight:SetAnchorHor(0.5, 0.5)
	btnRight:SetAnchorParamHor(120.0, 120.0)
	btnRight:SetAnchorVer(0.0, 0.0)
	btnRight:SetAnchorParamVer(60.0, 60.0)
	btnRight:SetSize(180, 60)
	btnRight:SetStateColor(UIButtonBase.BS_HOVERED, Float3:MakeColor(255, 255, 255))
	btnRight:SetStateColor(UIButtonBase.BS_NORMAL, Float3:MakeColor(255, 255, 255))
	btnRight:SetStateColor(UIButtonBase.BS_PRESSED, Float3:MakeColor(190, 190, 190))
	btnRight:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("Data/RobotControl/images/btnblue.png")
	btnRight:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetPicBoxType(UIPicBox.PBT_NINE)
	local fText = btnRight:CreateAddText(""..PX2_LM_APP:GetValue("Connect"))
    rc_UISetTextFont(fText:GetText(), 32)
    btnRight:SetScriptHandler("zo_ButBluetoothSerialFrameCallabck")
    ZERONE_BleConnect = btnRight

    UnRegistAllEventFunctions("BluetoothES::OnDisocveryNewDevice")
    RegistEventFunction("BluetoothES::OnDisocveryNewDevice", function(deviceStr)
        local stk = StringTokenizer(deviceStr, "$")
        if stk:Count() >= 2 then
            local deviceItem = rc_BleList:GetItemByUserDataString("NamePath", deviceStr)
            if nil==deviceItem then
                local strName = stk:GetAt(0)
                local strAddress = stk:GetAt(1)
                local rssi = stk:GetAt(2)
                local rssi100 = PX2_BLUETOOTH:Rssi100(rssi).."/100"

                local useStrName = strName.."  "..strAddress.." "..PX2_LM_APP:GetValue("SignDegree")..rssi100

                local uiItem = rc_BleList:AddItem(useStrName)
                uiItem:SetUserDataString("NamePath", deviceStr)
            end
        end
    end)

    UnRegistAllEventFunctions("BluetoothES::OnConnected")
    RegistEventFunction("BluetoothES::OnConnected", function()
        if nil~=ZERONE_BleConnect then
            ZERONE_BleConnect:GetText():SetText(""..PX2_LM_APP:GetValue("DisConnect"))
          
            System:SleepSeconds(2.0)

            -- startup
            zo_OnStartUp(ZERONE_IsRobotMotoUseSpeed)
        end
    end)

    UnRegistAllEventFunctions("BluetoothES::OnDisConnected")
    RegistEventFunction("BluetoothES::OnDisConnected", function()
        if nil~=ZERONE_BleConnect then
            ZERONE_BleConnect:GetText():SetText(""..PX2_LM_APP:GetValue("Connect"))
        end
    end)

    RegistEventFunction("SerialES::Open", function(tag)
        if 1==ZERONE_CurSerialOptType then
            if nil~=ZERONE_BleConnect then
                ZERONE_BleConnect:GetText():SetText(""..PX2_LM_APP:GetValue("DisConnect"))
                
                -- startup
                zo_OnStartUp(ZERONE_IsRobotMotoUseSpeed)
            end
        end
    end)

    RegistEventFunction("SerialES::Close", function(tag)
        if 1==ZERONE_CurSerialOptType then
            if nil~=ZERONE_BleConnect then
                ZERONE_BleConnect:GetText():SetText(""..PX2_LM_APP:GetValue("Connect"))
            end
        end
    end)

	return uiFrame
end