class 'Master'

function Master:__init(gameLevel)
	self.mGameLevel = gameLevel;
end

function Master:OnUpdate(dt)
	print("Master Updated");
end