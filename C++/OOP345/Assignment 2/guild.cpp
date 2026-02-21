#include "guild.h"

namespace seneca
{
    Guild::Guild() : m_name(""), m_members(nullptr), m_size(0)
    {
    }

    Guild::Guild(const char* name) : m_name(name), m_members(nullptr), m_size(0)
    {
    }

    Guild::~Guild()
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            m_members[i]->setHealthMax(m_members[i]->getHealthMax() - 300);
        }
        delete[] m_members;
    }

    Guild::Guild(const Guild& src) : m_name(src.m_name), m_members(nullptr), m_size(0) 
    {
        for (size_t i = 0; i < src.m_size; ++i) 
        {
            addMember(src.m_members[i]);
        }
    }

    Guild& Guild::operator=(const Guild& src)
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

        for (size_t i = 0; i < src.m_size; ++i) {
            addMember(src.m_members[i]);
        }

        return *this;

    }

    Guild::Guild(Guild&& src) noexcept
        : m_name(std::move(src.m_name)), m_members(src.m_members), m_size(src.m_size) {

        std::cout << "Moving Guild: " << m_name << std::endl;

        src.m_members = nullptr;
        src.m_size = 0;
    }

    Guild& Guild::operator=(Guild&& src) noexcept
    {
        if (this != &src)
        {
            for (size_t i = 0; i < m_size; ++i)
            {
                delete m_members[i];
            }
            delete[] m_members;
            m_members = nullptr;
            m_size = 0;

            m_name = std::move(src.m_name);
            m_members = src.m_members;
            m_size = src.m_size;


            src.m_members = nullptr;
            src.m_size = 0;

        }
        return *this;
    }

    void Guild::addMember(Character* c)
    {
        for (size_t i = 0; i < m_size; ++i) 
        {
            if (m_members[i]->getName() == c->getName())
            {
                return;
            }
        }

        Character** temp = new Character * [m_size + 1];

        for (size_t i = 0; i < m_size; ++i) 
        {
            temp[i] = m_members[i];
        }
        temp[m_size] = c->clone(); 

        c->setHealthMax(c->getHealthMax() + 300);

        delete[] m_members;
        m_members = temp;
        ++m_size;
    }

    void Guild::removeMember(const std::string& c) 
    {
        size_t index = m_size;

        for (size_t i = 0; i < m_size; ++i) 
        {
            if (m_members[i]->getName() == c) 
            {
                index = i;
                return;
            }
        }

        if (index == m_size)
        {
            return;
        }

        m_members[index]->setHealthMax(m_members[index]->getHealthMax() - 300);
        delete m_members[index];

        for (size_t i = index; i < m_size - 1; ++i)
        {
            m_members[i] = m_members[i + 1];
        }
        --m_size;

        if (m_size == 0) 
        {
            delete[] m_members;
            m_members = nullptr;
        }
    }

    Character* Guild::operator[](size_t idx) const 
    {
        if (idx < m_size)
        {
            return m_members[idx];
        }
        return nullptr;
    }

    void Guild::showMembers() const 
    {
        if (m_members == nullptr || m_size == 0) 
        {
            std::cout << "No guild." << std::endl;
        }
        else 
        {
            std::cout << "[Guild] " << m_name << std::endl;
            for (size_t i = 0; i < m_size; ++i) 
            {
                std::cout << "    " << (i + 1) << ": " << *m_members[i] << std::endl;
            }
        }
    }

}
