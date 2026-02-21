/***********************************************************************
// OOP244 workshop 9, Transcript module
//
// File	Transcript.coo
// Version 1.0
// Date 2024-11-18
// started by Fardad
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include <iostream>
#include "Transcript.h"
#include "Utils.h"
using namespace std;
namespace seneca {
	Transcript::Transcript(const char* studentName, int studentNumber) :
		m_studentName(ut.alocpy(studentName)), m_studentNumber(studentNumber)
	{
	}
	Transcript::Transcript(const Transcript& src) : 
		Marks(src), m_studentName(ut.alocpy(src.m_studentName)), m_studentNumber(src.m_studentNumber)
	{
	}

	Transcript& Transcript::operator=(const Transcript& src)
	{
		if (this != &src) {
			Marks::operator=(src);

			ut.strcpy(m_studentName, src.m_studentName);

			m_studentNumber = src.m_studentNumber;
		}
		return *this;
	}

	Transcript::~Transcript()
	{
		delete[] m_studentName;
	}

	std::ostream& Transcript::display(std::ostream& ostr) const
	{
		ostr << m_studentName << " (" << m_studentNumber << ")\n";
		ostr << "--------------------------------------------------------------------------\n";
		Marks::display(ostr);
		return ostr;
	}

}
