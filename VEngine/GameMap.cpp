#include "GameMap.h"
#include "Render.h"
namespace VE
{
	CGameMap::CGameMap(void)
		: m_playerLayer(0)
	{

	}

	void CGameMap::RenderLayer(VE::CRender* renderer, Tiled::CTileLayer* tilelayer)
	{
		// FOr the sub bitmaps
		VE::CBitmap tile;
		size_t prevID(0);

		// Top left x and y position of the camera
		const float tlx = renderer->Cam()->TopLeftPosPix().x;
		const float tly = renderer->Cam()->TopLeftPosPix().y;	


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
					tile = Tiled::CTileset::LoadTile(GetTilesets(), id);
				}

				prevID = id;

				int dx = col * GetTileWidth();
				int dy = row * GetTileHeight();

				if (tile)
					DrawBitmap(tile, VE::PixToMtr(b2Vec2(static_cast<float>(dx), static_cast<float>(dy))));
			}
		}
	}

	void CGameMap::Render(VE::CRender* renderer,  size_t begin, size_t end)
	{
		for (size_t i = begin; (i < TileLayers().size()) && (i <= end); ++i)
			RenderLayer(renderer, TileLayers().at(i));
	}
}