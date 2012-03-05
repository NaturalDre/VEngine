#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <string>
#include <vengine\GameObject.h>
#include <Box2D\Box2D.h>
#include <list>
#include <memory>
#include <vengine\Utility.h>

namespace VE
{
	class CLevelManager;
}

namespace VE
{
	class ILevelLoader
	{
		friend CLevelManager;

	protected:
		ILevelLoader(void) { }
		virtual void Logic(void) { }

		void FreeGameObjects(void) { m_gameObjects.clear(); }
		void FreeBodies(void) { m_bodies.clear(); }
	public:
		virtual void LoadLevel(const std::string& filename) { };
		virtual void UnloadCurrentLevel(void) { };
		virtual void AddObject(NE::IGameObject* gameObj) { m_gameObjects.push_back(std::unique_ptr<NE::IGameObject>(gameObj)); }
		virtual void AddBody(b2Body* body)  { m_bodies.push_back(std::unique_ptr<b2Body, Utility::b2BodyDtor>(body)); }
		virtual ~ILevelLoader(void) = 0 { }

	private:
		std::list<std::unique_ptr<NE::IGameObject>> m_gameObjects;
		std::list<std::unique_ptr<b2Body, Utility::b2BodyDtor>> m_bodies;
		ILevelLoader(ILevelLoader const&);
		void operator=(ILevelLoader const&);
	};

}
#endif