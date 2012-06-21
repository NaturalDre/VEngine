#ifndef LUAERROR_H
#define LUAERROR_H

#include <exception>
#include <sstream>

class LuaError: public std::exception
{
protected:

public:
	LuaError(const std::string scriptFile = "Script Filename Not Provided.\n");
	const char* what(void) const;

	//std::stringstream& Error(void) { return m_error; }
private:
	std::string m_scriptFile;
	std::string m_error;
	//std::stringstream m_error;
};
#endif