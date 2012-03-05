#include <vengine\Level\Tilelayer.h>
#include <vengine\Utility.h>
#include <vengine\Image.h>
#include <vengine\Render\Render.h>

namespace VE
{
	CTilelayer::CTilelayer(const size_t layerElement, lua_State* L, const std::list<SheetData>& sheets, const LayerSize& layerSize)
		: m_layerSize(layerSize)
		, m_sheets(sheets)
	{
		GatherData(layerElement, L);
	}

	CTilelayer::~CTilelayer(void)
	{

	}

	void CTilelayer::draw(void)
	{
		//std::unique_ptr<ALLEGRO_BITMAP, Utility::AlBitmapDel> canvas;
		
		//canvas.reset(al_create_bitmap(GetRenderMgr().GetCam()->GetWidthPix(), GetRenderMgr().GetCam()->GetHeightPix()));

		// Get the first tile's row and column
		const int col = GetRenderMgr().GetCam()->GetTopLeftPix().x / m_layerSize.tileWidth;
		const int row = GetRenderMgr().GetCam()->GetTopLeftPix().y / m_layerSize.tileHeight;
		// How many tiles can we draw in each direction before reaching the edge of the screen? The addition at the end if an offset so it doesn't end too early.
		const int MAXCOL = col + (GetRenderMgr().GetCam()->GetWidthPix()  / m_layerSize.tileWidth) + 3;
		const int MAXROW = row + (GetRenderMgr().GetCam()->GetHeightPix() / m_layerSize.tileHeight) + 3;

		// Will hold the sub bitmaps that we will be drawing. Declared here instead of loop for performance reasons
		std::unique_ptr<ALLEGRO_BITMAP, Utility::AlBitmapDel> sub;
		// The last ID we had to draw.
		int prevID(0);

		// Improves performance when drawing lots of the same bitmaps frequently.
		al_hold_bitmap_drawing(true);

		for (int curRow(row); curRow < static_cast<int>(m_mapElements.size()) && curRow < MAXROW; ++curRow)
		{
			// Tiled Map Editor starts at (0,0). It's impossible that anything is below that.
			if (curRow < 0)
				continue;
			for (int curCol(col); curCol < static_cast<int>(m_mapElements[curRow].size()) && curCol < MAXCOL; ++curCol)
			{
				// Tiled Map Editor starts at (0,0). It's impossible that anything is below that.
				if (curCol < 0)
				{
					curCol = -1;
					continue;
				}
				// The ID is the numerical representation of a tile
				int id = m_mapElements[curRow][curCol];
				// An ID of zero means there's nothing to draw.
				if (!id)
					continue;
				// The tileset that contains this id's tile TO DO: Try to make getSheet more efficient
				const SheetData& data = getSheet(id, m_sheets);
				// This is to help performance a bit. If this ID is the same as the one before
				// then sub also has that bitmap loaded and we don't need to reload it.
				if (prevID != id)
				{
					prevID = id;
					sub.reset(createTileSubBitmap(&data, id));
				}

				{
					// Calculate the world position of the tiles top left pixel
					int x = curCol * m_layerSize.tileWidth;
					int y = curRow * m_layerSize.tileHeight;

					// Convert the world coordinates to screen coordinates
					x -= GetRenderMgr().GetCam()->GetTopLeftPix().x;
					y -= GetRenderMgr().GetCam()->GetTopLeftPix().y;

					// Draw to screen
					al_draw_bitmap(sub.get(), x,y,0);
				}
			}
		}
		// We're not drawign lots of similar bitmaps
		al_hold_bitmap_drawing(false);
	}

	const SheetData& CTilelayer::getSheet(const size_t _gid, const std::list<SheetData>& _sheets)
	{
		for (auto iter = _sheets.begin(); iter != _sheets.end(); ++iter)
		{
			if (_gid >= (*iter).firstGid && _gid <= (*iter).lastGid)
				return (*iter);
		}
		throw(std::exception("Bad ID passed to GetSheet"));
	}

	void CTilelayer::GatherData(size_t layerElement, lua_State* L)
	{

		m_mapElements.resize(m_layerSize.gridElementsH, std::vector<size_t>(m_layerSize.gridElementsW, 0));
		for (size_t row = 0, luaElement = 1; row < m_layerSize.gridElementsH; ++row)
		{
			for (size_t col = 0; col < m_layerSize.gridElementsW; ++col)
				m_mapElements[row][col] = GetLayerDataValue(layerElement, luaElement++, L);
		}
	}

	ALLEGRO_BITMAP* CTilelayer::construct(size_t layerElement, lua_State* L, const std::list<SheetData>& _sheets, const LayerSize& _mapData)
	{
		//// The layer
		//LuaObject layerObj = GetLayerObject(layerElement, mapfile);
		//assert(layerObj.IsTable() != false);
		//// The data table/array. Each id in an element corresponding to a tile from a tilesheet.
		//LuaObject dataObj = layerObj.GetByName("data");
		//assert(layerObj.IsTable() != false);

		// Create a bitmap to begin drawing the map on that fits the map
		ALLEGRO_BITMAP* canvas(al_create_bitmap(m_layerSize.gridElementsW * m_layerSize.tileWidth, m_layerSize.gridElementsH * m_layerSize.tileHeight));

		al_set_target_bitmap(canvas);
		CLEARTOBLACK;
		al_convert_mask_to_alpha(canvas, BLACK);
		al_hold_bitmap_drawing(true);

		// Each tile is a subbitmap of a tilesheet. We keep this point to the last created
		// subbitmap. If the previous ID is the same as the current ID in the following for loop
		// then we don't need to find a load a new tile bitmap as this pointer already points to it.
		std::unique_ptr<ALLEGRO_BITMAP, Utility::AlBitmapDel> subBitmap(nullptr);

		// Last ID to be drawn. Only a non-zero number will ever be assigned here in the for loop.
		size_t prevID(0);

		for (
			size_t i = 1, ID = GetLayerDataValue(layerElement, i, L); 
			i <= GetLayerDataSize(layerElement, L); 
		++i, ID = GetLayerDataValue(layerElement, i, L))
		{
			// If the ID is zero then there's nothing to draw in this tile.
			if (!ID)
				continue;
			// Since we have a valid ID, find the sheet that holds this ID.
			const VE::SheetData& data = getSheet(ID, _sheets);
			// If the ID is not the same as the previous ID
			// We need to load the new ID's bitmap.
			if (prevID != ID)
			{
				prevID = ID;
				subBitmap.reset(createTileSubBitmap(&data, ID));
			}
			// Find the row and column that we are to draw to.
			b2Vec2 rc = Utility::GetColRow(m_layerSize.gridElementsW, i);
			// Do the math to translate the row/col to pixel coordinates of its top left
			b2Vec2 drawPos((rc.x-1) * m_layerSize.tileWidth, (rc.y-1) * m_layerSize.tileHeight);
			al_draw_bitmap(subBitmap.get(), drawPos.x, drawPos.y, 0);
		}

		al_hold_bitmap_drawing(false);
		al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
		return canvas;
	}

	ALLEGRO_BITMAP* VE::CTilelayer::createTileSubBitmap(const VE::SheetData* data, const size_t id)
	{
		b2Vec2 pos = VE::Utility::GetColRow(data->gridElementsW, (id - data->firstGid) + 1);
		if (!data->image)
			throw(std::exception("Empty pointer in SheetData for image."));
		return al_create_sub_bitmap(
			data->image.get(),
			(pos.x - 1) * (data->tileWidth + data->spacing),
			(pos.y - 1) * (data->tileHeight + data->spacing),
			data->tileWidth,
			data->tileHeight);
	}

	size_t CTilelayer::GetLayerDataValue(size_t layer, size_t index, lua_State* L)
	{
		assert(L != nullptr);

		lua_getglobal(L, "GetLayerDataVal");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			throw(std::exception("Could not get function GetLayerDataVal"));
		}
		// STK: func
		lua_pushinteger(L, layer);
		lua_pushinteger(L, index);
		// STK: func int int
		if (lua_pcall(L, 2, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if(!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int val = lua_tointeger(L, -1);
		lua_pop(L, 1);
		// STK:
		return val;
	}

	size_t CTilelayer::GetLayerDataSize(size_t layer, lua_State* L)
	{
		assert(L != nullptr);

		lua_getglobal(L, "GetLayerDataSize");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: func
		lua_pushinteger(L, layer);
		// STK: func int
		if (lua_pcall(L, 1, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if (!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int val = lua_tointeger(L, -1);
		lua_pop(L, 1);
		return val;
	}
}