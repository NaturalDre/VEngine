#ifndef PLAYER_H
#define PLAYER_H

#include "Physics.h"
#include "Entity.h"
#include "Observable.h"

namespace VE
{
	class CPlayerBody;
	class CPlayer: public IEntity
	{
	protected:
		CPlayer(CGameLevel* level);

	public:
		virtual ~CPlayer(void);

		/**
		* Called every frame for the object to update itself based on the current state of the game.
		* @param deltatime Amount of time since Update was last called.
		*/
		void Update(double deltatime);
		/**
		* Returns the position of the player.
		* @return The position in meters.
		*/
		b2Vec2 Position(void) const;
		void SetXSpeed(float x);
		void SetYSpeed(float y);
		void SetSpeed(const b2Vec2& speed);

		float GetXSpeed(void) const;
		float GetYSpeed(void) const;
		b2Vec2 GetSpeed(void) const;

		/**
		* Contains the physics properties and handles callbacks sent by
		* the physics engine.
		*/
		//CPlayerBody* Body(void) const { return m_body; }
		void MoveLeft(void);
		void MoveRight(void);

		// AdvanceLevel is for testing if observer class
		void AdvanceLevel(void);
		//void SetBody(b2Body* body) { m_body = body; }
		/**
		* Subscribe to a specific set of events that this object generates.
		*
		* List of Topics: Currently there are none.
		* @param topic The kinds of events you want to listen for. 
		* @param observer The object who will be notified of these events.
		*/
		void SubscribeTo(const std::string& topic, IObserver* observer);
		/**
		* Subscribe from a set of events that this object generates.
		*
		* @param topic The topic you no longer to to be notified about.
		* @param observer The object that no longer wants these events.
		*/
		void SubscribeFrom(const std::string& topic, IObserver* observer);
		/**
		* Subscribe from all events that this object generates.
		*
		* @param observer The object that no longer wants to listen to events from this object.
		*/
		void SubscribeFromAll(IObserver* observer);
	};

	CPlayer* CreatePlayer(CGameLevel* level);
}
#endif