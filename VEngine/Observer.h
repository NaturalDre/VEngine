#ifndef OBSERVER_H
#define OBSERVER_H

namespace VE
{
	class IEvent;
	class IObserver
	{
	protected:

	public:
		virtual void Notify(IEvent* ev = nullptr) = 0;
		virtual ~IObserver(void) {}
	private:

	};
}

#endif