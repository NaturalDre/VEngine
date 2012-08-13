#include "Bitmap.h"
#include <allegro5\allegro5.h>
#include <list>
#include <algorithm>

#include "GameLevel.h"
#include "Render.h"

using namespace VE;

typedef std::list<std::weak_ptr<CBitmap>> SubBitmaps;

class CBitmap::Bitmap
{
public:
	Bitmap(const std::string& filename)
		: m_bitmap(nullptr)
	{
		m_bitmap = al_load_bitmap(filename.c_str());
	}

	Bitmap(const Bitmap& parent, size_t x, size_t y, size_t w, size_t h)
		: m_bitmap(nullptr)
	{
		m_bitmap = al_create_sub_bitmap(parent.Raw(), x, y, w, h);
	}

	Bitmap(ALLEGRO_BITMAP* bitmap)
		: m_bitmap(nullptr)
	{
		assert(bitmap != nullptr);
		m_bitmap = bitmap;
	}

	Bitmap::Bitmap(const Bitmap& rhs)
		: m_bitmap(nullptr)
	{
		*this = rhs;
	}

	Bitmap::Bitmap(Bitmap&& rhs)
	{
		*this = std::move(rhs);
	}

	~Bitmap(void)
	{
		al_destroy_bitmap(m_bitmap);
		m_bitmap = nullptr;
	}

	const Bitmap& operator=(const Bitmap& rhs)
	{
		if (this == &rhs)
			return *this;

		al_destroy_bitmap(m_bitmap);
		m_bitmap = al_clone_bitmap(rhs.m_bitmap);
		return *this;
	}

	const Bitmap& operator=(Bitmap&& rhs)
	{
		if (this == &rhs)
			return *this;
		al_destroy_bitmap(m_bitmap);
		m_bitmap = rhs.m_bitmap;
		rhs.m_bitmap = nullptr;
		return *this;
	}

	bool IsValid(void) const { return (m_bitmap ? true : false); }
	ALLEGRO_BITMAP* Raw(void) const { return m_bitmap; }

	size_t GetWidth(void) const { if (IsValid()) return al_get_bitmap_width(m_bitmap); return 0; }
	size_t GetHeight(void) const { if(IsValid()) return al_get_bitmap_height(m_bitmap); return 0; }
	bool IsSubBitmap(void) const { if (IsValid()) return al_is_sub_bitmap(m_bitmap); return false; }
	bool IsLocked(void) const { if (IsValid()) return al_is_bitmap_locked(m_bitmap); return false; }
	int GetFlags(void) const { if (IsValid()) return al_get_bitmap_flags(m_bitmap); return false; }
	int GetFormat(void) const { if (IsValid()) return al_get_bitmap_format(m_bitmap); return false; }
	void ConvertMaskToAlpha(size_t r, size_t g, size_t b) { if (IsValid()) al_convert_mask_to_alpha(m_bitmap, al_map_rgb(r,g,b));}

	void Reset(void)
	{
		al_destroy_bitmap(m_bitmap);
		m_bitmap = nullptr;
	}

private:
	ALLEGRO_BITMAP* m_bitmap;
};

CBitmap::CBitmap(const std::string& filename)
	: d(new Bitmap(filename))
{

}

CBitmap::CBitmap(const CBitmap& parent, size_t x, size_t y, size_t w, size_t h)
	: d(nullptr)
{
	d = new Bitmap(*parent.d, x, y, w, h);
}

CBitmap::CBitmap(ALLEGRO_BITMAP* bitmap)
	: d(nullptr)
{
	d = new Bitmap(bitmap);
}

CBitmap::CBitmap(const CBitmap& rhs)
	: d(nullptr)
{
	d = new Bitmap("");
	*this = rhs;
}

CBitmap::CBitmap(CBitmap&& rhs)
	: d(nullptr)
{
	d = new Bitmap("");
	*this = std::move(rhs);
}

CBitmap::~CBitmap(void)
{
	delete d;
	d = nullptr;
}

const CBitmap& CBitmap::operator=(const CBitmap& rhs)
{
	if (this == &rhs)
		return *this;
	(*d) = (*rhs.d);
	return *this;
}

const CBitmap& CBitmap::operator=(CBitmap&& rhs)
{
	if (this == &rhs)
		*this;
	(*d) = std::move(*rhs.d);
	return *this;
}

void CBitmap::Reset(void) { d->Reset(); }
bool CBitmap::IsValid(void) const { return d->IsValid(); }
ALLEGRO_BITMAP* CBitmap::GetRaw(void) const { return d->Raw(); }
size_t CBitmap::GetWidth(void) const { return d->GetWidth();}
size_t CBitmap::GetHeight(void) const { return d->GetHeight(); }
bool CBitmap::IsSubBitmap(void) const { return d->IsSubBitmap(); }
bool CBitmap::IsLocked(void) const { return d->IsLocked(); }
int CBitmap::GetFlags(void) const { return d->GetFlags(); }
int CBitmap::GetFormat(void) const { return d->GetFormat(); }
void CBitmap::ConvertMaskToAlpha(size_t r, size_t g, size_t b) { d->ConvertMaskToAlpha(r,g,b); }

namespace VE
{
	bool IsDrawable(const CBitmap& bitmap, b2Vec2 bitmapPos, b2Vec2 bitmapCPos)
	{
		if (!bitmap.IsValid())
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
		if (!bitmap.IsValid())
			return;
		if (!VE::IsDrawable(bitmap, dpos))// Is the position to be drawn at out of view of the camera?
			return;												// If so, don't waste CPU time drawing it.

		dpos = MtrToPix(dpos);		// Meters->Pixels

		b2Vec2 drawPos(GameToScreenPosPix(GameLevel()->GetRenderer()->Cam(), dpos));
		al_draw_bitmap(bitmap.GetRaw(), drawPos.x, drawPos.y, flags);
	}

	void DrawBitmap(const CBitmap& bitmap, b2Vec2 dpos, b2Vec2 cpos, float angle, int flags)
	{
		if (!bitmap.IsValid())
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