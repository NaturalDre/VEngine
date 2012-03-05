#ifndef LAYERDATATYPES_H
#define LAYERDATATYPES_H

#include <allegro5\allegro5.h>

namespace VE
{
	struct SheetData
	{
	public:
		size_t firstGid;
		size_t lastGid;
		size_t tileWidth;
		size_t tileHeight;
		size_t gridElementsW;
		size_t gridElementsH;
		size_t imgWidth;
		size_t imgHeight;
		size_t spacing;
		ALLEGRO_COLOR trans;
		std::shared_ptr<ALLEGRO_BITMAP> image;
		std::string name;

		SheetData(void): firstGid(0), lastGid(0), tileWidth(0), tileHeight(0), imgWidth(0), imgHeight(0), spacing(0), trans()/*, image(NULL)*/, name(""){}
	};

	struct LayerSize
	{
		size_t gridElementsW;
		size_t gridElementsH;
		size_t tileWidth;
		size_t tileHeight;
	};
}
#endif