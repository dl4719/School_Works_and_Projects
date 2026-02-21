#ifndef SENECA_CONFIRMATIONORDER_H
#define SENECA_CONFIRMATIONORDER_H

#include <iostream>
#include "toy.h"

namespace seneca 
{
    class ConfirmationOrder
    {
        const Toy** toys;
        size_t toyCount;

    public:
        ConfirmationOrder();

        ~ConfirmationOrder();

        ConfirmationOrder(const ConfirmationOrder& src);

        ConfirmationOrder& operator=(const ConfirmationOrder& src);

        ConfirmationOrder(ConfirmationOrder&& src) noexcept;

        ConfirmationOrder& operator=(ConfirmationOrder&& src) noexcept;

        ConfirmationOrder& operator+=(const Toy& toy);

        ConfirmationOrder& operator-=(const Toy& toy);

        friend std::ostream& operator<<(std::ostream& os, const ConfirmationOrder& order);
    };
}

#endif // SENECA_CONFIRMATIONORDER_H
