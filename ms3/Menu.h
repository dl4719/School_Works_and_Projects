#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include <iostream>
#include "constants.h"
namespace seneca {
   class Menu;
   class MenuItem {
       char* content{};
       char* title{};
       char* entryPrompt{};
       char* exitOption{};
       size_t noOfIndents{};
       size_t indentSize{};
       int rows{-1};

       MenuItem(const char*, size_t, size_t, int);

       MenuItem(const MenuItem&) = delete;
       MenuItem& operator =(const MenuItem&) = delete;

       ~MenuItem();

       operator bool() const;

       std::ostream& display(std::ostream& os = std::cout) const;

       friend class Menu;

      
   };
   class Menu {
       size_t noOfIndentations{};
       size_t sizeOfIndentations{};
       size_t numOfMenuItems{};

       // MenuItem Attributes
       MenuItem title;
       MenuItem entryPrompt;
       MenuItem exitOption;

       MenuItem* m_items[MaximumNumberOfMenuItems]{};

   public:
       Menu(const Menu&) = delete;
       Menu& operator=(const Menu&) = delete;
       Menu(const char* title, const char* exitText = "Exit", size_t indentation = 0, size_t indentationSize = 3);
       Menu& operator<<(const char* menuItem);
       size_t select()const;
       virtual ~Menu();
   };
   size_t operator<<(std::ostream& ostr, const Menu& m);
}
#endif // !SENECA_MENU_H


