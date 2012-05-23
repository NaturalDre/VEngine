#include "BoxView.h"
#include <allegro5\allegro5.h>

BoxView::BoxView(void)
{

}

void BoxView::Draw(void)
{
	ALLEGRO_BITMAP* bitmap = al_load_bitmap("box.png");
	al_draw_bitmap(bitmap, 100, 100, 0);
	al_destroy_bitmap(bitmap);

}