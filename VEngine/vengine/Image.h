#ifndef IMAGE_H
#define IMAGE_H

#include <allegro5\allegro5.h>
#include <memory>
#include <string>

namespace VE
{
	// Loads a bitmap and returns a shared_ptr to it. If you use this function
	// explicitly to load bitmaps there should never be 2 instances of the same bitmap.
	std::shared_ptr<ALLEGRO_BITMAP> LoadBitmap(const std::string& filename);
	
	// Don't touch
	namespace Detail
	{
		namespace Image
		{
			// Perform per-frame maintenance for the image pointers.
			void Logic(void);
		}
	}
}
#endif