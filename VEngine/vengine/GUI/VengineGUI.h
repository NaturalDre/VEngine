#ifndef VENGINEGUI_H
#define VENGINEGUI_H

#include <allegro5\allegro5.h>
#include <Gwen\Renderers\Allegro.h>
#include <Gwen\Input\Allegro.h>
#include <Gwen\Skins\TexturedBase.h>

#include "vengine\GUI\GUIMainMenu.h"
#include <vengine\GUI\IngameMenu.h>

using namespace Gwen;

namespace VE
{
	class CVengineGUI: public Gwen::Controls::Base
	{
		friend CVengineGUI& GetUI(void);
	protected:


	public:
		CVengineGUI(Gwen::Controls::Canvas* canvas);
		~CVengineGUI(void);

		void PushInput(ALLEGRO_EVENT& ev) { m_input->ProcessMessage(ev); }
		void CloseAll(void);

		void ShowMainMenu(void);
		void ShowIngameMenu(void);

		//Controls::Canvas* GetCanvas(void) const { return m_canvas.get(); }

	private:
		std::unique_ptr<Gwen::Renderer::Allegro> m_renderer;
		std::unique_ptr<Gwen::Skin::TexturedBase> m_skin;
		std::unique_ptr<Gwen::Input::Allegro> m_input;


		//std::unique_ptr<Controls::Canvas> m_canvas;
		std::unique_ptr<CGUIMainMenu> m_mainMenu;
		std::unique_ptr<IngameMenu> m_ingameMenu;
	};

	CVengineGUI& GetUI(void);
}
#endif