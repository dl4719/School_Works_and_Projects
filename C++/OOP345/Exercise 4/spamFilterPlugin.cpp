#include <string>
#include <fstream>
#include <iostream>
#include "spamFilterPlugin.h"


seneca::SpamFilterPlugin::SpamFilterPlugin(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open spam rules file.");
    }

    size_t ruleCount = 0;
    std::string line;
    while (std::getline(file, line) && ruleCount < 100) {
        spamRules[ruleCount++] = line;
    }
}

seneca::SpamFilterPlugin::~SpamFilterPlugin()
{
}

seneca::SpamFilterPlugin::SpamFilterPlugin(const SpamFilterPlugin& src) : spamCount(src.spamCount) 
{
    for (size_t i = 0; i < spamCount; ++i) {
        spamRules[i] = src.spamRules[i];
    }
}

seneca::SpamFilterPlugin& seneca::SpamFilterPlugin::operator=(const SpamFilterPlugin& src) 
{
    if (this != &src) {
        spamCount = src.spamCount;
        for (size_t i = 0; i < 100; ++i) {
            spamRules[i] = src.spamRules[i];
        }
    }
    return *this;
}

void seneca::SpamFilterPlugin::operator()(Message& msg)
{
    for (size_t i = 0; i < 100; ++i) {
        if (spamRules[i].empty()) break;

        size_t pos = msg.m_subject.find(spamRules[i]);
        if (pos != std::string::npos) {
            msg.m_subject = "[SPAM] " + msg.m_subject;
            ++spamCount;
            break;
        }
    }
}

void seneca::SpamFilterPlugin::showStats() const
{
    std::cout << "[Spam Filter Plugin] Identified " << spamCount << " spam messages." << std::endl;
}


