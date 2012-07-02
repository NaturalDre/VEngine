#ifndef PLAYERBODY_H
#define PLAYERBODY_H

#include "ContactCallback.h"

class b2Body;
class b2World;

namespace VE
{

	class CPlayer;
	class CPlayerBody: public IContactCallback
	{
	public:
		CPlayerBody(CPlayer* player, b2World* world);
		~CPlayerBody(void);

		b2Body* Raw(void) const { return m_body; }
		b2Vec2 Position(void) const;

	private:
		b2World* m_world;
		b2Body* m_body;
		CPlayer* m_player;
	};
}
#endif