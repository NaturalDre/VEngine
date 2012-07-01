#ifndef ENTITY_H
#define ENTITY_H

class CGameLevel;

namespace VE
{
	class CGameLevel;
	class IEntity
	{
	public:
		IEntity(CGameLevel* level): m_gameLevel(level) {}

		virtual ~IEntity(void) { }
		virtual void Update(double deltaTime) = 0;

		inline CGameLevel* GameLevel(void) const { return m_gameLevel; }

	private:
		CGameLevel* m_gameLevel; // Game level this entity is a part of.
	};
}
#endif