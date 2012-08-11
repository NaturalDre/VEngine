#include "Utility.h"
#include <allegro5\allegro_native_dialog.h>
#include <physfs.h>
#include <lua.hpp>
#include <lauxlib.h>
void vWarning(const std::string& msg)
{
	al_show_native_message_box(al_get_current_display(), "Warning", "An error has occurred.", msg.c_str(), NULL, ALLEGRO_MESSAGEBOX_WARN);
	__asm 
	{ 
		int 3; 
	}
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

std::vector<char> BufferFile(const std::string& filename)
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

bool DoBuffer(lua_State* L, const std::vector<char>& buffer)
{
	// Non-zero from luaL_loadbuffer is error.
	if(!buffer.empty() && !luaL_loadbuffer(L, buffer.data(), buffer.size(), nullptr))
	{
		lua_pcall(L, 0, 0, 0);
		return true;
	}
	return false;
}

bool DoFile(lua_State* L, const std::string& filename)
{
	return DoBuffer(L, BufferFile(filename));
}

int GenerateEventID(char a, char b, char c, char d)
{
	return ALLEGRO_GET_EVENT_TYPE(a,b,c,d);
}