#ifndef PLAYER_H
#define PLAYER_H

#include "Physics.h"
#include "Entity.h"
#include "Observable.h"

namespace VE
{
	class CPlayer: public IEntity
	{
	protected:

	public:
		CPlayer(void);
		void Update(double deltatime);

		b2Vec2 Position(void) const { return m_pos; }

		void MoveLeft(void);
		void MoveRight(void);

		// AdvanceLevel is for testing if observer class
		void AdvanceLevel(void);

		void SubscribeTo(const std::string& topic, IObserver* observer) { m_publisher.Register(topic, observer); }
		void SubscribeFrom(const std::string& topic, IObserver* observer) { m_publisher.Deregister(topic, observer); }
		void SubscribeFromAll(IObserver* observer) { m_publisher.Deregister(observer); }

	private:
		// m_pos is for testing. Will be removed.
		b2Vec2 m_pos;
		CObservable m_publisher;
		int m_level;
	};
}
#endif