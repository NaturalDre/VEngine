#include "vengine\Application.h"
#include "vengine\Vengine.h"
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
			// Time since last frame
			m_deltaTime = al_current_time() - m_lastUpdateTime;
			++m_ingameTicks;
			// Objects are being updated therefore a redraw is needed.
			m_needRedraw = true;

			/* 
				Let RenderManager perform any pre update logic it needs to do, 
				such as freeing objects from last draw. No actual drawing is done here.
			*/
			//GetRenderMgr().Logic();

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
			//GetScriptMgr().Cleanup();
			GetLvlMgr().Cleanup();
			GetObjMgr().Cleanup();
			GetInputMgr().Cleanup();
			GetRenderMgr().Cleanup();
			// Cleanup should do any storing of data.
			// Exit is called here 'cause when destructors for the managers are called
			// the ycan yield problems that aren't my fault. The API's I use don't work 
			// well together on program end.
			//exit(EXIT_SUCCESS);
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

			GetScriptMgr().LoadScript("test.lua");
			//CLevelMap m;
			al_start_timer(m_timer.get());

			if (GetGUIMgr().GetGUI())
				GetGUIMgr().GetGUI()->ShowMainMenu();

			m_state = MAINMENU;


			while(true)
			{
				ALLEGRO_EVENT ev;

				al_wait_for_event(m_evQ.get(), &ev);

				if (ev.type == ALLEGRO_EVENT_TIMER)
					Update();
				else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					break;
				else if (ev.type >= ALLEGRO_EVENT_JOYSTICK_AXIS && ev.type  <  ALLEGRO_EVENT_TIMER)
				{
					// TO DO: Implement Input Manager Push Function
					GetInputMgr().PushInput(ev);

				}; 

				// If there are no events to process AND we don't need to redraw any updated game objected we draw to the screen
				if (m_needRedraw && al_is_event_queue_empty(m_evQ.get()))
				{
					m_needRedraw = false;
					//GUIManager::GetInstance().Update();
					//const double ctime = al_get_time();
					GetRenderMgr().Render();
					//std::cout << "\nRender Time: " << al_current_time() - ctime;
				}
			}

			OnCleanup();
			return EXIT_SUCCESS;
		}



	private:
		//std::unique_ptr<ALLEGRO_DISPLAY, Utility::AlDisplayDel> m_display;
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