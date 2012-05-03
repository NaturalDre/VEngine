#ifndef LOADLEVELDIALOG_H
#define LOADLEVELDIALOG_H

#include <Gwen\Controls\WindowControl.h>
#include <Gwen\Controls\ComboBox.h>
#include <Gwen\Controls\Label.h>
#include <Gwen\Controls\Button.h>

#include <memory>

namespace VE
{
	class CGUIMainMenu;
	class GUILoadLevelDialog: public Gwen::Controls::WindowControl
	{
		friend CGUIMainMenu;

		// When OK Button gets unpressed
		void OkDepressed(Gwen::Controls::Base* pControl);
		// When Cancel Button gets unpressed
		void CancelDepressed(Gwen::Controls::Base* pControl);



	protected:
		// Populates the combo box with the list of available levels
		void LoadLevels(void);
	public:
		// Should this menu be hidden?
		void MakeHidden(bool shouldHide);
		const std::unique_ptr<Gwen::Controls::ComboBox>& GetComboBox(void) const { return m_comboBox; }

	private:
		GUILoadLevelDialog(Gwen::Controls::Base* pParent);
		// Window the new game widgets
		//std::unique_ptr<Gwen::Controls::WindowControl> m_window;
		// OK Button - Loads level
		std::unique_ptr<Gwen::Controls::Button> m_okBtn;
		// Cancel button - Closes dialogue and returns to main menu
		std::unique_ptr<Gwen::Controls::Button> m_cancelBtn;
		// Label 
		std::unique_ptr<Gwen::Controls::Label> m_label;
		// Combo box for list of levels
		std::unique_ptr<Gwen::Controls::ComboBox> m_comboBox;

		// Font for label
		Gwen::Font m_font;
		
	};
}
#endif