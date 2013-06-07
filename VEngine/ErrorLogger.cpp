#include "ErrorLogger.h"
#include "Engine.h"
#include "UIConsole.h"
#include <luabind\luabind.hpp>
#include <boost\lexical_cast.hpp>
#include <iostream>
#include <allegro5\altime.h>
#define vTOSTRING boost::lexical_cast<std::string>

namespace VE
{
	void vShowMessage(const std::string& message, const std::string& file, int line)
	{
		std::cout << std::endl << "[" << al_current_time() << "]\t" <<
		 " MSG: " << message << " FILE: " << file << " LINE: " << line << std::endl;
	}

	void CErrorLogger::Export(lua_State* L)
	{
		using namespace luabind;
		module(L)
			[
				def("vShowMessage", &vShowMessage)
			];
	}
}