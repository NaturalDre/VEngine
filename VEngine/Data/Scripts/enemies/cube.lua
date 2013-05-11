class 'CubeScript'

function CubeScript:__init(cube)
	self.cube = cube;
end

function CubeScript:OnDamageTaken()
	if (self.cube)
		then LogNote("Cube[ID: " .. self.cube.entityID .. "] now has " .. self.cube.health .. " health.");
	end
end

function CubeScript:OnDeath()
	self.cube = nil;
end

LogNote("cube.lua loaded.");