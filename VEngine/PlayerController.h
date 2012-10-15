#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "EntityController.h"
#include "Physics.h"
#include <vector>

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

		bool IsKeyDown(size_t key) { return m_keys.at(key); }
		/// Makes sure the player is the facing the correct way
		/// when multiple keys are pressed and one is let go.
		void ProcessKeys(void);

		void HandleMouseMove(const ALLEGRO_EVENT& ev);
	public:
		/// @param player The player model that this controller will control.
		CPlayerController(CPlayer* player);
		~CPlayerController(void);

		void HandleEvent(const ALLEGRO_EVENT& ev);
		void Update(double deltaTime);

		void SetPlayer(CPlayer* player);
		inline CPlayer* GetPlayer(void) const { return m_player; }
		static void Export(lua_State* L);
	private:
		CPlayer* m_player;
		std::vector<bool> m_keys;
		bool m_movedLThisFrame;
		bool m_movedRThisFrame;
		bool m_movedUpThisFrame;
		bool m_movedDownThisFrame;

		b2Vec2 m_mousePos;
	};
}
#endif