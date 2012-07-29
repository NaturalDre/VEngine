#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "View.h"
#include "Observer.h"
#include "MultiAnimation.h"
#include "Common.h"

namespace VE
{
	class CPlayer;
	class CRender;
	class CPlayerView: public IView, public IObserver
	{
	protected:
		void Draw(void);
		void Notify(int eventCode);
		void ChangeDirection(DIRECTION dir);
	public:
		CPlayerView(CRender* render);
		~CPlayerView(void);

		CPlayer* Player(void) const { return m_player; }
		void SetPlayer(CPlayer* player);

	private:
		CPlayer* m_player;
		CMultiAnimation m_anims;
	};
}
#endif