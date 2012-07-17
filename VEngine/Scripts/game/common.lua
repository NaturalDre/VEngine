function GetFactory(name)
	local factory = _G[name];
	if (type(factory) == 'userdata')
		then return factory;
	else
		return nil;
	end
end

function NewScriptTable(script, name)
	Scripts[name] = script;
	print("NST called. " .. name);
	return Scripts[name];
end
