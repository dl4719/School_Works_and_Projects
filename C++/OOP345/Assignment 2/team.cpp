#include "team.h"

namespace seneca
{
	Team::Team() : m_name(""), m_members(nullptr), m_size(0)
	{
	}

	Team::Team(const char* name) : m_name(name), m_members(nullptr), m_size(0)
	{
	}
	
	Team::Team(const Team& src) : m_name(src.m_name), m_members(nullptr), m_size(0)
	{
		for (size_t i = 0; i < src.m_size; ++i)
		{
			addMember(src.m_members[i]);
		}
	}

	Team& Team::operator=(const Team& src) 
	{
		if (this == &src)
		{
			return *this;
		}

		for (size_t i = 0; i < m_size; ++i) {
			delete m_members[i];
		}
		delete[] m_members;

		m_name = src.m_name;
		m_size = 0;
		m_members = nullptr;

		for (size_t i = 0; i < src.m_size; ++i) 
		{
			addMember(src.m_members[i]);
		}

		return *this;
	}

	Team::Team(Team&& src) noexcept : m_name(std::move(src.m_name)), m_members(src.m_members),
		m_size(src.m_size)
	{
		src.m_members = nullptr;
		src.m_size = 0;
	}

	Team& Team::operator=(Team&& src) noexcept {
		if (this == &src)
		{
			return *this;
		}

		for (size_t i = 0; i < m_size; ++i)
		{
			delete m_members[i];
		}
		delete[] m_members;

		m_name = std::move(src.m_name);
		m_members = src.m_members;
		m_size = src.m_size;

		src.m_members = nullptr;
		src.m_size = 0;

		return *this;
	}

	void Team::addMember(const Character* c)
	{
		for (size_t i = 0; i < m_size; ++i)
		{
			if (m_members[i]->getName() == c->getName())
			{
				return;
			}
		}

		Character** tempCharacter = new Character * [m_size + 1];

		for (size_t i = 0; i < m_size; ++i)
		{
			tempCharacter[i] = m_members[i];
		}

		tempCharacter[m_size] = c->clone();
		delete[] m_members;
		m_members = tempCharacter;
		++m_size;
	}

	void Team::removeMember(const std::string& c) 
	{
		size_t idx = m_size;

		for (size_t i = 0; i < m_size; ++i) 
		{
			if (m_members[i]->getName() == c) 
			{
				idx = i;
				return;
			}
		}

		if (idx == m_size)
		{
			return;
		}

		delete m_members[idx];
		for (size_t i = idx; i < m_size - 1; ++i)
		{
			m_members[i] = m_members[i + 1];
		}
		--m_size;
	}

	Character* Team::operator[](size_t idx) const 
	{
		if (idx < m_size)
		{
			return m_members[idx];
		}

		return nullptr;
	}

	void Team::showMembers() const {
		if (m_size == 0)
		{
			std::cout << "No team." << std::endl;
		}
		else
		{
			std::cout << "[Team] " << m_name << std::endl;
			for (size_t i = 0; i < m_size; ++i) 
			{
				std::cout << "    " << (i + 1) << ": " << *m_members[i] << std::endl;
			}
		}
	}
}
