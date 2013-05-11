function OnAppStartup()
	LogNote("OnAppStartup has begun executing.");
	gMain = Main();	
	gGame:SetMainScript(Main);
	LogNote("OnAppStartup has finished executing.");
end