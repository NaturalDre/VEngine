#ifndef INGAMEMENU_H
#define INGAMEMENU_H

#include <Gwen\Controls\WindowControl.h>
#include <Gwen\Controls\ImagePanel.h>
#include <Gwen\Controls\Label.h>

#include <memory>

using namespace Gwen;

namespace VE
{
	class IngameMenu: public Gwen::Controls::Base
	{
	protected:

	public:
		IngameMenu(Gwen::Controls::Base* parent);
		~IngameMenu(void);

	private:
		Font m_labelFont;
	};
}
#endif