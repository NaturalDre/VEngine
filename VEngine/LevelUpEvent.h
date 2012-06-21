#ifndef LEVELUPEVENT_H
#define LEVELUPEVENT_H

#include "Event.h"

namespace VE
{
	class CPlayer;
	// This is just a test event to test the observer class, it will be deleted
	class LevelUpEvent: public IEvent
	{
	public:
		LevelUpEvent(CPlayer* player, int level): IEvent(ALLEGRO_GET_EVENT_TYPE('L', 'V', 'L', 'U')), m_player(player), m_level(level) { }

		int Level(void) const { return m_level; }
		CPlayer* Player(void) const { return m_player; }

	private:
		CPlayer* m_player;
		int m_level;
	};
}
#endif