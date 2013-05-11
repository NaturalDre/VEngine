class 'PlayerScript'

function PlayerScript:__init()
	self.EntityType = "Player";
end

function PlayerScript:Cleanup()

end

function PlayerScript:Update(dt)

end

function PlayerScript:OnHit()
	LogNote("Player has been hit.");
end

function PlayerScript:OnDeath()
	LogNote("Player has died.");
end

function PlayerScript:OnWeaponSwitch()
	LogNote("Player has switched weapons.");
end

LogNote("playerscript.lua has been loaded.");