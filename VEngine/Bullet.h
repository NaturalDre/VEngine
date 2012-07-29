#ifndef BULLET_H
#define BULLET_H

namespace VE
{
	class IWeapon;
	class IBullet
	{
		friend IWeapon;
	protected:
		inline void SetDamage(float damage) { m_damage = damage; }

	public:
		virtual ~IBullet(void) = 0 { }
		float GetDamage(void) { return m_damage; }

	private:
		float m_damage;
	};
}
#endif