#ifndef PLAYER_H
#define PLAYER_H

#include "Physics.h"

namespace VE
{
	class CPlayer
	{
	protected:

	public:
		CPlayer(void);
		void Update(double deltatime);

		b2Vec2 Position(void) const { return m_pos; }

		void MoveLeft(void);
		void MoveRight(void);

	private:
		// m_pos is for testing. Will be removed.
		b2Vec2 m_pos;
	};
}
#endif