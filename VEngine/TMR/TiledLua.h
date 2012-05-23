#ifndef TILEDLUA_H
#define TILEDLUA_H

#include <string>
#include <map>
#include <lua.hpp>

namespace Tiled
{
	std::string Version(lua_State* L);
	std::string Orientation(lua_State* L);
	// map.width
	size_t MapWidth(lua_State* L);
	// map.height
	size_t MapHeight(lua_State* L);
	// map.tilewidth
	size_t TileWidth(lua_State* L);
	// map.tileheight
	size_t TileHeight(lua_State* L);
	// #map.layers
	size_t LayerCount(lua_State* L);
	// map.layers[element].type
	std::string LayerType(lua_State* L, size_t element);

	// return map.layers[layer].objects[index] NOTE: Value at top of stack must be popped if
	// call returns true.
	bool PushTiledObject(lua_State* L, size_t layer, size_t index);
	// #map.layers[layer].objects
	size_t NumberOfObjects(lua_State* L, size_t layer);
	// table.properties; NOTE: Table must be at top of stack before call.
	std::map<const std::string, const std::string> GetProperties(lua_State*L);
	// map.layers[layer].data[index]
	size_t DataValue(lua_State* L, size_t layer, size_t index);
	// return map.layers[layer]. NOTE: Value at top of stack must be popped if 
	// call returns true.
	bool PushLayer(lua_State* L, size_t layer);


	std::string GetTilesetImage(size_t index, lua_State* L);
	size_t GetTilesetImgW(const size_t index, lua_State* L);
	size_t GetTilesetImgH(const size_t index, lua_State* L);
	std::string GetTilesetTrans(const size_t index, lua_State* L);
	size_t GetTilesetSpacing(const size_t, lua_State* L);
	std::string GetTilesetName(const size_t, lua_State* L);


	size_t GetNumOfTilesets(lua_State* L);
	size_t GetTilesetFirstGid(size_t index, lua_State* L);
	// Width of a tile on a tilesheet
	size_t GetTilesetTileWidth(size_t index, lua_State* L);
	size_t GetTilesetTileHeight(size_t index, lua_State* L);
}

#endif