#include "Tileset.h"
#include "TiledLua.h"
#include <lauxlib.h>
#include <assert.h>
#include <allegro5\allegro5.h>
#include "..\Utility.h"
#include <luabind\luabind.hpp>

using namespace Tiled;
using namespace luabind;

static Tile::Properties ConvertTableToProperties(const luabind::object& table)
{
	Tile::Properties props;
	for (luabind::iterator iter = luabind::iterator(table), end; iter != end; ++iter)
	{
			props.insert(std::pair<const std::string, const std::string>
				(luabind::object_cast<const std::string>(iter.key())
				, luabind::object_cast<std::string>(*iter)));
	}
	return std::move(props);
}

CTileset::CTileset(const luabind::adl::object& tileset)
	: m_isValid(false)
{
	if(!tileset.is_valid() || type(tileset) != LUA_TTABLE)
		return;

	try
	{
		LoadTilesetProperties(*this, tileset);
		m_tiles = LoadTilesetTiles(*this, tileset["tiles"]);
		m_isValid = true;
	}
	catch(const luabind::error& e)
	{
		lua_pop(e.state(), 1);
	}
	catch(...) { }
}

CTileset::~CTileset(void)
{

}

void CTileset::LoadTilesetProperties(CTileset& ts, const luabind::adl::object& tileset)
{
	ts.m_name = object_cast<std::string>(tileset["name"]);
	ts.m_firstGid = object_cast<size_t>(tileset["firstgid"]);
	ts.m_tileWidth = object_cast<size_t>(tileset["tilewidth"]);
	ts.m_tileHeight = object_cast<size_t>(tileset["tileheight"]);
	ts.m_spacing = object_cast<size_t>(tileset["spacing"]);

	ts.m_source = object_cast<std::string>(tileset["image"]);
	ts.m_imageWidth = object_cast<size_t>(tileset["imagewidth"]);
	ts.m_imageHeight = object_cast<size_t>(tileset["imageheight"]);
	ts.m_trans = object_cast<std::string>(tileset["transparentColor"]);

	ts.m_tilesAcross = ts.m_imageWidth / (ts.m_tileWidth + ts.m_spacing);
	assert((ts.m_tileHeight + ts.m_spacing));
	ts.m_tilesDown = ts.m_imageHeight / (ts.m_tileHeight + ts.m_spacing);
	ts.m_lastGid = ts.m_firstGid + (((ts.m_imageWidth / (ts.m_tileWidth + ts.m_spacing)) * (ts.m_imageHeight / (ts.m_tileHeight + ts.m_spacing)))-1);
}

std::list<Tile> CTileset::LoadTilesetTiles(CTileset& ts, const luabind::adl::object& data)
{
	std::list<Tile> tiles;

	if(!data.is_valid() || type(data) != LUA_TTABLE)
		return tiles;



	for (luabind::iterator iter = luabind::iterator(data), end; iter != end; ++iter)
	{
		luabind::object tile = *iter;
		
		tiles.push_back(Tile(luabind::object_cast<int>(tile["id"]), ConvertTableToProperties(tile["properties"])));	
	}
	return std::move(tiles);
}

CTileset* CTileset::ContainsGid(const std::vector<CTileset*>& tilesets, size_t id)
{
	for (auto iter = tilesets.begin(); iter != tilesets.end(); ++iter)
	{
		if ((*iter)->ContainsGid(id))
			return *iter;
	}
	return nullptr;
}

//VE::CBitmap CTileset::LoadTile(const std::vector<CTileset*>& tilesets, size_t id)
//{
//	CTileset* ts = ContainsGid(tilesets, id);
//	if(!ts || !ts->GetImage().IsValid())
//		return VE::CBitmap();
//
//	ColRow  cr = GetColRow(ts->TilesAcross(), id);
//
//	return std::move(VE::CBitmap(ts->GetImage(), 
//		(cr.col - 1) * (ts->ImageWidth() + ts->Spacing()),
//		(cr.row - 1) * (ts->ImageHeight() + ts->Spacing()),
//		ts->TileWidth(),
//		ts->TileHeight()));
//}