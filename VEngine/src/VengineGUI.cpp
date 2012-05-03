#include "vengine\GUI\VengineGUI.h"
#include <vengine\Render\Render.h>

namespace VE
{
	CVengineGUI::CVengineGUI(Gwen::Controls::Canvas* canvas)
		: Base(canvas)
	{
		assert(GetCanvas() != nullptr);

	m_renderer.reset(new Gwen::Renderer::Allegro());
		m_skin.reset(new Gwen::Skin::TexturedBase);
		m_input.reset(new Gwen::Input::Allegro);

		m_skin->SetRender(m_renderer.get());
		m_skin->Init("Images/DefaultSkin.png");
		m_skin->SetDefaultFont(L"Fonts/OpenSans.ttf", 11);


		GetCanvas()->SetSkin(m_skin.get());
		GetCanvas()->SetSize(GetScreenW(), GetScreenH());
		GetCanvas()->SetSize(GetScreenW(), GetScreenH());
		GetCanvas()->SetDrawBackground(false);
		GetCanvas()->SetBackgroundColor(Gwen::Color(150, 170, 170, 255));


		m_input->Initialize(GetCanvas());
		SetSize(GetScreenW(), GetScreenH());
		//m_mainMenu.reset(CGUIMainMenu::Create());
		//m_mainMenu->GetWindow()->SetHidden(true);

	}

	CVengineGUI::~CVengineGUI(void)
	{
		

	}

	void CVengineGUI::ShowMainMenu(void)
	{
		if (m_mainMenu)
			m_mainMenu->GetWindow()->SetHidden(false);
		else
		{
			m_mainMenu.reset(new CGUIMainMenu(this));
			m_mainMenu->SetHidden(false);
		}

		if (m_ingameMenu)
			m_ingameMenu->SetHidden(true);
	}

	void CVengineGUI::ShowIngameMenu(void)
	{
		if (m_mainMenu)
			m_mainMenu->SetHidden(true);
		if (!m_ingameMenu)
			m_ingameMenu.reset(new IngameMenu(this));

		m_mainMenu->SetHidden(true);
		m_ingameMenu->SetHidden(false);
	}

	CVengineGUI& GetUI(void)
	{
		static CVengineGUI instance(new Gwen::Controls::Canvas(nullptr));
		return instance;
	}
}