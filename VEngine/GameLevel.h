#ifndef ABSTRACTLEVELMODEL_H
#define ABSTRACTLEVELMODEL_H

#include "Process.h"
//#include "EngineCallback.h"
#include "Engine.h"
#include <string>
#include <unordered_set>
#include <luabind\object.hpp>
#include "Locator.h"
struct lua_State;

namespace VE
{
	class IEntity;
	class IView;
	class IAnimation;
	class CCamera;
	class CRender;
	class CPhysics;
	class CPlayer;
	class CPlayerView;
	class CPlayerController;
	class CEngine;
	class CGameMap;
	class CGameLevel:/* public IEngineCallback, */public IProcess
	{
	protected:
		void Think(double dt);
		void FreeMarkedEntities(void);
	public:
		CGameLevel(CEngine* engine);
		~CGameLevel(void);

		void AddPlayer(void);
		void RemovePlayer(void);

		CPlayer* GetPlayer(void) const;
		inline CPlayerController* GetPlayerController(void) const { return m_playerController; }

		CPhysics* GetPhysics(void) const { return m_engine->GetPhysics(); }

		void AddAnimation(IAnimation* anim) { m_animations.insert(anim); }
		void RemoveAnimation(IAnimation* anim) { m_animations.erase(anim); }

		void AddEntity(IEntity* entity) { m_entities.insert(entity); }
		void RemoveEntity(IEntity* entity) { m_entities.erase(entity); }

		void MarkForDeletion(IEntity* entity) { if (entity) m_entitiesToDelete.insert(entity); }

		lua_State* GetScriptEnv(void) const { return m_scriptEnv; }
		void SetScriptEnv(lua_State* L);

		const luabind::object& GetMainScript(void) const { return m_mainScript; }
		void SetMainScript(const luabind::object& mainScript) { m_mainScript = mainScript; }

		inline CGameMap* GetMap(void) const { return m_gameMap; }
		void LoadMap(const std::string& filename);

		inline CErrorLogger* GetLogger(void) const { return m_logger; }

		static void Export(lua_State* L);
	private:
		typedef std::unordered_set<IEntity*> EntitySet;
		typedef std::unordered_set<IAnimation*> AnimationSet;

		luabind::object m_mainScript;

		EntitySet m_entities;
		EntitySet m_entitiesToDelete;
		AnimationSet m_animations;

		CEngine* m_engine;
		CPlayer* m_player;
		CPlayerView* m_playerView;
		CPlayerController* m_playerController;
		CErrorLogger* m_logger;


		CGameMap* m_gameMap;

		lua_State* m_scriptEnv;
	};

	CGameLevel* GameLevel(void);
}
#endif