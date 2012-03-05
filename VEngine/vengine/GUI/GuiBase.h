#ifndef GUIBASE_H
#define GUIBASE_H

namespace VE
{
	class IGUIBase
	{
	protected:
		virtual void Logic(void) { };

	public:
		virtual void ShowMainMenu(void) { };
		virtual void ShowPauseMenu(void) { };
		virtual void ShowIngameMenu(void) { };

		virtual ~IGUIBase(void) = 0 { }
	private:
	};

	class IGUIElement
	{
	protected:
		IGUIElement(void) { }

	public:
		virtual void SetHidden(bool shouldHide) { }
		virtual ~IGUIElement(void) = 0 { }

	private:
	};
};
#endif