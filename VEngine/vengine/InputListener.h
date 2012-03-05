#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H

#include <allegro5\allegro5.h>

namespace VE
{
	class CInputManager;
}

namespace VE
{
	class IInputListener
	{
		friend CInputManager;
	protected:
		IInputListener(void);
		virtual ~IInputListener(void) = 0;

		virtual void OnKeyDown(int keyCode) { }
		virtual void OnKeyUp(int keyCode) { }
		virtual void OnCharTyped(ALLEGRO_EVENT& ev) { }

		virtual void OnMouseButtonDown(ALLEGRO_EVENT& ev) { }
		virtual void OnMouseButtonUp(ALLEGRO_EVENT& ev) {}

		virtual void OnMouseEnterDisplay(ALLEGRO_EVENT& ev) {}
		virtual void OnMouseLeaveDisplay(ALLEGRO_EVENT& ev) {}

		virtual void OnMouseWarped(ALLEGRO_EVENT& ev) {}
		virtual void OnMouseMoved(ALLEGRO_EVENT& ev) {}

	public:

	private:
		IInputListener(IInputListener const&);
		void operator=(IInputListener const&);
	};
};
#endif