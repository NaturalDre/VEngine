#ifndef LEVEL_H
#define LEVEL_H

#include <vengine\Level\LevelLoader.h>
#include <string>
#include <vengine\Physics.h>
#include <vengine\GameObject.h>

namespace VE
{
	class CApplicationImpl;
	class ILevelLoader;
}

namespace VE
{
	class CLevelManager
	{
		friend CApplicationImpl;
		friend CLevelManager& GetLvlMgr(void);
	protected:
		void Cleanup(void);
		void Logic(void);

	public:
		inline void SetLevelLoader(ILevelLoader* loader) { m_levelLoader.reset(loader); }
		void LoadLevel(const std::string& filename);
		void UnloadCurrentLevel(void);
		void AddBody(b2Body* body) { m_bodies.push_back(std::unique_ptr<b2Body, Utility::b2BodyDtor>(body)); }
		void AddGameObject(NE::IGameObject* gameObj) { m_gameObjects.push_back(std::unique_ptr<NE::IGameObject>(gameObj)); }
	private:
		CLevelManager(void);
		CLevelManager(CLevelManager const&);
		void operator=(CLevelManager const&);

		std::unique_ptr<ILevelLoader> m_levelLoader;
		std::list<std::unique_ptr<NE::IGameObject>> m_gameObjects;
		std::list<std::unique_ptr<b2Body, Utility::b2BodyDtor>> m_bodies;
	};

	CLevelManager& GetLvlMgr(void);
};
#endif