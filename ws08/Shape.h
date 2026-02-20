#ifndef SENECA_SHAPE_H
#define SENECA_SHAPE_H
#include <iostream>

namespace seneca {

    class Shape {
    public:
        // Pure virtual function to draw the shape, implemented in derived classes
        virtual void draw(std::ostream&) const = 0;

        // Pure virtual function to get specifications of the shape, implemented in derived classes
        virtual void getSpecs(std::istream&) = 0;

        // Virtual destructor to ensure proper cleanup of derived class objects
        virtual ~Shape() = default;
    };

    // Operator overload to handle output stream, relies on draw function
    std::ostream& operator <<(std::ostream&, const Shape&);

    // Operator overload to handle input stream, relies on getSpecs function
    std::istream& operator >>(std::istream&, Shape&);

}

#endif // !SENECA_SHAPE_H