#ifndef SENECA_NUMBERS_H_
#define SENECA_NUMBERS_H_
#include <iostream>
namespace seneca {
   class Numbers {
      double* m_numbers;
      char* m_filename;
      bool m_isOriginal;
      int m_numCount;
      bool isEmpty()const;
      bool load();
      void setEmpty();
      void setFilename(const char* filename);
      void sort();
      void save();
      int numberCount()const;
   public:
      Numbers();
      Numbers(const char* filename);
      Numbers(const Numbers&);
      ~Numbers();
      double average()const;
      double max()const;
      double min()const;
      Numbers& operator =(const Numbers&);
      Numbers& operator +=(double);
      std::ostream & display(std::ostream&) const;
   };

   std::ostream& operator<<(std::ostream& os, const Numbers& N);
   std::istream& operator>>(std::istream& istr, Numbers& N);
}
#endif // !SENECA_NUMBERS_H_

