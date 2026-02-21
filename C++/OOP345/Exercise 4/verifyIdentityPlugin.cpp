#include <string>
#include <fstream>
#include <iostream>
#include "verifyIdentityPlugin.h"

seneca::VerifyIdentityPlugin::VerifyIdentityPlugin(const char* filename) 
{
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open trusted email list file.");
    }

    size_t count = 0;
    std::string line;
    while (std::getline(file, line) && count < 100) {
        trustedEmails[count++] = line;
    }
    emailCount = count;
}

seneca::VerifyIdentityPlugin::~VerifyIdentityPlugin()
{
}

seneca::VerifyIdentityPlugin::VerifyIdentityPlugin(const VerifyIdentityPlugin& src) : emailCount(src.emailCount) 
{
    for (int i = 0; i < emailCount; ++i) {
        trustedEmails[i] = src.trustedEmails[i];
    }
}

void seneca::VerifyIdentityPlugin::operator()(Message& msg)
{
    for (size_t i = 0; i < emailCount; ++i) {
        if (trustedEmails[i].empty()) break;

        size_t pos = msg.m_subject.find(trustedEmails[i]);
        if (pos != std::string::npos) {
            msg.m_subject = "[TRUSTED] " + msg.m_subject;
            ++emailCount;
            break;
        }
    }
}

void seneca::VerifyIdentityPlugin::showStats() const
{
    std::cout << "[Identity Checker Plugin] can validate identity for ";
    for (size_t i = 0; i < emailCount; ++i) {
        std::cout << trustedEmails[i];
        if (i < emailCount - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}
