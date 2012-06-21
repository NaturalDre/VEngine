#ifndef ENTITYCONTROLLER_H
#define ENTITYCONTROLLER_H

namespace VE
{
	class IEntityController
	{
	protected:
		virtual ~IEntityController(void) { }

	public:
		virtual void Update(double deltaTime = 0) { };
	};
}
#endif