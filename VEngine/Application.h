#ifndef APPLICATION_H
#define APPLICATION_H

#include "TMR\MapFile.h"

struct lua_State;

namespace VE {

	class IObjectModel;
	class IObjectView;
	class CPlayer;

	enum InitError 
	{
		e_NoError,
		e_Core,
		e_Keyboard,
		e_Mouse,
		e_Image,
		e_Primitives,
		e_TTF
	};

	class CApplication
	{
	protected:
		CApplication(void);


	public:
		virtual ~CApplication(void);
		static CApplication* Create(void);

		/*
		* Init();
		*
		* Initializes the systems needed to run the game.
		* Sound, Bitmaps, Timers, etc...
		*
		* Returns:
		*	Enum(Decl. in Vengine.h) indicated what failed. Returns e_NoError on success.
		*/
		virtual int Init(void) = 0;
		/*
		* Run();
		*
		* Start the game loop.
		*/
		virtual int Run(int argc, const char* argv[]) = 0;
		/*
		* SetResolution()
		*
		* Set the application's screen resolution. Happens immedietly.
		*/
		void SetResolution(size_t width, size_t height);
		/*
		* GetMap()
		*
		* Returns an object representing the currently loaded map's mapfile.
		*
		* Notes: If map is invalid it's IsValid() parameter is false
		*/
		inline const Tiled::CMapFile& GetMap(void) const { return m_mapFile; }
		/*
		* LoadMap()
		*
		* Loads the description of the map into memory.
		*
		*	Params:
		*		const std::string& name - The map's filename and location relative to one of the data files. (e.g. data.zip)
		*
		* Returns:
		*	bool - True if it loaded without error. False otherwise.
		*/
		bool LoadMap(const std::string& fileName);
		/*
		* IsMapLoaded()
		*
		* Returns if a map is currently loaded
		*/
		bool IsMapLoaded(void) const { m_mapFile.IsValid(); }

		lua_State* LuaState(void) const { return m_luaState; }
	protected:
		Tiled::CMapFile m_mapFile;
		lua_State* m_luaState;
	};

	// Pointer to the global application instance
	CApplication* App(void);
	// Current width of the screen window.
	size_t GetDisplayWidth(void);
	// Current height of the screen window.
	size_t GetDisplayHeight(void);
}

#endif