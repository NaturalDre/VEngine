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
		typedef std::map<const std::string, const std::string> TiledObjectProperties;
	public:
		TiledObject(void): m_x(0), m_y(0), m_width(0), m_height(0) {}
		TiledObject(TiledObject&& rhs);

	public:
		inline const std::string& Name(void) const { return m_name; }
		inline const std::string& Type(void) const { return m_type; }
		inline float X(void) const { return m_x; }
		inline float Y(void) const { return m_y; }
		inline float Width(void) const { return m_width; }
		inline float Height(void) const { return m_height; }


		static TiledObject CreateFromLua(lua_State* L);
	private:
		std::string m_name;
		std::string m_type;
		float m_x;
		float m_y;
		float m_width;
		float m_height;
		TiledObjectProperties m_properties;
	};
}
#endif