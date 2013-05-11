#include "GameMap.h"
#include "Render.h"
#include "Utility.h"
#include <luabind\luabind.hpp>
#include "Camera.h"
#include <allegro5\allegro5.h>

namespace VE
{
	CGameMap::CGameMap(CGameLevel* gameLevel)
		: m_gameLevel(gameLevel)
		, m_playerLayer(0)
		, m_playerSpawn(0,0)

	{
		m_parser = CMapParser(gameLevel, this);
	}

	CBitmap CGameMap::LoadTile(const size_t id)
	{
		Tiled::CTileset* ts = Tiled::CTileset::ContainsGid(GetTilesets(), id);
		if (!ts)
			return CBitmap();

		const CBitmap const* image = GetTilesetImage(ts->Name());

		if (!image)
			return CBitmap();

		const ColRow  cr = GetColRow(ts->TilesAcross(), (id - ts->FirstGid()) + 1);

		VE::CBitmap bitmap(image, 
			(cr.col - 1) * (ts->ImageWidth() + ts->Spacing()),
			(cr.row - 1) * (ts->ImageHeight() + ts->Spacing()),
			ts->TileWidth(),
			ts->TileHeight());

		return std::move(bitmap);
	}

	CGameMap::ConstTileLayerIter CGameMap::FindTileLayer(const std::string& name)
	{
		for( ConstTileLayerIter iter = GetTileLayers().begin(); iter != GetTileLayers().end(); ++iter)
		{
			if ((*iter)->GetName() == name)
				return iter;
		}
		return GetTileLayers().end();
	}

	int CGameMap::FindTileLayerIndex(const std::string& name)
	{
		auto layerIter = FindTileLayer(name);
		size_t index(0);
		for (auto iter = GetTileLayers().begin(); iter != GetTileLayers().end(); ++iter, ++index)
		{
			if (iter == layerIter)
				return index;
		}
		return -1;
	}

	void CGameMap::RenderLayer(VE::CRender* renderer, Tiled::CTileLayer* tilelayer)
	{
		// FOr the sub bitmaps
		//VE::CBitmap tile;
		//size_t prevID(0);

		// Top left x and y position of the camera
		const float tlx = renderer->Cam()->TopLeftPosPix().x;
		const float tly = renderer->Cam()->TopLeftPosPix().y;	

		if (this->GetOrientation() == "orthogonal")
			RenderOrthogonal(renderer, tilelayer);
		else if (this->GetOrientation() == "isometric")
			RenderOrthogonal(renderer, tilelayer);
		else
			return;

		//const int startCol(static_cast<int>(tlx / GetTileWidth()));
		//const int startRow(static_cast<int>(tly / GetTileHeight()));

		//const int endCol = startCol + (VE::GetDisplayWidth() / GetTileWidth()) + 2; // +2 is buffer otherwise last col won't draw
		//const int endRow = startRow + (VE::GetDisplayHeight() / GetTileHeight()) + 2; // +2 is buffer otherwise last row won't draw



		//for (int y  = 1; y < 25; ++y)
		//{
		//	for (int x = 1; x < 25; ++x)
		//	{
		//		int drawX = ((x - y) * 32) + 300;
		//		int drawY = ((x + y) * 16);
		//		
		//		int id = tilelayer->GetDataVal(x, y);
		//		if (id == 0)
		//			continue;
		//		if (id != prevID)
		//		{
		//			prevID = id;
		//			tile = LoadTile(id);
		//			//tile.Load();
		//			//tile = Tiled::CTileset::LoadTile(GetTilesets(), id);
		//			
		//		}

		//		if (prevID != id)
		//			prevID = id;

		//		al_draw_bitmap(tile.GetRaw(), drawX, drawY, 0);
		//		int sigh = 0;
		//		//al_draw_bitmap(
		//	}
		//}

		//for (int i = 0; i < 25; i++)
		//{
		//	for (int j = 25; j >= 0; j--)
		//	{// Changed loop condition here.
		//		const int dx = (j * GetTileWidth() / 2) + (i * GetTileWidth() / 2);
		//		const int dy = (i * GetTileHeight() / 2) - (j * GetTileHeight() / 2);

		//		int id = tilelayer->GetDataVal(i, j);
		//		if (id == 0)
		//			continue;
		//		if (id != prevID)
		//		{
		//			prevID = id;
		//			tile = LoadTile(id);


		//		}

		//		if (prevID != id)
		//			prevID = id;

		//		al_draw_bitmap(tile.GetRaw(), dx + 0, dy + 300, 0);	
		//	}
		//}


		//for (int y  = 1; y < 25; ++y)
		//{
		//	for (int x = 1; x < 25; ++x)
		//	{
		//		int drawX = ((x - y) * 32) + 300;
		//		int drawY = ((x + y) * 16);
		//		
		//		int id = tilelayer->GetDataVal(x, y);
		//		if (id == 0)
		//			continue;
		//		if (id != prevID)
		//		{
		//			prevID = id;
		//			tile = LoadTile(id);
		//			//tile.Load();
		//			//tile = Tiled::CTileset::LoadTile(GetTilesets(), id);
		//			
		//		}

		//		if (prevID != id)
		//			prevID = id;

		//		al_draw_bitmap(tile.GetRaw(), drawX, drawY, 0);
		//		int sigh = 0;
		//		//al_draw_bitmap(
		//	}
		//}



		//// Coordinates for the tile at the top left of the screen based on
		//// the current viewport's anchor coordinates.
		//float mTileCoordX = tlx / static_cast<int>(GetTileWidth()); 
		//float mTileCoordY = (tly / static_cast<int>(GetTileHeight())) * 2;

		//const float mOffsetY(64);
		//const float mOffsetX(64);

		//// Tile render offset from base position.
		//float mRenderOffsetX = -(static_cast<int>(tlx) % static_cast<int>(GetTileWidth()));
		//float mRenderOffsetY = -(static_cast<int>(tly) % static_cast<int>(GetTileHeight()));

		//int renderX = mRenderOffsetX, renderY = mRenderOffsetY - GetTileHeight();

		//// Loop through tile coordinates, pull out tile information from the Tileset and
		//// draw tiles to the screen.
		//for(int y = 0; y < endCol; y++)
		//{
		//	// Determine if we're on an odd row and if we are subtract a half tile width
		//	// to the X render offset.
		//	renderX = mRenderOffsetX - ((y & 1) * (GetTileWidth() / 2));

		//	for(int x = 0; x < endRow; x++)
		//	{
		//		//mRenderer->drawImage(image, renderX, renderY);
		//		///renderX += mOffsetX;

		//		int id = tilelayer->GetDataVal(x, y);
		//		if (id == 0)
		//			continue;
		//		if (id != prevID)
		//		{
		//			prevID = id;
		//			tile = LoadTile(id);
		//			//tile.Load();
		//			//tile = Tiled::CTileset::LoadTile(GetTilesets(), id);
		//			
		//		}

		//		if (prevID != id)
		//			prevID = id;
		//		if (tile)
		//			DrawBitmap(tile, VE::PixToMtr(b2Vec2(static_cast<float>(renderX), static_cast<float>(renderY))));
		//		renderY += mOffsetY;

		//	//	int dx = col * GetTileWidth();
		//	//	int dy = row * GetTileHeight();

		//	//	if (tile)
		//			//DrawBitmap(tile, VE::PixToMtr(b2Vec2(static_cast<float>(dx), static_cast<float>(dy))));
		//	}
		//	//renderY += mOffsetY;
		//}

		////for (int row = startRow; row < endRow; ++row)
		////{
		////	for (int col = startCol; col < endCol; ++col)
		////	{
		////		int id = tilelayer->GetDataVal(row, col);
		////		if (id == 0)
		////			continue;
		////		if (id != prevID)
		////		{
		////			prevID = id;
		////			tile = LoadTile(id);
		////			//tile.Load();
		////			//tile = Tiled::CTileset::LoadTile(GetTilesets(), id);
		////			
		////		}

		////		if (prevID != id)
		////			prevID = id;

		////		int dx = col * GetTileWidth();
		////		int dy = row * GetTileHeight();

		////		if (tile)
		////			DrawBitmap(tile, VE::PixToMtr(b2Vec2(static_cast<float>(dx), static_cast<float>(dy))));
		////	}
		////}
	}

	void CGameMap::RenderOrthogonal(VE::CRender* renderer, Tiled::CTileLayer* tilelayer)
	{
		const float tlx = renderer->Cam()->TopLeftPosPix().x;
		const float tly = renderer->Cam()->TopLeftPosPix().y;	

		VE::CBitmap tile;
		size_t prevID(0);

		const int startCol(static_cast<int>(tlx / GetTileWidth()));
		const int startRow(static_cast<int>(tly / GetTileHeight()));

		const int endCol = startCol + (VE::GetDisplayWidth() / GetTileWidth()) + 2; // +2 is buffer otherwise last col won't draw
		const int endRow = startRow + (VE::GetDisplayHeight() / GetTileHeight()) + 2; // +2 is buffer otherwise last row won't draw

		for (int row = startRow; row < endRow; ++row)
		{
			for (int col = startCol; col < endCol; ++col)
			{
				int id = tilelayer->GetDataVal(row, col);
				if (id == 0)
					continue;
				if (id != prevID)
				{
					prevID = id;
					tile = LoadTile(id);
					//tile.Load();
					//tile = Tiled::CTileset::LoadTile(GetTilesets(), id);
					
				}

				if (prevID != id)
					prevID = id;

				int dx = col * GetTileWidth();
				int dy = row * GetTileHeight();

				if (tile)
					DrawBitmap(tile, VE::PixToMtr(b2Vec2(static_cast<float>(dx), static_cast<float>(dy))));
			}
		}
	}

	void CGameMap::RenderIsometric(VE::CRender* renderer, Tiled::CTileLayer* tilelayer)
	{

	}

	bool CGameMap::Read(const luabind::object& data)
	{	
		if (!Tiled::CMapFile::Read(data))
			return false;

		std::for_each(GetTilesets().begin(), GetTilesets().end(), [&](Tiled::CTileset* tileset)
		{
			if (!tileset->Name().empty() && !tileset->Source().empty())
			{
				m_tilesetImages[tileset->Name()] = CBitmap("Images/Tilesets/" + tileset->Source());
				m_tilesetImages[tileset->Name()].Load();
			}
		});

		m_parser.Parse();
		return true;
	}

	bool CGameMap::Read(const std::string& filename)
	{
		if (!Tiled::CMapFile::Read(filename))
			return false;

		std::for_each(GetTilesets().begin(), GetTilesets().end(), [&](Tiled::CTileset* tileset)
		{
			if (!tileset->Name().empty() && !tileset->Source().empty())
			{
				m_tilesetImages[tileset->Name()] = CBitmap("Images/Tilesets/" + tileset->Source());
				m_tilesetImages[tileset->Name()].Load();
			}
		});

		m_parser.Parse();
		return true;
	}

	const CBitmap* CGameMap::GetTilesetImage(const std::string& name) const
	{
		auto iter = m_tilesetImages.find(name);
		if (iter != m_tilesetImages.end())
			return &iter->second;
		return nullptr;
	}

	void CGameMap::Render(VE::CRender* renderer,  size_t begin, size_t end)
	{
		for (size_t i = begin; (i < GetTileLayers().size()) && (i <= end); ++i)
			RenderLayer(renderer, GetTileLayers().at(i));
	}

	void CGameMap::Render(VE::CRender* renderer, const std::string& begin, const std::string& end)
	{
		auto iter = FindTileLayer(begin);
		auto endIter = FindTileLayer(end);

		for(;iter != endIter; ++iter)
			RenderLayer(renderer, *iter);
	}

	void CGameMap::Export(lua_State* L)
	{
		using namespace luabind;
		module(L)
			[
				class_<CGameMap, Tiled::CMapFile>("CGameMap")
			];
	}
}