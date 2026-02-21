#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H
#include <iostream>
#include <string>
#include "character.h"

namespace seneca
{
	class Team
	{
		std::string m_name;
		Character** m_members;
		size_t m_size;

	public:
		Team();

		Team(const char* name);

		~Team()
		{
			for (size_t i = 0; i < m_size; ++i)
			{
				delete m_members[i];
			}
			delete[] m_members;
		}

		Team(const Team& src);
		Team& operator=(const Team& src);
		Team(Team&& src) noexcept;
		Team& operator=(Team&& src) noexcept;

		void addMember(const Character* c);
		void removeMember(const std::string& c);
		Character* operator [](size_t idx) const;
		void showMembers() const;
	};
}

#endif