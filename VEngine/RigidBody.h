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

		static void Export(lua_State* L);
	private:
		b2Body* m_body;
	};
}

#endif