#include "shoppingCart.h"

seneca::ShoppingCart::ShoppingCart(const std::string& name, int age, const Toy* toys[], size_t count)
    : childName(name), childAge(age), toyCount(count) {

    this->toys = new const Toy * [toyCount];
    for (size_t i = 0; i < toyCount; ++i) {
        this->toys[i] = new Toy(*toys[i]);
    }
}

seneca::ShoppingCart::~ShoppingCart()
{
    for (size_t i = 0; i < toyCount; ++i) {
        delete toys[i];
    }
    delete[] toys;
}

seneca::ShoppingCart::ShoppingCart(const ShoppingCart& src)
    : childName(src.childName), childAge(src.childAge), toyCount(src.toyCount) {

    toys = new const Toy * [toyCount];
    for (size_t i = 0; i < toyCount; ++i) {
        toys[i] = new Toy(*src.toys[i]);
    }
}

seneca::ShoppingCart& seneca::ShoppingCart::operator=(const ShoppingCart& src)
{
    if (this != &src) {
        for (size_t i = 0; i < toyCount; ++i) {
            delete toys[i];
        }
        delete[] toys;

        childName = src.childName;
        childAge = src.childAge;
        toyCount = src.toyCount;

        toys = new const Toy * [toyCount];
        for (size_t i = 0; i < toyCount; ++i) {
            toys[i] = new Toy(*src.toys[i]);
        }
    }
    return *this;
}

seneca::ShoppingCart::ShoppingCart(ShoppingCart&& src) noexcept
    : childName(std::move(src.childName)), childAge(src.childAge), toys(src.toys), toyCount(src.toyCount) 
{
    src.toys = nullptr;
    src.toyCount = 0;
}

seneca::ShoppingCart& seneca::ShoppingCart::operator=(ShoppingCart&& src) noexcept
{
    if (this != &src) {
        for (size_t i = 0; i < toyCount; ++i) {
            delete toys[i];
        }
        delete[] toys;

        childName = std::move(src.childName);
        childAge = src.childAge;
        toyCount = src.toyCount;
        toys = src.toys;

        src.toys = nullptr;
        src.toyCount = 0;
    }
    return *this;
}

std::ostream& seneca::operator<<(std::ostream& os, const ShoppingCart& cart)
{
    static int callCount = 0;
    callCount++;

    os << "--------------------------\n";
    os << "Order " << callCount << ": ";

    if (cart.childName.empty() || cart.childAge <= 0) {
        os << "This shopping cart is invalid.\n";
    }
    else if (cart.toyCount == 0) {
        os << "Shopping for " << cart.childName << " " << cart.childAge << " years old (0 toys)\n";
        os << "Empty shopping cart!\n";
    }
    else {
        os << "Shopping for " << cart.childName << " " << cart.childAge << " years old (" << cart.toyCount << " toys)\n";
        for (size_t i = 0; i < cart.toyCount; ++i) {
            os << *cart.toys[i];
        }
    }
    os << "--------------------------\n";
    return os;
}