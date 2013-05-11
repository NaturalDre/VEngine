#ifndef UICONSOLE_H
#define UICONSOLE_H

#include <Gwen\Gwen.h>
#include <gwen\Controls\Base.h>
#include <Gwen\Controls\ListBox.h>
#include <Gwen\Controls\TextBox.h>

namespace VE
{
	class CEngine;
	class CUIConsole: public GwenBase
	{
	protected:
		void OnEnter(GwenBase* base);

	public:
		CUIConsole(CEngine* engine, GwenCanvas* canvas);
		~CUIConsole(void);

		void AddToList(const std::string& text) { if (m_lb) m_lb->AddItem(text); }

	private:
		CEngine* m_engine;
		GwenListBox* m_lb;
		GwenTextBox* m_tb;
	};
}
#endif