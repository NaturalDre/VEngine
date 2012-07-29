#ifndef ERRORLOGGER_H
#define ERRORLOGGER_H

#include <sstream>
#include <string>
#include <queue>
namespace VE
{
	class CErrorLogger
	{
	protected:
		void LogType(double time, const std::string& text, const std::string& type);
	public:
		void LogError(const std::string& error);
		void LogNote(const std::string& error);
	private:
		std::queue<const std::string> m_errors;
	};
}

#endif