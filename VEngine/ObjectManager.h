#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <set>

namespace VE
{
	class CApplicationImpl;
	class IGameObject;
	class IObjectModel;
	class CObjectManager
	{
		friend CApplicationImpl;
		friend CObjectManager* ObjectMgr(void);
	protected:
		CObjectManager(void);
		~CObjectManager(void);

		void UpdateGameObjects(void);
	public:
		inline void Register(IGameObject* gameObj) { if (gameObj) m_gameObjects.insert(gameObj); }
		inline void Deregister(IGameObject* gameObj) { m_gameObjects.erase(gameObj); }
		/*
		* Register()
		*
		* Registers an object model to be updated every frame.
		*
		* Params:
		*	IObjectModel* - The object to update.
		*
		* Notes: 
		*	Called by IObjectModel's constructor.
		*/
		inline void Register(IObjectModel* objModel) { if (objModel) m_objectModels.insert(objModel); }
		/*
		* Deregister()
		*
		* Stop an object from being updated per frame.
		*
		* Params:
		*	IObjectView* - Object to stop updating.
		*
		* Notes:
		*	Called by IObjectModel's destructor.
		*/	
		inline void Deregister(IObjectModel* objModel) { m_objectModels.erase(objModel); }
		// Find the first game object using this tag. Nullpoint if none found with the tag.
		IGameObject* FindGameObject(const std::string& tag) const;
		// Check if the passed pointer is the pointer of an existing game object.
		bool GameObjectExists(IGameObject* gameObj) const;

	private:
		std::set<IGameObject*> m_gameObjects;
		std::set<IObjectModel*> m_objectModels;
	};

	CObjectManager* ObjectMgr(void);
};
#endif