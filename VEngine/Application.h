#ifndef APPLICATION_H
#define APPLICATION_H

struct lua_State;

namespace VE 
{
	class CEngine;
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
		lua_State* m_L;
		CGameLevelController* m_controller;
	};
}

#endif