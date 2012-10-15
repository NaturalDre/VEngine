#include "MapFile.h"
#include <assert.h>
#include "Tilelayer.h"
#include "ObjectLayer.h"
#include "TiledLua.h"
#include "..\Utility.h"
#include "..\Bitmap.h"
#include "..\Render.h"
#include <luabind\luabind.hpp>

#include <boost\foreach.hpp>
#include "lualib.h"
using namespace Tiled;

bool LoadTiledLib(lua_State* L)
{
	try { DoFile(L, "Scripts/map/TiledLib.lua"); return true; }
	catch (...) { return false; }
}

CMapFile::CMapFile(void)
{
	m_width = 0;
	m_height = 0;
	m_tileHeight = 0;
	m_tileWidth = 0;
	//m_playerLayer = 1;

	//m_physicsLayer = nullptr;
	m_valid = false;
}

CMapFile::~CMapFile(void)
{
	Reset();
}
void CMapFile::LoadMapData(CMapFile& map, lua_State* L)
{
	map.m_version = luabind::call_function<std::string>(L, "GetMapVersion");
	map.m_orientation = luabind::call_function<std::string>(L, "GetMapOrientation");
	map.m_width = luabind::call_function<size_t>(L, "GetMapWidth");
	map.m_height = luabind::call_function<size_t>(L, "GetMapHeight");
	map.m_tileWidth = luabind::call_function<size_t>(L, "GetMapTileWidth");
	map.m_tileHeight = luabind::call_function<size_t>(L, "GetMapTileHeight");

	// Put map.properties into an std::map<const string, const string>
	luabind::object props = luabind::call_function<luabind::object>(L, "GetMap");
	props.push(L);
	map.m_properties = Tiled::GetProperties(L);
	lua_pop(L, 1);
}

void CMapFile::LoadLayers(CMapFile& map, lua_State* L)
{

	for (size_t i = 1; i <= luabind::call_function<size_t>(L, "GetNumberOfTilesets"); ++i)
		map.m_tilesets.push_back(new CTileset(luabind::call_function<luabind::object>(L, "GetTileset", i)));


	for (size_t i = 1, max = luabind::call_function<size_t>(L, "GetNumberOfLayers"); i <= max; ++i)
	{
		luabind::object data = luabind::call_function<luabind::object>(L, "GetLayer", i);

		if (!data.is_valid())
			break;

		const std::string type = luabind::object_cast<std::string>(data["type"]);

		if (type == "tilelayer")
			map.m_tileLayers.push_back( new CTileLayer(data, map));
		else if (type == "objectgroup")
		{
			CObjectLayer* layer = new CObjectLayer(data);
			map.m_objectLayers.push_back(layer);
		}
	}
}

bool CMapFile::Read(const std::string& mapFile)
{
	Reset();
	// Open an lua state
	lua_State* L = lua_open();
	if (!L)
		return false;

	luaL_openlibs(L);
	luabind::open(L);

	// Attempt to load the file and load the script which 
	// contains Lua functions for operating on Tiled's 
	// Lua map files.
	// NOTE: Non-zero is error.
	if (luaL_dofile(L, mapFile.c_str()) || !LoadTiledLib(L))
	{
		lua_close(L);
		return false;
	}

	LoadMapData(*this, L);
	LoadLayers(*this, L);

	lua_close(L);
	return m_valid = true;
}

bool CMapFile::Read(const luabind::object& data)
{
	if (!data.is_valid() || !LoadTiledLib(data.interpreter()))
		return false;

	LoadMapData(*this, data.interpreter());
	LoadLayers(*this, data.interpreter());

	return m_valid = true;
}

const std::string CMapFile::GetProperty(const std::string& key)
{
	auto iter = m_properties.find(key);
	if (iter != m_properties.end())
		return iter->second;
	return "";
}

CTileset* CMapFile::GetTileset(const std::string& name) const
{
	for(auto iter = m_tilesets.begin(); iter != m_tilesets.end(); ++iter)
	{
		if ((*iter)->Name() == name)
			return *iter;
	}
	return nullptr;
}

const Object* CMapFile::FindObject(const std::string& name) const
{
	for (auto iter = m_objectLayers.begin(); iter != m_objectLayers.end(); ++iter)
	{
		const Object* obj = (*iter)->FindObject(name);
		if (obj)
			return obj;
	}
	return nullptr;
}

void CMapFile::Reset(void)
{
	m_version.clear();
	m_orientation.clear();
	m_properties.clear();
	m_width = 0;
	m_height = 0;
	m_tileWidth = 0;
	m_tileHeight = 0;

	BOOST_FOREACH(CTileLayer* tilelayer, m_tileLayers)
		delete tilelayer;
	m_tileLayers.clear();

	BOOST_FOREACH(CObjectLayer* objectlayer, m_objectLayers)
		delete objectlayer;
	m_objectLayers.clear();

	BOOST_FOREACH(CTileset* tileset, m_tilesets)
		delete tileset;
	m_tilesets.clear();

	m_valid = false;
}

void CMapFile::Export(lua_State* L)
{
	using namespace luabind;
	module(L)
		[
			class_<Tiled::CMapFile>("CMapFile")
			.property("version", &Tiled::CMapFile::GetVersion)
			.property("orientation", &Tiled::CMapFile::GetOrientation)
			.property("width", &Tiled::CMapFile::GetWidth)
			.property("height",&Tiled::CMapFile::GetHeight)
			.property("tileWidth", &Tiled::CMapFile::GetTileWidth)
			.property("tileHeight", &Tiled::CMapFile::GetTileHeight)
			.property("isValid", &Tiled::CMapFile::IsValid)
		];
}