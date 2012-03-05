#ifndef VENGINELEVEL_H
#define VENGINELEVEL_H

#include "vengine\Level\VengineMap.h"
#include "vengine\Level\Level.h"

namespace VE
{
	class CVengineLevelLoader;
}
namespace VE
{
	// This is an implementation of the base class IGameLevel.
	// This is meant to be tailored to specifically for the type of game I'm making.
	class CVengineLevel
	{
		friend CVengineLevelLoader;
	protected:
		void Logic(void);
		void LoadData(void);
		void Assemble(void);
		void EndLevel(void);

	public:
		CVengineLevel(const std::string& filename);

	private:
		const std::string m_filename;
		std::unique_ptr<CVengineMap> m_map;
	};
};
#endif