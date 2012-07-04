#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "EntityController.h"
#include <vector>

union ALLEGRO_EVENT;

namespace VE
{
	//struct KeyState
	//{
	//	bool isDown;
	//	
	//};

	class CPlayer;
	class CPlayerView;
	class CPlayerController: public IEntityController
	{
	protected:


		void HandleKeyDown(const ALLEGRO_EVENT& ev);
		void HandleKeyUp(const ALLEGRO_EVENT& ev);

		bool IsKeyDown(size_t key) { return m_keys.at(key); }
		// Makes sure the player is the facing the correct way
		// when multiple keys are pressed and one is let go.
		void ProcessKeys(void);
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
		std::vector<bool> m_keys;
		bool m_movedLThisFrame;
		bool m_movedRThisFrame;
		bool m_movedUpThisFrame;
		bool m_movedDownThisFrame;
	};
}
#endif