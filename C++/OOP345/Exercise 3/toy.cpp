#include "toy.h"

seneca::Toy::Toy(const std::string& toy)
{
    std::istringstream ss(toy);
    std::string reqField;

    std::getline(ss, reqField, ':');
    m_id = std::stoi(reqField);

    std::getline(ss, reqField, ':');
    m_name = reqField;
    m_name.erase(0, m_name.find_first_not_of(" "));
    m_name.erase(m_name.find_last_not_of(" ") + 1);

    std::getline(ss, reqField, ':');
    m_numItems = std::stoi(reqField);

    std::getline(ss, reqField, ':');
    m_price = std::stod(reqField);
}

void seneca::Toy::update(int numItems)
{
    this->m_numItems = numItems;
}

std::ostream& seneca::operator<<(std::ostream& os, const Toy& toy)
{
    double subtotal = toy.m_numItems * toy.m_price;
    double tax = subtotal * Toy::m_HST;
    double total = subtotal + tax;

    os << "Toy " << std::setw(8) << std::setfill('0') << toy.m_id << ": "
        << std::setw(24) << std::setfill('.') << std::right << toy.m_name << " "
        << std::setw(2) << std::setfill(' ') << std::right << toy.m_numItems << " items @ "
        << std::setw(6) << std::fixed << std::setprecision(2) << std::right << toy.m_price << "/item  "
        << "subtotal: " << std::setw(7) << std::right << subtotal << "  "
        << "tax: " << std::setw(6) << std::right << tax << "  "
        << "total: " << std::setw(7) << std::right << total << std::endl;

    return os;
}
