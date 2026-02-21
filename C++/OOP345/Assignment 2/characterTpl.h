#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H
#include <iostream>
#include <string>
#include "character.h"

namespace seneca
{
	template<typename T>
	class CharacterTpl : public Character
	{
		int m_healthMax;
		T m_health;

	public:
		CharacterTpl(const std::string& name, int maxHealth)
			:Character(name.c_str()), m_healthMax(maxHealth)
		{
			m_health = maxHealth;
		}

		void takeDamage(int dmg) override
		{
			m_health -= dmg;

			if (static_cast<int>(m_health) <= 0)
			{
				std::cout << getName() << " has been defeated!" << std::endl;
				m_health = 0;
			}
			else
			{
				std::cout << getName() << " took " << dmg << " damage," << static_cast<int>(m_health)
					<< " health remaining." << std::endl;
			}
		}

		int getHealth() const override
		{
			return static_cast<int>(m_health);
		}

		int getHealthMax() const override
		{
			return m_healthMax;
		}

		void setHealth(int health) override
		{
			m_health = health;

			if (static_cast<int>(m_health) > m_healthMax)
			{
				m_health = m_healthMax;
			}
			if (static_cast<int>(m_health) < 0)
			{
				m_health = 0;
			}
		}

		void setHealthMax(int health) override
		{
			m_healthMax = health;
			m_health = health;
		}
	};
}

#endif