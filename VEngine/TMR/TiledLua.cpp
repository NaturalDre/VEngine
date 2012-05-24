#include "TiledLua.h"
#include <assert.h>

//using namespace Tiled;

namespace Tiled
{
	std::string GetVersion(lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "GetMapVersion");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return 0;
			//throw(std::exception("GetMapWidth is not a function."));
		}
		// STK: func
		if (lua_pcall(L, 0, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if (!lua_isstring(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		std::string val = lua_tostring(L, -1);
		lua_pop(L, 1);
		// STK:
		return val;
	}

	std::string GetOrientation(lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "GetMapOrientation");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return 0;
			//throw(std::exception("GetMapWidth is not a function."));
		}
		// STK: func
		if (lua_pcall(L, 0, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if (!lua_isstring(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		std::string val = lua_tostring(L, -1);
		lua_pop(L, 1);
		// STK:
		return val;
	}

	size_t GetMapWidth(lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "GetMapWidth");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return 0;
			//throw(std::exception("GetMapWidth is not a function."));
		}
		// STK: func
		if (lua_pcall(L, 0, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if (!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int val = lua_tointeger(L, -1);
		lua_pop(L, 1);
		// STK:
		return val;
	}

	size_t GetMapHeight(lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "GetMapHeight");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: func
		if (lua_pcall(L, 0, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if (!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int val = lua_tointeger(L, -1);
		lua_pop(L, 1);
		// STK:
		return val;
	}

	size_t GetTileWidth(lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "GetMapTileWidth");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: func
		if (lua_pcall(L, 0, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if (!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int val = lua_tointeger(L, -1);
		lua_pop(L, 1);
		// STK:
		return val;
	}

	size_t GetTileHeight(lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "GetMapTileHeight");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: func
		if (lua_pcall(L, 0, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if (!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int val = lua_tointeger(L, -1);
		lua_pop(L, 1);
		// STK:
		return val;
	}

	size_t GetLayerCount(lua_State* L)
	{
		// STK: 
		lua_getglobal(L, "GetNumberOfLayers");
		// STK: func?
		if(!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return 0;
			//throw(std::exception(("GetNumberOfLayers" " was not found or is not a function").c_str()));
		}
		// STK: func
		if(lua_pcall(L, 0, 1, 0) != 0)
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			return 0;
			//throw(std::exception(("GetNumberOfLayers" + "\n" + error).c_str()));
		}
		// STK: int?
		if (!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int amount = lua_tointeger(L, -1);
		lua_pop(L, 1);
		// STK:
		return amount;
	}

	std::string GetLayerType(lua_State* L, size_t element)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "GetLayerType");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return "";
			//throw(std::exception((Var::L_ISTILELAYER + " was not found or is not a function.").c_str()));
		}
		// STK: func
		lua_pushinteger(L, element);
		// STK: func int
		if (lua_pcall(L, 1, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			return "";
			//throw(std::exception((Var::L_ISTILELAYER + "\n" + error).c_str()));
		}
		// STK: string?
		if (!lua_isstring(L, -1))
		{
			lua_pop(L, 1);
			return false;
		}
		// STK: bool
		std::string val = lua_tostring(L, -1);
		lua_pop(L, 1);
		// STK: 
		return val;
	}

	bool PushTiledObject(lua_State* L, size_t layer, size_t index)
	{
		assert(L != nullptr);

		lua_getglobal(L, "GetObjLayerObject");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			throw(std::exception("Could not get function GetLayerDataVal"));
		}
		// STK: func
		lua_pushinteger(L, layer);
		lua_pushinteger(L, index);
		// STK: func int int
		if (lua_pcall(L, 2, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: table?
		if(!lua_istable(L, -1))
		{
			lua_pop(L, 1);
			return false;
		}

		return true;
	};

	bool PushLayer(lua_State* L, size_t layer)
	{
		assert(L != nullptr);

		lua_getglobal(L, "GetLayerObject");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			throw(std::exception("Could not get function GetLayerObject"));
		}
		// STK: func
		lua_pushinteger(L, layer);
		//lua_pushinteger(L, index);
		// STK: func int int
		if (lua_pcall(L, 1, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: table?
		if(!lua_istable(L, -1))
		{
			lua_pop(L, 1);
			return false;
		}
		// STK:
		return true;
	}

	size_t NumberOfObjects(lua_State* L, size_t layer)
	{
		assert(L != nullptr);

		lua_getglobal(L, "GetNumOfObjLayerObjects");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: func
		lua_pushinteger(L, layer);
		// STK: func int
		if (lua_pcall(L, 1, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if (!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int val = lua_tointeger(L, -1);
		lua_pop(L, 1);
		return val;
	}

	std::map<const std::string, const std::string> GetProperties(lua_State*L)
	{
		// STK: table1 --
		lua_pushstring(L, "properties");
		// STK: table1 -- string
		lua_rawget(L, 1);
		// STK: table1 -- table2?
		if (!lua_istable(L, -1))
		{
			lua_pop(L, 1);
			// STL: table1 --
			throw(std::exception("Table has not 'properties' key."));
		}
		// STK: table1 -- table2
		lua_insert(L, 1);
		// STK: table2 table1 --
		lua_pushnil(L);
		// STK: table2 table1 -- nil
		std::map<const std::string, const std::string> props;
		while(lua_next(L, 1))
		{
			// STK: table2 table1 -- string? string?
			if (!lua_isstring(L, -2))
				throw(std::exception("A key in properties is a non string value."));
			else if(!lua_isstring(L, -1))
				throw(std::exception("A key in properties returned a non string value."));
			// STK: table2 table1 -- string string
			props.insert(std::pair<const std::string, const std::string>(lua_tostring(L, -2),lua_tostring(L, -1)));
			//props[lua_tostring(L, -2)] = lua_tostring(L, -1);
			lua_pop(L, 1);

		}
		// STK: table2 table1 --
		lua_remove(L, 1);
		// STK: table1
		return std::move(props);
	}

	size_t DataValue(lua_State* L, size_t layer, size_t index)
	{
		assert(L != nullptr);

		lua_getglobal(L, "GetLayerDataVal");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			throw(std::exception("Could not get function GetLayerDataVal"));
		}
		// STK: func
		lua_pushinteger(L, layer);
		lua_pushinteger(L, index);
		// STK: func int int
		if (lua_pcall(L, 2, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if(!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int val = lua_tointeger(L, -1);
		lua_pop(L, 1);
		// STK:
		return val;
	}

	std::string GetTilesetImage(size_t index, lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "GetTilesetImage");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: func
		lua_pushinteger(L, index);
		// STK: func int
		if (lua_pcall(L, 1, 1,0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: string?
		if (!lua_isstring(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: string
		std::string val = lua_tostring(L, -1);
		lua_pop(L, 1);
		// STK:
		return std::move(val);	
	}

	size_t GetTilesetImgW(const size_t index, lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "GetTilesetImageWidth");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: func
		lua_pushinteger(L, index);
		// STK: func int
		if (lua_pcall(L, 1, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if (!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int val = lua_tointeger(L, -1);
		lua_pop(L, 1);
		// STK:
		return val;
	}

	size_t GetTilesetImgH(const size_t index, lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "GetTilesetImageHeight");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: func
		lua_pushinteger(L, index);
		// STK: func int
		if (lua_pcall(L, 1, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if (!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int val = lua_tointeger(L, -1);
		lua_pop(L, 1);
		// STK:
		return val;
	}

	std::string GetTilesetTrans(const size_t index, lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "GetTilesetTrans");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: func
		lua_pushinteger(L, index);
		// STK: func int
		if (lua_pcall(L, 1, 1,0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: string?
		if (!lua_isstring(L, -1))
		{
			lua_pop(L, 1);
			return "";
		}
		// STK: string
		std::string val = lua_tostring(L, -1);
		lua_pop(L, 1);
		return std::move(val);	
	}

	size_t GetTilesetSpacing(const size_t index, lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "GetTilesetSpacing");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: func
		lua_pushinteger(L, index);
		// STK: func int
		if (lua_pcall(L, 1, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if (!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int val = lua_tointeger(L, -1);
		lua_pop(L, 1);
		// STK:
		return val;
	}

	std::string GetTilesetName(const size_t index, lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "GetTilesetName");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: func
		lua_pushinteger(L, index);
		// STK: func int
		if (lua_pcall(L, 1, 1,0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: string?
		if (!lua_isstring(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: string
		std::string val = lua_tostring(L, -1);
		lua_pop(L, 1);
		return val;
	}

	size_t GetNumOfTilesets(lua_State* L)
	{
		assert(L != nullptr);

		lua_getglobal(L, "GetNumberOfTilesets");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			throw(std::exception("GetNumberOfTilesets could not be found."));
		}
		// STK: func
		if (lua_pcall(L, 0, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if (!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int val = lua_tointeger(L, -1);
		lua_pop(L, 1);
		return val;
	}

	size_t GetTilesetFirstGid(size_t index, lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "GetTilesetFirstGid");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: func
		lua_pushinteger(L, index);
		// STK: func int
		if (lua_pcall(L, 1, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if (!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int val = lua_tointeger(L, -1);
		lua_pop(L, 1);
		// STK:
		return val;
	}

	size_t GetTilesetTileWidth(size_t index, lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "GetTilesetTileWidth");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			throw(std::exception("Could not get function GetTilesetTileWidth"));
		}
		// STK: func
		lua_pushinteger(L, index);
		// STK: func int
		if (lua_pcall(L, 1, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if (!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int val = lua_tointeger(L, -1);
		lua_pop(L, 1);
		// STK:
		return val;
	}

	size_t GetTilesetTileHeight(size_t index, lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "GetTilesetTileHeight");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: func
		lua_pushinteger(L, index);
		// STK: func int
		if (lua_pcall(L, 1, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if (!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int val = lua_tointeger(L, -1);
		lua_pop(L, 1);
		// STK:
		return val;
	}
}