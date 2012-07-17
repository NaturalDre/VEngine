#include "Tileset.h"
#include "TiledLua.h"
#include <lauxlib.h>
#include <assert.h>
#include <allegro5\allegro5.h>
#include "..\Utility.h"
#include <luabind\luabind.hpp>

using namespace Tiled;

CTileset::CTileset(void)
{

}

CTileset::~CTileset(void)
{

}

Tile::Properties ConvertTableToProperties(const luabind::object& table)
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

std::list<Tile> CTileset::ReadTiles(lua_State* L, size_t index)
{
	std::list<Tile> tiles;

	luabind::object data(luabind::call_function<luabind::object>(L, "GetTilesetTiles", index));

	if (luabind::type(data) != LUA_TTABLE)
		return tiles;

	for (luabind::iterator iter = luabind::iterator(data), end; iter != end; ++iter)
	{
		luabind::object tile = *iter;
		
		tiles.push_back(Tile(luabind::object_cast<int>(tile["id"]), ConvertTableToProperties(tile["properties"])));
	}

	//try 
	//{
	//	// STK: --
	//	PushTilesetTiles(L, index);
	//	// STK: -- table
	//	lua_insert(L, 1);
	//	// STK: table --
	//	lua_pushnil(L);
	//	// STK: table -- nil
	//	while(lua_next(L, 1))
	//	{
	//		// STK: table -- string table?
	//		if (!lua_istable(L, -1))
	//			throw(std::exception("Value is not a table."));
	//		// STK: table -- string table
	//		lua_getfield(L, -1, "id");
	//		// STK: table -- string table number?
	//		if (!lua_isnumber(L, -1))
	//		{
	//			lua_pop(L, 2);
	//			// STK: table -- string
	//			continue;
	//		}
	//		// STK: table -- string table number
	//		int id = lua_tonumber(L, -1);
	//		lua_pop(L, 1);
	//		// STK: table -- string table
	//		tiles.push_back(Tile(id, GetProperties(L)));
	//		lua_pop(L, 1);
	//		// STK: table -- string
	//	}
	//	// STK: table --
	//	lua_remove(L, 1);
	//	// STK: --
	//}
	//catch(...)
	//{
	//	tiles.clear();
	//}
	return std::move(tiles);
}

void CTileset::ReadMapFile(lua_State* L, size_t index)
{
	m_firstGid = luabind::call_function<size_t>(L, "GetTilesetFirstGid", index);
	m_tileWidth = luabind::call_function<size_t>(L, "GetTilesetTileWidth", index);
	m_tileHeight = luabind::call_function<size_t>(L, "GetTilesetTileHeight", index);
	m_source = luabind::call_function<std::string>(L, "GetTilesetImage", index);
	m_imageWidth = luabind::call_function<size_t>(L, "GetTilesetImageWidth", index);
	m_imageHeight = luabind::call_function<size_t>(L, "GetTilesetImageHeight", index);
	m_trans = luabind::call_function<std::string>(L, "GetTilesetTrans", index);
	m_spacing = luabind::call_function<size_t>(L, "GetTilesetSpacing", index);
	m_name = luabind::call_function<std::string>(L, "GetTilesetName", index);

	m_tiles = ReadTiles(L, index);

	if (m_tileWidth == 0)
		throw(std::exception("A tileset's tileWidth MUST NOT be zero"));
	if (m_tileHeight == 0)
		throw(std::exception("A tileset's tileHeight MUST NOT be zero"));

	m_tilesAcross = m_imageWidth / (m_tileWidth + m_spacing);
	assert((m_tileHeight + m_spacing));
	m_tilesDown = m_imageHeight / (m_tileHeight + m_spacing);
	m_lastGid = m_firstGid + (((m_imageWidth / (m_tileWidth + m_spacing)) * (m_imageHeight / (m_tileHeight + m_spacing)))-1);

	m_image = VE::CBitmap(al_load_bitmap(m_source.c_str()));
}

CTileset* CTileset::ContainsGid(const std::list<CTileset*>& tilesets, size_t id)
{
	for (auto iter = tilesets.begin(); iter != tilesets.end(); ++iter)
	{
		if ((*iter)->ContainsGid(id))
			return *iter;
	}
	return nullptr;
}

VE::CBitmap CTileset::LoadTile(const std::list<CTileset*>& tilesets, size_t id)
{
	CTileset* ts = ContainsGid(tilesets, id);
	if(!ts || !ts->GetImage().IsValid())
		return VE::CBitmap();

	ColRow  cr = GetColRow(ts->TilesAcross(), id);

	return std::move(VE::CBitmap(ts->GetImage(), 
		(cr.col - 1) * (ts->ImageWidth() + ts->Spacing()),
		(cr.row - 1) * (ts->ImageHeight() + ts->Spacing()),
		ts->TileWidth(),
		ts->TileHeight()));
}