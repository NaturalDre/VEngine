#include "vengine\GUI\GUIMainMenu.h"
#include "vengine\Render\Render.h"
#include "vengine\Utility.h"
#include "vengine\Level\Level.h"
#include <vengine\Script\LuaScript.h>
#include <vengine\GUI\VengineGUI.h>
namespace VE
{

	namespace MM
	{
		const int WINDOWIDTH(300);
		const int WINDOWHEIGHT(400);
		const int BUTTONHEIGHT(50);
	}

	void CGUIMainMenuLoadLevelPressed(void)
	{

	}

	void CGUIMainMenu::OptionsPressed(void)
	{

	}

	void CGUIMainMenu::NewGamePressed(void)
	{
	
			if (!m_ngMenu)
				m_ngMenu.reset(new GUILoadLevelDialog(nullptr));
			m_ngMenu->MakeHidden(false);
			//mm->SetHidden(true);
		

	}

	/////////////////////
	//// MAIN MENU///////
	/////////////////////
	CGUIMainMenu::CGUIMainMenu(Gwen::Controls::Base* parent)
		: Base(parent)
	{
		SetupWindow();
		SetupNewGame();
		SetupOptions();

		this->SetSize(GetScreenW(), GetScreenH());
	}

	CGUIMainMenu::~CGUIMainMenu(void)
	{

	}

	void CGUIMainMenu::SetupWindow(void)
	{
		m_window.reset(new Gwen::Controls::WindowControl(this));
		if (!m_window)
			throw (std::exception("Could not allocate memory for m_window in MainMenu"));
		m_window->SetSize(MM::WINDOWIDTH, MM::WINDOWHEIGHT);
		m_window->DisableResizing();
		m_window->SetTitle("MAIN MENU");
		m_window->SetClosable(false);
	}

	void CGUIMainMenu::SetupOptions(void)
	{

	}

	void CGUIMainMenu::SetupNewGame(void)
	{
		m_ngBtn.reset(new Gwen::Controls::Button(m_window.get()));
		if (!m_ngBtn)
			throw(std::exception("Could not allocate memory for m_ngBtn in MainMenu"));
		m_ngBtn->SetText("NEW GAME");
		// -<num> is buffer
		m_ngBtn->SetWidth(m_window->Width() - 15);
		m_ngBtn->SetHeight(MM::BUTTONHEIGHT);
		m_ngBtn->onPress.Add(this, &CGUIMainMenu::NewGamePressed);
		m_ngBtn->SetAlignment(Gwen::Pos::Center);
	}

	void CGUIMainMenu::MakeHidden(bool shouldHide)
	{
		if (shouldHide)
		{
			m_window->SetHidden(true);
		}
		else
		{
			m_window->SetHidden(false);
		}
	}
}