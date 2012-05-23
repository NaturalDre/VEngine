#include "Camera.h"

namespace VE
{
	CCamera::CCamera(IGameObject* gameObj)
		: m_gameObj(nullptr)
		, m_width(1024)
		, m_height(768)
	{


	}

	CCamera::~CCamera(void)
	{
		m_gameObj = nullptr;
	}
}