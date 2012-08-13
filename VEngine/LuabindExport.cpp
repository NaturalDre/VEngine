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
#include "WeaponAK47.h"
#include "GameMap.h"
using namespace luabind;
using namespace VE;

void ExportBindings(lua_State* L)
{
	// Allegro
	luabind::module(L)
		[
			def("al_get_time", &al_get_time)
		];

	// CErrorLogger
	luabind::module(L)
		[
			class_<CErrorLogger>("CErrorLogger")
			.def("LogError", &CErrorLogger::LogError)
			.def("LogNote", &CErrorLogger::LogNote)
		];

	/// CScript
	luabind::module(L)
		[
			class_<CScript>("CScript")
			.def(constructor<const object&>())
		];
	/// CRigidBody
	luabind::module(L)
		[
			class_<CRigidBody>("CRigidBody")
			.def(constructor<const object&>())
			.def("Free", &CRigidBody::Free)
		];
	/// CGameLevel
	luabind::module(L)
		[
			class_<CGameLevel>("CGameLevel")
			//.def(constructor<>())
			.def("AddPlayer", &CGameLevel::AddPlayer)
			.def("RemovePlayer", &CGameLevel::RemovePlayer)
			.property("player", &CGameLevel::GetPlayer)
			.property("renderer", &CGameLevel::GetRenderer)
			.property("physics", &CGameLevel::GetPhysics)
			.property("map", &CGameLevel::GetMap)
			.def("SetMainScript", &CGameLevel::SetMainScript)
			.def("LoadMap", &CGameLevel::LoadMap)			
		];

	/// IEntity
	luabind::module(L)
		[
			class_<IEntity>("IEntity")
		];

	/// CPlayer
	luabind::module(L)
		[
			class_<CPlayer, IEntity>("CPlayer")
			.property("speedX", &CPlayer::GetXSpeed, &CPlayer::SetXSpeed)
			.property("speedY", &CPlayer::GetYSpeed, &CPlayer::SetYSpeed)
			.property("speed", &CPlayer::GetSpeed, &CPlayer::SetSpeed)
		];
	/// CPlayerController
	luabind::module(L)
		[
			class_<CPlayerController>("CPlayerController")
			.property("player", &CPlayerController::GetPlayer, &CPlayerController::SetPlayer)
		];

	/// b2Vec2
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

	/// Tiled::CMapFile
	luabind::module(L)
		[
			class_<Tiled::CMapFile>("CMapFile")
			.property("version", &Tiled::CMapFile::GetVersion)
			.property("orientation", &Tiled::CMapFile::GetOrientation)

			.property("width", &Tiled::CMapFile::GetWidth)
			.property("height",&Tiled::CMapFile::GetHeight)
			.property("tileWidth", &Tiled::CMapFile::GetTileWidth)
			.property("tileHeight", &Tiled::CMapFile::GetTileHeight)
			//.property("tileLayers",  &Tiled::CMapFile::GetTileLayers)
			//.property("objectLayers", &Tiled::CMapFile::GetObjectLayers)
			//.property("tilesets", &Tiled::CMapFile::GetTilesets)
			.property("IsValid", &Tiled::CMapFile::IsValid)
		];

	luabind::module(L)
		[
			class_<CGameMap, Tiled::CMapFile>("CGameMap")
		];

	luabind::module(L)
		[
			class_<IWeapon>("IWeapon")
			.property("ammo", &IWeapon::GetAmmoCount)
			.property("maxAmmo", &IWeapon::GetMaxAmmo)
			.property("rarity", &IWeapon::GetRarity)
		];

	/// CWeaponAK47
	luabind::module(L)
		[
			class_<CWeaponAK47, IWeapon>("CWeaponAK47")
			.property("player", &CWeaponAK47::GetPlayer)
		];
}