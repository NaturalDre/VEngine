#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Physics.h"

namespace luabind
{
	namespace adl
	{
		class object;
	}
}

namespace VE
{
	class CRigidBody
	{
	public:
		CRigidBody(const luabind::adl::object& obj);
		~CRigidBody(void);

		void Free(void);

	private:
		b2Body* m_body;
	};
}

#endif