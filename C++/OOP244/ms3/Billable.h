#ifndef SENECA_BILLABLE_H
#define SENECA_BILLABLE_H
#include <iostream>
using namespace std;
namespace seneca {
   class Billable {
	   char* m_name{}; // name or description
	   double m_price{}; // base price

   protected:
	   void price(double value); // Sets the item’s price.
	   void name(const char* name); // Sets the item’s name, handling dynamic allocation.

   public:
	   Billable() = default; // default constructor
	   Billable(const Billable& src); // copy constructor
	   Billable& operator =(const Billable& src); // copy assignment operator
	   virtual ~Billable();

	   virtual double price() const; // Returns the item’s price, allowing derived classes to override if needed.
	   operator const char* ()const;

	   virtual ostream& print(ostream& ostr = cout)const = 0; // Displays item information in a formatted way.
	   virtual bool order() = 0; // Takes customer order for details of the item(e.g., size, customizations).
	   virtual bool ordered()const = 0; // Returns true if details have been set, indicating the item is ordered.
	   virtual ifstream& read(ifstream& file) = 0; //Reads item details from an input file.

	   
   };
   double operator+(double money, const Billable& B);
   double& operator+=(double& money, const Billable& B);  
}
#endif // !SENECA_BILLABLE_H
