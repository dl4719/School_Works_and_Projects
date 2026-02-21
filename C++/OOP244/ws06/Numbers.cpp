#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <fstream>
#include "Numbers.h"
using namespace std;
namespace seneca {

  
   Numbers::Numbers() { 
      setEmpty();
      m_isOriginal = false;
   }

   Numbers::Numbers(const char* filename) { 
      setEmpty();
      m_isOriginal = true;
      setFilename(filename);
      m_numCount = numberCount();
      if (m_numCount == 0 || !load()) {
         delete[] m_numbers;
         delete[] m_filename;
         setEmpty();
         m_isOriginal = false; 
      }
      else {
         sort();
      }
   }

   Numbers::Numbers(const Numbers& src) {
       setEmpty();
       m_isOriginal = false;
       
       m_numCount = src.m_numCount;
       m_numbers = new double[m_numCount];
       for (int i = 0; i < m_numCount; i++) {
           m_numbers[i] = src.m_numbers[i];
       }

   }

   Numbers::~Numbers()
   {
       save();
       delete[] m_numbers;
       delete[] m_filename;
   }
   
   bool Numbers::isEmpty() const { 
      return m_numbers == nullptr;
   }

   bool Numbers::load()
   {
       if (m_numCount > 0) {
           m_numbers = new double[m_numCount];
           ifstream file(m_filename);
           int i = 0;
           while (file && i < m_numCount) {
               file >> m_numbers[i];
               if (file) ++i;
           }
           if (i != m_numCount) {
               delete[] m_numbers;
               setEmpty();
               return false;
           }
           return true;
       }
       return false;
   }

   void Numbers::setEmpty() { 
      m_numbers = nullptr;
      m_filename = nullptr;
      m_numCount = 0;
   }
   void Numbers::setFilename(const char* filename) { 
      delete[] m_filename;
      m_filename = new char[strlen(filename) + 1];
      strcpy(m_filename, filename);
   }
   void Numbers::sort() {
      int i, j;
      double temp;
      for (i = m_numCount - 1; i > 0; i--) {
         for (j = 0; j < i; j++) {
            if (m_numbers[j] > m_numbers[j + 1]) {
               temp = m_numbers[j];
               m_numbers[j] = m_numbers[j + 1];
               m_numbers[j + 1] = temp;
            }
         }
      }
   }

   void Numbers::save()
   {
       if (m_isOriginal == true && isEmpty() == false) {
           std::ofstream out(m_filename);
           for (int i = 0; i < m_numCount; i++) {
               out << m_numbers[i] << "\n";
           }
       }
   }

   int Numbers::numberCount() const
   {
       int count = 0;

       std::ifstream fin(m_filename);
       while (!fin.fail()) {
           if (fin.get() == '\n') {
               count++;
           }
       }
       
       return count;
   }

   

   double Numbers::average() const {
      double aver = 0.0;
      if (!isEmpty()) {
         for (int i = 0; i < m_numCount; i++)
            aver += m_numbers[i];
         aver = aver / m_numCount;
      }
      return aver;
   }
   double Numbers::min() const {
      double minVal = 0.0;
      if (!isEmpty()) {
         minVal = m_numbers[0];
         for (int i = 1; i < m_numCount; i++)
            if (minVal > m_numbers[i]) minVal = m_numbers[i];
      }
      return minVal;
   }
   double Numbers::max() const {
      double maxVal = 0.0;
      if (!isEmpty()) {
         maxVal = m_numbers[0];
         for (int i = 1; i < m_numCount; i++)
            if (maxVal < m_numbers[i]) maxVal = m_numbers[i];
      }
      return maxVal;
   }

   Numbers& Numbers::operator =(const Numbers& src) 
   {
       if (this != &src) {
           delete[] m_numbers;

           m_numCount = src.m_numCount;

           m_numbers = new double[m_numCount];
           for (int i = 0; i < m_numCount; i++) {
               m_numbers[i] = src.m_numbers[i];
           }

       }
       return *this;
   }

   Numbers& Numbers::operator +=(double n)
   {
       double* temp = new double[m_numCount + 1];
       int i;
       for (i = 0; i < m_numCount; i++) {
           temp[i] = m_numbers[i];
       }
       temp[i] = n;
       delete[] m_numbers;

       m_numCount++;
       m_numbers = temp;
       sort();
       return *this;
   }

   std::ostream& Numbers::display(std::ostream& os) const
   {
       if (!isEmpty()) {
           os.setf(ios::fixed);
           os.precision(2);
           os << "=========================" << endl;
           os << ((m_isOriginal) ? m_filename : "*** COPY ***") << endl;
           for (int i = 0; i < m_numCount; i++) {
               os << m_numbers[i];
               if (i != m_numCount - 1) os << ", ";
           }
           os << endl << "-------------------------" << endl;
           os << "Total of " << m_numCount << " number(s)" << endl
               << "Largest number:  " << max() << endl
               << "Smallest number: " << min() << endl
               << "Average:         " << average() << endl
               << "=========================";
       }
       else {
           os << "Empty list";
       }
       return os;
       
   }
   std::ostream& operator<<(std::ostream& os, const Numbers& N)
   {
       N.display(os);

       return os;
   }
   std::istream& operator>>(std::istream& is, Numbers& N)
   {
       double abc;
       is >> abc;
       if (!is.fail()) {
           N += abc;
       }
       return is;
   }
}
