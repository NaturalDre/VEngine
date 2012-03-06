#ifndef TILED_H
#define TILED_H

#include <map>
#include <string>

struct lua_State;

namespace Tiled
{
	/*
	* struct TiledObject
	*
	* This represents the 'object' table that is found in Tiled's exort of
	* an 'objectlayer'.
	*
	*/
	struct TiledObject
	{
		TiledObject(void): x(0), y(0), width(0), height(0) {}
		TiledObject(TiledObject&& rhs);

		std::string name;
		std::string type;
		float x;
		float y;
		float width;
		float height;
		std::map<const std::string, std::string> properties;
	};

	/*
	* ToTiledObject()
	*
	* Returns an C++ represenation of the Lua table export of
	* Tiled's object table found within its 'objecylayer'.
	*
	* Params:
	*		lua_State* L: The lua_State where the 'object' table is.
	*
	* Notes:
	*		The table MUST be at position 1 on the stack. It MUST also
	*		actually be an object from Tiled's objectlayer or exceptions
	*		will be thrown.
	*
	* Throws:
	*		std::exception:	If the value at position 1 on the stack is
	*						is not a table.
	*		LuaError:	If the table does not have one or more of the requires
	*					keys a TiledObject MUST have. (The ones defined in the struct)
	*/
	TiledObject ToTiledObject(lua_State* L);

	std::map<const std::string, std::string> GetProperties(lua_State*L);
};
#endif