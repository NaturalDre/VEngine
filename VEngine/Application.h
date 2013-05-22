#ifndef APPLICATION_H
#define APPLICATION_H

#include "ErrorLogger.h"

struct lua_State;

namespace VE 
{
	class CEngine;
	class CGameLevel;
	class CGameLevelController;
	class CApplication
	{
	protected:
		void Init(void);
		void SetupScriptEnv(void);
		
		void SetupDirectories(void);

	public:
		CApplication(void);
		~CApplication(void);

		int Run(void);
	private:
		CEngine* m_engine;
		CGameLevel* m_gameLevel;
	};
}

#endif