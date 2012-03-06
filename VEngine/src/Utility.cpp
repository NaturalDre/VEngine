#include "vengine\Utility.h"
#include <allegro5\allegro5.h>
#include <allegro5\allegro_native_dialog.h>
#include <physfs.h>
#include <stdio.h>
#include <stdlib.h>
#include <lauxlib.h>
#include <vengine\Script\LuaScript.h>
#include <vengine\Physics.h>

namespace VE
{
	namespace Utility
	{
		/*
		* GetStringVal()
		* 
		* Gets and returns a string value from an luatable.
		* 
		* Params:
		*		const std::string& key: The key of the table whose value you want. Must not be empty.
		*		lua_State* L: The state the table is in. Must not be null.
		*
		* Returns: std::string
		*		The value of Table[key]. The lua_State is left the same as it was when passed.
		*
		* Throws: LuaError if Table[key] does not return a string value.
		*
		* Notes:
		*		The first value on the stack MUST be the table you want
		*		BEFORE you call this function. The function does not check
		*		to confirm that this is true. You should do so before the call.
		*/
		std::string GetStringVal(const std::string& key, lua_State* L)
		{
			// STK: table --
			lua_pushstring(L, key.c_str());
			// STK: table -- string
			lua_rawget(L, 1);
			// STK: table -- string?
			if (!lua_isstring(L, -1))
			{
				lua_pop(L, 1);
				// STK: table --
				throw(LuaError("Table object's " + key + " property did not return a string value.", "Not provided", __FILE__, __LINE__));
			}
			// STK: table -- string
			std::string val(lua_tostring(L, -1));
			lua_pop(L, 1);
			return std::move(val);
		}
		/*
		* GetFloatVal()
		* 
		* Gets and returns a float value from an luatable.
		* 
		* Params:
		*		const std::string& key: The key of the table whose value you want. Must not be empty.
		*		lua_State* L: The state the table is in. Must not be null.
		*
		* Returns: float
		*		The value of Table[key]. The lua_State is left the same as it was when passed.
		*
		* Throws: LuaError if Table[key] does not return a float value.
		*
		* Notes:
		*		The first value on the stack MUST be the table you want
		*		BEFORE you call this function. The function does not check
		*		to confirm that this is true. You should do so before the call.
		*/
		float GetFloatVal(const std::string& key, lua_State* L)
		{
			// STK: table --
			lua_pushstring(L, key.c_str());
			// STK: table -- string
			lua_rawget(L, 1);
			// STK: table -- number?
			if (!lua_isnumber(L, -1))
			{
				lua_pop(L, 1);
				// STK: table --
				throw(LuaError("Table object's " + key + "property did not return a string value.", "Not provided", __FILE__, __LINE__));
			}
			// STK: table -- number
			float val(lua_tonumber(L, -1));
			lua_pop(L, 1);
			return val;
		}


		void Utility::ReportError(const std::string& msg, const std::string& errorTitle, const std::string& windowTitle)
		{
			al_show_native_message_box(al_get_current_display(), 
				windowTitle.c_str(), 
				errorTitle.c_str(), 
				msg.c_str(),
				NULL, ALLEGRO_MESSAGEBOX_ERROR);
		}

		std::string Utility::StripFilename(const std::string&  filename)
		{
			if (filename.empty())
				return std::string();

			// Position of the last '/'. +1 because I don't want the '/'. I want what is after it.
			size_t slash = filename.find_last_of('/') + 1;
			size_t dot = filename.find_last_of('.');
			if (dot == std::string::npos)
				dot = filename.size();
			return filename.substr(slash, dot - slash);
		}

		b2Vec2 Utility::GetColRow(size_t cols, size_t id)
		{
			if (cols == 0)
				return b2Vec2();

			if (id % cols == 0)
				return b2Vec2(cols, id / cols);
			else
				return b2Vec2(id % cols, (static_cast<size_t>(id / cols) + 1));
		}

		std::vector<char> Utility::FileToBuffer(const std::string filename)
		{
			std::vector<char> buffer;

			if (!PHYSFS_exists(filename.c_str()))
				return buffer;

			PHYSFS_file* pFile = PHYSFS_openRead(filename.c_str());
			if(!pFile)
				return buffer;

			buffer.resize(PHYSFS_fileLength(pFile));
			PHYSFS_read(pFile, buffer.data(), 1, buffer.size());
			PHYSFS_close(pFile);
			pFile = nullptr;
			return std::move(buffer);
		}

		bool Utility::L_BufferAndLoad(const std::string& filename, lua_State* L)
		{
			std::vector<char> buffer = FileToBuffer(filename);

			if (buffer.empty() || luaL_loadbuffer(L, buffer.data(), buffer.size(), nullptr) || lua_pcall(L, 0, 0, 0))
				return false;

			return true;
		}
	}
	//Utility::TiledObject Utility::ToTiledObject(lua_State* L)
	//{
	//	// STK: table? --
	//	if (!lua_istable(L, 1))
	//		throw(std::exception("Bottom object on the stack is not a table."));
	//	// STK: table --
	//	TiledObject obj;
	//	obj.name = Tiled::GetStringVal("name", L);
	//	obj.type = Tiled::GetStringVal("type", L);
	//	obj.x = Tiled::GetFloatVal("x", L);
	//	obj.y = Tiled::GetFloatVal("y", L);
	//	obj.width = Tiled::GetFloatVal("width", L);
	//	obj.height = Tiled::GetFloatVal("height", L);
	//	obj.properties = std::move(Tiled::GetProperties(L));
	//	return obj;
	//}

	//void Utility::b2BodyDtor::operator()(b2Body* body)
	//{
	//	if (body)
	//		GetPhysMgr().GetWorld()->DestroyBody(body);
	//}
}