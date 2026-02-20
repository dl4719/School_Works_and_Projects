#include <iomanip>
#include "Line.h"
#include "Utils.h"
using namespace std;
namespace seneca {

	Line::Line(const char* label, int length) : LblShape(label)
	{
		if (length < ut.strlen(label)) {
			m_length = ut.strlen(label);
		}
		else {
			m_length = length;
		}
	}

	void Line::draw(std::ostream& os) const
	{
		if (m_length > 0 && label() != nullptr)
		{
			os << label() << "\n";
			os.width(m_length);
			os.fill('=');
			os << "=";
		}
	}

	void Line::getSpecs(std::istream& is)
	{
		LblShape::getSpecs(is);

		is >> m_length;

		is.ignore();
	}


}