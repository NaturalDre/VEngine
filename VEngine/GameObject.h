#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Physics.h"
#include "ObjectModel.h"
#include "Utility.h"
namespace VE
{
	class IGameObject: public IObjectModel
	{
	protected:
		IGameObject(void);
		~IGameObject(void);

	public:
		// Position of this object in the game world. Meters.
		virtual b2Vec2 Pos(void) const = 0; 
		//b2Vec2 PosPix(void) const { return mtrToPix(Pos()

	protected:
		
	};

}
#endif