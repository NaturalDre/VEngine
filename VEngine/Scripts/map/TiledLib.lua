-- This is a helper function to call constructor
-- for classes exported by Luabind.
-- Checks if a variable exists in the global space
-- with this name and checks if it's a function.
-- If it is a function it calls it and passes it
-- 'data'.
function CallFactory(name, data)
	func = _G[name];
	if (type(func) == 'userdata')
		then func(data);
		print(name .. " factory called.");
	end
end
-- Gathers every object in each objectgroup from
-- the Tiled map file and stores them in 'data'
function LoadObjects(data)
	assert(type(map) == 'table', "map is not a table");
	local layers = map.layers;

	for layerKey,layerVal in pairs(layers) do
		if(layerVal.type == 'objectgroup')
			then for objectKey, objectVal in pairs(layerVal.objects) do
				--if (objectVal.name ~= "")
					--then data[objectVal.name
				table.insert(data, objectVal);
			end
		end
	end
	print(#data .. " Objects Loaded. ");
end

function GetMapVersion()
	return map.version;
end

function GetMapOrientation()
	return map.orientation;
end

function GetMapWidth()
	return map.width
end

function GetMapHeight()
	return map.height;
end

function GetMapTileWidth()
	return map.tilewidth
end

function GetMapTileHeight()
	return map.tileheight
end


function GetMapProp(a)
	return map.properties[a]
end

function GetTileset(index)
	return map.tilesets[index];
end

function GetTilesetTiles(index)
	return map.tilesets[index].tiles;
end

function GetTilesetTileWidth(a)
	return map.tilesets[a].tilewidth
end

function GetTilesetTileHeight(a)
	return map.tilesets[a].tileheight
end

function GetTilesetImage(a)
	return map.tilesets[a].image
end

function GetTilesetImageHeight(a)
	return map.tilesets[a].imageheight
end

function GetTilesetImageWidth(a)
	return map.tilesets[a].imagewidth
end

function GetTilesetSpacing(a)
	return map.tilesets[a].spacing
end

function GetTilesetName(a)
	return map.tilesets[a].name
end

function GetTilesetTrans(a)
	return map.tilesets[a].transparentColor
end

function GetTilesetFirstGid(a)
	return map.tilesets[a].firstgid
end

function GetLayerType(a)
	return map.layers[a].type;
end

function IsTilelayer(a)
	if (map.layers[a].type == "tilelayer")
		then return true
	end
	return false
end

function IsPhysicslayer(a)
	if (map.layers[a].properties["type"] == "physicslayer")
		then return true
	end
	return false
end

function GetNumberOfTilesets()
	return #map.tilesets
end

function GetNumberOfLayers()
	return #map.layers
end

function GetNumOfObjLayerObjects(a)
	return #map.layers[a].objects
end

function GetObjLayerObject(layer, index)
		if (map.layers[layer].type == "objectgroup")
			then return map.layers[layer].objects[index];
		end
		return "Not an object layer.";
end

function GetLayerObject(a)
	return map.layers[a];
end

function GetLayerDataVal(a,b)
	return map.layers[a].data[b]
end

function GetLayerDataSize(a)
	return #map.layers[a].data
end

print("TiledLib.lua loaded.");
