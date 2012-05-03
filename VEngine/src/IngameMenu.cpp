#include <vengine\GUI\IngameMenu.h>
#include <vengine\Render\Render.h>
#include <boost\lexical_cast.hpp>
#include <vengine\ObjectManager.h>




namespace VE
{

struct RenderCallback: public IRenderListener
{
	RenderCallback(IngameMenu* igm)
	{

	}
	void Draw(void)
	{
		
	}

	IngameMenu* igm;
};

	IngameMenu::IngameMenu(Gwen::Controls::Base* parent)
		: Base(parent)
	{
		m_labelFont.facename = L"Fonts/OpenSans.ttf";
		m_labelFont.size = 30;
		m_labelFont.bold = true;
		m_labelFont.dropshadow = true;
	}

	IngameMenu::~IngameMenu(void)
	{
		
	}
}