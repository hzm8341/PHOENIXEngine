-- stop.lua

function stop()
    PX2_VOICESDK:EnableAutoSpeak(false)
    PX2_VOICESDK:EnableAutoSpeakTTS(false)   
    PX2BBLOCK_SYS:setDeviceID(0)
end