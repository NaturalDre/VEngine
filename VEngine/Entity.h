#ifndef ENTITY_H
#define ENTITY_H

namespace VE
{
	class IBullet;
	class CGameLevel;
	class IEntity
	{
	public:
		IEntity(CGameLevel* level): m_gameLevel(level) {}

		virtual ~IEntity(void) { }
		virtual void Update(double deltaTime) = 0;

		inline CGameLevel* GameLevel(void) const { return m_gameLevel; }

		virtual bool OnContact(IBullet* bullet) { return false; } // Return true to accept he contact
		virtual bool OnContact(IEntity* entity) { return false; } // Return true to accept he contact
	private:
		CGameLevel* m_gameLevel; // Game level this entity is a part of.
	};
}
#endif