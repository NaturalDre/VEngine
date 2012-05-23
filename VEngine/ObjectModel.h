#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H

#include <allegro5\allegro5.h>

namespace VE {
	class CApplicationImpl;
	
	class IObjectModel
	{
		friend CApplicationImpl;
	protected:
		IObjectModel(void);
		~IObjectModel(void);

		virtual void Update(void) { }
		//virtual void InputEvent(ALLEGRO_EVENT* ev) { }
		virtual void GameEvent(ALLEGRO_EVENT* ev) { }

		//virtual void KeyPress(int keyCode) { }
		//virtual void KeyRelease(int keyCode) { }
		//virtual void KeyChar(ALLEGRO_EVENT* ev) { }
		//virtual void ButtonPress(ALLEGRO_EVENT* ev) { }
		//virtual void ButtonRelease(ALLEGRO_EVENT* ev) { }
		//virtual void MouseEnterDisplay(ALLEGRO_EVENT* ev) { }
		//virtual void MouseLeaveDisplay(ALLEGRO_EVENT* ev) { }
		//virtual void MouseWarp(ALLEGRO_EVENT* ev) { }
		//virtual void MouseMove(ALLEGRO_EVENT* ev) { }

	public:

	private:

	};

}
#endif