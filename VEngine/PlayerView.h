#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "View.h"

namespace VE
{
	class CPlayer;
	class CRender;
	class CPlayerView: public IView
	{
	protected:
		void Draw(void);

	public:
		CPlayerView(CRender* render);
		~CPlayerView(void);

		CPlayer* Player(void) const { return m_player; }
		void SetPlayer(CPlayer* player);

	private:
		CPlayer* m_player;
	};
}
#endif