#ifndef APPLICATION_H
#define APPLICATION_H

#include "Vengine.h"
#include "TMR\MapFile.h"

VENGINE_BEGIN_NAMESPACE

class IObjectModel;
class IObjectView;
class CPlayer;

class CApplication
{
protected:
	CApplication(void);

public:
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
	bool LoadMap(const std::string& fileName) { return m_mapFile.ReadMapFile(fileName); }
	/*
	 * IsMapLoaded()
	 *
	 * Returns if a map is currently loaded
	 */
	bool IsMapLoaded(void) const;
	// Pointer to the player
	CPlayer* GetPlayer(void) const { return m_player; }
	// Set the player
	void SetPlayer(CPlayer* player) { m_player = player; }
protected:
	Tiled::CMapFile m_mapFile;
	bool m_mapLoaded;
	CPlayer* m_player;
};

// Pointer to the global application instance
CApplication* App(void);
// Current width of the screen window.
size_t GetDisplayWidth(void);
// Current height of the screen window.
size_t GetDisplayHeight(void);

namespace Internal {
	/*
	 * Register()
	 *
	 * Registers an object model to be updated every frame.
	 *
	 * Params:
	 *	IObjectModel* - The object to update.
	 *
	 * Notes: 
	 *	Called by IObjectModel's constructor. Ptr added to CApplicationImpl
	 */
	void Register(IObjectModel*);
	/*
	 * Deregister()
	 *
	 * Stop an object from being updated per frame.
	 *
	 * Params:
	 *	IObjectView* - Object to stop updating.
	 *
	 * Notes:
	 *	Called by IObjectModel's destructor. Ptr added to CApplicationImpl
	 */
	void Deregister(IObjectModel*);
}

VENGINE_END_NAMESPACE

#endif