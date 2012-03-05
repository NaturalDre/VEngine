#include "vengine\GUI\GUI.h"
#include <vengine\Render\Render.h>

namespace VE
{
	CGUIManager::CGUIManager(void)
	{
		m_renderer.reset(new Gwen::Renderer::Allegro());
		m_skin.reset(new Gwen::Skin::TexturedBase);
		m_input.reset(new Gwen::Input::Allegro);

		m_skin->SetRender(m_renderer.get());
		m_skin->Init("Images/DefaultSkin.png");
		m_skin->SetDefaultFont(L"Fonts/OpenSans.ttf", 11);

		m_canvas.reset(new Gwen::Controls::Canvas(m_skin.get()));
		m_canvas->SetSize(GetScreenW(), GetScreenH());
		m_canvas->SetDrawBackground(false);
		m_canvas->SetBackgroundColor(Gwen::Color(150, 170, 170, 255));


		m_input->Initialize(m_canvas.get());
	}

	CGUIManager::~CGUIManager(void)
	{

	}

	void CGUIManager::Draw(void)
	{
		m_canvas->RenderCanvas();
	}

	void CGUIManager::Logic(void)
	{

	}

	CGUIManager& GetGUIMgr(void)
	{
		static CGUIManager instance;
		return instance;
	}

}