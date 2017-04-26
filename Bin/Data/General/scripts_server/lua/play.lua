-- play.lua

function preplay()

end

function OnConnect(generalServer, clientID)
    PX2_LOGGER:LogInfo("ServerPlayer", "OnConnect "..clientID)
end

function OnDisConnect(generalServer, clientID)
    PX2_LOGGER:LogInfo("ServerPlayer", "OnDisConnect "..clientID)
end

function OnRecv(generalServer, clientID, strBuf)
    PX2_LOGGER:LogInfo("ServerPlayer", "OnRecv "..clientID..":"..strBuf)
end

function play()
    PX2_GS:AddOnConnectCallback("OnConnect")
    PX2_GS:AddOnDisconnectCallback("OnDisConnect")
    PX2_GS:AddOnRecvCallback("OnRecv")
end
