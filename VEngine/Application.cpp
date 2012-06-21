#include "Application.h"
#include "Engine.h"
#include "GameLevelController.h"
#include "GameLevel.h"

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

		m_engine->SetSystemController(new CGameLevelController);
		return m_engine->Run();
	}
}