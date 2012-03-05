#include "vengine\GUI\GUIMainMenu.h"
#include "vengine\GUI\GUI.h"
#include "vengine\Render\Render.h"
#include "vengine\Utility.h"
#include "vengine\Level\Level.h"
#include <vengine\Script\LuaScript.h>

namespace VE
{
	int L_MMPanic(lua_State* L)
	{
		if (lua_isstring(L, -1))
		{
			lua_pop(L, 1);
			throw(LuaError(lua_tostring(L, -1)));
		}
		Utility::ReportError("L_MMPanic called. No error string provided. Exiting...");
		exit(EXIT_FAILURE);
	}
	namespace NGM
	{
		const int BUTTONWIDTH(175);
		const int BUTTONHEIGHT(50);

		const char* LS_MAPLIST("Maps/MapList.lua");
		namespace Var
		{
			const char* L_MAPLIST("MapList");
			const char* L_MAPNAME("Name");
			const char* L_MAPLOC("Location");
		}
	}

	namespace MM
	{
		const int WINDOWIDTH(300);
		const int WINDOWHEIGHT(400);
		const int BUTTONHEIGHT(50);
	}
	////////////////////
	/// NG Callback ////
	////////////////////
	CGUINewGameMenu::Callback::Callback(void)
		: ngm(nullptr)
		, mm(nullptr)
	{

	}

	void CGUINewGameMenu::Callback::CancelDepressed(Gwen::Controls::Base* pControl)
	{
		pControl = static_cast<Gwen::Controls::Button*>(pControl);
		if (ngm && !pControl->IsDisabled())
		{
			ngm->SetHidden(true);
			mm->SetHidden(false);
		}
	}

	void CGUINewGameMenu::Callback::OkDepressed(Gwen::Controls::Base* pControl)
	{
		if (!pControl->IsDisabled())
		{
			pControl = static_cast<Gwen::Controls::Button*>(pControl);
			const std::string filename = ngm->GetComboBox()->GetSelectedItem()->GetName();
			GetLvlMgr().GetLevelLoader()->LoadLevel(filename);
		}
	}


	/////////////////////
	/// New Game Menu ///
	/////////////////////

	CGUINewGameMenu::CGUINewGameMenu(CGUIMainMenu* mm)
		: m_mm(mm)

	{
		m_font.facename = L"Fonts/OpenSans.ttf";
		m_font.size = 25;

		m_window.reset(new Gwen::Controls::WindowControl(GetGUIMgr().GetCanvas()));
		m_window->SetSize(400, 150);
		m_window->DisableResizing();
		m_window->SetClosable(false);
		m_window->SetTitle("START A NEW GAME");
		m_window->SetHidden(true);

		m_okBtn.reset(new Gwen::Controls::Button(m_window.get()));
		m_okBtn->SetText("OK");
		m_okBtn->SetDisabled(true);
		m_okBtn->SetWidth(NGM::BUTTONWIDTH);
		m_okBtn->SetHeight(NGM::BUTTONHEIGHT);
		// Times 2 is buffer so half of button is not cut off
		m_okBtn->SetPos(m_okBtn->X(), m_window->Height() - m_okBtn->Height() * 2);
		m_okBtn->onUp.Add(&m_cb, &Callback::OkDepressed);
		
		m_cancelBtn.reset(new Gwen::Controls::Button(m_window.get()));
		m_cancelBtn->SetText("CANCEL");
		m_cancelBtn->SetDisabled(false);
		m_cancelBtn->onUp.Add(&m_cb, &Callback::CancelDepressed);
		m_cancelBtn->SetWidth(NGM::BUTTONWIDTH);
		m_cancelBtn->SetHeight(NGM::BUTTONHEIGHT);
		// +15 is a buffer to increase space in-between cancel + ok
		m_cancelBtn->SetPos(m_window->Width() - (m_cancelBtn->Width() + 15), m_okBtn->Y());

		m_label.reset(new Gwen::Controls::Label(m_window.get()));
		m_label->SetFont(&m_font);
		m_label->SetText("LOAD: ");
		m_label->SizeToContents();		

		m_comboBox.reset(new Gwen::Controls::ComboBox(m_window.get()));
		m_comboBox->SetFont(&m_font);
		// Add level names/locations ot the combo box
		LoadLevels();
		m_comboBox->SizeToContents();
		// + 20 is buffer because SizeToContents make the combobox slightly too wide
		m_comboBox->SetWidth(m_window->Width() - (m_label->Width() + 20));
		// + 15 buffer so the combobox + label aren't too close
		m_comboBox->SetPos(m_window->Width() - (m_comboBox->Width() + 15), m_label->Y());

		if (m_comboBox->GetSelectedItem() && !m_comboBox->GetSelectedItem()->GetText().empty())
			m_okBtn->SetDisabled(false);


		m_cb.ngm = this;
		m_cb.mm = m_mm;
	}

	void CGUINewGameMenu::SetHidden(bool shouldHide)
	{
		if (shouldHide)
			MakeHidden();
		else
			MakeVisible();
	}

	void CGUINewGameMenu::MakeHidden(void)
	{
		m_window->SetHidden(true);
		//m_window->MakeModal(true);
	}

	void CGUINewGameMenu::MakeVisible(void)
	{
		m_window->SetHidden(false);
	}

	void CGUINewGameMenu::LoadLevels(void)
	{
		lua_State* L = lua_open();
		lua_atpanic(L, L_MMPanic);
		if (!Utility::L_BufferAndLoad(NGM::LS_MAPLIST, L))
			return;

		try 
		{
			lua_getglobal(L, "MapCount");
			// STK: int?
			const size_t count = luaL_checknumber(L, 1); 
			// STK: int
			lua_pop(L, 1);
			// STK:


			for (size_t i(1); i <= count; ++i)
			{
				lua_getglobal(L, "GetMapNameLoc");
				// STK: func?
				if (!lua_isfunction(L, -1))
				{
					lua_pop(L, -1);
					return;
				}
				// STK: func
				lua_pushinteger(L, i);
				// STK: func int
				if(lua_pcall(L, 1, 2, 0))
				{
					const char* error = lua_tostring(L, -1);
					lua_pop(L, 1);
					throw(LuaError(error, NGM::LS_MAPLIST, __FILE__));
				}
				// STK: string? string?
				if (lua_isstring(L, -2) && lua_isstring(L, -1))
				{

					// STK: string string
					const char* name = lua_tostring(L, -2);
					const char* loc = lua_tostring(L, -1);
					lua_pop(L, 2);
					// STK:
					m_comboBox->AddItem(Gwen::Utility::StringToUnicode(name), loc);
				}
				else
					throw(LuaError("MapList.Name and/or MapList.Location is not a string.", NGM::LS_MAPLIST, __FILE__));
			}
		}
		catch(LuaError& e)
		{
			if (e.luafile.empty())
				e.luafile = NGM::LS_MAPLIST;
			if (e.cppfile.empty())
				e.cppfile = __FILE__;

			Utility::ReportError(e.what(), e.luafile, e.cppfile);
			abort();
		}
		lua_close(L);
		L = nullptr;
	}

	/////////////////////
	//// Callbacks //////
	/////////////////////

	CGUIMainMenu::Callback::Callback(void)
		: mm(nullptr)
	{

	}

	void CGUIMainMenu::Callback::LoadLevelPressed(void)
	{

	}

	void CGUIMainMenu::Callback::OptionsPressed(void)
	{

	}

	void CGUIMainMenu::Callback::NewGamePressed(void)
	{
		if (mm)
		{
			if (!mm->m_ngMenu)
				mm->m_ngMenu.reset(new CGUINewGameMenu(mm));
			mm->m_ngMenu->SetHidden(false);
			mm->SetHidden(true);
		}

	}

	/////////////////////
	//// MAIN MENU///////
	/////////////////////
	CGUIMainMenu::CGUIMainMenu(void)
	{
		m_cb.mm = this;
	}

	CGUIMainMenu::~CGUIMainMenu(void)
	{

	}

	void CGUIMainMenu::SetupWindow(void)
	{
		m_window.reset(new Gwen::Controls::WindowControl(GetGUIMgr().GetCanvas()));
		if (!m_window)
			throw (std::exception("Could not allocate memory for m_window in MainMenu"));
		m_window->SetSize(MM::WINDOWIDTH, MM::WINDOWHEIGHT);
		m_window->DisableResizing();
		m_window->SetTitle("MAIN MENU");
		m_window->SetClosable(false);
	}

	void CGUIMainMenu::SetupOptions(void)
	{

	}

	void CGUIMainMenu::SetupNewGame(void)
	{
		m_ngBtn.reset(new Gwen::Controls::Button(m_window.get()));
		if (!m_ngBtn)
			throw(std::exception("Could not allocate memory for m_ngBtn in MainMenu"));
		m_ngBtn->SetText("NEW GAME");
		// -<num> is buffer
		m_ngBtn->SetWidth(m_window->Width() - 15);
		m_ngBtn->SetHeight(MM::BUTTONHEIGHT);
		m_ngBtn->onPress.Add(&m_cb, &Callback::NewGamePressed);
		m_ngBtn->SetAlignment(Gwen::Pos::Center);
	}

	void CGUIMainMenu::SetHidden(bool shouldHide)
	{
		if (shouldHide)
		{
			m_window->SetHidden(true);

		}
		else
		{
			m_window->SetHidden(false);
		}
	}
	CGUIMainMenu* CGUIMainMenu::Create(void)
	{
		CGUIMainMenu* mm(new CGUIMainMenu);

		if (!mm)
			throw(std::exception("Could not allocate memory for CGUIMainMenu"));

		mm->SetupWindow();
		mm->SetupNewGame();
		mm->SetupOptions();

		return mm;
	}
}