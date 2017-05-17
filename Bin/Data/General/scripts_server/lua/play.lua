-- play.lua

function preplay()

end

function OnConnect(objPtr, clientID)
    PX2_LOGGER:LogInfo("ServerPlayer", "OnConnect "..clientID)
end

function OnDisConnect(objPtr, clientID)
    PX2_LOGGER:LogInfo("ServerPlayer", "OnDisConnect "..clientID)
end

function OnRecv(objPtr, clientID, strBuf)
    PX2_LOGGER:LogInfo("ServerPlayer", "OnRecv "..clientID..":"..strBuf)

    generalServer = Cast:ToGS(objPtr)
    generalServer:SendString(clientID, "wow!")
end

function play()
	if nil~= PX2_GS then
		PX2_GS:AddOnConnectCallback("OnConnect")
		PX2_GS:AddOnDisconnectCallback("OnDisConnect")
		PX2_GS:AddOnRecvCallback("OnRecv")
	end
end
