#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

namespace VE
{
	class IGUIBase;

	enum GAMESTATE
	{ 
		MAINMENU
		, GAMEPAUSED
		, GAMEINPROGRESS
	};
}

namespace VE
{
	class CApplication
	{
	protected:
		CApplication(void);

	public:
		// Initialize the core functions. Must be called before anything
		virtual int Init(void) = 0;
		// Run the application
		virtual int Run(void) = 0;
		// Amount of time passed ingame. (e.g. doesn't include time in main menu or pause time)
		//double GetGameTime(void) { return m_gametime; }
		// 
		virtual void Pause(void) { }
		//
		GAMESTATE GetGameState(void) const { return m_state; }
		//
		double DeltaTime(void) const { return m_deltaTime; }
		//
		double GetIngameTicks(void) const { return m_ingameTicks; }
	protected:
		//double m_gametime;
		double m_deltaTime;
		double m_ingameTicks;
		GAMESTATE m_state;
	};

	CApplication* CreateApp(void);
	CApplication* GetApp(void);

	namespace Utility
	{
		inline float GetScreenWidth(void);
		inline float GetScreenHeight(void);
		float GetFPS(void);
	}
}
#endif