#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vengine\Level\LevelLoader.h>
#include <vengine\GameObject.h>
#include <vengine\Level\VengineLevel.h>
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
		/*
		 * CallFactories()
		 *
		 * Calls factory functions for any objects in a mapfile's ObjectLayer.
		 *
		 * Throws: std::exception by LoadFile. (See for details).
		 * 
		 * Notes:
		 *		Calls the function m_RegisterFactories points to(Set by SetLevelFactories()). 
		 *		That function should add any C++ Factory Functions to the global table
		 *		FactoryTable in the passed lua_State. When a level is loaded, this function (CallFactories()),
		 *		will try to match an Object(using its Type value) in an ObjectLayer(From Tiled Map Editor) with a key in the
		 *		FactoryTable table(which is in Lua). If there's a match, it will get the value of that Key
		 *		and call the C++ function stored at that Key. (See SetLevelFactories for more).
		 */
		void CallFactories(const std::string& filename);
		/*
		 * LoadFiles()
		 *
		 * Helper function. Attempts to load and execute the lua script located at filename.
		 *
		 * Throws:	std::exception if it can not load filename or if VEngine's levelfunctions script
		 *			could not be loaded.
		 */
		static void LoadFiles(const std::string& filename, lua_State* L);
	public:
		void LoadLevel(const std::string& filename);
		void UnloadCurrentLevel(void);
		/*
		 *	AddBody() and AddGameObject
		 *
		 *	These functions are used to give ownership of the object to the level manager.
		 *
		 *	Notes:
		 *		When a level is loading its game data (usually when factories are called, though this function
		 *		may be called outside of this scenario) it needs to give ownsership of the objects to something.
		 *		This is what the function is meant for. When a level is unloaded these objects will be freed.
		 */
		void AddBody(b2Body* body) { m_bodies.push_back(std::unique_ptr<b2Body, Utility::b2BodyDtor>(body)); }
		void AddGameObject(NE::IGameObject* gameObj) { m_gameObjects.push_back(std::unique_ptr<NE::IGameObject>(gameObj)); }

		/*
		 *	SetLevelFactories()
		 *
		 *	Used to provide Factory functions for a level file.
		 *
		 *	Notes:
		 *		The lua_State which is passed houses the data for the level file, which
		 *		includes a table called FactoryTable. This function should add C++ static
		 *		functions to this table using strings as the keys. When an object Type parameter
		 *		in Tiled is the same as one of the Keys in this table, that function at that
		 *		key will be called. On the Lua stack will be a table object containing all
		 *		the values for that object(e.g. x,y,width,height,properties).
		 */
		void SetLevelFactories(void(*func)(lua_State* L));
	private:
		CLevelManager(void);
		CLevelManager(CLevelManager const&);
		void operator=(CLevelManager const&);

		std::list<std::unique_ptr<NE::IGameObject>> m_gameObjects;
		std::list<std::unique_ptr<b2Body, Utility::b2BodyDtor>> m_bodies;
		std::unique_ptr<CVengineLevel> m_currentLevel;

		void(*m_RegisterFactories)(lua_State* L);
	};

	CLevelManager& GetLvlMgr(void);
};
#endif