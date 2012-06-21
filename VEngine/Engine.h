#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

struct ALLEGRO_EVENT_QUEUE;
struct ALLEGRO_TIMER;
struct ALLEGRO_DISPLAY;
union ALLEGRO_EVENT;



namespace VE
{
	class ISystemController;
	class IView;
	class CEngine
	{
	protected:

		void Update(void);
		void Render(void);
		void HandleEvent(ALLEGRO_EVENT& ev);

	public:
		CEngine(void);
		~CEngine(void);

		int Init(void);
		int Run(void);

		void SetSystemController(ISystemController* controller);

	private:
		ALLEGRO_EVENT_QUEUE* m_evQ;
		ALLEGRO_TIMER* m_timer;
		ALLEGRO_DISPLAY* m_display;
		ISystemController* m_controller;
		bool m_done;
		bool m_needRedraw;
		bool m_isInit;
	};
}
#endif