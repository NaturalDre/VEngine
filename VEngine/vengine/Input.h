#ifndef INPUT_H
#define INPUT_H

#include <allegro5\allegro5.h>
#include <set>
#include "InputListener.h"
namespace VE
{
	class CApplicationImpl;
}

namespace VE
{
	class CInputManager
	{
		friend IInputListener;
		friend CApplicationImpl;
		friend CInputManager& GetInputMgr(void);

	protected:
		void PushInput(ALLEGRO_EVENT& ev);
		void AddListener(IInputListener* listener);
		void RemoveListener(IInputListener* listener);

		void Cleanup(void);
	public:

	private:
		CInputManager(void);

		std::set<IInputListener*> m_listeners;
	};

	CInputManager& GetInputMgr(void);
}
#endif