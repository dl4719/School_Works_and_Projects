#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H
#include <iostream>
#include <string>
#include "characterTpl.h"
#include "abilities.h"
#include "weapons.h"

namespace seneca
{
	template<typename T, typename Ability_t, typename Weapon_t>
	class Barbarian : public CharacterTpl<T>
	{
		int m_baseAttack;
		int m_baseDefense;

		Ability_t m_ability;

		Weapon_t m_weapons[2];

	public:
		Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense,
			Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
			:CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense),
			m_ability()
		{
			m_weapons[0] = primaryWeapon;
			m_weapons[1] = secondaryWeapon;
		}

		int getAttackAmnt() const override
		{
			double totalDamage = m_baseAttack + 
				(static_cast<double>(m_weapons[0]) / 2) + (static_cast<double>(m_weapons[1]) / 2);

			return static_cast<int>(totalDamage);
		}

		int getDefenseAmnt() const override
		{
			return m_baseDefense;
		}

		Character* clone() const override
		{
			return new Barbarian(*this);
		}

		void attack(Character* enemy) override
		{
			std::cout << this->Character::getName() << " is attacking " << enemy->getName() << "." << std::endl;

			m_ability.useAbility(this);

			int damage = getAttackAmnt();

			m_ability.transformDamageDealt(damage);

			std::cout << "Barbarian deals " << damage << " melee damage!" << std::endl;

			enemy->takeDamage(damage);
		}

		void takeDamage(int dmg) override
		{
			std::cout << this->Character::getName() << " is attacked for " << dmg << " damage." << std::endl;
			std::cout << "Barbarian has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;

			dmg -= m_baseDefense;
			if (dmg < 0)
				dmg = 0;

			m_ability.transformDamageReceived(dmg);

			CharacterTpl<T>::takeDamage(dmg);
		}
	};
}

#endif