#ifndef ABSTRACTLEVELMODEL_H
#define ABSTRACTLEVELMODEL_H

#include <string>
#include <unordered_set>
#include <set>
#include <luabind\object.hpp>

struct lua_State;

namespace Tiled
{
	class CMapFile;
}

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
	class CGameLevel//: public IObject
	{
	protected:

	public:
		CGameLevel(void);
		~CGameLevel(void);

		/// Calls Update on all Updatable Controllers
		void UpdateAll(double deltaTime);

		void AddPlayer(void);
		void RemovePlayer(void);

		CPlayer* GetPlayer(void) const;
		inline CPlayerController* GetPlayerController(void) const { return m_playerController; }

		inline CRender* Renderer(void) const { return m_renderer; }
		inline CPhysics* Physics(void) const { return m_physics; }

		void AddAnimation(IAnimation* anim) { m_animations.insert(anim); }
		void RemoveAnimation(IAnimation* anim) { m_animations.erase(anim); }

		void AddEntity(IEntity* entity) { m_controllers.insert(entity); }
		void RemoveEntity(IEntity* entity) { m_controllers.erase(entity); }

		lua_State* GetScriptEnv(void) const { return m_scriptEnv; }
		void SetScriptEnv(lua_State* L);

		void LoadMap(const std::string& filename);

		void SetMainScript(const luabind::object& mainScript) { m_mainScript = mainScript; }

	private:
		typedef std::unordered_set<IEntity*> EntitySet;
		typedef std::unordered_set<IAnimation*> AnimationSet;

		EntitySet m_controllers;
		AnimationSet m_animations;

		CPlayer* m_player;
		CPlayerView* m_playerView;
		CPlayerController* m_playerController;

		CRender* m_renderer;
		CPhysics* m_physics;
		Tiled::CMapFile* m_mapFile;
		luabind::object m_mainScript;
		lua_State* m_scriptEnv;
	};

	CGameLevel* GameLevel(void);
}
#endif