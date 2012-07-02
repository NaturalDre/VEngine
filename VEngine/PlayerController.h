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
		void HandleKeyDown(const ALLEGRO_EVENT& ev);
		void HandleKeyUp(const ALLEGRO_EVENT& ev);

	public:
		/*
		* CPlayerController()
		*
		* Params:
		*	player - The player model that this controller will control.
		*/
		CPlayerController(CPlayer* player = nullptr);
		~CPlayerController(void);

		void HandleEvent(const ALLEGRO_EVENT& ev);
		void Update(double deltaTime);

		void SetPlayer(CPlayer* player);

	private:
		CPlayer* m_player;

		bool m_movedLThisFrame;
		bool m_movedRThisFrame;
		bool m_movedUpThisFrame;
		bool m_movedDownThisFrame;
	};
}
#endif