#include "vengine\Application.h"
#include "vengine\Vengine.h"
#include <vengine\GUI\VengineGUI.h>

#include <memory>
#include <physfs.h>
#include <iostream>
namespace VE
{
	const float FPS(60.0f);
}
namespace VE
{
	////////////////////////////
	//////// Application Impl //
	////////////////////////////
	class CApplicationImpl: public CApplication
	{
	protected:
		// Initialize systems
		int Init(void)
		{
			if (!al_init())
			{
				Utility::ReportError("Failed to initialize Allegro");
				return -1;
			}
			if (!al_install_keyboard())
			{
				Utility::ReportError("Failed to install the keyboard.");
				return -1;
			}
			if (!al_install_mouse())
			{
				Utility::ReportError("Failed to install the mouse.");
				return -1;
			}
			if (!al_init_image_addon())
			{
				Utility::ReportError("Failed to initialize the image addon.");
				return -1;
			}
			if (!al_init_primitives_addon())
			{
				Utility::ReportError("Failed to initialize the primitives addon");
				return -1;
			}

			al_init_font_addon();
			if (!al_init_ttf_addon())
			{
				Utility::ReportError("Failed to initialize the TTF addon.");
				return -1;
			}

			PHYSFS_init(nullptr);
			PHYSFS_addToSearchPath("data.zip", 1);
			PHYSFS_addToSearchPath("data", 1);
			al_set_physfs_file_interface();

			m_evQ.reset(al_create_event_queue());
			if (!m_evQ)
				return -1;

			m_timer.reset(al_create_timer(1.0f / Global::FPS));
			if (!m_timer)
				return -1;

			if (GetRenderMgr().Init(1024, 768))
				return -1;


			al_register_event_source(m_evQ.get(), al_get_timer_event_source(m_timer.get()));
			al_register_event_source(m_evQ.get(), al_get_keyboard_event_source());
			al_register_event_source(m_evQ.get(), al_get_mouse_event_source());
			al_register_event_source(m_evQ.get(), al_get_display_event_source(al_get_current_display()));
			
			m_isInit = true;
			return 0;
		}

		void Update(void)
		{
			/*
			 *	This function is the update loop.
			 */

			// Time since last frame
			m_deltaTime = al_current_time() - m_lastUpdateTime;
			m_lastUpdateTime = al_current_time();
			++m_ingameTicks;
			// Objects are being updated therefore a redraw is needed.
			m_needRedraw = true;
			// Let the level manager perform any operations it needs.
			GetLvlMgr().Logic();
			// Update animations.
			GetObjMgr().UpdateAnimations();
			// Update game objects.
			GetObjMgr().UpdateGameObjects();
			// Update physics world.
			GetPhysMgr().UpdateWorld();
		}

		void OnCleanup(void)
		{
			GetLvlMgr().Cleanup();
			GetObjMgr().Cleanup();
			GetInputMgr().Cleanup();
			GetRenderMgr().Cleanup();
		}

	public:

		CApplicationImpl(void)
			: m_needRedraw(true)
			, m_isInit(false)
			, m_lastUpdateTime(0.0)
		{

		}

		int Run(void)
		{
			if (!m_isInit)
				return EXIT_FAILURE;

			al_start_timer(m_timer.get());

			GetUI().ShowMainMenu();

			m_state = MAINMENU;

			while(true)
			{
				ALLEGRO_EVENT ev;
				// Rest/Wait until an event is received.
				al_wait_for_event(m_evQ.get(), &ev);

				// These if-statements process the received event

				// If the event was a timer event, it's time to update the game world.
				if (ev.type == ALLEGRO_EVENT_TIMER)
					Update();
				else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					break;
				else if (ev.type >= ALLEGRO_EVENT_JOYSTICK_AXIS && ev.type  <  ALLEGRO_EVENT_TIMER)
				{
					// Let all input listeners know about the input that was just received.
					GetInputMgr().PushInput(ev);
				}; 

				// If world was updated and therefore needs redrawing AND there are no more events to process we draw the world to the screen.
				if (m_needRedraw && al_is_event_queue_empty(m_evQ.get()))
				{
					m_needRedraw = false;
					GetRenderMgr().Render();
				}
			}

			OnCleanup();
			return EXIT_SUCCESS;
		}



	private:
		std::unique_ptr<ALLEGRO_TIMER, Utility::AlTimerDel> m_timer;
		std::unique_ptr<ALLEGRO_EVENT_QUEUE, Utility::AlQueueDel> m_evQ;
		bool m_needRedraw;
		bool m_isInit;
		double m_lastUpdateTime;
	};

	///////////////////////////////////
	////////// CApplication ///////////
	///////////////////////////////////
	static CApplicationImpl* app(nullptr);

	CApplication::CApplication(void)
		: m_deltaTime(0.0)
		, m_ingameTicks(0.0)
	{

	}

	CApplication* CreateApp(void)
	{
		app = new CApplicationImpl;
		return app;
	}

	CApplication* GetApp(void)
	{
		assert(app != nullptr);
		return app;
	}

	float Utility::GetFPS(void) { return FPS; }
}