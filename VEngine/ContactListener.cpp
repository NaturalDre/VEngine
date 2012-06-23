#include "ContactListener.h"
#include <Box2D\Box2D.h>

namespace VE
{
	void CContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fA = contact->GetFixtureA();
		b2Fixture* fB = contact->GetFixtureB();

		if (fA)
		{
			IContactCallback* cbA = static_cast<IContactCallback*>(fA->GetUserData());
			if (cbA)
				cbA->BeginContact(contact);
		}
		if (fB)
		{
			IContactCallback* cbB = static_cast<IContactCallback*>(fB->GetUserData());
			if (cbB)
				cbB->BeginContact(contact);
		}
	}

	void CContactListener::EndContact(b2Contact* contact)
	{
		b2Fixture* fA = contact->GetFixtureA();
		b2Fixture* fB = contact->GetFixtureB();

		if (fA)
		{
			IContactCallback* cbA = static_cast<IContactCallback*>(fA->GetUserData());
			if (cbA)
				cbA->EndContact(contact);
		}
		if (fB)
		{
			IContactCallback* cbB = static_cast<IContactCallback*>(fB->GetUserData());
			if (cbB)
				cbB->EndContact(contact);
		}
	}

	void CContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		b2Fixture* fA = contact->GetFixtureA();
		b2Fixture* fB = contact->GetFixtureB();

		if (fA)
		{
			IContactCallback* cbA = static_cast<IContactCallback*>(fA->GetUserData());
			if (cbA)
				cbA->PreSolve(contact, oldManifold);
		}
		if (fB)
		{
			IContactCallback* cbB = static_cast<IContactCallback*>(fB->GetUserData());
			if (cbB)
				cbB->PreSolve(contact, oldManifold);
		}
	}

	void CContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{
		b2Fixture* fA = contact->GetFixtureA();
		b2Fixture* fB = contact->GetFixtureB();

		if (fA)
		{
			IContactCallback* cbA = static_cast<IContactCallback*>(fA->GetUserData());
			if (cbA)
				cbA->PostSolve(contact, impulse);
		}
		if (fB)
		{
			IContactCallback* cbB = static_cast<IContactCallback*>(fB->GetUserData());
			if (cbB)
				cbB->PostSolve(contact, impulse);
		}
	}
}