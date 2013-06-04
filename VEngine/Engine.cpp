#include "Engine.h"
#include "Vengine.h"

#include <allegro5\allegro5.h>
#include <allegro5\allegro_physfs.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>

#include <algorithm>
#include <physfs.h>
#include <luabind\luabind.hpp>
#include <luabind\lua_include.hpp>
#include <lauxlib.h>
#include "EngineCallback.h"
#include "Physics.h"
#include "UIConsole.h"
#include "Render.h"

#include "Utility.h"
#include "Locator.h"

namespace VE
{
	CEngine::CEngine(void)
		: m_timer(nullptr)
		, m_evQ(nullptr)
		, m_display(nullptr)
		, m_scriptEnv(nullptr)
		, m_physics(nullptr)
		, m_renderer(nullptr)
		, m_console(nullptr)
		, m_canvas(nullptr)
		, m_gwenRenderer(nullptr)
		, m_done(false)
		, m_isInit(false)
		, m_pausePhysics(true)
		, m_pauseLogic(true)
		, m_timeLastUpdated(0)
		, m_gameTime(0)
	{

	}

	CEngine::~CEngine(void)
	{
		// We don't own it.
		m_callback = nullptr;

		al_destroy_display(m_display);
		m_display = nullptr;

		al_destroy_timer(m_timer);
		m_timer = nullptr;

		al_destroy_event_queue(m_evQ);
		m_evQ = nullptr;
	}

	int CEngine::InitBase(void)
	{
			if (!al_init())
				return -1;

			if (!al_init_image_addon())
				return -2;

			if (!al_init_primitives_addon())
				return -3;

			if (!al_install_keyboard())
				return -4;

			if (!al_install_mouse())
				return -5;

			al_init_font_addon();

			if (!al_init_ttf_addon())
				return -7;

			return 0;
	}

	void CEngine::ExportBindings(void)
	{
		luabind::module(GetScriptEnv())
			[
				luabind::class_<CEngine>("CEngine")
				.property("physics", &CEngine::GetPhysics)
				.property("pausePhysics", &CEngine::IsPhysicsPaused, &CEngine::SetPausePhysics)
				.property("pauseLogic", &CEngine::IsLogicPaused, &CEngine::SetPauseLogic)
			];

		DoFile(GetScriptEnv(), "Scripts/core.lua");
		luabind::settable(luabind::globals(GetScriptEnv()), "gEngine", this);
		int test = 4;
	}

	int CEngine::Init(void)
	{
		try
		{
			if (InitBase())
				return -1;

			PHYSFS_init(nullptr);
			PHYSFS_addToSearchPath("Core", 1);
			al_set_physfs_file_interface();	

			m_scriptEnv = lua_open();
			luaL_openlibs(m_scriptEnv);
			luabind::open(m_scriptEnv);

			ExportBindings();

			m_evQ = al_create_event_queue();
			m_timer = al_create_timer(1.0f / 60.0f);
			m_display = al_create_display(800, 600);
			m_renderer = new CRender;
			CLocator::Provide(m_renderer);
			m_physics = new CPhysics;

			m_gwenRenderer = new GwenAllegroRenderer;

			m_gwenSkin.SetRender(m_gwenRenderer);
			m_gwenSkin.Init("Images/DefaultSkin.png");
			m_gwenSkin.SetDefaultFont(L"Fonts/OpenSans.ttf", 14);

			m_canvas = new GwenCanvas(&m_gwenSkin);
			m_canvas->SetSize(GetDisplayWidth(), GetDisplayHeight());
			m_canvas->SetDrawBackground(false);
			m_renderer->SetUICanvas(m_canvas);
			m_gwenInput.Initialize(m_canvas);
			m_console = new CUIConsole(this, m_canvas);
			m_console->SetHidden(true);

			al_register_event_source(m_evQ, al_get_timer_event_source(m_timer));
			al_register_event_source(m_evQ, al_get_display_event_source(m_display));
			al_register_event_source(m_evQ, al_get_keyboard_event_source());
			al_register_event_source(m_evQ, al_get_mouse_event_source());

			m_isInit = true;
		}
		catch(...)
		{
			m_isInit = false;
			return 1;
		}

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
		const double ct = al_current_time();
		const double dt = ct - m_timeLastUpdated;
		m_timeLastUpdated = ct;
		
		if (!IsLogicPaused())
		{
			m_gameTime += dt;
			for(auto iter = m_processes.begin(); iter != m_processes.end(); ++iter)
			{
				if ((*iter)->ShouldDelete())
				{
					delete *iter;
					iter = m_processes.erase(iter);
					if (iter == m_processes.end())
						break;
				}
				else
					(*iter)->Think(dt);
			}
		}

		if (!IsPhysicsPaused())
			GetPhysics()->Simulate();
	}

	void CEngine::Render(void)
	{
		CLocator::GetRenderer()->Render();
	}

	void CEngine::HandleEvent(ALLEGRO_EVENT& ev)
	{
		if (m_canvas)
		{
			if (m_console && ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_TILDE)
			{

				m_console->SetHidden(!m_console->Hidden());
				SetPauseLogic(!m_console->Hidden());
				SetPausePhysics(!m_console->Hidden());
			}
			else
					m_gwenInput.ProcessMessage(ev);
		}
	}


	void CEngine::AddProcess(IProcess* process)
	{
		m_processes.push_back(process);
		m_processes.sort();
	}

	void CEngine::RemoveProcess(IProcess* process)
	{
		m_processes.remove(process);
	}

	void CEngine::CloseScriptEnv(void)
	{
		lua_close(m_scriptEnv);
		m_scriptEnv = nullptr;
	}
}