#include "LuabindExport.h"
#include <luabind\luabind.hpp>
#include <luabind\adopt_policy.hpp>

#include "Script.h"
#include "RigidBody.h"
#include "GameLevel.h"
#include "Render.h"
#include "Player.h"
#include "PlayerController.h"
#include "Animation.h"
#include "Physics.h"

using namespace luabind;
using namespace VE;

void ExportBindings(lua_State* L)
{
	/// CScript
	luabind::module(L)
		[
			class_<CScript>("Script")
			.def(constructor<const object&>())
		];
	/// CRigidBody
	luabind::module(L)
		[
			class_<CRigidBody>("RigidBody")
			.def(constructor<const object&>())
			.def("Free", &CRigidBody::Free)
		];
	/// CGameLevel
	luabind::module(L)
		[
			class_<CGameLevel>("GameLevel")
			.def(constructor<>())
			.def("AddPlayer", &CGameLevel::AddPlayer)
			.def("RemovePlayer", &CGameLevel::RemovePlayer)
			.def("GetPlayer", &CGameLevel::GetPlayer)
			.def("GetRenderer", &CGameLevel::Renderer)
			.def("GetPhysics", &CGameLevel::Physics)			
			.def("AddAnimation", &CGameLevel::AddAnimation)
			.def("RemoveAnimation", &CGameLevel::RemoveAnimation)
			.def("AddEntity", &CGameLevel::AddEntity)
			.def("RemoveEntity", &CGameLevel::RemoveEntity)
			.def("LoadMap", &CGameLevel::LoadMap)			
		];
	/// CPlayer
	luabind::module(L)
		[
			class_<IEntity>("Entity"),
			class_<CPlayer, IEntity>("Player")
			.def("SetXSpeed", &CPlayer::SetXSpeed)
			.def("SetYSpeed", &CPlayer::SetYSpeed)
			.def("GetXSpeed", &CPlayer::GetXSpeed)
			.def("GetYSpeed", &CPlayer::GetYSpeed)
		];
	/// CPlayerController
	luabind::module(L)
		[
			class_<CPlayerController>("PlayerController")
			.def("SetPlayer", &CPlayerController::SetPlayer)
			.def("GetPlayer", &CPlayerController::GetPlayer)
		];

	/// b2Vec2
	luabind::module(L)
		[
			class_<b2Vec2>("b2Vec2")
			.def(constructor<>())
			.def(constructor<float, float>())
			.def("SetZero", &b2Vec2::SetZero)
			.def("Length", &b2Vec2::Length)
			.def("LengthSquared", &b2Vec2::LengthSquared)
			.def("Normalize", &b2Vec2::Normalize)
			.def("IsValid", &b2Vec2::IsValid)
			.def("Skew", &b2Vec2::Skew)
			.def_readwrite("x", &b2Vec2::x)
			.def_readwrite("y", &b2Vec2::y)
		];
}