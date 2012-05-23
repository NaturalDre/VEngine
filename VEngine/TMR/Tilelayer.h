#ifndef TILELAYER_H
#define TILELAYER_H

#include "Layer.h"
#include <vector>
#include <map>

struct lua_State;

namespace Tiled
{
	class CMapFile;
	class CTileLayer: public ILayer
	{
	public:
		CTileLayer(void);

		bool ReadMap(lua_State* L, const size_t layerIndex, CMapFile* mapFile);
		inline int Type(void) const { return e_TileLayer; }
		
		size_t GetDataVal(size_t row, size_t col);
		inline const std::vector<std::vector<size_t>>& GetData(void) const { return m_data; }
	private:
		std::map<const std::string, const std::string> m_properties;
		std::vector<std::vector<size_t>> m_data;
	};
}
#endif