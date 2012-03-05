#include "vengine\Image.h"
#include <map>

namespace VE
{
	struct ImageManager
	{
		// Does the manager have a weak_ptr by this filename?
		bool Contains(const std::string& filename) const
		{
			auto iter = m_bitmaps.find(filename);
			if (iter != m_bitmaps.end())
				return true;
			return false;
		}
		// List of pointers the manager keeps track of.
		std::map<const std::string, std::weak_ptr<ALLEGRO_BITMAP>> m_bitmaps;
	};

	// Return an instance of the image manager
	ImageManager& GetImgMgr(void) 
	{
		static ImageManager instance;
		return instance;
	}

	std::shared_ptr<ALLEGRO_BITMAP> LoadBitmap(const std::string& filename)
	{
		// Check if the manager has a pointer by this filename.
		if (GetImgMgr().Contains(filename))
		{	// If so, check if it's expired.
			std::weak_ptr<ALLEGRO_BITMAP>& bitmap = GetImgMgr().m_bitmaps[filename];
			if (!bitmap.expired())	// If not expired, convert it to a shared_ptr and return it
				return std::shared_ptr<ALLEGRO_BITMAP>(std::move(bitmap));
		}
		// If the manager does not have a pointer by the filename or it is expired, try loading it.
		std::shared_ptr<ALLEGRO_BITMAP> bitmap(al_load_bitmap(filename.c_str()), al_destroy_bitmap);
		GetImgMgr().m_bitmaps[filename] = bitmap;
		return std::move(bitmap);
	}

	void Detail::Image::Logic(void)
	{
		// Some fucking thing is preventing me from using std::remove_if so gotta do it this way.
		// Remove any expired pointers.
		for (auto iter = GetImgMgr().m_bitmaps.begin(); iter != GetImgMgr().m_bitmaps.end();)
		{
			if ((*iter).second.expired())
				iter = GetImgMgr().m_bitmaps.erase(iter);
			if (iter == GetImgMgr().m_bitmaps.end())
				break;
		}
	}
}