#include <iostream>
#include "cstr.h"
#include "CC.h"
using namespace std;
namespace seneca {

   void CC::display(const char* name, unsigned long long number, short expYear, short expMon, short cvv) const{
      char lname[31]{};
      strcpy(lname, name, 30);
      cout << "| ";
      cout.width(30);
      cout.fill(' ');
      cout.setf(ios::left);
      cout << lname << " | ";
      prnNumber(number);
      cout << " | " << cvv << " | ";
      cout.unsetf(ios::left);
      cout.setf(ios::right);
      cout.width(2);
      cout << expMon << "/" << expYear << " |" << endl;
      cout.unsetf(ios::right);
   }

   bool CC::validate(const char* name, unsigned long long cardNo, short cvv, short expMon, short expYear) const
   {
       if (name == nullptr || strlen(name) <= 2) { //cardholder name is a nullptr or less than two characters
           return false;

       }

       if (cardNo < 4000000000000000ull || cardNo > 4099999999999999ull) { //cardNo is out of range
           return false;

       }

       if (cvv < 100 || cvv > 999) { //cvv is out of range
           return false;

       }

       if (expMon < 1 || expMon > 12) { //expMon is out of range
           return false;

       }

       if (expYear < 24 || expYear > 32) { //expYear is out of range
           return false;

       }

       return true; //if all conditions are true
   }

   void CC::prnNumber(unsigned long long CCnum) const
   {
       int temp;
       
       unsigned long long remainder;

       remainder = CCnum;
       // cout << remainder << "||| ";
       
       temp = remainder / 1000000000000ull;
       
       if (temp < 1000 && temp > 99) {
           cout << "0" << temp << " ";
       }
       else if (temp < 100 && temp > 9) {
           cout << "00" << temp << " ";
       }
       else if (temp < 10 && temp > 1) {
           cout << "000" << temp << " ";
       }
       else if (temp < 1) {
           cout << "0000" << temp << " ";
       }
       else {
           cout << temp << " ";
       }

       remainder = remainder % 1000000000000ull;
/////////////////////////////////////////////////////////////////////// first group


       // cout << remainder << "||| ";

       temp = remainder / 100000000ull;

       if (temp < 1000 && temp > 99) {
           cout << "0" << temp << " ";
       }
       else if (temp < 100 && temp > 9) {
           cout << "00" << temp << " ";
       }
       else if (temp < 10 && temp > 1) {
           cout << "000" << temp << " ";
       }
       else if (temp < 1) {
           cout << "0000" << temp << " ";
       }
       else {
           cout << temp << " ";
       }

       remainder = remainder % 100000000ull;
/////////////////////////////////////////////////////////////////////// Second group

       temp = remainder / 10000ull;

       if (temp < 1000 && temp > 99) {
           cout << "0" << temp << " ";
       }
       else if (temp < 100 && temp > 9) {
           cout << "00" << temp << " ";
       }
       else if (temp < 10 && temp > 1) {
           cout << "000" << temp << " ";
       }
       else if (temp < 1) {
           cout << "0000" << temp << " ";
       }
       else {
           cout << temp << " ";
       }

       remainder = remainder % 10000ull;
/////////////////////////////////////////////////////////////////////// Third group

       temp = remainder / 1ull;

       if (temp < 1000 && temp > 99) {
           cout << "0" << temp;
       }
       else if (temp < 100 && temp > 9) {
           cout << "00" << temp;
       }
       else if (temp < 10 && temp > 1) {
           cout << "000" << temp;
       }
       else if (temp < 1) {
           cout << "0000" << temp;
       }
       else {
           cout << temp;
       }
/////////////////////////////////////////////////////////////////////// Last group
   }

   void CC::set()
   {
       cardholder = nullptr;
       cardCVV = 0;
       cardExpMonth = 0;
       cardExpYear = 0;
       cardNum = 0;

   }

   void CC::cleanUp()
   {
       freeMem(*&cardholder);
       set();

   }

   bool CC::isEmpty() const
   {
       if (cardholder == nullptr) {
           return true;

       }
       else {
           return false;
       }
   }

   void CC::set(const char* cc_name, unsigned long long cc_no, short cvv, short expMon, short expYear)
   {
       cleanUp();

       if (validate(cc_name, cc_no, cvv, expMon, expYear)) {
           alocpy(cardholder, cc_name);

           cardNum = cc_no;

           cardCVV = cvv;

           cardExpMonth = expMon;

           cardExpYear = expYear;

       }
   }

   void CC::display() const
   {
       if (isEmpty()) {
           cout << "Invalid Credit Card Record\n";

       }
       else {
           display(cardholder, cardNum, cardExpYear, cardExpMonth, cardCVV);

       }

   }



}