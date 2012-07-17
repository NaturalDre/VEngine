#ifndef ABSTRACTLEVELMODEL_H
#define ABSTRACTLEVELMODEL_H

#include <string>
#include <unordered_set>
#include <set>

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
		void Setup(void);

	public:
		CGameLevel(void);
		~CGameLevel(void);

		inline void SetLevelName(const std::string& levelName) { m_levelName = levelName; }
		inline std::string LevelName(void) const { return m_levelName; }

		/// Calls Update on all Updatable Controllers
		void UpdateAll(double deltaTime);

		inline CPlayer* Player(void) const { return m_player; }
		inline CPlayerController* PlayerController(void) const { return m_playerController; }
		void SetPlayerController(CPlayerController* controller);

		inline CRender* Renderer(void) const { return m_renderer; }
		inline CPhysics* Physics(void) const { return m_physics; }

		void AddAnimation(IAnimation* anim) { m_animations.insert(anim); }
		void RemoveAnimation(IAnimation* anim) { m_animations.erase(anim); }

		void AddEntity(IEntity* entity) { m_controllers.insert(entity); }
		void RemoveEntity(IEntity* entity) { m_controllers.erase(entity); }

		lua_State* GetScriptEnv(void) const { return m_scriptEnv; }
		void SetScriptEnv(lua_State* L);

		void LoadMap(const std::string& filename);

	private:
		typedef std::unordered_set<IEntity*> EntitySet;
		typedef std::unordered_set<IAnimation*> AnimationSet;

		std::string m_levelName;
		EntitySet m_controllers;
		AnimationSet m_animations;

		CPlayer* m_player;
		CPlayerView* m_playerView;
		CPlayerController* m_playerController;

		CRender* m_renderer;
		CPhysics* m_physics;
		Tiled::CMapFile* m_mapFile;

		lua_State* m_scriptEnv;
	};

	CGameLevel* GameLevel(void);
}
#endif