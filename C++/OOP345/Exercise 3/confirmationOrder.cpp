#include "confirmationOrder.h"

seneca::ConfirmationOrder::ConfirmationOrder() : toys(nullptr), toyCount(0) 
{
}

seneca::ConfirmationOrder::~ConfirmationOrder()
{
    delete[] toys;
}

seneca::ConfirmationOrder::ConfirmationOrder(const ConfirmationOrder& src) : toyCount(src.toyCount) 
{
    toys = new const Toy * [toyCount];
    for (size_t i = 0; i < toyCount; ++i) {
        toys[i] = src.toys[i];
    }
}

seneca::ConfirmationOrder& seneca::ConfirmationOrder::operator=(const ConfirmationOrder& src)
{
    if (this != &src) {
        delete[] toys;

        toyCount = src.toyCount;
        toys = new const Toy * [toyCount];
        for (size_t i = 0; i < toyCount; ++i) {
            toys[i] = src.toys[i];
        }
    }
    return *this;
}

seneca::ConfirmationOrder::ConfirmationOrder(ConfirmationOrder&& src) noexcept
    : toys(src.toys), toyCount(src.toyCount) 
{
    src.toys = nullptr;
    src.toyCount = 0;
}

seneca::ConfirmationOrder& seneca::ConfirmationOrder::operator=(ConfirmationOrder&& src) noexcept
{
    if (this != &src) {
        delete[] toys;

        toys = src.toys;
        toyCount = src.toyCount;

        src.toys = nullptr;
        src.toyCount = 0;
    }
    return *this;
}

seneca::ConfirmationOrder& seneca::ConfirmationOrder::operator+=(const Toy& toy)
{
    for (size_t i = 0; i < toyCount; ++i) {
        if (toys[i] == &toy) return *this;
    }

    const Toy** temp = new const Toy * [toyCount + 1];
    for (size_t i = 0; i < toyCount; ++i) {
        temp[i] = toys[i];
    }
    temp[toyCount] = &toy;

    delete[] toys;
    toys = temp;
    toyCount++;
    return *this;
}

seneca::ConfirmationOrder & seneca::ConfirmationOrder::operator-=(const Toy & toy)
{
    size_t index = toyCount;
    for (size_t i = 0; i < toyCount; ++i) {
        if (toys[i] == &toy) {
            index = i;
            break;
        }
    }

    if (index == toyCount) return *this;

    for (size_t i = index; i < toyCount - 1; ++i) {
        toys[i] = toys[i + 1];
    }

    toyCount--;
    const Toy** temp = new const Toy * [toyCount];
    for (size_t i = 0; i < toyCount; ++i) {
        temp[i] = toys[i];
    }
    delete[] toys;
    toys = temp;

    return *this;
}

std::ostream& seneca::operator<<(std::ostream& os, const ConfirmationOrder& order)
{
    os << "--------------------------\n";
    os << "Confirmations to Send\n";
    os << "--------------------------\n";

    if (order.toyCount == 0) {
        os << "There are no confirmations to send!\n";
    }
    else {
        for (size_t i = 0; i < order.toyCount; ++i) {
            os << *order.toys[i];
        }
    }
    os << "--------------------------\n";
    return os;
}
