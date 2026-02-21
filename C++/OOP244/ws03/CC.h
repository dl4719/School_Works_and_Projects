#ifndef SENECA_CC_H_
#define SENECA_CC_H_
#include <iostream>
namespace seneca {
   class CC {
	   char* cardholder;
	   short cardCVV, cardExpMonth, cardExpYear;
	   unsigned long long cardNum;

	   void display(const char* name, unsigned long long number, short expYear, short expMon, short cvv) const;
  
	   bool validate(const char* name,
		   unsigned long long cardNo,
		   short cvv,
		   short expMon,
		   short expYear)const;

	   void prnNumber(unsigned long long CCnum)const;

   public:

	   // Sets the object to a safe empty state by setting all the values to zero and the name pointer to nullptr.
	   void set();

	   // First, it will deallocate the cardholder's (using freeMem in cstr.h) name and then it will call the set() method to set the object to a safe empty state.
	   void cleanUp();

	   // Returns if the CC object is in a safe empty state or not; by returning true if the cardholder name pointer attribute of the object is nullptr, otherwise, it will return false.
	   bool isEmpty() const;

	   // First, it will cleanUp() the object to a safe empty state. Then if all the arguments are valid using validate(), it will dynamically keep a copy of the name in the name attribute (using alocpy function in cstr.h) and then sets the rest of the attributes to their corresponding values.
	   // If validation fails, nothing will be set.
	   void set(const char* cc_name, unsigned long long cc_no, short cvv, short expMon = 12, short expYear = 24);

	   // If the object isEmpty(), print "Invalid Credit Card Record" and go to newline;
	   // If it is not in a safe empty state, display the CC class using the private display method.
	   // This method does not modify the class. (it is constant)
	   void display() const;
   };

}
#endif // !SENECA_CC_H_


