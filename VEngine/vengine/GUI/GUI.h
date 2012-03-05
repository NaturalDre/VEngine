#ifndef GUI_H
#define GUI_H

#include <Gwen\Gwen.h>
#include <Gwen\Renderers\Allegro.h>
#include <Gwen\Skins\TexturedBase.h>
#include <Gwen\Input\Allegro.h>

#include "vengine\GUI\GuiBase.h"
namespace VE
{
	class IGUIBase;
	class CRenderManager;
}

namespace VE
{
	class CGUIManager
	{
		friend CGUIManager& GetGUIMgr(void);
		friend CRenderManager;

	protected:
		void Draw(void);
		void Logic(void);

	public:
		~CGUIManager(void);
		
		Gwen::Controls::Canvas* GetCanvas(void) const { return m_canvas.get(); }
		IGUIBase* GetGUI(void) const { return m_gui; }

		void SetGUI(IGUIBase* gui) { m_gui = gui; }
		void PushInput(ALLEGRO_EVENT& ev) { m_input->ProcessMessage(ev); }

	private:
		CGUIManager(void);
		CGUIManager(CGUIManager const&);
		void operator=(CGUIManager const&);

		std::unique_ptr<Gwen::Controls::Canvas> m_canvas;
		std::unique_ptr<Gwen::Renderer::Allegro> m_renderer;
		std::unique_ptr<Gwen::Skin::TexturedBase> m_skin;
		std::unique_ptr<Gwen::Input::Allegro> m_input;
		IGUIBase* m_gui;
	};

	CGUIManager& GetGUIMgr(void);
}
#endif