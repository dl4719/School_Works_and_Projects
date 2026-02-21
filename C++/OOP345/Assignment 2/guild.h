#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H
#include <iostream>
#include <string>
#include "character.h"

namespace seneca
{
    class Guild {
        std::string m_name;
        Character** m_members;
        size_t m_size;

    public:
        Guild();
        
        Guild(const char* name);
        
        ~Guild();

        Guild(const Guild& src);
        Guild& operator=(const Guild& src);
        Guild(Guild&& src) noexcept;
        Guild& operator=(Guild&& src) noexcept;

        void addMember(Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };
}
#endif