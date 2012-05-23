#include "Utility.h"
#include <allegro5\allegro_native_dialog.h>

void vWarning(const std::string& msg)
{
	al_show_native_message_box(al_get_current_display(), "Warning", "An error has occurred.", msg.c_str(), NULL, ALLEGRO_MESSAGEBOX_WARN);
}
ColRow GetColRow(size_t cols, size_t id)
{
	if (cols == 0)
		return ColRow();

	if (id % cols == 0)
		return ColRow(cols, id / cols);
	else
		return ColRow(id % cols, (static_cast<size_t>(id / cols) + 1));
}
