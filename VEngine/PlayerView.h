#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "View.h"
#include "Observer.h"
#include "Bitmap.h"

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
		CPlayer* m_player;
		CBitmap m_bitmap;
	};
}
#endif