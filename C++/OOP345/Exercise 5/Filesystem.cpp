#include "Filesystem.h"

seneca::Filesystem::Filesystem(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        throw std::runtime_error("Filesystem not created: Cannot open file " + filename);
    }
    m_root = new Directory("/");
    m_current = m_root;

    std::string line;
    while (std::getline(file, line)) 
    {
        line.erase(0, line.find_first_not_of(" "));
        line.erase(line.find_last_not_of(" ") + 1);

        std::istringstream iss(line);
        std::string path, contents;
        if (std::getline(iss, path, '|')) 
        {
            path.erase(0, path.find_first_not_of(" "));
            path.erase(path.find_last_not_of(" ") + 1);

            Directory* dir = m_root;
            std::istringstream pathStream(path);
            std::string segment, lastSegment;
            bool isFile = false;

            while (std::getline(pathStream, segment, '/'))
            {
                lastSegment = segment;
                Resource* found = dir->find(segment);
                if (!found)
                {
                    if (pathStream.rdbuf()->in_avail() == 0) {
                        isFile = true;
                    }
                    else 
                    {
                        Directory* newDir = new Directory(segment);
                        *dir += newDir;
                        dir = newDir;
                    }
                }
                else if (found->type() == NodeType::DIR)
                {
                    dir = static_cast<Directory*>(found);
                }
            }

            if (path.back() == '/') 
            {
                if (!dir->find(segment))
                {
                    *dir += new Directory(segment);
                }
            }
            else {

                if (isFile && std::getline(iss, contents)) 
                {
                    contents.erase(0, contents.find_first_not_of(" "));
                    contents.erase(contents.find_last_not_of(" ") + 1);
                    *dir += new File(lastSegment, contents);
                }
            }
        }
    }
}

seneca::Filesystem::~Filesystem()
{
	delete m_root;
}

seneca::Filesystem::Filesystem(Filesystem&& src) noexcept 
	: m_root(src.m_root), m_current(src.m_current)
{
	src.m_root = nullptr;
	src.m_current = nullptr;
}

seneca::Filesystem& seneca::Filesystem::operator=(Filesystem&& src) noexcept
{
	if (this != &src) {
		delete m_root;
		m_root = src.m_root;
		m_current = src.m_current;
		src.m_root = nullptr;
		src.m_current = nullptr;
	}
	return *this;
}

seneca::Filesystem& seneca::Filesystem::operator+=(Resource* res)
{
	*m_current += res;
	return *this;
}

seneca::Directory* seneca::Filesystem::change_directory(const std::string& dirName)
{
    if (dirName == "/")
    {
        m_current = m_root;
        return m_current;
    }

    std::istringstream pathStream(dirName);
    std::string segment;
    Directory* dir = m_current;

    while (std::getline(pathStream, segment, '/')) 
    {
        Resource* found = dir->find(segment);
        if (!found || found->type() != NodeType::DIR) 
        {
            throw std::invalid_argument("Cannot change directory! " + dirName + " not found!");
        }
        dir = static_cast<Directory*>(found);
    }

    m_current = dir;
    return m_current;
}

seneca::Directory* seneca::Filesystem::get_current_directory() const
{
	return m_current;
}

