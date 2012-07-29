#include "ErrorLogger.h"
#include <boost\lexical_cast.hpp>
#include <iostream>
#include <allegro5\altime.h>
#define vTOSTRING boost::lexical_cast<std::string>

namespace VE
{
	void CErrorLogger::LogType(double time, const std::string& error, const std::string& type)
	{
		m_errors.push("\n"+ type +": [" + vTOSTRING(time) + "]\t" + error);
		std::cerr << m_errors.back();
	}

	void CErrorLogger::LogError(const std::string& error) { LogType(al_get_time(), error, "Error"); }
	void CErrorLogger::LogNote(const std::string& error) { LogType(al_get_time(), error, "Note"); }
}