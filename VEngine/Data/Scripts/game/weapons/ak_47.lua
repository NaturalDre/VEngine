class 'Script_AK'

function Script_AK:__init(ak)
	self.ak = ak;
	LogNote("Script_AK initialized.");
end

function Script_AK:OnFire()
	LogNote("Ammo Count: " .. self.ak.ammo);
end

function Script_AK:OnReload()

end

LogNote("Script_AK loaded.");