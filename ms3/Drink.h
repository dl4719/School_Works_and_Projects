#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H

#include "Billable.h"
using namespace std;
namespace seneca {
   class Drink : public Billable{
	   char m_size{};
   public:
	   ostream& print(ostream& ostr = cout)const;
	   bool order();
	   bool ordered()const;
	   ifstream& read(ifstream& file);
	   double price() const;

   };

}
#endif // !SENECA_DRINK_H


