#ifndef GAMELEVELCONTROLLER_H
#define GAMELEVELCONTROLLER_H

#include "SystemController.h"

union ALLEGRO_EVENT;

namespace VE
{
	class IEvent;
	class CGameLevel;
	class CRender;
	class CGameLevelController: public ISystemController
	{
	protected:
		virtual void Notify(IEvent* ev = nullptr);

		virtual void PushSystemEvent(ALLEGRO_EVENT& ev) ;
		virtual void Update(double deltaTime);
		virtual void Render(void);


	public:
		CGameLevelController(void);
		~CGameLevelController(void);

		CGameLevel* GameLevel(void) const { return m_gameLevel; }
	private:
		CGameLevel* m_gameLevel;
	};
}
#endif