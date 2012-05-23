#include "Application.h"
#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_physfs.h>
#include <allegro5\timer.h>
#include "Render.h"
#include "ObjectModel.h"
#include "Utility.h"
#include "BoxView.h"

namespace VE {

	const float FPS(60.0f);

	class CApplicationImpl;
	CApplicationImpl* APP = nullptr;

	class CApplicationImpl: public CApplication
	{
	public:
		CApplicationImpl(void)
		{
			APP = this;
		}

		~CApplicationImpl(void)
		{
			al_destroy_timer(m_timer);
			m_timer = nullptr;

			al_destroy_event_queue(m_evQ);
			m_evQ = nullptr;

			al_destroy_display(m_display);
			m_display = nullptr;
		}

	protected:
		int Init(void)
		{
			if (!al_init())
			{
				return e_Core;
			}
			if (!al_install_keyboard())
			{
				return e_Keyboard;
			}
			if (!al_install_mouse())
			{
				return e_Mouse;
			}
			if (!al_init_image_addon())
			{
				return e_Image;
			}
			if (!al_init_primitives_addon())
			{
				return e_Primitives;
			}

			al_init_font_addon();
			if (!al_init_ttf_addon())
			{
				return e_TTF;
			}

			PHYSFS_init(nullptr);
			PHYSFS_addToSearchPath("Images.zip", 1);
			al_set_physfs_file_interface();

			m_timer = al_create_timer(1.0f / FPS);
			m_display = al_create_display(1024, 768);
			m_evQ = al_create_event_queue();

			al_register_event_source(m_evQ, al_get_timer_event_source(m_timer));
			al_register_event_source(m_evQ, al_get_keyboard_event_source());
			al_register_event_source(m_evQ, al_get_mouse_event_source());
			al_register_event_source(m_evQ, al_get_display_event_source(m_display));
			return e_NoError;
		}
		
		void Update(void)
		{
			BOOST_FOREACH(IObjectModel* model, m_models)
				model->Update();
		}

		int Run(int argc, const char* argv[])
		{
			if (!m_initialized)
				return EXIT_FAILURE;


			//BoxView bv;

			al_start_timer(m_timer);
			while(true)
			{
				ALLEGRO_EVENT ev;
				al_wait_for_event(m_evQ, &ev);

				if (ev.type == ALLEGRO_EVENT_TIMER)
					Update();
				else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					break;
				else if(ev.type >= ALLEGRO_EVENT_JOYSTICK_AXIS && ev.type < ALLEGRO_EVENT_TIMER)
					HandleInput(&ev);

				if(m_needRedraw && al_is_event_queue_empty(m_evQ))
				{
					al_clear_to_color(al_map_rgb(0,0,0));
					Renderer()->DrawScene();
					al_flip_display();
				}
			}
			return 0;
		}

		void HandleInput(ALLEGRO_EVENT* ev)
		{
/*			std::for_each(m_models.begin(), m_models.end(), [&](IObjectModel* listener)
			{
				if (ev->type == ALLEGRO_EVENT_KEY_UP)
					listener->KeyRelease(ev->keyboard.keycode);
				else if(ev->type == ALLEGRO_EVENT_KEY_DOWN)
					listener->KeyPress(ev->keyboard.keycode);
				else if(ev->type == ALLEGRO_EVENT_MOUSE_AXES)
					listener->MouseMove(ev);
				else if(ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
					listener->ButtonPress(ev);
				else if(ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
					listener->ButtonRelease(ev);
				else if(ev->type == ALLEGRO_EVENT_KEY_CHAR)
					listener->KeyChar(ev);
			});*/			
		}


	public:
		inline bool NeedRedraw(void) const { return m_needRedraw; }
		inline void AddModel(IObjectModel* model) { if (model) m_models.insert(model); }
		inline void RemoveModel(IObjectModel* model) { m_models.erase(model); }



	private /* Member Variables*/:
		bool m_initialized;
		bool m_needRedraw;
		ALLEGRO_TIMER* m_timer;
		ALLEGRO_EVENT_QUEUE* m_evQ;
		ALLEGRO_DISPLAY* m_display;
		std::set<IObjectModel*> m_models;
	};

	VE::CApplication* App(void) { return APP; }

	CApplication::CApplication(void)
	{
		m_mapLoaded = false;
		m_player = nullptr;
	}

	CApplication* CApplication::Create(void)
	{
		// If an instance already exists return a nullptr.
		if (APP)
			return nullptr;
		APP = new CApplicationImpl;
		return APP;
	}

	size_t GetDisplayWidth(void)
	{
		return al_get_display_width(al_get_current_display());
	}

	size_t GetDisplayHeight(void)
	{
		return al_get_display_height(al_get_current_display());
	}

	void Internal::Register(IObjectModel* model)
	{
		APP->AddModel(model);
	}

	void Internal::Deregister(IObjectModel* model)
	{
		APP->RemoveModel(model);
	}
}