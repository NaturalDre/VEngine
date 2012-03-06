FactoryTable = {

}


function IsPhysicslayer(a)
	if (map.layers[a].properties["type"] == "physicslayer")
		then return true
	end
	return false
end

function CallFunction(name, object)
	if (FactoryTable[name] ~= nil)
		then FactoryTable[name](object)
	end
	--print(name)
end

function CallObjFactories(objects)
	for i = 1, #objects, 1 do
		CallFunction(objects[i].type, objects[i])
		--App.Trace("IsTable")
	end
end

function CallSolidGrounds(objects)
	for i = 1, #objects, 1 do
		CallFunction("SolidGround", objects[i])
	end
end

function FindObjects()
	for i = 1, #map.layers, 1 do
		if (map.layers[i].type  == "objectgroup")
			then if (IsPhysicslayer(i))
					then CallSolidGrounds(map.layers[i].objects);
			else
				CallObjFactories(map.layers[i].objects)
			end
		end
	end

	return map.width;
end

