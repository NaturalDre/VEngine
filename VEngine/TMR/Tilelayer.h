#ifndef TILELAYER_H
#define TILELAYER_H

#include "Layer.h"
#include <vector>
#include <map>
#include <luabind\object.hpp>

struct lua_State;

namespace Tiled
{
	class CMapFile;
	class CTileLayer: public ILayer
	{
	public:
		CTileLayer(const luabind::object& tilelayer, const CMapFile& mapFile);

		inline int GetType(void) const { return e_TileLayer; }
		inline const std::vector<std::vector<size_t>>& GetData(void) const { return m_data; }
		size_t GetDataVal(size_t row, size_t col);

	private:
		std::vector<std::vector<size_t>> m_data;
	};
}
#endif