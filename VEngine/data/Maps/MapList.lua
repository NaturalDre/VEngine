--
MapList =
{
	{
		Name = "Intro";
		Location = "Maps/EV_Intro/Tutorial.lua";
	},
	{
		Name = "Level 1";
		Location = "Maps/Level1/Level1a.lua";
	},
	{
		Name = "Bam";
		Location = "Maps/Level1/Bam.lua";
	}
}

MapCount = #MapList;

function MapListCount()
	return #MapList
end

function GetMapName(index)
	if (MapList[index] ~= nil)
		then return MapList[index].Name;
	end
end

function GetMapLocation(index)
	if (MapList[index] ~= nil)
		then return MapList[index].Location;
	end
end

function GetMapNameLoc(index)
	if (MapList[index] ~= nil)
		then return MapList[index].Name, MapList[index].Location;
	end
end
