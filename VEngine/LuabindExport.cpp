#include "LuabindExport.h"
#include <luabind\luabind.hpp>
#include <luabind\adopt_policy.hpp>
#include <allegro5\altime.h>
#include "Script.h"
#include "RigidBody.h"
#include "GameLevel.h"
#include "Render.h"
#include "Player.h"
#include "PlayerController.h"
#include "Animation.h"
#include "Physics.h"
#include "TMR\MapFile.h"
#include "ErrorLogger.h"
#include "ContactCallback.h"
#include "GameMap.h"

using namespace luabind;
using namespace VE;

void Export_allegro(lua_State* L)
{
	// Allegro
	luabind::module(L)
		[
			def("al_get_time", &al_get_time)
		];
}

void Export_b2Vec2(lua_State* L)
{
	luabind::module(L)
		[
			class_<b2Vec2>("b2Vec2")
			.def(constructor<>())
			.def(constructor<float, float>())
			.def("SetZero", &b2Vec2::SetZero)
			.property("length", &b2Vec2::Length)
			.def("LengthSquared", &b2Vec2::LengthSquared)
			.def("Normalize", &b2Vec2::Normalize)
			.def("IsValid", &b2Vec2::IsValid)
			.def("Skew", &b2Vec2::Skew)
			.def_readwrite("x", &b2Vec2::x)
			.def_readwrite("y", &b2Vec2::y)
		];
}

void ExportBindings(lua_State* L)
{

	Export_allegro(L);
	CPhysics::Export(L);

	IContactCallback::Export(L);
	IEntity::Export(L);

	CErrorLogger::Export(L);
	CScript::Export(L);
	CRigidBody::Export(L);
	CGameLevel::Export(L);

	CPlayer::Export(L);
	CPlayerController::Export(L);

	Export_b2Vec2(L);


	Tiled::CMapFile::Export(L);
	CGameMap::Export(L);
}