#include <iomanip>
#include "Rectangle.h"
#include "Utils.h"
using namespace std;
namespace seneca {

	Rectangle::Rectangle(const char* label, int width, int height) : LblShape(label)
	{

		if (height < 3) {
			m_height = 3;
		}
		else {
			m_height = height;
		}
		

		if (width < (ut.strlen(label) + 2)) {
			m_width = ut.strlen(label) + 2;
		}
		else {
			m_width = width;
		}
		
	}

	void Rectangle::draw(std::ostream& os) const
	{
		if (m_height > 0) {
			os << "+" << setw(m_width - 2) << setfill('-') << "-" << "+" << endl;
			os << "|" << setw(m_width - 2) << setfill(' ') << left << label() << "|" << endl;
			for (int i = 0; i < m_height - 3; i++) {
				os << "|" << setw(m_width - 2) << setfill(' ') << " " << "|" << endl;
			}
			os << "+" << setw(m_width - 2) << setfill('-') << "-" << "+";

		}
	}

	void Rectangle::getSpecs(std::istream& is)
	{
		LblShape::getSpecs(is);
		
		char comma;
		is >> m_width >> comma >> m_height;

		is.ignore();
	}

}