#include "Directory.h"
#include <iomanip>

namespace seneca {
    Directory::Directory(const std::string& name) 
    {
        m_name = name;
        if (!m_name.empty() && m_name.back() == '/')
        {
            m_name.pop_back();
        }
    }

    Directory::~Directory() {
        for (auto resource : m_contents) 
        {
            delete resource;
        }
    }

    void Directory::update_parent_path(const std::string& path)
    {
        m_parent_path = path;
        if (m_parent_path.back() != '/') 
        {
            m_parent_path += '/';
        }

        for (auto res : m_contents)
        {
            res->update_parent_path(this->path());
        }
    }

    NodeType Directory::type() const 
    {
        return NodeType::DIR;
    }

    std::string Directory::path() const
    {
        if (m_parent_path.empty())
        {
            return m_name + "/";
        }
        return m_parent_path + (m_parent_path.back() == '/' ? "" : "/") + m_name + "/";
    }

    std::string Directory::name() const
    {
        return m_name;
    }

    int Directory::count() const 
    {
        return static_cast<int>(m_contents.size());
    }

    size_t Directory::size() const 
    {
        size_t totalSize = 0;
        for (const auto& resource : m_contents) 
        {
            totalSize += resource->size();
        }
        return totalSize;
    }

    Directory& Directory::operator+=(Resource* src)
    {
        for (const auto& resource : m_contents) 
        {
            if (resource->name() == src->name()) 
            {
                throw std::runtime_error("Duplicate resource name found.");
            }
        }
        src->update_parent_path(this->path());
        m_contents.push_back(src);
        return *this;
    }

    Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags)
    {
        
        for (auto res : m_contents) 
        {
            if (res->name() == name) 
            {
                return res;
            }
        }

        if (std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) != flags.end())
        {
            for (auto res : m_contents) 
            {
                if (res->type() == NodeType::DIR)
                {
                    Resource* found = static_cast<Directory*>(res)->find(name, flags);
                    if (found) 
                    {
                        return found;
                    }
                }
            }
        }

        return nullptr;
    }



    void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags)
    {
        for (auto it = m_contents.begin(); it != m_contents.end(); ++it) 
        {
            if ((*it)->name() == name)
            {
                if ((*it)->type() == NodeType::DIR && 
                    std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) == flags.end()) 
                {
                    throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
                }
                delete* it;
                m_contents.erase(it);
                return;
            }
        }
        throw std::runtime_error(name + " does not exist in " + this->name());
    }

    void Directory::display(std::ostream& os, const std::vector<FormatFlags>& flags) const 
    {
        os << "Total size: " << size() << " bytes\n";

        for (const auto& resource : m_contents) 
        {
            os << (resource->type() == NodeType::DIR ? "D | " : "F | ");
            os << std::left << std::setw(15) << resource->name() << " | ";

            if (std::find(flags.begin(), flags.end(), FormatFlags::LONG) != flags.end()) {
                if (resource->type() == NodeType::DIR) {
                    os << std::right << std::setw(2) << resource->count() << " | "
                        << std::right << std::setw(10) << resource->size() << " bytes";
                }
                else {
                    os << "    | " << std::right << std::setw(10) << resource->size() << " bytes";
                }
            }
            os << std::endl;
        }
    }
}