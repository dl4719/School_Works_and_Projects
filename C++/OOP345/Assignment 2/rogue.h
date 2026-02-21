#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H
#include <iostream>
#include <string>
#include "characterTpl.h"
#include "abilities.h"
#include "weapons.h"

namespace seneca
{
	template<typename T, typename FirstAbility_t, typename SecondAbility_t>
	class Rogue : public CharacterTpl<T>
	{
		int m_baseAttack;
		int m_baseDefense;

		FirstAbility_t m_firstAbility;
		SecondAbility_t m_secondAbility;

		seneca::Dagger m_weapon;

	public:
		Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
			:CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense)
		{
		}

		int getAttackAmnt() const override
		{
			return m_baseAttack + (2 * static_cast<double>(m_weapon));
		}

		int getDefenseAmnt() const override
		{
			return m_baseDefense;
		}

		Character* clone() const override
		{
			return new Rogue(*this);
		}

		void attack(Character* enemy) override
		{
			std::cout << this->Character::getName() << " is attacking " << enemy->getName() << "." << std::endl;

			m_firstAbility.useAbility(this);
			m_secondAbility.useAbility(this);

			int damage = getAttackAmnt();

			m_firstAbility.transformDamageDealt(damage);
			m_secondAbility.transformDamageDealt(damage);

			std::cout << "Rogue deals " << damage << " melee damage!" << std::endl;

			enemy->takeDamage(damage);
		}

		void takeDamage(int dmg) override
		{
			std::cout << this->Character::getName() << " is attacked for " << dmg << " damage." << std::endl;

			int reducedDamage = dmg - getDefenseAmnt();

			if (reducedDamage < 0)
				reducedDamage = 0;

			std::cout << "Rogue has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;

			m_firstAbility.transformDamageDealt(reducedDamage);
			m_secondAbility.transformDamageDealt(reducedDamage);

			this->takeDamage(reducedDamage);
		}
	};
}
#endif