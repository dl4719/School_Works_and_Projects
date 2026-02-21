#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H
#include <iostream>
#include <string>
#include "characterTpl.h"
#include "abilities.h"
#include "weapons.h"

namespace seneca
{
	template <typename Weapon_t>
	class Archer : public CharacterTpl<seneca::SuperHealth>
	{
		int m_baseAttack;
		int m_baseDefense;

		Weapon_t m_weapon;

	public:
		Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
			:CharacterTpl(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense), m_weapon(weapon)
		{
		}

		int getAttackAmnt() const override
		{
			return static_cast<int>(1.3 * m_baseAttack);
		}

		int getDefenseAmnt() const override
		{
			return static_cast<int>(1.2 * m_baseDefense);
		}

		Character* clone() const override
		{
			return new Archer(*this);
		}

		void attack(Character* enemy) override
		{
			std::cout << getName() << " is attacking " << enemy->getName() << "." << std::endl;
			
			int damage = getAttackAmnt();

			std::cout << "Archer deals " << damage << " ranged damage!" << std::endl;

			enemy->takeDamage(damage);
		}

		void takeDamage(int dmg) override
		{
			std::cout << getName() << " is attacked for " << dmg << " damage." << std::endl;

			int reducedDmg = dmg - getDefenseAmnt();

			if (reducedDmg < 0)
				reducedDmg = 0;

			std::cout << "Archer has a defense of " << getDefenseAmnt() 
				<< ". Reducing the damage received." << std::endl;

			CharacterTpl::takeDamage(reducedDmg);
		}
	};
}
#endif