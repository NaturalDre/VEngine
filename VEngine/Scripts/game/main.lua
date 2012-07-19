class 'Main'

function Main:__init()
	print("Main created.");
	StoreObjects(Objects);
end

function Main:StartUp()
	print("Main starting up.");

	self.LoadObjects();
	
	Game:AddPlayer();
end

function Main:LoadObjects()
	for k,v in pairs(Objects) do
		print("Loading an object of type '" .. v.type .. "'");
		local f = GetFactory(v.type);
		if (type(f) == 'userdata') then
			table.insert(LoadedObjects, f(v));
		end
	end
end

function Main:LoadTileObjects()

end

function Main:Update(dt)

end

