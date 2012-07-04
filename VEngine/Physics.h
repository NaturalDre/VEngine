#ifndef PHYSICS_H
#define PHYSICS_H

#include <Box2D\Box2D.h>

const float SCALE(32.0f);


class DebugDraw;

namespace Tiled
{
	class TiledObject;
}

enum
{
	e_Friendly = 0x0001
	, e_Player
	, e_Enemy
	, e_FriendlyBullet
	, e_EnemyBullet
	, e_Static
};

namespace VE
{
	class CContactListener;
	class CCamera;
	class CPhysics
	{
	public:
		CPhysics(CCamera* cam);
		~CPhysics(void);

		inline void Simulate(void) const { m_world->Step(m_timeStep, m_velocityIters, m_positionIters); }
		inline b2World* World(void) const { return m_world; }
		inline CContactListener* ContactListener(void) const { return m_contactListener; }

	private:
		float m_timeStep;
		size_t m_velocityIters, m_positionIters;

		b2World* m_world;
		DebugDraw* m_debugDrawer;
		CContactListener* m_contactListener;
	};


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
	b2Vec2 GameToScreenPosPix(CCamera* cam, const b2Vec2& posPix);
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
	inline float MtrToPix(float meters) { return (meters * SCALE); }
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
	inline b2Vec2 MtrToPix(b2Vec2 vec) { vec *= SCALE; return vec; }
	inline float PixToMtr(float pixels) { return (pixels / SCALE); }
	inline b2Vec2 PixToMtr(b2Vec2 vec) { vec.x /= SCALE; vec.y /= SCALE; return vec; }

	// Tiled using the top left of a tile as it's origin. Box2D uses an object's center.
	// This function converts a Tiled origin to Box2D origin.
	inline b2Vec2 TiledToBoxCoords(b2Vec2& posPix, float widthPix, float heightPix) 
	{ 
		return PixToMtr(posPix) + b2Vec2(PixToMtr(widthPix) / 2.0f, PixToMtr(heightPix) / 2.0f); 
	}
	//*
	//	Tiled does not position it's objects using the center of the object like Box2D tends 
	//	to do. So we need a helper function to do that for us and return it in meters.
	//*	
	b2Vec2 GetWorldCenterMtrs(const Tiled::TiledObject& obj);
}
#endif