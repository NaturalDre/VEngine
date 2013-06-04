#include "GameMapView.h"
#include "Locator.h"
#include "Render.h"
#include "Common.h"

namespace VE
{
	CGameMapView::CGameMapView(CGameMap* map, size_t begin, size_t end)
		: IView(-10)
		, m_gameMap(map)
		, m_begin(begin)
		, m_end(end)
	{

	}

	CGameMapView::~CGameMapView(void)
	{

	}

	void CGameMapView::Draw(void)
	{
		for (size_t i = m_begin; (i < GetGameMap()->GetTileLayers().size()) && (i <= m_end); ++i)
			RenderLayer(GetGameMap()->GetTileLayers().at(i));
	}
	void CGameMapView::RenderLayer(Tiled::CTileLayer* tilelayer)
	{
		// Top left x and y position of the camera
		const float tlx = CLocator::GetRenderer()->GetCamera()->TopLeftPosPix().x;
		const float tly = CLocator::GetRenderer()->GetCamera()->TopLeftPosPix().y;	

		if (GetGameMap()->GetOrientation() == "orthogonal")
			RenderOrthogonal(tilelayer);
		else if (GetGameMap()->GetOrientation() == "isometric")
			RenderIsometric(tilelayer);
		else
			return;
	}

	void CGameMapView::RenderOrthogonal(Tiled::CTileLayer* tilelayer)
	{
		const float tlx = CLocator::GetRenderer()->GetCamera()->TopLeftPosPix().x;
		const float tly = CLocator::GetRenderer()->GetCamera()->TopLeftPosPix().y;	

		std::shared_ptr<CBitmap> tile = nullptr;
		size_t prevID(0);

		const int startCol(static_cast<int>(tlx / GetGameMap()->GetTileWidth()));
		const int startRow(static_cast<int>(tly / GetGameMap()->GetTileHeight()));

		const int endCol = startCol + (VE::GetDisplayWidth() / GetGameMap()->GetTileWidth()) + 2; // +2 is buffer otherwise last col won't draw
		const int endRow = startRow + (VE::GetDisplayHeight() / GetGameMap()->GetTileHeight()) + 2; // +2 is buffer otherwise last row won't draw

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
				}

				if (prevID != id)
					prevID = id;

				int dx = col * GetGameMap()->GetTileWidth();
				int dy = row * GetGameMap()->GetTileHeight();

				if (tile)
					DrawBitmap(*tile, VE::PixToMtr(b2Vec2(static_cast<float>(dx), static_cast<float>(dy))));
			}
		}
	}

	void CGameMapView::RenderIsometric(Tiled::CTileLayer* tilelayer)
	{

	}

	std::shared_ptr<CBitmap> CGameMapView::LoadTile(const size_t id)
	{
		Tiled::CTileset* ts = Tiled::CTileset::ContainsGid(GetGameMap()->GetTilesets(), id);
		if (!ts)
			return nullptr;

		const std::shared_ptr<CBitmap> image = GetGameMap()->GetTilesetImage(ts->Name());

		if (!image)
			return nullptr;

		const ColRow  cr = GetColRow(ts->TilesAcross(), (id - ts->FirstGid()) + 1);

		std::shared_ptr<CBitmap> bitmap = CreateBitmap(image, 
			(cr.col - 1) * (ts->ImageWidth() + ts->Spacing()),
			(cr.row - 1) * (ts->ImageHeight() + ts->Spacing()),
			ts->TileWidth(),
			ts->TileHeight());

		return std::move(bitmap);
	}
}