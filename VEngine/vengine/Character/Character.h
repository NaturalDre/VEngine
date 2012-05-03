#ifndef CHARACTER_H
#define CHARACTER_H

#include <vengine\GameObject.h>
#include <vengine\ContactListener.h>
#include <set>

namespace VE
{


	class ICharacter: public NE::IGameObject
	{
	protected:
		ICharacter(void);
		b2Body* GetBody(void) const { return m_body.get(); }
	public:
		virtual ~ICharacter(void) = 0;

		virtual bool IsDead(void) const { return m_health <= 0;}


		const b2Vec2& GetMoveSpeed(void) const { return m_moveSpeed; }
		const b2Vec2& GetMaxVel(void) const { return m_maxVel; }
		// Amount of exp character has
		size_t GetExp(void) const { return m_exp; }
		// Character's health case
		float GetHealth(void) const { return m_health; }
		// Maximum health
		float GetMaxHealth(void) const { return m_maxHealth; }
		// Width in meters
		float GetCharacterWidth(void) const { return m_characterWidth; }
		// Height in meters
		float GetCharacterHeight(void) const { return m_characterHeight; }
		
		void SetMoveSpeed(const b2Vec2& speed) { m_moveSpeed = speed; }
		void SetMaxVel(const b2Vec2& vel) { m_maxVel = vel; }
		
		
		// Move the character
		virtual void Move(b2Vec2& dir) { }
		// Move the character on its X axis
		void MoveX(float desiredVel);


	protected:
		const std::string m_name;
		std::unique_ptr<b2Body, Utility::b2BodyDtor> m_body;
		b2Vec2 m_moveSpeed;
		b2Vec2 m_maxVel;
		b2Vec2 m_moveBy;
		float m_health;
		float m_maxHealth;
		size_t m_level;
		size_t m_exp;
		size_t m_gold;
		// Meters
		float m_characterWidth, m_characterHeight;
	};
}
#endif