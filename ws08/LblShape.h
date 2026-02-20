#ifndef SENECA_LABELEDSHAPE_H
#define SENECA_LABELEDSHAPE_H
#include <iostream>
#include "Shape.h"

namespace seneca {

    class LblShape : public Shape {
        // Dynamically allocated label for the shape
        char* m_label = nullptr;
    protected:
        // Returns the label string for derived classes to access
        char* label() const;
    public:
        // Default constructor
        LblShape();

        // Constructor with label initialization
        LblShape(const char*);

        // Copy constructor and assignment operator are deleted to prevent copying
        LblShape(const LblShape&) = delete;
        LblShape& operator =(const LblShape&) = delete;

        // Reads label specifications from input stream
        void getSpecs(std::istream&);

        // Destructor to release dynamically allocated memory
        ~LblShape();
    };
}

#endif // !SENECA_LABELEDSHAPE_H