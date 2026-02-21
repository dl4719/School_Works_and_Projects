#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H

#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iomanip>

namespace seneca
{
    enum class Err_Status 
    {
        Err_Success,
        Err_NotFound,
        Err_OutOfMemory
    };

    template <typename T>
    class Database 
    {
        static constexpr size_t MAX_SIZE = 20;

        std::string keys[MAX_SIZE];
        T values[MAX_SIZE];
        size_t entryCount;
        std::string filename;

        static std::shared_ptr<Database<T>> instance;

        Database(const std::string& filename) : filename(filename), entryCount(0) {
            std::cout << "[" << this << "] Database<T>(const std::string&)" << std::endl;
            std::ifstream file(filename);
            std::string key;
            T value;

            while (file >> key >> value) 
            {
                if (entryCount >= MAX_SIZE)
                    break;

                for (char& c : key) {
                    if (c == '_') c = ' ';
                }

                encryptDecrypt(value);
                keys[entryCount] = key;
                values[entryCount] = value;
                entryCount++;
            }
        }
        
        void encryptDecrypt(T& value) {}

    public:

        static std::shared_ptr<Database<T>> getInstance(const std::string& dbFileName)
        {
            if (!instance) 
            {
                instance = std::shared_ptr<Database<T>>(new Database<T>(dbFileName));
            }
            return instance;
        }

        Err_Status GetValue(const std::string& key, T& value)
        {
            for (size_t i = 0; i < entryCount; ++i)
            {
                if (keys[i] == key)
                {
                    value = values[i];
                    encryptDecrypt(values[i]);
                    return Err_Status::Err_Success;
                }
            }
            return Err_Status::Err_NotFound;
        }

        Err_Status SetValue(const std::string& key, const T& value) 
        {
            if (entryCount >= MAX_SIZE) 
                return Err_Status::Err_OutOfMemory;

            T encryptedValue = value;
            encryptDecrypt(encryptedValue);

            keys[entryCount] = key;
            values[entryCount] = value;
            entryCount++;

            return Err_Status::Err_Success;
        }

        ~Database() 
        {
            std::cout << "[" << this << "] ~Database<T>()" << std::endl;

            std::string backupFile = filename + ".bkp.txt";
            std::ofstream backup(backupFile);

            for (size_t i = 0; i < entryCount; ++i) 
            {
                T encryptedValue = values[i];
                encryptDecrypt(encryptedValue);
                backup << std::left << std::setw(25) << keys[i] << " -> " << encryptedValue << "\n";
            }
        }
    };

    template <typename T>
    std::shared_ptr<Database<T>> Database<T>::instance = nullptr;

    template <>
    void Database<std::string>::encryptDecrypt(std::string& value)
    {
        const char secret[]{ "secret encryption key" };
        for (char& C : value)
        {
            for (size_t i = 0; secret[i] != '\0'; ++i)
            {
                C ^= secret[i];
            }
        }
    }

    template <>
    void Database<long long>::encryptDecrypt(long long& value)
    {
        const char secret[]{ "super secret encryption key" };

        char* bytePtr = reinterpret_cast<char*>(&value);

        for (size_t i = 0; i < sizeof(value); ++i)
        {
            for (size_t j = 0; secret[j] != '\0'; ++j)
            {
                bytePtr[i] ^= secret[j];
            }
        }
    }

}
#endif
