#ifndef GUIMAINMENU_H
#define GUIMAINMENU_H

#include <Gwen\Gwen.h>
#include <Gwen\Controls\WindowControl.h>
#include <Gwen\Controls\Button.h>
#include <Gwen\Controls\ImagePanel.h>
#include <Gwen\Controls\Label.h>
#include <Gwen\Controls\ComboBox.h>
#include "vengine\GUI\GuiBase.h"

namespace VE
{
		/*
		 * TO DO:
		 *  Options
		 *	New/Load Game
		 *
		 */
	class CGUIMainMenu;

	///////////////////////////////////////
	/////////// CGUINEWGAMEMENU ///////////
	//////////////////////////////////////
	class CGUINewGameMenu: public IGUIElement
	{
		friend CGUIMainMenu;
		//////////////////////////////////
		///// NEW GAME GUI CALLBACK //////
		//////////////////////////////////
		struct Callback: public Gwen::Event::Handler
		{
			// When OK Button gets unpressed
			void OkDepressed(Gwen::Controls::Base* pControl);
			// When Cancel Button gets unpressed
			void CancelDepressed(Gwen::Controls::Base* pControl);

		public:
			// Constructor
			Callback(void);

			// New Game Menu
			CGUINewGameMenu* ngm;
			// Main Menu
			CGUIMainMenu* mm;
		}; 
		// END CGUINEWGAMEMENU CALLBACK

	protected:
		// Helper function to make New Game Menu hidden
		void MakeHidden(void);
		// Helper function to make New Game Menu visible
		void MakeVisible(void);
		//
		void LoadLevels(void);
	public:
		// Should this menu be hidden?
		void SetHidden(bool shouldHide);
		const std::unique_ptr<Gwen::Controls::ComboBox>& GetComboBox(void) const { return m_comboBox; }

	private:
		CGUINewGameMenu(CGUIMainMenu* mm );
		// Window the new game widgets
		std::unique_ptr<Gwen::Controls::WindowControl> m_window;
		// OK Button - Loads level
		std::unique_ptr<Gwen::Controls::Button> m_okBtn;
		// Cancel button - Closes dialogue and returns to main menu
		std::unique_ptr<Gwen::Controls::Button> m_cancelBtn;
		// Label 
		std::unique_ptr<Gwen::Controls::Label> m_label;
		// Combo box for list of levels
		std::unique_ptr<Gwen::Controls::ComboBox> m_comboBox;

		// Callback for handling OnEvents for this menu
		Callback m_cb;
		// The main menu. (So we can hide it/make it visible when neccessary).
		CGUIMainMenu* m_mm;
		// Font for label
		Gwen::Font m_font;
		
	};

	////////////////////////////////////////
	///////// CGUIMAINMENU /////////////////
	////////////////////////////////////////
	class CGUIMainMenu: public IGUIElement
	{
		////////////////////////////////////
		/////// MAIN MENU CALLBACK /////////
		////////////////////////////////////

		// Callbacks for main menu buttons
		struct Callback: public Gwen::Event::Handler
		{
			Callback(void);
			// When m_ngBtn is pressed
			void NewGamePressed(void);
			// When m_loadBtn is pressed
			void LoadLevelPressed(void);
			// When m_opBtn is pressed
			void OptionsPressed(void);

		public:
			CGUIMainMenu* mm;
		};
		// END CGUIMAINMENU CALLBACK
		friend CGUIMainMenu::Callback;
	protected:
		void SetupWindow(void);
		void SetupOptions(void);
		void SetupNewGame(void);

	public:
		~CGUIMainMenu(void);
		// Returns the window containing the manu menu items.
		inline const std::unique_ptr<Gwen::Controls::WindowControl>& GetWindow(void) const { return m_window; }
		// Handle visibility
		void SetHidden(bool shouldHide);
		
		// Factory function
		static CGUIMainMenu* Create(void);

	private:
		CGUIMainMenu(void);
		// Callbacks needed by gwen to handle OnEvent callbacks
		Callback m_cb;
		// Holds the widgets for the main menu
		std::unique_ptr<Gwen::Controls::WindowControl> m_window;
		// Button clicked to bring up level loader/continue game
		std::unique_ptr<Gwen::Controls::Button> m_ngBtn;
		// New game menu - Allows you to select and load a level
		std::unique_ptr<CGUINewGameMenu> m_ngMenu;

	};
}
#endif