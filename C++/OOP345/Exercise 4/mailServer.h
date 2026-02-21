#ifndef SENECA_MAILSERVER_H
#define SENECA_MAILSERVER_H

#include "plugin.h"
#include "message.h"

using Observer_fn = void(const seneca::Message&);
using Observer_pfn = void(*)(const seneca::Message&);

namespace seneca
{
    class MailServer 
    {
        std::string m_userName;
        std::string m_userAddress;
        Message* m_inbox;
        size_t m_cnt;
        Observer_pfn onNewMailArrived;
        Plugin* m_plugins[2];

    public:
        MailServer(const char* name, const char* address);
        ~MailServer();
        MailServer(const MailServer& src);

        MailServer& operator=(const MailServer& src);

        MailServer(MailServer&& src) noexcept;
        MailServer& operator=(MailServer&& src) noexcept;

        void receiveMail(Message msg);
        void addPlugin(Plugin* thePlugin);
        void setObserver(Observer_pfn observer);
        size_t getInboxSize() const;
        void showInbox() const;
        Message& operator[](size_t idx);
    };
}
#endif