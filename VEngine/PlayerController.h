#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "EntityController.h"

union ALLEGRO_EVENT;

namespace VE
{
	class CPlayer;
	class CPlayerView;
	class CPlayerController: public IEntityController
	{
	protected:

	public:
		/*
		* CPlayerController()
		*
		* Params:
		*	player - The player model that this controller will control. This
		*			 controller will now own the pointer and delete it during destruction.
		*/
		CPlayerController(CPlayer* player, CPlayerView* playerView);
		~CPlayerController(void);
		void HandleEvent(const ALLEGRO_EVENT& ev);
		void Update(double deltaTime);

	private:
		CPlayer* m_player;
		CPlayerView* m_playerView;

		bool m_movedLThisFrame;
		bool m_movedRThisFrame;
	};
}
#endif