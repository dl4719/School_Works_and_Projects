#include <iostream>
#include <iomanip>
#include <cstring>
#include <ostream>
#include "Professor.h"
#include "Employee.h"
#include "Utils.h"
//John Doe,IPC144 - Introduction to Programming Using C, 3, 12312, 65432
using namespace seneca;
using namespace std;

	double Professor::devPay() const
	{
		return salary()*0.01*m_noSections;
	}

	Professor::Professor(const char* name, const char* subject, size_t noSections, size_t employeeNo, double salary)
		:Employee(name, employeeNo, salary), subjectName(ut.alocpy(subject)), m_noSections(noSections) {}

	seneca::Professor::~Professor()
	{
		delete[] subjectName;
	}

	std::istream& Professor::read(std::istream& istr)
	{
		char buffer[1024]{};
		Employee::read(istr);
		istr.ignore();
		istr.getline(buffer, 1024, ',');
		if (istr) ut.alocpy(subjectName, buffer);
		istr >> m_noSections;
		return istr;
	}

	std::ostream& Professor::write(std::ostream& ostr) const
	{
		char subject[21]{};
		if (subjectName) ut.strcpy(subject, subjectName, 20);
		Employee::write(ostr);
		ostr << " ";
		ostr.width(20);
		ostr.setf(ios::left);
		ostr << subject << " |";
		ostr.unsetf(ios::left);
		ostr.width(6);
		ostr.setf(ios::right);
		ostr << m_noSections << " |";
		ostr.fill(' ');
		ostr.setf(ios::fixed);
		ostr.precision(2);
		ostr.width(9);
		ostr << devPay() << " |";
		ostr.unsetf(ios::right);
		return ostr;
	}

	std::ostream& Professor::title(std::ostream& ostr) const
	{
		Employee::title();
		return ostr << " Teaching Subject     | Sec # | $Dev Pay |";
	}

	std::ostream& seneca::operator<<(std::ostream& ostr, const Professor& P)
	{
		return P.write(ostr);
	}

	std::istream& seneca::operator>>(std::istream& istr, Professor& P)
	{
		return P.read(istr);
	}
