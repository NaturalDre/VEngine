#include "Observable.h"
#include "Observer.h"
#include "Event.h"

namespace VE
{
	void CObservable::NotifyAll(IEvent* ev)
	{
		for(auto topicIter = m_topics.begin(); topicIter != m_topics.end(); ++topicIter)
			for(auto obsIter = topicIter->second.begin(); obsIter != topicIter->second.end(); ++obsIter)
				(*obsIter)->Notify(ev);
	}

	void CObservable::NotifyAll(const std::string& topic, IEvent* ev)
	{
		auto topicIter = m_topics.find(topic);
		if (topicIter == m_topics.end())
			return;

		for (auto obsIter = topicIter->second.begin(); obsIter != topicIter->second.end(); ++obsIter)
		{
			(*obsIter)->Notify(ev);
		}

		delete ev;
	}

	void CObservable::Register(const std::string& topic, IObserver* observer)
	{
		m_topics[topic].insert(observer);
	}

	void CObservable::Deregister(const std::string& topic, IObserver* observer)
	{
		auto iter = m_topics.find(topic);
		if (iter != m_topics.end())
			iter->second.insert(observer);
	}

	void CObservable::Deregister(IObserver* observer)
	{
		for(auto topicIter = m_topics.begin(); topicIter != m_topics.end(); ++topicIter)
			topicIter->second.erase(observer);
	}
}