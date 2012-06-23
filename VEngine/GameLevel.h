#ifndef ABSTRACTLEVELMODEL_H
#define ABSTRACTLEVELMODEL_H

#include <string>
#include <unordered_set>
#include <set>

namespace VE
{
	//class IEntityController;
	class IEntity;
	class IView;


	class CRender;
	class CPhysics;
	class CPlayer;
	class CPlayerView;
	class CPlayerController;
	class CGameLevel//: public IObject
	{
	protected:

	public:
		CGameLevel(CRender* renderer);
		~CGameLevel(void);

		inline void SetLevelName(const std::string& levelName) { m_levelName = levelName; }
		inline std::string LevelName(void) const { return m_levelName; }

		// Call Update on all Updatable Controllers
		void UpdateAll(double deltaTime);

		inline CPlayerController* Player(void) const { return m_playerController; }
		void SetPlayerController(CPlayerController* controller);

		inline CRender* Renderer(void) const { return m_renderer; }
		inline CPhysics* Physics(void) const { return m_physics; }

	private:
		typedef std::unordered_set<IEntity*> EntitySet;

		std::string m_levelName;
		EntitySet m_controllers;

		CPlayer* m_player;
		CPlayerView* m_playerView;
		CPlayerController* m_playerController;

		CRender* m_renderer;
		CPhysics* m_physics;
	};
}
#endif