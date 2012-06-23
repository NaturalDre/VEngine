#include "Render.h"
#include "View.h"
#include "TMR\MapFile.h"
#include <algorithm>
#include <allegro5\allegro5.h>
#include "Physics.h"

namespace VE
{
	// Helper function to draw a tilelayer
	void RenderLayer(CRender* renderer, const Tiled::CMapFile& mf, Tiled::CTileLayer* layer);

	CRender::CRender(void)
		: m_mapFile(nullptr)
		, m_camera(nullptr)
		, m_physics(nullptr)
	{

	}

	CRender::~CRender(void)
	{

	}

	void CRender::AddView(IView* view)
	{
		if (view == nullptr)
			return;

		auto iter = std::find(m_views.begin(), m_views.end(), view);
		if (iter == m_views.end())
			m_views.push_back(view);
	}

	void CRender::RemoveView(IView* view)
	{
		auto iter = std::find(m_views.begin(), m_views.end(), view);
		if (iter != m_views.end())
			m_views.erase(iter);
	}

	void CRender::Render(void)
	{
		if (!m_camera)
			return;

		// Draw map
		if (m_mapFile)
		{
			auto layers = m_mapFile->TileLayers();
			for (auto iter = layers.begin(); iter != layers.end(); ++iter)
				RenderLayer(this, *m_mapFile, *iter);
		}

		std::sort(m_views.begin(), m_views.end(), [](IView* lhs, IView* rhs)
		{
			return lhs->DrawOrder() < rhs->DrawOrder();
		});

		for (auto iter = m_views.begin(); iter != m_views.end(); ++iter)
			(*iter)->Draw();

		if (m_physics)
			m_physics->World()->DrawDebugData();

		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));

	}

	void RenderLayer(CRender* renderer, const Tiled::CMapFile& mf, Tiled::CTileLayer* layer)
	{
		// Tile(sub bitmap)
		ALLEGRO_BITMAP* tile = nullptr;
		size_t prevID(0);

		// TO DO: Use the camera's top left as values for below variables instead of 0

		// Top left x and y position of the camera
		const float tlx = renderer->Cam()->TopLeftPosPix().x;
		const float tly = renderer->Cam()->TopLeftPosPix().y;	


		const int startCol(tlx / mf.TileWidth());
		const int startRow(tly / mf.TileHeight());

		const int endCol = (GetDisplayWidth() / mf.TileWidth()) + 2; // +2 is buffer otherwise last col won't draw
		const int endRow = (GetDisplayHeight() / mf.TileHeight()) + 2; // +2 is buffer otherwise last row won't draw

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

	size_t GetDisplayWidth(void)
	{
		return al_get_display_width(al_get_current_display());
	}

	size_t GetDisplayHeight(void)
	{
		return al_get_display_height(al_get_current_display());
	}
}