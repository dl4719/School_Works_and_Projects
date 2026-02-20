#ifndef SENECA_MENU_H
#define SENECA_MENU_H

#include <iostream>

namespace seneca {
   class MenuItem {
	   char* content{};
	   size_t noOfIndents{};
	   size_t indentSize{};
	   int rows{};
   
   public:
	   MenuItem(const char*, size_t, size_t, int);

	   MenuItem(const MenuItem&) = delete;
	   MenuItem& operator =(const MenuItem&) = delete;

	   ~MenuItem();

	   operator bool() const;

	   std::ostream& display(std::ostream& os = std::cout) const;
   };

}
#endif // !SENECA_MENU_H


