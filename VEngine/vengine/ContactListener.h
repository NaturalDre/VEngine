#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <vengine\Physics.h>
#include <set>


namespace VE
{
	class CContactListener;
}

namespace VE
{
	class FixtureCallback
	{
		friend CContactListener;

	protected:
		virtual void BeginContact(b2Contact* contact) {};

		virtual void EndContact(b2Contact* contact) {};

		virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {};

		virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {};

		virtual void PostTimeStep(void) {};
	public:
		FixtureCallback(void);
		virtual ~FixtureCallback(void);

	private:
	};

	class CApplicationImpl;

	class CContactListener: public b2ContactListener
	{
		friend FixtureCallback;
		friend CApplicationImpl;
	protected:
		void BeginContact(b2Contact* contact);

		void EndContact(b2Contact* contact);

		void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
		// Called directly after a timestep has completed.
		void PostTimeStep(void);

		void AttachCallback(FixtureCallback* callback) { m_fixtureCallbacks.insert(callback); }
		void DetatchCallback(FixtureCallback* callback) { m_fixtureCallbacks.erase(callback); }

		FixtureCallback* GetCallbackA(b2Contact*);
		FixtureCallback* GetCallbackB(b2Contact*);


	public:
		CContactListener(void);
		~CContactListener(void);

		FixtureCallback* FindCallback(void* callback);
	private:
		std::set<FixtureCallback*> m_fixtureCallbacks;
	};

	CContactListener* GetContactListener(void);
}
#endif