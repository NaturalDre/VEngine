require 'script'

function SetupScript(scriptID)
	s = Script(scriptID);
	s.print = print;

	return s;
end
