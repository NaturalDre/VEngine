#include "Tileset.h"
#include <lauxlib.h>
#include <assert.h>
#include "TiledLua.h"
#include <allegro5\allegro5.h>
#include "..\Utility.h"

using namespace Tiled;

CTileset::CTileset(void)
{

}

CTileset::~CTileset(void)
{
	//al_destroy_bitmap(m_image);
	//m_image = nullptr;
}

void CTileset::ReadMapFile(lua_State* L, size_t index)
{
	m_firstGid = GetTilesetFirstGid(index, L);
	m_tileWidth = GetTilesetTileWidth(index, L);
	m_tileHeight = GetTilesetTileHeight(index, L);
	m_source = GetTilesetImage(index, L);
	m_imageWidth = GetTilesetImgW(index, L);
	m_imageHeight = GetTilesetImgH(index, L);
	m_trans = GetTilesetTrans(index, L);
	m_spacing = GetTilesetSpacing(index, L);
	m_name = GetTilesetName(index, L);
	m_tileWidth = GetTilesetTileWidth(index, L);
	m_tileHeight = GetTilesetTileHeight(index, L);

	if (m_tileWidth == 0)
		throw("A tileset's tileWidth MUST NOT be zero");
	if (m_tileHeight == 0)
		throw("A tileset's tileHeight MUST NOT be zero");

	m_tilesAcross = m_imageWidth / (m_tileWidth + m_spacing);
	assert((m_tileHeight + m_spacing));
	m_tilesDown = m_imageHeight / (m_tileHeight + m_spacing);
	m_lastGid = m_firstGid + (((m_imageWidth / (m_tileWidth + m_spacing)) * (m_imageHeight / (m_tileHeight + m_spacing)))-1);

	m_image = VE::CBitmap(al_load_bitmap(m_source.c_str()));
}

CTileset* CTileset::ContainsGid(const std::list<CTileset*>& tilesets, size_t id)
{
	for (auto iter = tilesets.begin(); iter != tilesets.end(); ++iter)
	{
		if ((*iter)->ContainsGid(id))
			return *iter;
	}
	return nullptr;
}

VE::CBitmap CTileset::LoadTile(const std::list<CTileset*>& tilesets, size_t id)
{
	CTileset* ts = ContainsGid(tilesets, id);
	if(!ts || !ts->GetImage().IsValid())
		return VE::CBitmap();

	ColRow  cr = GetColRow(ts->TilesAcross(), id);

	return std::move(VE::CBitmap(ts->GetImage(), 
		(cr.col - 1) * (ts->ImageWidth() + ts->Spacing()),
		(cr.row - 1) * (ts->ImageHeight() + ts->Spacing()),
		ts->TileWidth(),
		ts->TileHeight()));
}