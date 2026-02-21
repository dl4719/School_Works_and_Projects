#ifndef SENECA_SHOPPINGCART_H
#define SENECA_SHOPPINGCART_H

#include <iostream>
#include <string>
#include "toy.h"

namespace seneca 
{
    class ShoppingCart
    {
        std::string childName;
        int childAge;
        const Toy** toys;
        size_t toyCount;

    public:
        ShoppingCart(const std::string& name, int age, const Toy* toys[], size_t count);
        ~ShoppingCart();
        ShoppingCart(const ShoppingCart& src);

        ShoppingCart& operator=(const ShoppingCart& src);
        ShoppingCart(ShoppingCart&& src) noexcept;
        ShoppingCart& operator=(ShoppingCart&& src) noexcept;

        friend std::ostream& operator<<(std::ostream& os, const ShoppingCart& cart);
    };
}
#endif