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
			.def("GetPlayer", &CGameLevel::GetPlayer)
			.def("GetRenderer", &CGameLevel::Renderer)
			.def("GetPhysics", &CGameLevel::Physics)			
			//.def("AddAnimation", &CGameLevel::AddAnimation)
			//.def("RemoveAnimation", &CGameLevel::RemoveAnimation)
			//.def("AddEntity", &CGameLevel::AddEntity)
			//.def("RemoveEntity", &CGameLevel::RemoveEntity)
			.def("SetMainScript", &CGameLevel::SetMainScript)
			.def("GetMap", &CGameLevel::GetMap)
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
			.def("SetXSpeed", &CPlayer::SetXSpeed)
			.def("SetYSpeed", &CPlayer::SetYSpeed)
			.def("GetXSpeed", &CPlayer::GetXSpeed)
			.def("GetYSpeed", &CPlayer::GetYSpeed)
		];
	/// CPlayerController
	luabind::module(L)
		[
			class_<CPlayerController>("CPlayerController")
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

	/// Tiled::CMapFile
	luabind::module(L)
		[
			class_<Tiled::CMapFile>("CMapFile")
			//.def(constructor<>())
			//.def("Read", (bool(Tiled::CMapFile::*)(const std::string&)) &Tiled::CMapFile::Read)
			//.def("ReadFromTable", (bool(Tiled::CMapFile::*)(const luabind::object&)) &Tiled::CMapFile::Read)
			.def("GetVersion", &Tiled::CMapFile::GetVersion)
			.def("GetOrientation", &Tiled::CMapFile::GetOrientation)
			//.def("GetProperties",
			.def("GetWidth", &Tiled::CMapFile::GetWidth)
			.def("GetHeight",&Tiled::CMapFile::GetHeight)
			.def("GetTileWidth", &Tiled::CMapFile::GetTileWidth)
			.def("GetTileHeight", &Tiled::CMapFile::GetTileHeight)
			.def("GetTileLayers",  &Tiled::CMapFile::GetTileLayers)
			.def("GetObjectLayers", &Tiled::CMapFile::GetObjectLayers)
			.def("GetTilesets", &Tiled::CMapFile::GetTilesets)
			.def("IsValid", &Tiled::CMapFile::IsValid)
		];

	luabind::module(L)
		[
			class_<CGameMap, Tiled::CMapFile>("CGameMap")
		];

	luabind::module(L)
		[
			class_<IWeapon>("IWeapon")
			.def("GetAmmoCount", &IWeapon::GetAmmoCount)
			.def("GetMaxAmmo", &IWeapon::GetMaxAmmo)
			.def("GetRarity", &IWeapon::GetRarity)
		];

	/// CWeaponAK47
	luabind::module(L)
		[
			class_<CWeaponAK47, IWeapon>("CWeaponAK47")
			.def("GetPlayer()", &CWeaponAK47::GetPlayer)
		];
}