#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <string>
#include <list>
#include <memory>

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

	public:
		virtual void LoadLevel(const std::string& filename) { };
		virtual void UnloadCurrentLevel(void) { };
		virtual ~ILevelLoader(void) = 0 { }

	private:
		ILevelLoader(ILevelLoader const&);
		void operator=(ILevelLoader const&);
	};

}
#endif