function GetFactory(name)
	local factory = _G[name];
	if (type(factory) == 'userdata')
		then return factory;
	else
		return nil;
	end
end

function LogNote(str)
	gLogger:LogNote(str .. "");
end
