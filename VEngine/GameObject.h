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
		// Tag
		const std::string& Tag(void) const { return m_tag; }
		//
		void SetTag(const std::string& tag) { m_tag = tag; }

	protected:
		std::string m_tag;
	};

}
#endif