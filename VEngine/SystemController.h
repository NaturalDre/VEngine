#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

union ALLEGRO_EVENT;

namespace VE
{
	class ISystemController
	{
	public:
		virtual ~ISystemController(void) { };

		virtual void PushSystemEvent(ALLEGRO_EVENT& ev) = 0;
		virtual void Update(double deltaTime) = 0;
		virtual void Render(void) = 0;
	};
}
#endif