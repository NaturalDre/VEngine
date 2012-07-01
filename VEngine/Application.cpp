#include "Application.h"
#include "Engine.h"
#include "GameLevelController.h"
#include "GameLevel.h"
#include <physfs.h>
#include <allegro5\allegro_physfs.h>
#include "Bitmap.h"

namespace VE
{
	CApplication::CApplication(void)
	{
		m_engine = new CEngine;

	}

	CApplication::~CApplication(void)
	{
		delete m_engine;
		m_engine = nullptr;
	}

	int CApplication::Run(void)
	{
		if (m_engine->Init())
			return -1;

		PHYSFS_addToSearchPath("Images.zip", 1);
		PHYSFS_addToSearchPath("Maps/Adventure", 1);

		m_engine->SetSystemController(new CGameLevelController);
		CBitmap b("box.png");
		return m_engine->Run();
	}
}