#ifndef TILEDOBJECT_H
#define TILEDOBJECT_H

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
	class TiledObject
	{
	public:
		TiledObject(void): x(0), y(0), width(0), height(0) {}
		TiledObject(TiledObject&& rhs);

	public:
		static TiledObject CreateFromLua(lua_State* L);
	private:
		std::string name;
		std::string type;
		float x;
		float y;
		float width;
		float height;
		std::map<const std::string, std::string> properties;
	};
}
#endif