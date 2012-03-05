#include "vengine\Input.h"
#include <algorithm>
#include "vengine\GUI\GUI.h"

namespace VE
{
	CInputManager::CInputManager(void)
	{

	}

	void CInputManager::AddListener(IInputListener* listener)
	{
		m_listeners.insert(listener);
	}

	void CInputManager::RemoveListener(IInputListener* listener)
	{
		m_listeners.erase(listener);
	}

	void CInputManager::PushInput(ALLEGRO_EVENT& ev)
	{
		GetGUIMgr().PushInput(ev);
		std::for_each(m_listeners.begin(), m_listeners.end(), [&](IInputListener* listener)
		{
			if (ev.type == ALLEGRO_EVENT_KEY_UP)
				listener->OnKeyUp(ev.keyboard.keycode);
			else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
				listener->OnKeyDown(ev.keyboard.keycode);
			else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
				listener->OnMouseMoved(ev);
			else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				listener->OnMouseButtonDown(ev);
			else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
				listener->OnMouseButtonUp(ev);
			else if(ev.type == ALLEGRO_EVENT_KEY_CHAR)
				listener->OnCharTyped(ev);
		});
	}

	void CInputManager::Cleanup(void)
	{

	}

	CInputManager& GetInputMgr(void)
	{
		static CInputManager instance;
		return instance;
	}
}