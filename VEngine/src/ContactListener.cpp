#include <vengine\ContactListener.h>
#include <vengine\Application.h>
#include <vengine\GameObject.h>

namespace VE
{
	//*******************************************//
	//**************CONTACT LISTENER*************//
	//*******************************************//
	CContactListener* global(nullptr);

	CContactListener* GetContactListener(void)
	{
		return global;
	}
	CContactListener::CContactListener(void)
	{
		global = this;
	}

	CContactListener::~CContactListener(void)
	{
		global = nullptr;

	}


	void CContactListener::BeginContact(b2Contact* contact)
	{ 
		/* handle begin event */ 
		
		// If Fixture A/B's body has valid IGameObject pointer as it's userdata
		// let that game object know about this BeginContact.
		if (contact->GetFixtureA()->GetBody()->GetUserData())
			contact->GetFixtureA()->GetBody()->GetUserData()->OnBeginContact(contact);
		if (contact->GetFixtureB()->GetBody()->GetUserData())
			contact->GetFixtureB()->GetBody()->GetUserData()->OnBeginContact(contact);
	}

	void CContactListener::EndContact(b2Contact* contact)
	{ 
		/* handle end event */ 

		// If Fixture A/B's body has valid IGameObject pointer as it's userdata
		// let that game object know about this EndContact.
		if (contact->GetFixtureA()->GetBody()->GetUserData())
			contact->GetFixtureA()->GetBody()->GetUserData()->OnEndContact(contact);
		if (contact->GetFixtureB()->GetBody()->GetUserData())
			contact->GetFixtureB()->GetBody()->GetUserData()->OnEndContact(contact);
	}

	void CContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{ 
		/* handle pre-solve event */ 
		if (contact->GetFixtureA()->GetBody()->GetUserData())
			contact->GetFixtureA()->GetBody()->GetUserData()->OnPreSolve(contact, oldManifold);
		if (contact->GetFixtureB()->GetBody()->GetUserData())
			contact->GetFixtureB()->GetBody()->GetUserData()->OnPreSolve(contact, oldManifold);
	}

	void CContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{ 
		/* handle post-solve event */ 
		if (contact->GetFixtureA()->GetBody()->GetUserData())
			contact->GetFixtureA()->GetBody()->GetUserData()->OnPostSolve(contact, impulse);
		if (contact->GetFixtureB()->GetBody()->GetUserData())
			contact->GetFixtureB()->GetBody()->GetUserData()->OnPostSolve(contact, impulse);
	}
}