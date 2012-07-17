class 'Main'

function Main:__init()
	print("Main created.");
	--self.Objects = { }
	--self.LoadedObjects = { }
end

function Main:StartUp()
	print("Main starting up.");
	LoadObjects(Objects);

	for k,v in pairs(Objects) do
		print("Loading an object of type '" .. v.type .. "'");
		local f = GetFactory(v.type);
		if (type(f) == 'userdata') then
			table.insert(LoadedObjects, f(v));
		end
		f = nil;
	end
end

function Main:LoadObjects()

end

function Main:LoadTileObjects()

end

function Main:Update(dt)

end

