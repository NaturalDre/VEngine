#ifndef TILETILESET_H
#define TILETILESET_H

#include <string>
#include <list>
#include "Tileset.h"
#include "Layer.h"

struct lua_State;
struct ALLEGRO_BITMAP;

namespace Tiled
{
	class CTileset
	{
	public:
		CTileset(void);
		~CTileset(void);

		void ReadMapFile(lua_State* L, size_t index);
		
		inline std::string Name(void) const { return m_name; }
		inline std::string Source(void) const { return m_source; }
		inline std::string Trans(void) const { return m_trans; }

		inline size_t FirstGid(void) const { return m_firstGid; }
		inline size_t LastGid(void) const { return m_lastGid; }
		
		inline size_t TileWidth(void) const { return m_tileWidth; }
		inline size_t TileHeight(void) const { return m_tileHeight; }
		inline size_t ImageWidth(void) const { return m_tileWidth; }
		inline size_t ImageHeight(void) const { return m_tileHeight; }
		inline size_t Spacing(void) const { return m_spacing; }
		inline size_t TilesAcross(void) const { return m_tilesAcross; }
		inline size_t TilesDown(void) const { return m_tilesDown; }

		/*
		* ContainsGid()
		*
		* Check if this tileset contains the gid
		*/
		bool ContainsGid(size_t gid) const { return ((gid >= m_firstGid) && (gid <= m_lastGid)); }
		/*
		* ContainsGid()
		*
		* Check if a list of tilsets contain the gid
		*/
		static CTileset* ContainsGid(const std::list<CTileset*>& tilesets, size_t id);
		/*
		* LoadTile()
		*
		* Checks a list of tilesets to find which one contains the gid and then loads and returns it.
		*
		* Notes: 
		*	You must free the memory. 
		* CAUTION: 
		*	If you don't free the memory before the tileset that you got it 
		*	from is destroyed, then later free it, the behavior will be undefined.
		*/
		static ALLEGRO_BITMAP* LoadTile(const std::list<CTileset*>& tilesets, size_t id);
		/*
		* GetImage()
		*
		* Get the image file.
		*
		* Notes:
		*	Null pointer if it wasn't able to find and load the image. 
		*	The image isn't loaded by this function, it is loaded when ReadMapFile() is called.
		*/
		ALLEGRO_BITMAP*  GetImage(void) const { return m_image; }

	private:
		std::string m_name;
		std::string m_source;
		std::string m_trans;

		size_t m_firstGid;
		size_t m_lastGid;
		
		size_t m_tileWidth;
		size_t m_tileHeight;
		size_t m_imageWidth;
		size_t m_imageHeight;
		size_t m_spacing;
		size_t m_tilesAcross;
		size_t m_tilesDown;

		ALLEGRO_BITMAP* m_image;
	};
}

#endif