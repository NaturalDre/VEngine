#ifndef VENGINEGUI_H
#define VENGINEGUI_H

#include "GuiBase.h"
#include "vengine\GUI\GUIMainMenu.h"

namespace VE
{
	class CVengineGUI: public IGUIBase
	{
	protected:
		void ShowMainMenu(void);

	public:
		CVengineGUI(void);
		~CVengineGUI(void);

	private:
		std::unique_ptr<CGUIMainMenu> m_mainMenu;
	};
}
#endif