#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

//#include "vengine\GameObject.h"
#include <list>
#include <vengine\Character\Player.h>

namespace VE
{
	class CApplicationImpl;
	class NE::IGameObject;
	class IAnimationBase;
}


namespace VE
{
	using namespace NE;
	class CObjectManager
	{
		friend NE::IGameObject;
		friend CApplicationImpl;
		friend CObjectManager& GetObjMgr(void);

	protected:
		void UpdateGameObjects(void);
		void UpdateAnimations(void);

	public:
		/*
		 * Add()
		 *
		 * Add a game object to be updated  at the beginning of a new frame.
		 *
		 * Called by NE::IGameObject's constructor. Should not be called anywhere else.
		 */
		void Add(NE::IGameObject* obj) { m_gameObjects.push_back(obj); }
		/*
		 * Remove()
		 * 
		 * Remove a game object to stop it from being updated per frame;.
		 * 
		 * Called by NE::IGameObject's destructor. Should not be called anywhere else.
		 */
		void Remove(NE::IGameObject* obj) { m_gameObjects.remove(obj); }
		/*
		 * Add()
		 * 
		 * Add animation object so it can do its timing logic at the start of a new frame.
		 * 
		 * Called by IAnimationBase's constructor
		 */
		void Add(IAnimationBase* anim) { m_animations.push_back(anim); }
		/*
		 * Remove
		 *
		 * Remove animation object to prevent it from doing its timing logic.
		 * 
		 * Should only be called by IAnimationBase's destructor
		 */
		void Remove(IAnimationBase* anim) { m_animations.remove(anim); }
		/*
		 * Logic()
		 * 
		 * TO DO: Do any needed operations before we update any of our stored objects.
		 *
		 * Not sure on its exact use yet. Placeholder.
		 */
		void Logic(void);
		/*
		 * Cleanup()
		 *
		 * Free any used resources/performance any operations
		 */
		void Cleanup(void);

	public:
		CObjectManager(void);
		void SetPlayer(CPlayer* player) { m_player.reset(player); }
		CPlayer* GetPlayer(void) const { return m_player.get(); }
		

	private:
		// Do not implement
		CObjectManager(CObjectManager const&);
		// Do not implement
		void operator=(CObjectManager const&);
		// Game objects that need updating
		std::list<NE::IGameObject*> m_gameObjects;
		// Animations that need updating
		std::list<IAnimationBase*> m_animations;
		// The player
		std::unique_ptr<CPlayer> m_player;
	};

	CObjectManager& GetObjMgr(void);
}
#endif