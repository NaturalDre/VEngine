#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <list>
#include "ErrorLogger.h"
#include <Gwen\Renderers\Allegro.h>
#include <Gwen\Input\Allegro.h>
#include <Gwen\Controls\Canvas.h>
#include <Gwen\Skins\TexturedBase.h>

struct lua_State;
struct ALLEGRO_EVENT_QUEUE;
struct ALLEGRO_TIMER;
struct ALLEGRO_DISPLAY;
union ALLEGRO_EVENT;

struct lua_State;


namespace VE
{
	class IEngineCallback;
	class IProcess;
	class IView;
	class CPhysics;
	class CRender;
	class CUIConsole;
	class CInputManager;
	class CEngine
	{
		typedef std::list<IProcess*> Processes;
	protected:
		void Update(void);
		void Render(void);
		void HandleEvent(ALLEGRO_EVENT& ev);

		int InitBase(void);
		void ExportBindings(void);
	public:
		CEngine(void);
		~CEngine(void);

		/// Initializes the core functions of the engine.
		int Init(void);
		/// Begins the game loop.
		int Run(void);
		/// @param callback Is notified of specific system events during the game loop.
		/// @see EngineCallback.h
		void SetCallback(IEngineCallback* callback) { m_callback = callback; }
		///
		void AddProcess(IProcess* process);
		void RemoveProcess(IProcess* process);

		/// Shuts down the lua_State used by the game. 
		/// \note This is meant to only be used if you need to free the state
		///		before freeing the engine. (Since the state may have references
		///		to game objects, this will likely be called before freeing the
		///		game level.
		void CloseScriptEnv(void);

		inline CPhysics* GetPhysics(void) const { return m_physics; }

		inline lua_State* GetScriptEnv(void) const { return m_scriptEnv; }
		inline CUIConsole* GetConsole(void) const { return m_console; }

		inline void SetPausePhysics(bool shouldPause) { m_pausePhysics = shouldPause; }
		inline void SetPauseLogic(bool shouldPause) { m_pauseLogic = shouldPause; }
		inline bool IsPhysicsPaused(void) const { return m_pausePhysics; }
		inline bool IsLogicPaused(void) const { return m_pauseLogic; }

	private:
		ALLEGRO_EVENT_QUEUE* m_evQ;
		ALLEGRO_TIMER* m_timer;
		ALLEGRO_DISPLAY* m_display;
		IEngineCallback* m_callback;
		lua_State* m_scriptEnv;
		CPhysics* m_physics;
		CRender* m_renderer;
		//CInputManager* m_inputManager;
		CUIConsole* m_console;
		GwenCanvas* m_canvas;
		GwenAllegroRenderer* m_gwenRenderer;
		GwenAllegroInput m_gwenInput;
		GwenTexturedBaseSkin m_gwenSkin;
		Processes m_processes;
		bool m_done;
		bool m_needRedraw;
		bool m_isInit;
		bool m_pauseLogic;
		bool m_pausePhysics;
		double m_timeLastUpdated;
		double m_gameTime;
	};
}
#endif