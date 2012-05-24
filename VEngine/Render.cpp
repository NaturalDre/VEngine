#include "Render.h"
#include "Utility.h"
#include "ObjectView.h"
#include "Application.h"
#include <assert.h>
#include <algorithm>
#include <allegro5\allegro5.h>

// Helper function to draw a tilelayer
void RenderLayer(const Tiled::CMapFile& mf, Tiled::CTileLayer* layer);


namespace VE
{
	CRender* render = nullptr;

	CRender::CRender(void)
	{
		m_playerLayer = 0;
		m_camera = new CCamera;
	}

	void CRender::DrawScene(void)
	{
		// The map file; Contains all info on how to the map is structured
		const Tiled::CMapFile& mapFile = App()->GetMap();
		// List of all the TileLayers in the map file.
		auto layers = App()->GetMap().TileLayers();
		// We go through all the layers and draw them in order(bottom layer is first in the list)
		for (auto iter = layers.begin(); iter != layers.end(); ++iter)
		{
			// Draw the layer
			RenderLayer(mapFile, *iter);
		}
		
		
		BOOST_FOREACH(IObjectView* view, m_views)
		{
			view->Draw();
		}

		World()->DrawDebugData();
	}

	CRender* Renderer(void)
	{
		assert(App() != nullptr);
		if (!render)
			render = new CRender;
		return render;
	}
}

void RenderLayer(const Tiled::CMapFile& mf, Tiled::CTileLayer* layer)
{
	// Tile(sub bitmap)
	ALLEGRO_BITMAP* tile = nullptr;
	size_t prevID(0);

	// TO DO: Use the camera's top left as values for below variables instead of 0

	// Top left x and y position of the camera
	const float tlx = VE::Renderer()->Cam()->TopLeftPosPix().x;
	const float tly = VE::Renderer()->Cam()->TopLeftPosPix().y;	


	const int startCol(tlx / mf.TileWidth());
	const int startRow(tly / mf.TileHeight());



	const int endCol = (VE::GetDisplayWidth() / mf.TileWidth()) + 2; // +2 is buffer otherwise last col won't draw
	const int endRow = (VE::GetDisplayHeight() / mf.TileHeight()) + 2; // +2 is buffer otherwise last row won't draw

	for (int row = startRow; row < endRow; ++row)
	{
		for (int col = startCol; col < endCol; ++col)
		{
			int id = layer->GetDataVal(row, col);
			if (id == 0)
				continue;
			if (id != prevID)
			{
				if (tile)
				{
					al_destroy_bitmap(tile);
					tile = nullptr;
				}
				prevID = id;
				tile = Tiled::CTileset::LoadTile(mf.Tilesets(), id);
			}
			//if (tile)
			//	al_draw_bitmap(tile, (col -1) * mf.GetTileWidth(), (row - 1) * mf.GetTileHeight(), 0);

			prevID = id;

			float dx = col * mf.TileWidth();
			float dy = row * mf.TileHeight();

			dx -= tlx;
			dy -= tly;
			
			if (tile)
				al_draw_bitmap(tile, dx, dy, 0);
		}
	}

	if (tile)
	{
		al_destroy_bitmap(tile);
		tile = nullptr;
	}
}