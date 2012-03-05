#ifndef LEVEL_H
#define LEVEL_H

#include "vengine\Level\LevelLoader.h"
#include <string>
#include <memory>

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
		inline std::unique_ptr<ILevelLoader>& GetLevelLoader(void) { return m_levelLoader; }

	private:
		CLevelManager(void);
		CLevelManager(CLevelManager const&);
		void operator=(CLevelManager const&);

		std::unique_ptr<ILevelLoader> m_levelLoader;
	};

	CLevelManager& GetLvlMgr(void);
};
#endif