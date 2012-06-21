#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "View.h"
#include "Observer.h"
namespace VE
{
	class CPlayer;
	class CRender;
	class CPlayerView: public IView, public IObserver
	{
	protected:
		void Draw(void);
		void Notify(IEvent* ev = nullptr);
	public:
		CPlayerView(CRender* render);
		~CPlayerView(void);

		CPlayer* Player(void) const { return m_player; }
		void SetPlayer(CPlayer* player);

	private:
		// For testing
		bool m_leveled;
		// For testing
		int m_level;
		CPlayer* m_player;
	};
}
#endif