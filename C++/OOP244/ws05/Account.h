#ifndef SENECA_ACCOUNT_H_
#define SENECA_ACCOUNT_H_
#include <iostream>

namespace seneca {
    class Account {
      int m_number;
      double m_balance; 
      void setEmpty() {
          m_number = -1;
          m_balance = 0.0;
      }
   public:
      Account();
      Account(int number, double balance);

      // Helper functions
      int getAccNum() const;
      double getAccBal() const;

      // Type conversion operator(s)
      operator bool() const;
      operator int() const;
      operator double() const;

      // Unary operator(s)
      bool operator ~() const;

      // Binary operator(s)
      Account& operator =(int);
      Account& operator =(Account&);
      Account& operator +=(double);
      Account& operator -=(double);
      Account& operator <<(Account&);
      Account& operator >>(Account&);

      std::ostream& display()const;
  
   };

    // Stand-alone helper functions
    double operator +(const Account&, const Account&);
    double& operator +=(double&, const Account&);
}
#endif // SENECA_ACCOUNT_H_