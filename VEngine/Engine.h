#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <list>
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
	class CEngine
	{
		typedef std::list<IProcess*> Processes;
	protected:
		void Update(void);
		void Render(void);
		void HandleEvent(ALLEGRO_EVENT& ev);

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
	private:
		ALLEGRO_EVENT_QUEUE* m_evQ;
		ALLEGRO_TIMER* m_timer;
		ALLEGRO_DISPLAY* m_display;
		IEngineCallback* m_callback;
		Processes m_processes;
		bool m_done;
		bool m_needRedraw;
		bool m_isInit;

		double m_timeLastUpdated;
		double m_gameTime;
	};
}
#endif