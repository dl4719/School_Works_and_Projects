#ifndef SENECA_TOY_H
#define SENECA_TOY_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

namespace seneca
{
    class Toy
    {
        int m_id{};
        std::string m_name;
        int m_numItems{};
        double m_price{};
        static constexpr double m_HST = 0.13;

    public:
        Toy() = default;
        Toy(const std::string& toy);

        void update(int numItems);

        friend std::ostream& operator<<(std::ostream& os, const Toy& toy);
    };
}
#endif 