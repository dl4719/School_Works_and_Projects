#ifndef SENECA_SPAMFILTERPLUGIN_H
#define SENECA_SPAMFILTERPLUGIN_H

#include "plugin.h"
#include "message.h"

namespace seneca 
{
    class SpamFilterPlugin : public Plugin 
    {
        std::string spamRules[100];
        size_t spamCount = 0;

    public:
        SpamFilterPlugin(const char* filename);
        ~SpamFilterPlugin();
        SpamFilterPlugin(const SpamFilterPlugin& src);
        SpamFilterPlugin& operator=(const SpamFilterPlugin& other);

        void operator()(Message& msg);

        void showStats() const;
    };
}
#endif
