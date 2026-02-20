#include "LblShape.h"
#include "Utils.h"
using namespace std;
namespace seneca {
	char* LblShape::label() const
	{
		return m_label;
	}
	LblShape::LblShape()
	{
		if (m_label != nullptr) m_label = nullptr;
	}

	LblShape::LblShape(const char* src)
	{
		ut.alocpy(m_label, src);
	}

	LblShape::~LblShape()
	{
		delete[] m_label;
	}

	void LblShape::getSpecs(std::istream& is)
	{
		char temp[81];
		is.getline(temp, 81, ',');
		if (is) ut.alocpy(m_label, temp);
	}
}