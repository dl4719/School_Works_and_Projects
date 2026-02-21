#define _CRT_SECURE_NO_WARNINGS
#include "Drink.h"
#include "Food.h"
#include "Billable.h"
#include "Ordering.h"
#include "constants.h"
#include "Menu.h"
#include "Utils.h"
#include <cstdio>
#include <iomanip>
#include <fstream>
using namespace std;
namespace seneca {
    size_t Ordering::m_billSerialNum = 1;

   size_t Ordering::countRecords(const char* thefile) const 
   {
       char nextLine;
       size_t newLineCounter = 0;
       std::ifstream readFile(thefile);
       
       if (readFile.is_open()) {
           while (readFile.get(nextLine)) {
               if (nextLine == '\n') {
                   newLineCounter++;
               }
           }
       }
       readFile.close();
       return newLineCounter;
   }

   void Ordering::billTitlePrint(ostream& os) const
   {
       os << "Bill # " << std::setfill('0') << std::setw(3) << m_billSerialNum << " ";
       os << std::setfill('=') << std::setw(29) << "" << std::endl;
   }

   void Ordering::printTotal(ostream& os, double subTotal) const
   {
       double taxAmount = subTotal * Tax;
       double total = subTotal + taxAmount;

       os << std::setw(21) << " "
           << std::setw(10) << std::left << "Total:"
           << std::setw(9) << std::right << std::fixed << std::setprecision(2) << subTotal << std::endl;

       os << std::setw(21) << " "
           << std::setw(10) << std::left << "Tax:"
           << std::setw(9) << std::right << std::fixed << std::setprecision(2) << taxAmount << std::endl;

       os << std::setw(21) << " "
           << std::setw(10) << std::left << "Total+Tax:"
           << std::setw(9) << std::right << std::fixed << std::setprecision(2) << total << std::endl;

       os << std::setfill('=') << std::setw(40) << "" << std::endl;
   }

   Ordering::Ordering(const char* drinkFile, const char* foodFile)
   {
       m_billableCounter = 0;

       billItems = new Billable * [MaximumNumberOfMenuItems];

       m_drinkCounter = countRecords(drinkFile);
       m_foodCounter= countRecords(foodFile);

       std::ifstream drinkFileStream(drinkFile);
       std::ifstream foodFileStream(foodFile);

       if (drinkFileStream.is_open() && foodFileStream.is_open()) {
           drinkArray = new Drink[m_drinkCounter];
           foodArray = new Food[m_foodCounter];

           size_t drinksCounter = 0;
           for (size_t i = 0; i < m_drinkCounter; i++)
           {
               if (!drinkArray[i].read(drinkFileStream)) {
                   break;
               }
               drinksCounter++;
           }

           size_t foodsCounter = 0;
           for (size_t i = 0; i < m_foodCounter; i++)
           {
               if (!foodArray[i].read(foodFileStream)) {
                   break;
               }
               foodsCounter++;
           }

           if (drinksCounter != m_drinkCounter || foodsCounter != m_foodCounter) {
               delete[] drinkArray;
               delete[] foodArray;

               drinkArray = nullptr;
               foodArray = nullptr;

               m_drinkCounter = 0;
               m_foodCounter = 0;
           }
       }
       else {
           m_drinkCounter = 0;
           m_foodCounter = 0;
       }

       if (drinkFileStream.is_open()) drinkFileStream.close();
       if (foodFileStream.is_open()) foodFileStream.close();
       
   }

   Ordering::~Ordering()
   {
       delete[] drinkArray;
       delete[] foodArray;

       for (size_t i = 0; i < m_billableCounter; ++i) {
           delete billItems[i];
       }
       delete[] billItems;
   }

   Ordering::operator bool() const
   {
       return (foodArray != nullptr && drinkArray != nullptr);
   }

   size_t Ordering::noOfBillItems() const
   {
       return m_billableCounter;
   }

   bool Ordering::hasUnsavedBill() const
   {
       return m_billableCounter > 0;
   }

   void Ordering::listFoods(ostream& os) const
   {
       os << "List Of Avaiable Meals\n";
       os << std::setfill('=') << std::setw(40) << "" << std::endl;

       for (size_t i = 0; i < m_foodCounter; ++i) {
           foodArray[i].print(os);
           os << "\n";
       }

       os << std::setfill('=') << std::setw(40) << "" << std::endl;
   }

   void Ordering::listDrinks(ostream& os) const
   {
       os << "List Of Avaiable Drinks\n";
       os << std::setfill('=') << std::setw(40) << "" << std::endl;

       for (size_t i = 0; i < m_drinkCounter; ++i) {
           drinkArray[i].print(os);
           os << "\n";
       }

       os << std::setfill('=') << std::setw(40) << "" << std::endl;
   }

   void Ordering::orderFood()
   {
       Menu foodMenu("Food Menu", "Back to Order", 2);  

       for (size_t i = 0; i < m_foodCounter; i++) {
           foodMenu << foodArray[i];
       }

       size_t selection = foodMenu.select();
       if (selection) {

           size_t selectedIndex = selection - 1;

           Food* selectedFood = new Food(foodArray[selectedIndex]);

           if (selectedFood->order()) {
               billItems[m_billableCounter] = selectedFood;
               m_billableCounter++;
           }
           else {
               delete selectedFood;
           }
           
       }
   }

   void Ordering::orderDrink()
   {
       Menu drinkMenu("Drink Menu", "Back to Order", 2);
       for (size_t i = 0; i < m_drinkCounter; i++) {
           drinkMenu << drinkArray[i];
       }

       size_t selection = drinkMenu.select();
       if (selection) {
           size_t selectedIndex = selection - 1;
           Drink* selectedDrink = new Drink(drinkArray[selectedIndex]);

           if (selectedDrink->order()) {

               billItems[m_billableCounter] = selectedDrink;
               m_billableCounter++;
           }
           else {
               delete selectedDrink;
           }
       }
   }

   void Ordering::printBill(ostream& os) const
   {
       double totalPrice = 0;
       billTitlePrint(os);

       for (size_t i = 0; i < m_billableCounter; i++) {
            billItems[i]->print(os);
            os << '\n';

            totalPrice += billItems[i]->price();
       }

       printTotal(os, totalPrice);
   }

   void Ordering::resetBill()
   {
       char fileName[20];
       std::ofstream billFile(ut.makeBillFileName(fileName, m_billSerialNum));

       if (billFile.is_open()) {
           printBill(billFile);

           cout << "Saved bill number " << m_billSerialNum << "\n";
           cout << "Starting bill number " << ++m_billSerialNum << "\n";

           for (size_t i = 0; i < m_billableCounter; ++i) {
               delete billItems[i];
           }
           m_billableCounter = 0;
       }
       billFile.close();
   }
}