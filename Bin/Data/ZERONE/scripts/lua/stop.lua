-- stop.lua

function stop()
    local udpServer = PX2_PROJ:PoolGet("DUPServer")
    if nil~=udpServer then
        udpServer:Stop()
    end
    ZERONE_UDPServer = nil

    PX2_VOICESDK:EnableAutoSpeak(false)
    PX2_VOICESDK:EnableAutoSpeakTTS(false)   
end