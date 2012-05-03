#include <vengine\GUI\LoadLevelDialog.h>
#include <vengine\Level\Level.h>
#include <vengine\GUI\VengineGUI.h>
#include <vengine\Render\Render.h>
#include <vengine\Utility.h>
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

	void GUILoadLevelDialog::CancelDepressed(Gwen::Controls::Base* pControl)
	{
		pControl = static_cast<Gwen::Controls::Button*>(pControl);
		if (!pControl->IsDisabled())
		{
			MakeHidden(true);
		}
	}

	void GUILoadLevelDialog::OkDepressed(Gwen::Controls::Base* pControl)
	{
		if (!pControl->IsDisabled())
		{
			pControl = static_cast<Gwen::Controls::Button*>(pControl);
			const std::string filename = GetComboBox()->GetSelectedItem()->GetName();
			GetLvlMgr().LoadLevel(filename);
			GetUI().ShowIngameMenu();
			SetHidden(true);
		}
	}


	/////////////////////
	/// New Game Menu ///
	/////////////////////

	GUILoadLevelDialog::GUILoadLevelDialog(Gwen::Controls::Base* pParent)
		: WindowControl(GetUI().GetCanvas())
	{
		//this->SetSize(GetScreenW(), GetScreenH());
		m_font.facename = L"Fonts/OpenSans.ttf";
		m_font.size = 25;

		//m_window.reset(new Gwen::Controls::WindowControl(this));
		SetSize(400, 150);
		DisableResizing();
		SetClosable(false);
		SetTitle("START A NEW GAME");
		SetHidden(true);

		m_okBtn.reset(new Gwen::Controls::Button(this));
		m_okBtn->SetText("OK");
		m_okBtn->SetDisabled(true);
		m_okBtn->SetWidth(NGM::BUTTONWIDTH);
		m_okBtn->SetHeight(NGM::BUTTONHEIGHT);
		// Times 2 is buffer so half of button is not cut off
		m_okBtn->SetPos(m_okBtn->X(), Height() - m_okBtn->Height() * 2);
		m_okBtn->onUp.Add(this, &GUILoadLevelDialog::OkDepressed);
		
		m_cancelBtn.reset(new Gwen::Controls::Button(this));
		m_cancelBtn->SetText("CANCEL");
		m_cancelBtn->SetDisabled(false);
		m_cancelBtn->onUp.Add(this, &GUILoadLevelDialog::CancelDepressed);
		m_cancelBtn->SetWidth(NGM::BUTTONWIDTH);
		m_cancelBtn->SetHeight(NGM::BUTTONHEIGHT);
		// +15 is a buffer to increase space in-between cancel + ok
		m_cancelBtn->SetPos(Width() - (m_cancelBtn->Width() + 15), m_okBtn->Y());

		m_label.reset(new Gwen::Controls::Label(this));
		m_label->SetFont(&m_font);
		m_label->SetText("LOAD: ");
		m_label->SizeToContents();		

		m_comboBox.reset(new Gwen::Controls::ComboBox(this));
		m_comboBox->SetFont(&m_font);
		// Add level names/locations ot the combo box
		LoadLevels();
		m_comboBox->SizeToContents();
		// + 20 is buffer because SizeToContents make the combobox slightly too wide
		m_comboBox->SetWidth(Width() - (m_label->Width() + 20));
		// + 15 buffer so the combobox + label aren't too close
		m_comboBox->SetPos(Width() - (m_comboBox->Width() + 15), m_label->Y());

		if (m_comboBox->GetSelectedItem() && !m_comboBox->GetSelectedItem()->GetText().empty())
			m_okBtn->SetDisabled(false);
	}

	void GUILoadLevelDialog::MakeHidden(bool shouldHide)
	{
		if (shouldHide)
		{
			SetHidden(true);
			this->DestroyModal();
		}
		else
		{
			SetHidden(false);
			MakeModal(true);
		}
	}

	void GUILoadLevelDialog::LoadLevels(void)
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
}