#include "Engine.h"
#include <allegro5\allegro5.h>
#include <allegro5\allegro_physfs.h>
#include <allegro5\allegro_image.h>
#include <algorithm>

#include <physfs.h>
#include "SystemController.h"
#include "View.h"

namespace VE
{
	CEngine::CEngine(void)
		: m_timer(nullptr)
		, m_evQ(nullptr)
		, m_display(nullptr)
		, m_done(false)
		, m_controller(nullptr)
		, m_isInit(false)
	{

	}

	CEngine::~CEngine(void)
	{
		delete m_controller;
		m_controller = nullptr;

		al_destroy_display(m_display);
		m_display = nullptr;

		al_destroy_timer(m_timer);
		m_timer = nullptr;

		al_destroy_event_queue(m_evQ);
		m_evQ = nullptr;
	}

	int CEngine::Init(void)
	{
		al_init();
		al_install_keyboard();
		al_init_image_addon();

		m_evQ = al_create_event_queue();
		m_timer = al_create_timer(1.0f / 60.0f);
		m_display = al_create_display(800, 600);

		al_register_event_source(m_evQ, al_get_timer_event_source(m_timer));
		al_register_event_source(m_evQ, al_get_display_event_source(m_display));
		al_register_event_source(m_evQ, al_get_keyboard_event_source());

		PHYSFS_init(nullptr);
		al_set_physfs_file_interface();

		m_isInit = true;
		return 0;
	}

	int CEngine::Run(void)
	{
		if (!m_isInit)
			return -1;

		al_start_timer(m_timer);
		while(!m_done)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(m_evQ, &ev);

			if (ev.type == ALLEGRO_EVENT_TIMER)
				Update();
			else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				break;
			else if (ev.type >= ALLEGRO_EVENT_JOYSTICK_AXIS && ev.type < ALLEGRO_EVENT_TIMER)
				HandleEvent(ev);

			if (m_needRedraw && al_is_event_queue_empty(m_evQ))
				Render();
		}

		return 0;
	}

	void CEngine::Update(void)
	{
		if (m_controller)
			m_controller->Update(0);
	}

	void CEngine::Render(void)
	{
		// Let the controller know rendering is about to begin(It should use this to know when to draw the map).
		m_controller->Render();

		//std::sort(m_views.begin(), m_views.end(), [](IView* lhs, IView* rhs)
		//{
		//	return lhs->DrawOrder() < rhs->DrawOrder();
		//});

		//for (auto iter = m_views.begin(); iter != m_views.end(); ++iter)
		//	(*iter)->Draw();
	}

	void CEngine::HandleEvent(ALLEGRO_EVENT& ev)
	{
		if (m_controller)
			m_controller->PushSystemEvent(ev);
	}

	void CEngine::SetSystemController(ISystemController* controller)
	{
		delete m_controller;
		m_controller = controller;
	}
}