#ifndef ENTITY_H
#define ENTITY_H


namespace VE
{
	class CGameLevel;
	class IEntity
	{
	public:
		virtual ~IEntity(void) { }
		virtual void Update(double deltaTime) = 0;

	};
}
#endif