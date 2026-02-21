#ifndef SENECA_VERIFYIDENTITYPLUGIN_H
#define SENECA_VERIFYIDENTITYPLUGIN_H

#include "plugin.h"
#include "message.h"

namespace seneca 
{
    class VerifyIdentityPlugin : public Plugin 
    {
        std::string trustedEmails[100];
        size_t emailCount = 0;

    public:
        VerifyIdentityPlugin(const char* filename);
        ~VerifyIdentityPlugin();
        VerifyIdentityPlugin(const VerifyIdentityPlugin& src);

        void operator()(Message& msg);

        void showStats() const;
    };
}
#endif
