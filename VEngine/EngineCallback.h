#ifndef ENGINECALLBACK_H
#define ENGINECALLBACK_H

union ALLEGRO_EVENT;

namespace VE
{
	class IEngineCallback
	{
	public:
		virtual ~IEngineCallback(void) { };

		virtual void HandleEvent(const ALLEGRO_EVENT& ev) = 0;
		virtual void Render(void) = 0;
	};
}
#endif