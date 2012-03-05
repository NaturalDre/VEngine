#include "vengine\GUI\VengineGUI.h"

namespace VE
{
	CVengineGUI::CVengineGUI(void)
	{
		m_mainMenu.reset(CGUIMainMenu::Create());
		m_mainMenu->GetWindow()->SetHidden(true);
	}

	CVengineGUI::~CVengineGUI(void)
	{


	}

	void CVengineGUI::ShowMainMenu(void)
	{
		m_mainMenu->GetWindow()->SetHidden(false);
	}
}