#include "Utility.h"
#include <allegro5\allegro_native_dialog.h>
#include <physfs.h>

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

std::vector<char> FileToBuffer(const std::string filename)
{
	std::vector<char> buffer;

	if (!PHYSFS_exists(filename.c_str()))
		return buffer;

	PHYSFS_file* pFile = PHYSFS_openRead(filename.c_str());
	if(!pFile)
		return buffer;

	buffer.resize(PHYSFS_fileLength(pFile));
	PHYSFS_read(pFile, buffer.data(), 1, buffer.size());
	PHYSFS_close(pFile);
	pFile = nullptr;
	return std::move(buffer);
}