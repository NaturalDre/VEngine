#include <vengine\ContactListener.h>

#include <vengine\Application.h>

namespace VE
{
	//*******************************************//
	//**************FIXTURE CALLBACK*************//
	//*******************************************//

	FixtureCallback::FixtureCallback(void)
	{
		GetPhysMgr().GetContactListener()->AttachCallback(this);
	}
	
	FixtureCallback::~FixtureCallback(void)
	{
		GetPhysMgr().GetContactListener()->DetatchCallback(this);
	}

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
		m_fixtureCallbacks.clear();
	}

	FixtureCallback* CContactListener::FindCallback(void* callback) 
	{ 
		auto iter = m_fixtureCallbacks.find(static_cast<FixtureCallback*>(callback)); 
		if (iter != m_fixtureCallbacks.end())
			return *iter;
		return nullptr;
	}

	FixtureCallback* CContactListener::GetCallbackA(b2Contact* contact)
	{
		return FindCallback(contact->GetFixtureA()->GetUserData());
	}
	FixtureCallback* CContactListener::GetCallbackB(b2Contact* contact)
	{
		return FindCallback(contact->GetFixtureB()->GetUserData());
	}

	void CContactListener::BeginContact(b2Contact* contact)
	{ 
		/* handle begin event */ 
		FixtureCallback* cA(GetCallbackA(contact));
		FixtureCallback* cB(GetCallbackB(contact));

		if (cA)
			cA->BeginContact(contact);
		if (cB)
			cB->BeginContact(contact);
	}

	void CContactListener::EndContact(b2Contact* contact)
	{ 
		/* handle end event */ 
		FixtureCallback* cA(GetCallbackA(contact));
		FixtureCallback* cB(GetCallbackB(contact));

		if (cA)
			cA->EndContact(contact);
		if (cB)
			cB->EndContact(contact);
	}

	void CContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{ 
		/* handle pre-solve event */ 
		FixtureCallback* cA(GetCallbackA(contact));
		FixtureCallback* cB(GetCallbackB(contact));

		if (cA)
			cA->PreSolve(contact, oldManifold);
		if (cB)
			cB->PreSolve(contact, oldManifold);
	}

	void CContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{ 
		/* handle post-solve event */ 
		FixtureCallback* cA(GetCallbackA(contact));
		FixtureCallback* cB(GetCallbackB(contact));

		if (cA)
			cA->PostSolve(contact, impulse);
		if (cB)
			cB->PostSolve(contact, impulse);
	}

	void CContactListener::PostTimeStep(void)
	{
		for(auto iter = m_fixtureCallbacks.begin(); iter != m_fixtureCallbacks.end(); ++iter)
			(*iter)->PostTimeStep();
	}
}