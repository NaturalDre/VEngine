#include "Bitmap.h"
#include "GameLevel.h"
#include "Render.h"
#include <luabind\luabind.hpp>
#include <allegro5\allegro5.h>
#include <list>
#include <algorithm>

using namespace VE;

typedef std::list<std::weak_ptr<CBitmap>> SubBitmaps;

CBitmap::CBitmap(const std::string& filename, size_t scene)
	: IAsset(filename, IAsset::GRAPHICAL, scene) 
	, m_data(nullptr)
{

}

CBitmap::CBitmap(const std::shared_ptr<CBitmap>& parent, size_t x, size_t y, size_t w, size_t h)
	: IAsset(parent->GetFilename(), IAsset::GRAPHICAL, -1)
	, m_data(nullptr)
{
	if (parent->IsLoaded())
	{
		m_data = al_create_sub_bitmap(parent->GetRaw(), x, y, w, h);
		SetLoaded(true);
	}
}

CBitmap::CBitmap(ALLEGRO_BITMAP* bitmap)
	: IAsset("", IAsset::GRAPHICAL, -1)
	, m_data(bitmap)
{
	assert(bitmap != nullptr);
}

CBitmap::~CBitmap(void)
{
	Unload();
}

ALLEGRO_BITMAP* CBitmap::GetRaw(void) const { return m_data; }

size_t CBitmap::GetWidth(void) const { if (IsLoaded()) return al_get_bitmap_width(m_data); return 0; }
size_t CBitmap::GetHeight(void) const { if(IsLoaded()) return al_get_bitmap_height(m_data); return 0; }
bool CBitmap::IsSubBitmap(void) const { if (IsLoaded()) return al_is_sub_bitmap(m_data); return false; }
bool CBitmap::IsLocked(void) const { if (IsLoaded()) return al_is_bitmap_locked(m_data); return false; }
int CBitmap::GetFlags(void) const { if (IsLoaded()) return al_get_bitmap_flags(m_data); return false; }
int CBitmap::GetFormat(void) const { if (IsLoaded()) return al_get_bitmap_format(m_data); return false; }
void CBitmap::ConvertMaskToAlpha(size_t r, size_t g, size_t b) { if (IsLoaded()) al_convert_mask_to_alpha(m_data, al_map_rgb(r,g,b));}

void CBitmap::OnLoad(void)
{
	if (IsLoaded())
		Unload();
	if (!GetFilename().empty())
		m_data = al_load_bitmap(GetFilename().c_str());
	if (m_data)
		SetLoaded(true);
}

void CBitmap::OnUnload(void)
{
	if (IsLoaded())
	{
		al_destroy_bitmap(m_data);
		m_data = nullptr;
		SetLoaded(false);
	}
}

namespace VE
{
	bool IsDrawable(const CBitmap& bitmap, b2Vec2 bitmapPos, b2Vec2 bitmapCPos)
	{
		if (!bitmap.IsLoaded())
			return false;

		CCamera* cam = GameLevel()->GetRenderer()->Cam();

		b2Vec2 camTopL = cam->TopLeftPosPix();
		// Copy the vector then add it's with and height to get its bottom right
		b2Vec2 camBotR(camTopL);
		camBotR.x += cam->Width();
		camBotR.y += cam->Height();

		// Convert to pix
		bitmapPos = MtrToPix(bitmapPos);
		bitmapPos -= bitmapCPos;
		float bitmapWidth(bitmap.GetWidth());
		float bitmapHeight(bitmap.GetHeight());

		if (													// If none of the below statements are true then the bitmap is within view of the camera.
			(bitmapPos.x > (camBotR.x - 1))		||	// Is the left side of the bitmap to the right of the camera?
			((bitmapPos.x + bitmapWidth - 1) < camTopL.x)	||	// Is the right side of the bitmap to the left side of the camera?
			(bitmapPos.y > (camBotR.y - 1))		||	// Is the top of the bitmap below the camera?
			(bitmapPos.y + bitmapHeight - 1) < camTopL.y)		// Is the bottom of the bitmap above the camera?
			return false;

		return true;
	}

	void DrawBitmap(const CBitmap& bitmap, b2Vec2 dpos, int flags)
	{
		if (!bitmap.IsLoaded())
			return;
		if (!VE::IsDrawable(bitmap, dpos))// Is the position to be drawn at out of view of the camera?
			return;												// If so, don't waste CPU time drawing it.

		dpos = MtrToPix(dpos);		// Meters->Pixels

		b2Vec2 drawPos(GameToScreenPosPix(GameLevel()->GetRenderer()->Cam(), dpos));
		al_draw_bitmap(bitmap.GetRaw(), drawPos.x, drawPos.y, flags);
	}

	void DrawBitmap(const CBitmap& bitmap, b2Vec2 dpos, b2Vec2 cpos, float angle, int flags)
	{
		if (!bitmap.IsLoaded())
			return;
		// Is the position to be drawn at out of view of the camera?
		// If so, don't waste CPU time drawing it.
		if (!VE::IsDrawable(bitmap, dpos))
			return;												

		// We need to convert the positions to pixels 'cause that's
		// what Allegro works with.
		dpos = MtrToPix(dpos);
		cpos = MtrToPix(cpos);

		// Where on the user's screen is the position at?
		b2Vec2 drawPos(GameToScreenPosPix(GameLevel()->GetRenderer()->Cam(), dpos));

		// Box2D considers the center (0,0), not the top left, so
		// we need to do some conversating when providing the center position
		// to Allegro.
		al_draw_rotated_bitmap(bitmap.GetRaw(), 
			(bitmap.GetWidth() / 2.0f) + cpos.x,
			(bitmap.GetHeight() / 2.0f) + cpos.y, drawPos.x, drawPos.y, angle, flags);
	}


}