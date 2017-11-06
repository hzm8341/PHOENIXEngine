-- server.lua

function p_OnRecvUDP(objPtr, strBuf)
	local token = StringTokenizer(strBuf, " ")

	local ip = ""
	local cmd = ""
	local param0 = ""
	local param1 = ""

	if token:Count() > 0 then
		ip = token:GetAt(0)
	end
	if token:Count() > 1 then
		cmd = token:GetAt(1)
	end
	if token:Count() > 2 then
		param0 = token:GetAt(2)
	end
	if token:Count() > 3 then
		param1 = token:GetAt(3)
	end
end

function p_ProcessCMDs(cmd, param0, param1)

end