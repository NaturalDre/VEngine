#ifndef PLAYEREVENTS_H
#define PLAYEREVENTS_H

#include "Event.h"
#include "Constants.h"
#include <allegro5\allegro5.h>

namespace VE
{
	class DirectionChanged: public IEvent
	{
	private:

	public:
		DirectionChanged(Direction dir): IEvent(ALLEGRO_GET_EVENT_TYPE('D', 'I', 'R', 'C')), m_dir(dir) { }
		Direction GetDir(void) const { return m_dir; }
	private:
		Direction m_dir;
	};
};

#endif