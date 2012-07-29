#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>

struct lua_State;

#define vMin(a,b) ((a < b) ? a : b )
#define vMax(a,b) ((a > b) ? a : b )
#define vContains(val, min, max) ((val >= min) && (val <= max))

void ShowError(const std::string&);
#define vError ShowError

std::vector<char> BufferFile(const std::string& filename);
bool DoBuffer(lua_State* L, const std::vector<char>& buffer);
bool DoFile(lua_State* L, const std::string& filename);

struct ColRow 
{ 
	ColRow(size_t _col  = 0, size_t _row = 0): col(_col), row(_row) {} 
	size_t col, row; 
};

ColRow GetColRow(size_t cols, size_t id);
#endif