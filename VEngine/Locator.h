#pragma once

namespace VE
{
	class IRenderService;
	class IPhysicsService;
	class CLocator
	{
	public:
		static void Provide(IRenderService* service) { m_renderService = service; }
		static void Provide (IPhysicsService* service) { m_physicsService = service; }

		static IRenderService* GetRenderer(void) { return m_renderService; }
		static IPhysicsService* GetPhysics(void) { return m_physicsService; }
	private:
		static IRenderService* m_renderService;
		static IPhysicsService* m_physicsService;
	};
}