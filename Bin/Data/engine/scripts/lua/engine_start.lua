-- engine_start.lua

-- classes & inheritance
function class(baseClass, body)
	local ret = body or {};
	
	-- if there's a base class, attach our new class to it
	if (baseClass ~= nil) then
		setmetatable(ret, ret);
		ret.__index = baseClass;
		ret.base = baseClass;
	end
	
	-- Add the Create() function.  This will end up being added to each subclass which isn't ideal.  This 
	-- function should probably be stored in a single place so we only have to create it once.
	-- 		-self: The self pointer that's calling this function.
	--		-constructionData: The table sent in as construction data.  Think of it like a constructor.
	--		-originalSubClass: Used for recursion.  Don't pass anything into this parameter, it's filled 
	--						   automatically.  It's used in case the C++ side needs access to the leaf 
	--						   subclass that is being instantiated.  For an example, see ScriptProcess 
	--						   in C++.
	ret.New = function(self, constructionData, originalSubClass)
		local obj;
		if (self.__index ~= nil) then
			if (originalSubClass ~= nil) then
				obj = self.__index:New(constructionData, originalSubClass);
			else
				obj = self.__index:New(constructionData, self);
			end
		else
			obj = constructionData or {};
		end
		
		setmetatable(obj, obj);
		obj.__index = self;
		
		-- copy any operators over
		if (self.__operators ~= nil) then
			for key, val in pairs(self.__operators) do
				obj[key] = val;
			end
		end
		
		return obj;
	end
	
	-- Returns true if otherClass appears in this objects class hierarchy anywhere.
	ret.IsInstance = function(self, otherClass)
		local cls = self.__index;
		while cls do
			if cls == otherClass then 
				return true
			end
			cls = cls.base
		end
		return false
	end
	
	return ret;
end

-- redefine require and print
do
	local OldRequire = require;  -- save the old require() function
	local resourceIdMap = {};  -- map of resource id's we've already loaded
	
	require = function(script)
		if (not resourceIdMap[script]) then
			if (PX2_SC_LUA:CallFile(script)) then
				resourceIdMap[script] = true;
			else
				-- failed to load file through the resource system so fall back to the old method
				OldRequire(script);
			end
		end
	end
end

do
    local OldPrint = print;  -- save the old print() function
    
    print = function(text)
		if (text ~= nil) then
			PX2_LOGGER:LogInfo("script_lua", text)
		else
			PX2_LOGGER:LogInfo("script_lua", "<nil>")
		end
	end
end

-- Utility functions
Utils = {};

-- Concatenate the contents of the parameter list, separated by the string delimiter (just like in perl)
-- example: Utils.Join(", ", {"Anna", "Bob", "Charlie", "Dolores"})
-- results: "Anna, Bob, Charlie, Dolores"
function Utils.Join(delimiter, list)
	local len = table.getn(list)
	if len == 0 then
		return "" 
	end
	local string = list[1]
	for i = 2, len do
		string = string .. delimiter .. list[i] 
	end
	return string
end

-- Split text into a list consisting of the strings in text, separated by strings matching delimiter (which may be a pattern). 
-- example: Utils.Split(",%s*", "Anna, Bob, Charlie,Dolores")
-- results: {"Anna", "Bob", "Charlie", "Delores"}
function Utils.Split(delimiter, text)
	local list = {}
	local pos = 1
	if string.find("", delimiter, 1) then -- this would result in endless loops
		--error("delimiter matches empty string!")
		print("delimiter matches empty string!")
	end
	
	while 1 do
		local first, last = string.find(text, delimiter, pos)
		if first then -- found?
			if first < pos then
				print("[WARNING] Lua Split() function failed; first < pos\nfirst = "..first.."; last = "..last.."; pos = "..pos);
				break
			end
			table.insert(list, string.sub(text, pos, first-1))
			pos = last + 1
		else
			table.insert(list, string.sub(text, pos))
			break
		end
	end
	return list
end

function Utils.ConvertBoolToString(bool)
	if (bool == true) then
		return "true";
	else
		return "false";
	end
end

function Utils.DumpTable(table)
	for key, val in pairs(table) do
		print(key, val);
	end
end

-- private function used by Utils.DumpObject()
function Utils._BuildMemberSet(obj, memberSet)
	if (obj.__index ~= nil and obj ~= obj.__index) then
		Utils._BuildMemberSet(obj.__index, memberSet);
	end
	
	for key, val in pairs(obj) do
		if (key ~= "__index" and memberSet[key] == nil) then
			memberSet[key] = true;
		end
	end
end

function Utils.DumpObject(obj)
	-- There might be copies of the same variable at various levels in the hierarchy so we need to build an
	-- exclusive set of names.
	local memberSet = {};
	Utils._BuildMemberSet(obj, memberSet);
	
	-- Loop through the set of member names and print them out, along with the value from the original object's
	-- perspective.
	for key, val in pairs(memberSet) do
		print(key, obj[key]);
	end
end

function wrap(func, ...)
	local args = {...}
	local co = coroutine.running()
	table.insert(args, function()
		coroutine.resume(co)
	end)
	func(unpack(args))
	coroutine.yield()
end

local _sleep = sleep
function sleep(second)
	wrap(_sleep, second)
end

FES_NORMAL = 0
FES_ITALIC = 1
FES_UNDERLINE = 2

FD_NORMAL = 0
FD_SHADOW = 1
FD_BORDER = 2

TEXTALIGN_LEFT		=	1
TEXTALIGN_HCENTER	=	2
TEXTALIGN_RIGHT		=	4
TEXTALIGN_TOP		=	8
TEXTALIGN_VCENTER	=	16
TEXTALIGN_BOTTOM	=	32

function engine_start()
	PX2_LOGGER:LogInfo("script_lua", "engine_start")
end
engine_start()