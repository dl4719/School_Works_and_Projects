#ifndef SENECA_RECTANGLE_H
#define SENECA_RECTANGLE_H
#include "LblShape.h"

namespace seneca {

    class Rectangle : public LblShape {
        // Width of the rectangle
        int m_width{};
        // Height of the rectangle
        int m_height{};
    public:
        // Default constructor
        Rectangle() = default;

        // Constructor that initializes label, width, and height
        Rectangle(const char*, int, int);

        // Draws the rectangle using the label, width, and height
        void draw(std::ostream&) const;

        // Gets specifications of the rectangle (label, width, height) from input
        void getSpecs(std::istream&);
    };

}

#endif // !SENECA_RECTANGLE_H