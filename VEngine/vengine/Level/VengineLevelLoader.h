#ifndef VENGINELEVELLOADER_H
#define VENGINELEVELLOADER_H

#include "vengine\Level\LevelLoader.h"
#include "vengine\Level\VengineLevel.h"
//#include <vengine\GameObject.h>

namespace VE
{
	class CVengineLevelLoader: public ILevelLoader
	{
	protected:
		void LoadLevel(const std::string& filename);
		void UnloadCurrentLevel(void);
		void Logic(void);

		void GatherObjects(const std::string& filename);
		//void AddObject(NE::IGameObject* gameObj);
		static void LoadFiles(const std::string& filename, lua_State* L);
		static void RegisterFactories(lua_State* L);

	public:
		~CVengineLevelLoader(void);

	private:
		std::unique_ptr<CVengineLevel> m_currentLevel;
	};
}
#endif