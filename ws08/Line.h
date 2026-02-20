#ifndef SENECA_LINE_H
#define SENECA_LINE_H
#include "LblShape.h"

namespace seneca {

    class Line : public LblShape {
        // Length of the line
        int m_length{};
    public:
        // Default constructor
        Line() = default;

        // Constructor that initializes label and length
        Line(const char* label, int length);

        // Draws the line, using the label and length
        void draw(std::ostream&) const;

        // Gets specifications of the line (label and length) from input
        void getSpecs(std::istream&);
    };

}

#endif // !SENECA_LINE_H