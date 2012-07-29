#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "TMR\MapFile.h"

namespace VE
{
	class CRender;
	class CGameMap: public Tiled::CMapFile
	{
	protected:
		void RenderLayer(VE::CRender* renderer, Tiled::CTileLayer* tilelayer);

	public:
		CGameMap(void);
		~CGameMap(void) { }

		inline size_t GetPlayerLayer(void) const { return m_playerLayer; }
		inline void SetPlayerLayer(size_t layer) { m_playerLayer = layer; }

		void Render(VE::CRender* renderer, size_t begin, size_t end);

	private:
		size_t m_playerLayer;
	};
}

#endif