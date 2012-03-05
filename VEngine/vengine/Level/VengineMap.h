#ifndef VENGINEMAP_H
#define VENGINEMAP_H

#include <lua.hpp>
#include <string>
#include <vengine\Level\MapLayer.h>
#include <memory>
#include <list>
#include <vector>
#include <vengine\Level\LayerDataTypes.h>
#include <vengine\Render\RenderListener.h>
namespace VE
{
	class CVengineMap
	{
	protected:
		void LoadMapFile(void);

		static size_t GetNumberOfLayers(lua_State* L);

		static size_t GetMapWidth(lua_State* L);
		static size_t GetMapHeight(lua_State* L);
		static size_t GetMapTileWidth(lua_State* L);
		static size_t GetMapTileHeight(lua_State* L);

		static std::string GetTilesetImage(size_t index, lua_State* L);
		static size_t GetTilesetImgW(const size_t index, lua_State* L);
		static size_t GetTilesetImgH(const size_t index, lua_State* L);
		static std::string GetTilesetTrans(const size_t index, lua_State* L);
		static size_t GetTilesetSpacing(const size_t, lua_State* L);
		static std::string GetTilesetName(const size_t, lua_State* L);

		static bool IsTilelayer(const size_t index, lua_State* L);
		static bool IsPhysicslayer(const size_t index, lua_State* L);

		static size_t GetNumOfTilesets(lua_State* L);
		static size_t GetTilesetFirstGid(size_t index, lua_State* L);
		// Width of a tile on a tilesheet
		static size_t GetTilesetTileWidth(size_t index, lua_State* L);
		static size_t GetTilesetTileHeight(size_t index, lua_State* L);

	public:
		virtual ~CVengineMap(void);

		// Load the layer size/width/tiles
		void LoadLayerData(void);
		// Load the tile sheets
		void LoadTilesheetData(void);
		// Put the map together
		void Assemble(void);
		// Free data
		void Disassemble(void);
		// Load physics objects. Pass the index of the physics layer. 
		// TO DO: See if there's a better place for this.
		void CreatePhysics(size_t physicsLayer);

		inline const std::unique_ptr<IMapLayer>& GetLayer(size_t element) { assert(element < m_layers.size()); return m_layers[element]; }
		inline size_t GetLayerCount(void) const { return m_layers.size(); }

		static std::unique_ptr<CVengineMap> Create(const std::string& filename);

	private:
		CVengineMap(void);

		std::vector<std::unique_ptr<IMapLayer>> m_layers;
		std::list<SheetData> m_sheetData;
		std::unique_ptr<IRenderListener> m_render;
		lua_State* m_L;
		std::string m_filename;
		LayerSize m_layerSize;

	};


}
#endif