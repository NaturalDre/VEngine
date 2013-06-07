class 'Main'
class 'Red' (IComponent)

class 'TestComponent' (IComponent);
 
 function TestComponent:__init()
	IComponent.__init(self);
 end
 
 function TestComponent:Update(dt)
	print(gPlayer.position.x, gPlayer.position.y);
 end


function Red:__init()
	IComponent.__init(self)
end

function Red:Update(dt)
	print('Red:Update called.')
end

--function TestC:Update(dt)
	--LuaEntity:DefaultUpdate(dt);
	LogNote("TestC Update");
--end

function Test()
	a = TestC();
	a:Update(1);
	--a:DefaultUpdate(1);
end

function Main:__init()
	--dofile("Data/Maps/Adventure/Adventure.lua");
	--LogNote(typename(map));
	--loadfile("Adventure.lua");
	--StoreObjects(gObjects);
end

function Main:StartUp()
	LogNote("Main:StartUp has begun executing.");
	
	gGame:LoadMap("Maps/Adventure/Nature.lua");

	--map = run("Data/Maps/Adventure/Adventure.lua");
	--self.LoadObjects();
	--gGame:AddPlayer();
	gPlayer = CreatePlayer(gGame, b2Vec2(1,2));
	LogNote("Main:StartUp has finished executing.");
end

function Main:Cleanup()

end

function Main:LoadObjects()
	for k,v in pairs(gObjects) do
		LogNote("Loading an object of type '" .. v.type .. "'");
		local f = GetFactory(v.type);
		if (type(f) == 'userdata') then
			table.insert(gLoadedObjects, f(v));
		end
	end
end

function Main:LoadTileObjects()

end

function Main:Update(dt)

end

