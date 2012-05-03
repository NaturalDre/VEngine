#ifndef PLAYER_H
#define PLAYER_H

#include <vengine\Character\Character.h>
#include <vengine\Animation\BasicAnimation.h>
#include <vengine\Physics.h>
#include <vengine\Utility.h>
#include <vengine\InputListener.h>
#include <memory>
#include <vector>
#include <lua.hpp>
#include <vengine\Application.h>
#include <vengine\Render\RenderListener.h>

struct ALLEGRO_BITMAP;

using namespace NE;

namespace VE
{
	class CBasicAnimation;
	class IRenderListener;
};

namespace VE
{
	enum  PLAYERCONTROLS {
		PL_JUMP = ALLEGRO_KEY_W
		, PL_LEFT = ALLEGRO_KEY_A
		, PL_RIGHT = ALLEGRO_KEY_D
	};


	class CPlayer: public ICharacter
	{
	protected:
		//////////////////////
		//////// Input ///////
		//////////////////////
		class Input: public IInputListener
		{
			friend CPlayer;
		protected:
			void OnUpdate(void);

			void OnKeyDown(int keyCode);
			void OnKeyUp(int keyCode);

			void OnMouseButtonDown(ALLEGRO_EVENT* ev);
			void OnMouseButtonUp(ALLEGRO_EVENT* ev);

			void OnMouseMoved(ALLEGRO_EVENT* ev);
		public:
			Input(CPlayer* player);
			~Input(void);


			// Is the left key down right now?
			bool IsLKeyDown(void) { return m_moveLKeyDown; }
			// Is the right key down right now?
			bool IsRKeyDown(void) { return m_moveRKeyDown; }
			// Are both the left and right keys down right now?
			bool IsBothLRKeysDown(void) { return (m_moveLKeyDown && m_moveRKeyDown); }
			// Did the left key go down this frame?
			bool LKeyDownThisFrame(void) { return (GetApp()->GetIngameTicks() == m_frameMoveLPressed); }
			// Did the right key go down this frame?
			bool RKeyDownThisFrame(void) { return (GetApp()->GetIngameTicks() == m_frameMoveRPressed); }

			bool IsJumpKeyDown(void) { return m_keys[VE::PL_JUMP]; }
			bool IsUseKeyDown(void) { return m_useKeyDown; }
			bool IsLeftMouseDown(void) { return m_leftMouseDown; }

			bool IsKeyDown(int keyCode);
			bool KeyDownThisFrame(int keyCode);
		private:
			CPlayer* m_player;
			std::vector<bool> m_keys;
			std::vector<double> m_frameKeyDown;
			// These variables keep track of which frame a key was last pressed.
			double m_frameMoveRPressed;
			double m_frameMoveLPressed;
			double m_frameMoveUpPressed;
			double m_frameMoveDownPressed;

			// These variables keep track of whether a key is down right now
			bool m_moveRKeyDown;
			bool m_moveLKeyDown;
			bool m_jumpKeyDown;
			bool m_moveDownKeyDown;
			bool m_useKeyDown;

			bool m_leftMouseDown;
		};
		//////////////////////
		////// Render ////////
		//////////////////////
		class Render: public VE::IRenderListener
		{
			friend CPlayer;
		protected:
			void Draw(void);
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
		void CreateBody(const Tiled::TiledObject& data);
		void OnBeginContact(b2Contact* contact);
		void OnEndContact(b2Contact* contact);
		void HandleBeginContact(b2Fixture* us, b2Fixture* them);
		void HandleEndContact(b2Fixture* us, b2Fixture* them);


		
		static CPlayer* Create(void);

	public:	
		// Destructor
		~CPlayer(void);

		b2Vec2 GetPos(void) const { return m_body->GetPosition(); }
		bool IsGrounded(void) const;



		static int L_Create(lua_State* L);
	private:
		// Constructor
		CPlayer(void);

		// Draws the player at render time
		std::unique_ptr<IRenderListener> m_render;
		
		CPlayer::Input m_input;

		std::set<b2Fixture*> m_feetTouching;
		b2Fixture* m_feetFixture;
	};
}
#endif