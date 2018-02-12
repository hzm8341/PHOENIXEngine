-- ChaosConnect.lua

function ch_Connect()
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
    list:SetItemBackPicBox("Data/PhoenixCode/images/ui/common/beijing.png")
    list:SetItemBackColor(Float3(0.7, 0.7, 0.7))
    list:SetReleasedDoSelect(true)
    list:SetFontSize(24)
    g_ChaosBleList = list

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
    btnLeft:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("Data/Chaos/images/btnblue.png")
    btnLeft:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetPicBoxType(UIPicBox.PBT_NINE)
    local fText = btnLeft:CreateAddText(""..PX2_LM_APP:GetValue("Scan"))
    ch_UISetTextFont(fText:GetText(), 32)
    btnLeft:SetScriptHandler("ch_ButBluetoothFrameCallabck")

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
	btnRight:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetTexture("Data/Chaos/images/btnblue.png")
	btnRight:GetPicBoxAtState(UIButtonBase.BS_NORMAL):SetPicBoxType(UIPicBox.PBT_NINE)
	local fText = btnRight:CreateAddText(""..PX2_LM_APP:GetValue("Connect"))
    ch_UISetTextFont(fText:GetText(), 32)
    btnRight:SetScriptHandler("ch_ButBluetoothFrameCallabck")
    g_ChaosBleConnect = btnRight

    UnRegistAllEventFunctions("BluetoothES::OnDisocveryNewDevice")
    RegistEventFunction("BluetoothES::OnDisocveryNewDevice", function(deviceStr)
        local stk = StringTokenizer(deviceStr, "$")
        if stk:Count() >= 2 then
            local deviceItem = g_ChaosBleList:GetItemByUserDataString("NamePath", deviceStr)
            if nil==deviceItem then
                local strName = stk:GetAt(0)
                local strAddress = stk:GetAt(1)
                local rssi = stk:GetAt(2)
                local rssi100 = PX2_BLUETOOTH:Rssi100(rssi).."/100"

                local useStrName = strName.."  "..strAddress.." "..PX2_LM_APP:GetValue("SignDegree")..rssi100

                local uiItem = g_ChaosBleList:AddItem(useStrName)
                uiItem:SetUserDataString("NamePath", deviceStr)
            end
        end
    end)

    UnRegistAllEventFunctions("BluetoothES::OnConnected")
    RegistEventFunction("BluetoothES::OnConnected", function()
        if nil~=g_ChaosBleConnect then
            g_ChaosBleConnect:GetText():SetText(""..PX2_LM_APP:GetValue("DisConnect"))
        end
    end)

    UnRegistAllEventFunctions("BluetoothES::OnDisConnected")
    RegistEventFunction("BluetoothES::OnDisConnected", function()
        if nil~=g_ChaosBleConnect then
            g_ChaosBleConnect:GetText():SetText(""..PX2_LM_APP:GetValue("Connect"))
        end
    end)

    UnRegistAllEventFunctions("SerialES::Open")
    RegistEventFunction("SerialES::Open", function()
        if nil~=g_ChaosBleConnect then
            g_ChaosBleConnect:GetText():SetText(""..PX2_LM_APP:GetValue("DisConnect"))
        end
    end)

    UnRegistAllEventFunctions("SerialES::Close")
    RegistEventFunction("SerialES::Close", function()
        if nil~=g_ChaosBleConnect then
            g_ChaosBleConnect:GetText():SetText(""..PX2_LM_APP:GetValue("Connect"))
        end
    end)

	return uiFrame
end

function ch_ScanBleDevices()
    if nil~=g_ChaosBleList then

        g_ChaosBleList:RemoveAllItems()
        
        PX2_BLUETOOTH:GetPairedDevices()
        local numPairedDevices = PX2_BLUETOOTH:GetNumPairedDevices()
        for i=1, numPairedDevices, 1 do
            local deviceStr = PX2_BLUETOOTH:GetPairedDevice(i-1)
            local stk = StringTokenizer(deviceStr, "$")

            if stk:Count() >= 2 then
                local strName = stk:GetAt(0)
                local strAddress = stk:GetAt(1)

                local useStrName = strName

                local uiItem = g_ChaosBleList:AddItem(useStrName)
                
                local text = UIFText:New()
                uiItem:AttachChild(text)
                text.LocalTransform:SetTranslateY(-1.0)
                text:SetAnchorHor(0.5, 1.0)
                text:SetAnchorVer(0.0, 1.0)
                text:GetText():SetFontColor(Float3.WHITE)
                text:GetText():SetText(""..PX2_LM_APP:GetValue("IsPaired"))

                uiItem:SetUserDataString("NamePath", deviceStr)
            end
        end
    end
    PX2_BLUETOOTH:DoDiscovery()
end

function ch_bluetoothTryToConnect()
    local item = g_ChaosBleList:GetSelectedItem()

    if nil~=item then
        local namePath = item:GetUserDataString("NamePath")
        PX2_LOGGER:LogInfo("Chaos", "NamePath:"..namePath)
        if ""~=namePath then
            local stk = StringTokenizer(namePath, "$")
            if stk:Count() >= 2 then
                local strName = stk:GetAt(0)
                local strAddress = stk:GetAt(1)
                local rssi = stk:GetAt(2)

                if ""~=strAddress then
                    ch_blueToConnect(strAddress)
                end
            end
        end
    end
end

function ch_blueToConnect(strAddress)
    coroutine.wrap(function()
        PX2_LOGGER:LogInfo("Chaos", "connect to"..strAddress)
        PX2_BLUETOOTH:Connect(strAddress)
    end)()
end

function ch_ScanSerialDevices()
    g_ChaosBleList:RemoveAllItems()

    local serial = Serial()
    serial:GetPortList()
    local numPorts = serial:GetNumPorts()
    for i=0, numPorts-1 do
        local portStr = serial:GetPort(i)
        local item = g_ChaosBleList:AddItem(portStr)
        item:SetUserDataString("NamePath", portStr)
    end  
end

function ch_SerialTryToConnect()
    local item = g_ChaosBleList:GetSelectedItem()

    if nil~=item then
        local namePath = item:GetUserDataString("NamePath")
        PX2_LOGGER:LogInfo("PHOENIXCode", "NamePath:"..namePath)        
        if ""~=namePath then
            PX2BBLOCK_SYS:SetSetType(BBlockSystem.ST_SERIAL, namePath)
        end
    end
end


function ch_ButBluetoothFrameCallabck(ptr, callType)
    local obj = Cast:ToO(ptr) 
	local name = obj:GetName()	
    
    local platType = PX2_APP:GetPlatformType()

    if UICT_PRESSED==callType then
        playFrameScale(obj)
    elseif UICT_RELEASED==callType then
        playFrameNormal(obj)

        if "BtnDlgLeft"==name then
            if Application.PLT_WINDOWS==platType then
                ch_ScanSerialDevices()
            else
                ch_ScanBleDevices()
            end        
        elseif "BtnDlgRight"==name then
            if Application.PLT_WINDOWS==platType then
                ch_SerialTryToConnect()
            else
                if not PX2_BLUETOOTH:IsConnected() then
                    ch_bluetoothTryToConnect()
                else
                    PX2_BLUETOOTH:DisConnect()
                end
            end
        end
	end
end