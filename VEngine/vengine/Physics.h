#ifndef PHYSICS_H
#define PHYSICS_H

#include <Box2D\Box2D.h>
#include <lua.hpp>
#include <string>
#include <map>

const float DEFAULTDENSITY(0.3f);
const float DEFAULTFRICTION(0.3f);

class DebugDraw;

namespace VE
{
	class CApplicationImpl;
	class CContactListener;
}

namespace VE
{
	extern const float SCALE;

	class CPhysicsManager
	{
		friend CApplicationImpl;
		friend CPhysicsManager& GetPhysMgr(void);

	protected:
		/*
		 *	UpdateWorld()
		 *
		 *	Updates the physics world.
		 */
		void UpdateWorld(void);

	public:
		/*
		 * GetWorld()
		 *
		 * Box2D's physics world.
		 *
		 * Returns: b2World* : The world houses all Box2D's physics data and factories.
		 */
		b2World* GetWorld(void) const { return m_world.get(); }
		/*
		 *	BodyExists()
		 *
		 *	Checks if a body ny this address exists.
		 *
		 *	Params:
		 *		b2Body* body: The body to check.
		 */
		bool BodyExists(b2Body* body);
		/*
		 *	BodyExists()
		 *
		 *	static_cast's to a b2Body* and calls BodyExists(b2Body*)
		 *
		 */
		bool BodyExists(void* body);
		/*
		 *	GetContactListener()
		 *
		 *	Gets the contact listener for Box2D.
		 *
		 *	Notes:	Anytime a collision begins and ends the listener is notified
		 *			and checks both objects' bodies for a pointer to a IGameObject.
		 *			If the pointer points to an existing body, the corresponding
		 *			IGameObject is notified of the collision so it can act accordingly.
		 *			It also checks the fixtures that collided for a userdata pointer to
		 *			a fixture callback and calls the appropriate functions on the pointer.
		 * 
		 */
		CContactListener* GetContactListener(void) const { return m_contactListener.get(); }
		/*
		 * DrawDebugData()
		 *
		 * Draws every visible object in the Box2D world to the screen.
		 *
		 * Notes:	Use this to determine if you're drawing your objects in the right place.
		 */
		void DrawDebugData(void);

	private:
		CPhysicsManager(void);
		// Don't implement
		CPhysicsManager(CPhysicsManager const&);
		// Don't implement
		void operator=(CPhysicsManager const&);

		std::unique_ptr<b2World> m_world;
		std::unique_ptr<CContactListener> m_contactListener;
		std::unique_ptr<DebugDraw> m_debugDraw;
	};

	CPhysicsManager& GetPhysMgr(void);

	namespace Utility
	{
		/*
		 * struct TiledObject
		 *
		 * This represents the 'object' table that is found in Tiled's exort of
		 * an 'objectlayer'.
		 *
		 */
		struct TiledObject
		{
			TiledObject(void): x(0), y(0), width(0), height(0) {}
			TiledObject(TiledObject&& rhs);

			std::string name;
			std::string type;
			float x;
			float y;
			float width;
			float height;
			std::map<const std::string, std::string> properties;
		};
		/*
		 * ToTiledObject()
		 *
		 * Returns an C++ represenation of the Lua table export of
		 * Tiled's object table found within its 'objecylayer'.
		 *
		 * Params:
		 *		lua_State* L: The lua_State where the 'object' table is.
		 *
		 * Notes:
		 *		The table MUST be at position 1 on the stack. It MUST also
		 *		actually be an object from Tiled's objectlayer or exceptions
		 *		will be thrown.
		 *
		 * Throws:
		 *		std::exception:	If the value at position 1 on the stack is
		 *						is not a table.
		 *		LuaError:	If the table does not have one or more of the requires
		 *					keys a TiledObject MUST have. (The ones defined in the struct)
		 */
		TiledObject ToTiledObject(lua_State* L);
		/* 
		 * GameToScreenPosPix()
		 * 
		 * Returns distance of position from the current camera's top left position.
		 *
		 * Params:
		 *		const b2Vec2&: The position whose distance from the camera you want.
		 *
		 * Notes:
		 *		The viewing area of the camera is considered the screen, so if you want
		 *		to draw something that is at some position in the world and when you pass
		 *		that position to this function and it returns (240, 530), then you draw it
		 *		at (240, 530) on the screen. Consequently, if the X or Y position returned
		 *		is larger than the camera's width/height(if those are also equal to the 
		 *		game screen's width/height) then it is not visible on the screen.
		 */
		b2Vec2 GameToScreenPosPix(const b2Vec2& posPix);
		/*
		 * mtrToPix()
		 *
		 * Converts meters to pixels.
		 *
		 * Params:
		 *		float meters: The meters to be converted.
		 * Returns: 
		 *		float - The converted meters to pixels value.
		 */
		inline float mtrToPix(float meters) { return (meters * SCALE); }
		/*
		 * mtrToPix()
		 *
		 * Converts meters to pixels.
		 *
		 * Params:
		 *		b2Vec2 vec - Vector respresenting a 2D position in meters.
		 *
		 * Returns:
		 *		b2Vec2 - The converted 2D vector's meter position as pixels.
		 */
		inline b2Vec2 mtrToPix(b2Vec2 vec) { vec *= SCALE; return vec; }
		inline float pixToMtr(float pixels) { return (pixels / SCALE); }
		inline b2Vec2 pixToMtr(b2Vec2 vec) { vec.x /= SCALE; vec.y /= SCALE; return vec; }
		int CreateSolidGround(lua_State* L);
		inline b2Vec2 TiledToBoxCoords(b2Vec2& posPix, float widthPix, float heightPix) 
		{ 
			return Utility::pixToMtr(posPix) + b2Vec2(Utility::pixToMtr(widthPix) / 2.0f, Utility::pixToMtr(heightPix) / 2.0f); 
		}
		//*
		//	Tiled does not position it's objects using the center of the object like Box2D tends 
		//	to do. So we need a helper function to do that for us and return it in meters.
		//*	
		inline b2Vec2 GetWorldCenterMtrs(const TiledObject& obj) 
		{ 
			b2Vec2 pos(obj.x, obj.y);
			return TiledToBoxCoords(pos, obj.width, obj.height);
		}

	}
}
#endif