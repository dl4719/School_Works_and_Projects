#ifndef SENECA_FILESYSTEM_H
#define SENECA_FILESYSTEM_H

#include <fstream>
#include <sstream>
#include "Directory.h"

namespace seneca {
    class Filesystem {
        Directory* m_root;
        Directory* m_current;

    public:
        Filesystem(const std::string& rootName = "");

        // Destructor
        ~Filesystem();

        // Prevent copy operations
        Filesystem(const Filesystem&) = delete;
        Filesystem& operator=(const Filesystem&) = delete;

        // Allow move operations
        Filesystem(Filesystem&& src) noexcept;

        Filesystem& operator=(Filesystem&& src) noexcept;

        // Add resource to the current directory
        Filesystem& operator+=(Resource* res);

        // Change directory
        Directory* change_directory(const std::string& dirName = "");

        // Get current directory
        Directory* get_current_directory() const;
    };
}

#endif
