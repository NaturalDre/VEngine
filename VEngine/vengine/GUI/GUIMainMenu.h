#ifndef GUIMAINMENU_H
#define GUIMAINMENU_H

#include <Gwen\Gwen.h>
#include <Gwen\Controls\WindowControl.h>
#include <Gwen\Controls\Button.h>
#include <Gwen\Controls\ImagePanel.h>
#include <Gwen\Controls\Label.h>
#include <Gwen\Controls\ComboBox.h>
#include <vengine\GUI\LoadLevelDialog.h>
namespace VE
{

	class CGUIMainMenu;
	class CGUIMainMenu: public Gwen::Controls::Base
	{


		// When m_ngBtn is pressed
		void NewGamePressed(void);
		// When m_loadBtn is pressed
		void LoadLevelPressed(void);
		// When m_opBtn is pressed
		void OptionsPressed(void);

		// END CGUIMAINMENU CALLBACK

	protected:
		void SetupWindow(void);
		void SetupOptions(void);
		void SetupNewGame(void);

	public:
		CGUIMainMenu(Gwen::Controls::Base* parent);
		~CGUIMainMenu(void);
		// Returns the window containing the manu menu items.
		inline const std::unique_ptr<Gwen::Controls::WindowControl>& GetWindow(void) const { return m_window; }
		// Handle visibility
		void MakeHidden(bool shouldHide);

	private:

		// Holds the widgets for the main menu
		std::unique_ptr<Gwen::Controls::WindowControl> m_window;
		// Button clicked to bring up level loader/continue game
		std::unique_ptr<Gwen::Controls::Button> m_ngBtn;
		// New game menu - Allows you to select and load a level
		std::unique_ptr<GUILoadLevelDialog> m_ngMenu;

	};
}
#endif