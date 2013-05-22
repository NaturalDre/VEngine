function GetFactory(name)
	local factory = _G[name];
	if (type(factory) == 'userdata')
		then return factory;
	else
		return nil;
	end
end

function LogNote(msg, file, line)
	file = file or "N/A";
	line = line or 0;
	vShowMessage(msg, file, line);
end
