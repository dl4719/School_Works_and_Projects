#ifndef SENECA_ORDERING_H
#define SENECA_ORDERING_H
#include "Food.h"
#include "Drink.h"
#include "Billable.h"
#include "constants.h"
#include <iostream>
using namespace std;
namespace seneca {
   class Ordering {
       size_t m_foodCounter{};
       size_t m_drinkCounter{};
       size_t m_billableCounter{};
       static size_t m_billSerialNum;

       Food* foodArray{};
       Drink* drinkArray{};

       Billable** billItems{};

      size_t countRecords(const char* file)const;

      void billTitlePrint(ostream& os) const;
      void printTotal(ostream& os, double total) const;
   public:
       Ordering() = delete;
       Ordering(Ordering& src) = delete;
       Ordering(const char* drinkFile, const char* foodFile);
       ~Ordering();

       operator bool() const;
       size_t noOfBillItems() const;
       bool hasUnsavedBill() const;
       void listFoods(ostream& os = std::cout) const;
       void ListDrinks(ostream& os = std::cout) const;
       void orderFood();
       void orderDrink();
       void printBill(ostream& os = std::cout) const;
       void resetBill();
   };
}
#endif // !SENECA_ORDERING_H


