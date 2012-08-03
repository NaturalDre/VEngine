#ifndef MAPPARSER_H
#define MAPPARSER_H

namespace VE
{
	class CGameMap;
	class CGameLevel;
	class CMapParser
	{
	protected:
		void DoMapProperties(void);
		void DoTileLayers(void);

		void RemoveRuleGids(void);
	public:
		CMapParser(void) { }
		CMapParser(CGameLevel* gamelevel, CGameMap* gameMap);
		~CMapParser(void);

		void Parse(void);

	private:
		CGameLevel* m_gameLevel;
		CGameMap* m_gameMap;
	};
}
#endif