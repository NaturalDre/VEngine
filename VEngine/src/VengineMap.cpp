#include "vengine\Level\VengineMap.h"
#include <vengine\Level\Tilelayer.h>

#include <vengine\Utility.h>
#include <exception>
#include <lualib.h>
#include <lauxlib.h>
#include <physfs.h>
#include <vector>
#include <vengine\Image.h>
#include <allegro5\allegro_color.h>


const std::string LS_MAPFUNCTIONS("Scripts/LuaMapFunctions.lua");

namespace VE
{
	namespace Var
	{
		const std::string L_GETNUMBEROFLAYERS	= "GetNumberOfLayers";

		const std::string L_GETMAPWIDTH			= "GetMapWidth";
		const std::string L_GETMAPHEIGHT		= "GetMapHeight";
		const std::string L_GETMAPTILEWIDTH		= "GetMapTileWidth";
		const std::string L_GETMAPTILEHEIGHT	= "GetMapTileHeight";

		const std::string L_GETTILESETIMAGE		= "GetTilesetImage";
		const std::string L_GETTILESETIMGW		= "GetTilesetImageW";
		const std::string L_GETTILESETIMGH		= "GetTilesetImageH";
		const std::string L_GETTILESETTRANS		= "GetTilesetTrans";
		const std::string L_GETTILESETSPACING	= "GetTilesetSpacing";
		const std::string L_GETTILESETNAME		= "GetTilesetName";

		const std::string L_ISTILELAYER			= "IsTilelayer";
		const std::string L_ISPHYSICSLAYER		= "IsPhysicslayer";

		const std::string L_GETNUMOFTILESETS	= "GetNumberOfTilesets";
		const std::string L_GETTILESETFIRSTGID	= "GetTilesetFirstGid";
		const std::string L_GETTILESETTILEW		= "GetTilesetTileWidth";
		const std::string L_GETTILESETTILEH		= "GetTilesetTileHeight";
	}


	////////////////////////////////
	/////// CVengineMap Render /////
	////////////////////////////////
	class VengineMapRender: public IRenderListener
	{
	private:
		void Draw(void)
		{
			for (size_t i(0); i < m_map->GetLayerCount(); ++i)
				m_map->GetLayer(i)->draw();
		}

	public:
		VengineMapRender(CVengineMap* map)
			: m_map(map)
		{

		}

	private:
		CVengineMap* m_map;
	};

	////////////////////////////////
	////////// CVengineMap /////////
	////////////////////////////////

	CVengineMap::CVengineMap(void)
		: m_L(nullptr)
	{
		m_render.reset(new VengineMapRender(this));
	}

	CVengineMap::~CVengineMap(void)
	{
		lua_close(m_L);
		m_L = nullptr;
	}

	void CVengineMap::LoadMapFile(void)
	{
		// Open the state
		m_L = lua_open();
		if (!m_L)
			throw(std::exception("Could not open lua state"));

		// Check that the file exists
		if (!PHYSFS_exists(m_filename.c_str()))
			throw(std::exception((m_filename + " does not exist.").c_str()));
		else
		{
			// If it does, try to open it.
			PHYSFS_file* pFile = PHYSFS_openRead(m_filename.c_str());
			if (!pFile)
				throw(std::exception((m_filename + " could not be opened by PHYFS").c_str()));

			// If opened, load the contents into a buffer
			std::vector<char> buffer(PHYSFS_fileLength(pFile));
			PHYSFS_read(pFile, buffer.data(), 1, buffer.size());
			PHYSFS_close(pFile);
			pFile = nullptr;

			// Load the buffer for execution in LUA
			if (luaL_loadbuffer(m_L, buffer.data(), buffer.size(), nullptr))
			{
				const char* error = lua_tostring(m_L, -1);
				lua_pop(m_L, 11);
				throw(std::exception(("Could not load buffer for: " + m_filename + "\n" + error).c_str()));
			}
			// Execute the buffer
			if(lua_pcall(m_L, 0, LUA_MULTRET, 0))
			{
				const char* error = lua_tostring(m_L, -1);
				lua_pop(m_L, 1);
				throw(std::exception(("Could not execute chunk for: " + m_filename + " " + error).c_str()));
			}
		}

		// Load functions for operating on the loaded buffer
		if (!PHYSFS_exists("Scripts/LuaMapFunctions.lua"))
			throw(std::exception("Scripts/LuaMapFunctions.lua does not exist in PHYSFS"));
		else
		{
			PHYSFS_file* pFile = PHYSFS_openRead(LS_MAPFUNCTIONS.c_str());
			if (!pFile)
				throw(std::exception((LS_MAPFUNCTIONS + " could not be opened for reading by PHYSFS").c_str()));

			std::vector<char> buffer(PHYSFS_fileLength(pFile));
			PHYSFS_read(pFile, buffer.data(), 1, buffer.size());
			PHYSFS_close(pFile);
			pFile = nullptr;

			if (luaL_loadbuffer(m_L, buffer.data(), buffer.size(), nullptr))
			{
				const char* error = lua_tostring(m_L, -1);
				lua_pop(m_L, 1);
				throw(std::exception(("Could not load chunk for: " + LS_MAPFUNCTIONS + "\n" + error).c_str()));
			}
			if (lua_pcall(m_L, 0, LUA_MULTRET, 0))
			{
				const char* error = lua_tostring(m_L, -1);
				lua_pop(m_L, 1);
				throw(std::exception(("Could not execute chunk for: " + LS_MAPFUNCTIONS + "\n" + error).c_str()));
			}
		}
	}

	void CVengineMap::LoadLayerData(void)
	{
		m_layerSize.gridElementsW = GetMapWidth(m_L);
		m_layerSize.gridElementsH = GetMapHeight(m_L);

		m_layerSize.tileWidth = GetMapTileWidth(m_L);
		m_layerSize.tileHeight = GetMapTileHeight(m_L);
	}

	void CVengineMap::LoadTilesheetData(void)
	{
		SheetData data;
		for (size_t i = 1; i <= GetNumOfTilesets(m_L); ++i)
		{
			data.firstGid = GetTilesetFirstGid(i, m_L);
			data.tileWidth = GetTilesetTileWidth(i, m_L);
			data.tileHeight = GetTilesetTileHeight(i, m_L);
			data.image = VE::LoadBitmap(GetTilesetImage(i, m_L));
			if (!data.image)
				throw((std::string("Could not load tileset image: ") + GetTilesetImage(i, m_L)));
			data.imgHeight = GetTilesetImgH(i, m_L);
			data.imgWidth = GetTilesetImgW(i, m_L);
			if (!GetTilesetTrans(i, m_L).empty()) // If the pointer is valid then there's a transparent color.
				data.trans = al_color_html(GetTilesetTrans(i, m_L).c_str());
			data.spacing = GetTilesetSpacing(i, m_L);
			data.name = GetTilesetName(i, m_L);

			if (data.tileWidth == 0)
				throw("A tileset's tileWidth MUST NOT be zero");
			if (data.tileHeight == 0)
				throw("A tileset's tileHeight MUST NOT be zero");

			data.gridElementsW = data.imgWidth / (data.tileWidth + data.spacing);
			assert((data.tileHeight + data.spacing));
			data.gridElementsH = data.imgHeight / (data.tileHeight + data.spacing);
			data.lastGid = data.firstGid + (((data.imgWidth / (data.tileWidth + data.spacing)) * (data.imgHeight / (data.tileHeight + data.spacing)))-1);
			if (data.image.get())
				al_convert_mask_to_alpha(data.image.get(), data.trans);
			m_sheetData.push_back(data);
		}
	}


	void CVengineMap::Assemble(void)
	{
		for(size_t i = 1; i <= GetNumberOfLayers(m_L); ++i)
		{
			if (IsTilelayer(i, m_L))
			{
				std::unique_ptr<IMapLayer> ptr(new CTilelayer(i, m_L, m_sheetData, m_layerSize));
			m_layers.push_back(std::move(ptr));
			}
			else if(IsPhysicslayer(i, m_L))
				CreatePhysics(i);
		}
	}

	void CVengineMap::CreatePhysics(size_t physicsLayer)
	{

	}

	size_t CVengineMap::GetNumberOfLayers(lua_State* L)
	{
		// STK: 
		lua_getglobal(L, Var::L_GETNUMBEROFLAYERS.c_str());
		// STK: func?
		if(!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			throw(std::exception((Var::L_GETNUMBEROFLAYERS + " was not found or is not a function").c_str()));
		}
		// STK: func
		if(lua_pcall(L, 0, 1, 0) != 0)
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception((Var::L_GETNUMBEROFLAYERS + "\n" + error).c_str()));
		}
		// STK: int?
		if (!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int amount = lua_tonumber(L, -1);
		lua_pop(L, 1);
		// STK:
		return amount;
	}

	bool CVengineMap::IsTilelayer(const size_t index, lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, Var::L_ISTILELAYER.c_str());
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			throw(std::exception((Var::L_ISTILELAYER + " was not found or is not a function.").c_str()));
		}
		// STK: func
		lua_pushinteger(L, index);
		// STK: func int
		if (lua_pcall(L, 1, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception((Var::L_ISTILELAYER + "\n" + error).c_str()));
		}
		// STK: bool?
		if (!lua_isboolean(L, -1))
		{
			lua_pop(L, 1);
			return false;
		}
		// STK: bool
		bool val = lua_toboolean(L, -1);
		lua_pop(L, 1);
		// STK: 
		return val;
	}

	bool CVengineMap::IsPhysicslayer(const size_t index, lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "IsPhysicslayer");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return false;
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
		// STK: bool?
		if (!lua_isboolean(L, -1))
		{
			lua_pop(L, 1);
			return false;
		}
		// STK: bool
		bool val = lua_toboolean(L, -1);
		lua_pop(L, 1);
		// STK:
		return val;
	}

	size_t CVengineMap::GetMapWidth(lua_State* L)
	{
		assert(L != nullptr);
		// STK:
		lua_getglobal(L, "GetMapWidth");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return false;
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

	size_t CVengineMap::GetMapHeight(lua_State* L)
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

	size_t CVengineMap::GetMapTileWidth(lua_State* L)
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

	size_t CVengineMap::GetMapTileHeight(lua_State* L)
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

	std::string CVengineMap::GetTilesetImage(size_t index, lua_State* L)
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

	size_t CVengineMap::GetTilesetImgW(const size_t index, lua_State* L)
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

	size_t CVengineMap::GetTilesetImgH(const size_t index, lua_State* L)
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

	std::string CVengineMap::GetTilesetTrans(const size_t index, lua_State* L)
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

	size_t CVengineMap::GetTilesetSpacing(const size_t index, lua_State* L)
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

	std::string CVengineMap::GetTilesetName(const size_t index, lua_State* L)
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
	
	size_t CVengineMap::GetNumOfTilesets(lua_State* L)
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

	size_t CVengineMap::GetTilesetFirstGid(size_t index, lua_State* L)
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

	size_t CVengineMap::GetTilesetTileWidth(size_t index, lua_State* L)
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

	size_t CVengineMap::GetTilesetTileHeight(size_t index, lua_State* L)
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

	std::unique_ptr<CVengineMap> CVengineMap::Create(const std::string& filename)
	{
		std::unique_ptr<CVengineMap> map(new CVengineMap);

		if (!map)
			throw(std::exception("Could not allocate memory for CVengineMap."));
		
		map->m_filename = filename;
		map->LoadMapFile();
		map->LoadLayerData();
		map->LoadTilesheetData();

		return std::move(map);
	}
}