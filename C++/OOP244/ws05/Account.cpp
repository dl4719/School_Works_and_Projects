#include <iostream>
#include "Account.h"

using namespace std;
namespace seneca {
   // New account
   Account::Account() {  
      m_number = 0;
      m_balance = 0.0;
   }
   Account::Account(int number, double balance ) {
      setEmpty();
      if (number >= 10000 && number <= 99999
         && balance > 0) {
         m_number = number;
         m_balance = balance;
      }
   }
   int Account::getAccNum() const
   {
       return m_number;
   }
   double Account::getAccBal() const
   {
       return m_balance;
   }
   Account::operator bool() const
   {
       if (m_number < 10000 || m_number > 100000 || m_balance < 0)
           return false;

       return true;
   }
   Account::operator int() const
   {
       return m_number;
   }
   Account::operator double() const
   {
       return m_balance;
   }
   bool Account::operator~() const
   {
       if (m_number == 0)
           return true;

       return false;
   }
   Account& Account::operator=(int accNum)
   {
       if (accNum < 10000 || accNum > 99999) {
           setEmpty(); // Set object(Account) to invalid state
       }
       else if (m_number == 0) {
           m_number = accNum;
       }

       return *this;
   }
   Account& Account::operator=(Account& acc)
   {
       if (m_number == 0 && acc.m_number != -1) {
           
           m_number = acc.m_number;
           m_balance = acc.m_balance;
           acc.m_number = 0;
           acc.m_balance = 0.0;
       }

       return *this;
   }
   Account& Account::operator += (double deposit)
   {
       if (m_number != 0 && deposit < 0) {
           // Do nothing
       }
       else {
           m_balance += deposit;
       }
       
       return *this;
   }
   Account& Account::operator-=(double deposit)
   {
       if ((m_number > 0 && deposit < 0) || m_balance < deposit) {
           // Do nothing
       }
       else {
           m_balance -= deposit;
       }

       return *this;
   }
   Account& Account::operator<<(Account& acc)
   {
       if (m_number != 0 && acc.m_number != 0 && m_number != acc.m_number) {
           m_balance += acc.m_balance;
           acc.m_balance = 0.0;
       }

       return *this;
   }
   Account& Account::operator>>(Account& acc)
   {
       if (m_number != 0 && acc.m_number != 0 && m_number != acc.m_number) {
           acc.m_balance += m_balance;
           m_balance = 0.0;
       }
       return *this;
   }
   double operator+(const Account& left, const Account& right)
   {
       double sum = 0.0;

       if (left.getAccNum() == -1 || right.getAccNum() == -1 )
           return 0.0;

       return sum = left.getAccBal() + right.getAccBal();
   }
   double& operator+=(double& left, const Account& right)
   {
       left += right.getAccBal();
       return left;
   }
   std::ostream& Account::display() const{
      if (*this) {  
         cout << " ";
         cout << m_number;
         cout << " | ";
         cout.width(12);
         cout.precision(2);
         cout.setf(ios::right);
         cout.setf(ios::fixed);
         cout << m_balance;
         cout.unsetf(ios::right);
         cout << " ";
      }
      else if(~*this) {
         cout << "  NEW  |         0.00 ";
      }
      else {
         cout << "  BAD  |    ACCOUNT   ";
      }
      return cout;
   }

 
}