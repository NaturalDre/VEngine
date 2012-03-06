ScriptTable = { }

Script = class(function(s, ID)
	s.scriptID = ID;
	s.G = _G;
	s.print = _G.print;
	s.setfenv = _G.setfenv;
	s.io = _G.io;
	ScriptTable[ID] = s;
end);

function Script:__tostring()
	return self.scriptID
end

function SetupScript(scriptID)
	local s = Script(scriptID);
	s.print = print;

	return s;
end


print("script.lua successfully loaded.")
