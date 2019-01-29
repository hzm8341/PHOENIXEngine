-- stop.lua

function engine_project_prestop()

end

function engine_project_stop()
    local udpServer = PX2_PROJ:PoolGet("DUPServer")
    if nil~=udpServer then
        udpServer:Stop()
    end
    ZERONE_UDPServer = nil

    PX2_PROJ:PoolSet("Arduino", nil)

    PX2_VOICESDK:EnableAutoSpeak(false)
    PX2_VOICESDK:EnableAutoSpeakTTS(false)   
end