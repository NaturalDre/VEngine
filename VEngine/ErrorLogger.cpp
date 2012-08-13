#include "ErrorLogger.h"
#include "Engine.h"
#include "UIConsole.h"

#include <boost\lexical_cast.hpp>
#include <iostream>
#include <allegro5\altime.h>
#define vTOSTRING boost::lexical_cast<std::string>

namespace VE
{
	CErrorLogger::CErrorLogger(CEngine* engine)
		: m_engine(engine)
	{

	}

	CErrorLogger::~CErrorLogger(void)
	{
		m_engine = nullptr;
	}

	void CErrorLogger::LogType(double time, const std::string& error, const std::string& type)
	{
		m_errors.push(type +": [" + vTOSTRING(time) + "] " + error);
		if (m_engine && m_engine->GetConsole())
			m_engine->GetConsole()->AddToList(m_errors.back());
		//std::cerr << m_errors.back();
	}

	void CErrorLogger::LogError(const std::string& error) { LogType(al_get_time(), error, "Error"); }
	void CErrorLogger::LogNote(const std::string& error) { LogType(al_get_time(), error, "Note"); }
}