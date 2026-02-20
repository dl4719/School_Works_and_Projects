#ifndef SENECA_FOOD_H
#define SENECA_FOOD_H
#include "Billable.h"
#include "Menu.h"
namespace seneca {
   class Food : public Billable {
	   bool m_ordered{};
	   bool m_child{};
	   char* m_customize{};

   public:
	   Food();
	   Food(const Food& src);
	   ~Food();
	   Food& operator =(const Food& src);

	   ostream& print(ostream& ostr = cout)const;
	   bool order();
	   bool ordered()const;
	   ifstream& read(ifstream& file);

	   double price() const;
   };
}
#endif // !SENECA_FOOD_H


