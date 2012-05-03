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
	class CApplicationImpl;

	class CContactListener: public b2ContactListener
	{
		friend CApplicationImpl;
	protected:
		void BeginContact(b2Contact* contact);

		void EndContact(b2Contact* contact);

		void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
		// Called directly after a timestep has completed.
		void PostTimeStep(void);


	public:
		CContactListener(void);
		~CContactListener(void);

	private:

	};

	CContactListener* GetContactListener(void);
}
#endif