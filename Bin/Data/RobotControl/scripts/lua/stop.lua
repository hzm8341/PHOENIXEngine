--stop.lua

function engine_project_prestop() 
end

function engine_project_stop() 
    PX2_VOICESDK:EnableAutoSpeak(false)
    PX2_VOICESDK:EnableAutoSpeakTTS(false)   
end

