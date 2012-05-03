#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <list>
#include <vengine\Physics.h>
#include <vengine\Script\LuaScript.h>
namespace VE
{
	class CObjectManager;
	class CContactListener;
	class CLuaScript;
}

namespace NE
{
	class NE::IGameObject
	{
		friend VE::CObjectManager;
		friend VE::CContactListener;
	protected:
		NE::IGameObject(const std::string& tag = std::string(), int typeID = 0);


		// Called at the beginning of a frame.
		virtual void OnUpdate(void) { }
		// Called when the physics world has been updated for this frame.
		virtual void OnFrameEnd(void) { }
		// Called when level is about to be unloaded. *Might perform save data with this function*
		virtual void OnLevelEnd(void) { }
		// Called when this object begins contact with another [physics enabled] object.
		virtual void OnBeginContact(b2Contact* contact) { }
		// Called when this object ends contact with another [physics enabled] object.
		virtual void OnEndContact(b2Contact* contact) { }
		virtual void OnPreSolve(b2Contact* contact, const b2Manifold* oldManifold) {}
		virtual void OnPostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}
		/*
		 *	When the player presses the interact button near a game object
		 *	this function will be called. (If it is the closest interactable
		 *	object.
		 */
		virtual void Interact(void) { }
		//
		void AttachScript(VE::CLuaScript* script) { m_scripts.push_back(std::unique_ptr<VE::CLuaScript>(script)); }


	public:
		// Position of this object. Should be overriden.
		virtual b2Vec2 GetPos(void) const { return b2Vec2(0,0); } 
		virtual ~IGameObject(void);

		int GetTypeID(void) const { return m_typeID; }

	private:
		//
		const std::list<std::unique_ptr<VE::CLuaScript>>& GetScripts(void) { return m_scripts; }

		/*
		 *	Tag used to searching for a game object by name.
		 *	IMPORTANT: Try not to use the same name twice if you plan to 
		 *	use this feature.
		 */
		const std::string m_tag;
		/*
		 * List of scripts. The update functions on these 
		 * will be called just before this gameobject's own
		 * OnUpdate function is called in the order they appear
		 * in the list.
		 */
		std::list<std::unique_ptr<VE::CLuaScript>> m_scripts;
		int m_typeID;
	};

}
namespace VE
{
	//class IGameObject
	//{
	//	friend CObjectManager;
	//protected:
	//	NE::IGameObject(const std::string& tag = std::string());
	//	virtual ~IGameObject(void);

	//	// Called at the beginning of a frame.
	//	virtual void OnUpdate(void) { }
	//	// Called when the physics world has been updated for this frame.
	//	virtual void OnFrameEnd(void) { }
	//	// Called when level is about to be unloaded. *Might perform save data with this function*
	//	virtual void OnLevelEnd(void) { }
	//	// Called when this object begins contact with another [physics enabled] object.
	//	virtual void OnBeginContact(b2Contact* contact) { }
	//	// Called when this object ends contact with another [physics enabled] object.
	//	virtual void OnEndContact(b2Contact* contact) { }
	//	/*
	//	 *	When the player presses the interact button near a game object
	//	 *	this function will be called. (If it is the closest interactable
	//	 *	object.
	//	 */
	//	virtual void Interact(void) { }

	//public:
	//	// Position of this object. Should be overriden.
	//	virtual b2Vec2 GetPos(void) { return b2Vec2(0,0); } 

	//private:
	//	/*
	//	 *	Tag used to searching for a game object by name.
	//	 *	IMPORTANT: Try not to use the same name twice if you plan to 
	//	 *	use this feature.
	//	 */
	//	const std::string m_tag;
	//	/*
	//	 * List of scripts. The update functions on these 
	//	 * will be called just before this gameobject's own
	//	 * OnUpdate function is called in the order they appear
	//	 * in the list.
	//	 */
	//	std::list<std::unique_ptr<CLuaScript>> m_scriptComponents;
	//};
}
#endif