#ifndef PLAYER_H
#define PLAYER_H

#include <vengine\Character\Character.h>
#include <vengine\Animation\BasicAnimation.h>
#include <vengine\Physics.h>
#include <vengine\Utility.h>
#include <memory>
#include <lua.hpp>

struct ALLEGRO_BITMAP;

using namespace NE;
namespace VE
{
	class CBasicAnimation;
	class IRenderListener;
}

namespace VE
{
	class CPlayer: public ICharacter
	{
	public:
		//////////////////////
		////// Render ////////
		//////////////////////
		class Render
		{
			friend CPlayer;
		protected:

		public:
			/* 
			 * Pass player object to render. Does not own.
			 * Only a player object should be creating these.
			 * Must be deleted before player object is to avoid
			 * using the player pointer after it has been freed.
			 */
			Render(CPlayer* player);
			// Destructor
			~Render(void);

		private:
			CPlayer *const m_player;
			CBasicAnimation m_animation;
			std::shared_ptr<ALLEGRO_BITMAP> m_playerSprite;
		};

		void OnUpdate(void);
		void Interact(void);

	protected:
			void CreateBody(b2Vec2& posMtrs, float widthMtrs, float heightMtrs);
			void CreateBody(const Utility::TiledObject& data);
			static CPlayer* Create(void);

	public:	
		// Destructor
		~CPlayer(void);

		b2Vec2 GetPos(void) const { return m_body->GetPosition(); }


		static int L_Create(lua_State* L);
	private:
		// Constructor
		CPlayer(void);

		// Draws the player at render time
		std::unique_ptr<IRenderListener> m_render;
		// 
		std::unique_ptr<b2Body, Utility::b2BodyDtor> m_body;
	};
}
#endif