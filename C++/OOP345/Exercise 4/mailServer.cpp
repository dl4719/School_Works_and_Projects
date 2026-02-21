#include <iostream>
#include <string>
#include "mailServer.h"

seneca::MailServer::MailServer(const char* name, const char* address)
    : m_userName(name), m_userAddress(address), m_inbox(nullptr), m_cnt(0), onNewMailArrived(nullptr) 
{
    m_plugins[0] = nullptr;
    m_plugins[1] = nullptr;
}

seneca::MailServer::~MailServer()
{
    delete[] m_inbox;
}

seneca::MailServer::MailServer(const MailServer& src)
    : m_userName(src.m_userName), m_userAddress(src.m_userAddress), m_cnt(src.m_cnt),
    onNewMailArrived(src.onNewMailArrived) {
    m_inbox = new Message[m_cnt];  // Allocate new memory for inbox
    for (size_t i = 0; i < m_cnt; ++i) {
        m_inbox[i] = src.m_inbox[i];  // Copy each message
    }
    for (int i = 0; i < 2; ++i) {
        m_plugins[i] = src.m_plugins[i];  // Shallow copy of plugins
    }
}

seneca::MailServer& seneca::MailServer::operator=(const MailServer& src)
{
    if (this != &src) {  // Self-assignment check
        delete[] m_inbox;  // Clean up existing inbox

        m_userName = src.m_userName;
        m_userAddress = src.m_userAddress;
        m_cnt = src.m_cnt;
        onNewMailArrived = src.onNewMailArrived;

        m_inbox = new Message[m_cnt];  // Allocate new memory for inbox
        for (size_t i = 0; i < m_cnt; ++i) {
            m_inbox[i] = src.m_inbox[i];  // Copy messages
        }

        for (int i = 0; i < 2; ++i) {
            m_plugins[i] = src.m_plugins[i];  // Shallow copy of plugins
        }
    }
    return *this;
}

seneca::MailServer::MailServer(MailServer&& src) noexcept
    : m_userName(std::move(src.m_userName)), m_userAddress(std::move(src.m_userAddress)),
    m_inbox(src.m_inbox), m_cnt(src.m_cnt), onNewMailArrived(src.onNewMailArrived) 
{
    for (int i = 0; i < 2; ++i) {
        m_plugins[i] = src.m_plugins[i];  // Move plugins
    }
    src.m_inbox = nullptr;  // Avoid double-delete
    src.m_cnt = 0;
    src.onNewMailArrived = nullptr;
}

seneca::MailServer& seneca::MailServer::operator=(MailServer&& src) noexcept
{
    if (this != &src) {  // Self-assignment check
        delete[] m_inbox;  // Clean up existing inbox

        m_userName = std::move(src.m_userName);
        m_userAddress = std::move(src.m_userAddress);
        m_inbox = src.m_inbox;
        m_cnt = src.m_cnt;
        onNewMailArrived = src.onNewMailArrived;

        for (int i = 0; i < 2; ++i) {
            m_plugins[i] = src.m_plugins[i];  // Move plugins
        }

        src.m_inbox = nullptr;  // Avoid double-delete
        src.m_cnt = 0;
        src.onNewMailArrived = nullptr;
    }
    return *this;
}

void seneca::MailServer::receiveMail(Message msg)
{
    if (msg.m_toAddress != m_userAddress) {
        throw "Message is not for this user";  // Simplified error handling
    }

    // Resize inbox if necessary
    if (m_cnt == 0) {
        m_inbox = new Message[1];  // Allocate memory for first message
    }
    else {
        Message* temp = new Message[m_cnt + 1];  // Allocate new array with room for one more message
        for (size_t i = 0; i < m_cnt; ++i) {
            temp[i] = m_inbox[i];  // Copy old messages
        }
        delete[] m_inbox;  // Free old inbox
        m_inbox = temp;  // Point to the new inbox
    }

    m_inbox[m_cnt++] = msg;  // Add new message

    // Process plugins
    for (int i = 0; i < 2; ++i) {
        if (m_plugins[i]) {
            (*m_plugins[i])(msg);  // Call the plugin operator()
        }
    }

    // Notify observer if registered
    if (onNewMailArrived) {
        onNewMailArrived(msg);
    }
}

void seneca::MailServer::addPlugin(Plugin* thePlugin)
{
    for (int i = 0; i < 2; ++i) {
        if (m_plugins[i] == nullptr) {
            m_plugins[i] = thePlugin;
            return;
        }
    }
    throw "No space for more plugins";  // Simplified error handling
}

void seneca::MailServer::setObserver(Observer_pfn observer)
{
    onNewMailArrived = observer;
}

size_t seneca::MailServer::getInboxSize() const
{
    return m_cnt;
}

void seneca::MailServer::showInbox() const
{
    for (size_t i = 0; i < m_cnt; ++i) {
        std::cout << m_inbox[i].m_fromName << " "
            << m_inbox[i].m_fromAddress << " "
            << m_inbox[i].m_date << " "
            << m_inbox[i].m_subject << std::endl;
    }
}

seneca::Message& seneca::MailServer::operator[](size_t idx)
{
    if (idx >= m_cnt) {
        throw std::out_of_range("Index " + std::to_string(idx) + " is out of bounds");
    }
    return m_inbox[idx];
}

