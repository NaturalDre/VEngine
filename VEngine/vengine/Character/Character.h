#ifndef CHARACTER_H
#define CHARACTER_H

#include <vengine\GameObject.h>

namespace VE
{
	class ICharacter: public NE::IGameObject
	{
	protected:
		ICharacter(void);

	public:
		virtual ~ICharacter(void) = 0;

		virtual bool IsDead(void) const { return m_health <= 0;}


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
		// Move the character
		virtual void Move(b2Vec2& dir) { }

	protected:
		const std::string m_name;
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