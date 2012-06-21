#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <unordered_map>
#include <unordered_set>
#include <string>

namespace VE
{
	class IEvent;
	class IObserver;
	typedef std::unordered_map<std::string,  std::unordered_set<IObserver*>> ObserverTopics;

	class CObservable
	{
	protected:

	public:
		CObservable(void) { }
		~CObservable(void) { }

		void NotifyAll(IEvent* ev);
		void NotifyAll(const std::string& topic, IEvent* ev);

		// Register with specific topic
		void Register(const std::string& topic, IObserver* observer);
		// Deregister from specific topic
		void Deregister(const std::string& topic, IObserver* observer);
		// Deregister from all topics.
		void Deregister(IObserver* observer);

	private:
		ObserverTopics m_topics;

		CObservable(const CObservable&);
		void operator==(const CObservable&);
	};
}
#endif