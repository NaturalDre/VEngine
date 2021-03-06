#ifndef ERRORLOGGER_H
#define ERRORLOGGER_H

#include <sstream>
#include <string>
#include <queue>

struct lua_State;

namespace VE
{
	class CEngine;
	class CErrorLogger
	{
	protected:
		void LogType(double time, const std::string& text, const std::string& type);
	public:
		CErrorLogger(CEngine* engine = nullptr);
		~CErrorLogger(void);

		void LogError(const std::string& error);
		void LogNote(const std::string& error);

		inline void SetEngine(CEngine* engine) { m_engine = engine; }

		static void Export(lua_State* L);
	private:
		CEngine* m_engine;
		std::queue<const std::string> m_errors;
	};
}

#endif