#include "LuaError.h"
#include <boost\lexical_cast.hpp>

LuaError::LuaError(const std::string scriptFile)
{
	//m_error << "LUAERROR: " << scriptFile;
}

const char* LuaError::what(void) const
{
	return "LuaError";
	//return m_error.str().c_str();
}