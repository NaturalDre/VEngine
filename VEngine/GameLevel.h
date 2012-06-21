#ifndef ABSTRACTLEVELMODEL_H
#define ABSTRACTLEVELMODEL_H

#include <string>
#include <unordered_set>
#include <set>

namespace VE
{
	class IEntityController;
	class IView;

	class CPlayer;
	class CPlayerController;
	class CRender;
	class CGameLevel//: public IObject
	{
	protected:

	public:
		CGameLevel(CRender* renderer);
		~CGameLevel(void);

		void SetLevelName(const std::string& levelName);
		std::string LevelName(void) const { return m_levelName; }

		// Call Update on all Updatable Controllers
		void UpdateAll(double deltaTime);

		inline CPlayerController* Player(void) const { return m_playerController; }
		void SetPlayerController(CPlayerController* controller);

	private:
		typedef std::unordered_set<IEntityController*> UpdateControllers;

		std::string m_levelName;
		UpdateControllers m_controllers;
		CPlayerController* m_playerController;

		CRender* m_renderer;
	};
}
#endif