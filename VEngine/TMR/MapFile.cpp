#include "MapFile.h"
#include <assert.h>
#include <lua.hpp>
#include "Tilelayer.h"
#include "ObjectLayer.h"
#include "TiledLua.h"

using namespace Tiled;

CMapFile::CMapFile(void)
{
	m_width = 0;
	m_height = 0;
	m_tileHeight = 0;
	m_tileWidth = 0;

	m_physicsLayer = nullptr;
	m_valid = false;
}

void CMapFile::LoadMapData(lua_State* L)
{
	m_version = GetVersion(L);
	m_orientation = GetOrientation(L);
	m_width = GetMapWidth(L);
	m_height = GetMapHeight(L);
	m_tileWidth = GetTileWidth(L);
	m_tileHeight = GetTileHeight(L);
}

void CMapFile::LoadLayers(lua_State* L)
{
	for (size_t i = 1; i <= GetNumOfTilesets(L); ++i)
	{
		CTileset* ts = new CTileset;
		ts->ReadMapFile(L, i);
		m_tilesets.push_back(ts);
	}

	for (size_t i = 1, max = GetLayerCount(L); i <= max; ++i)
	{
		const std::string type = GetLayerType(L, i);

		if(type == "tilelayer")
		{
			CTileLayer* layer = new CTileLayer;
			layer->ReadMap(L, i, this);
			m_tileLayers.push_back(layer);
		}
		else if (type == "objectgroup")
		{
			CObjectLayer* layer = new CObjectLayer;
			layer->ReadMapFile(this, L, i);

			if (layer->Property("type") == "physics")
				m_physicsLayer = layer;
			else
				m_objectLayers.push_back(layer);
		}
	}
}

bool CMapFile::ReadMapFile(const std::string& mapFile, std::string& err)
{
	// Open an lua state
	lua_State* L = lua_open();

	if (!L)
	{
		err = "Unable to create Lua State.";
		return false;
	}

	// Attempt to load the file.
	// NOTE: Non-zero is error.
	if (luaL_dofile(L, mapFile.c_str()))
	{
		err = "Unable to load file.";
		return false;
	}
	// Load the script which contains Lua functions for operating 
	// on Tiled's Lua map files.
	// NOTE: Non-zero is error
	if (luaL_dofile(L, "TiledMapFunctions.lua"))
	{
		err = "Unable to load Lua file that contains functions for "
			"operating on Tiled's Lua map file.";
		return false;
	}

	LoadMapData(L);
	LoadLayers(L);
	//CTileLayer* layer = new CTileLayer();
	//layer->ReadMap(L, 1, this);
	//m_layers.push_back(layer);
	return m_valid = true;
}