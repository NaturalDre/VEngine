#ifndef TILESET_H
#define TILESET_H

#include <allegro5\allegro5.h>
#include <vector>
#include <list>
#include <memory>
#include <lua.hpp>
#include <vengine\Level\LayerDataTypes.h>
#include <vengine\Level\MapLayer.h>

namespace VE
{
	class CVengineMap;
	class CTilelayer: public IMapLayer
	{
		friend CVengineMap;
	protected:
		// Constructor
		CTilelayer(const size_t layerElement, lua_State* L, const std::list<SheetData>& sheets, const LayerSize& layerSize);
		void GatherData(size_t layerElement, lua_State* L);
		// Draw this layer to the screen TO DO: Make better
		void draw(void);
		void DrawTile(SheetData* data, size_t id);
		// Create an image from the map data from the layer data
		ALLEGRO_BITMAP* construct(size_t layerElement, lua_State* L, const std::list<SheetData>& _sheets, const LayerSize& layerSize);
		
		
		// Get the spritesheet that contains the gid
		static const SheetData& getSheet(const size_t _gid, const std::list<SheetData>& _sheets);
		// Helper function to create a sub bitmap that gets sent to image manager to save memory
		static ALLEGRO_BITMAP* createTileSubBitmap(const SheetData* data, const size_t id) ;
		static size_t GetLayerDataValue(size_t layer, size_t index, lua_State* L);
		static size_t GetLayerDataSize(size_t layer, lua_State* L);
	public:
		~CTilelayer(void);

		std::vector<std::vector<size_t>>& GetElements(void) { return m_mapElements; }
	private:
		CTilelayer(CTilelayer const&);
		void operator=(CTilelayer const&);


		std::shared_ptr<ALLEGRO_BITMAP> m_layerImage;
		std::vector<std::vector<size_t>> m_mapElements;
		std::list<SheetData> m_sheets;
		LayerSize m_layerSize;
	};
}
#endif