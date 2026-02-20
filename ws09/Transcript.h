/***********************************************************************
// OOP244 workshop 9, Transcript module
//
// File	Transcript.h
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
#ifndef SENECA_TRANSCRIPT_H
#define SENECA_TRANSCRIPT_H
#include <iostream>
#include "Marks.h"
namespace seneca {
   class Transcript :
      public Marks {
      // character pointer student name
       char* m_studentName{};
      // unsigned integer or size_t student number
       size_t m_studentNumber{};

   public:
      // Constructor
       Transcript(const char* studentName, int studentNumber);

      // Rule of Three
       Transcript(const Transcript& src);
       Transcript& operator =(const Transcript& src);
      // Destructor
       ~Transcript();

       std::ostream& display(std::ostream& ostr = std::cout)const;
   };
}
#endif // !SENECA_TRANSCRIPT_H


