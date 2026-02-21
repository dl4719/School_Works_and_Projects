#define _CRT_SECURE_NO_WARNINGS
#include "FoodOrder.h"
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;
namespace seneca
{

    double FoodOrder::getTaxRate() const
    {
        return g_taxrate;
    }

    void FoodOrder::setTaxRate(double tax)
    {
        g_taxrate = tax;
    }

    double FoodOrder::getDailyDiscount() const
    {
        return g_dailydiscount;
    }

    void FoodOrder::setDailyDiscount(double discount)
    {
        g_dailydiscount = discount;
    }

    void FoodOrder::read(std::istream& is)
    {
        if (!is)
        {
            return;
        }

        std::string customerName, foodDescription;
        double price = 0.0;
        char dailySpecial = '\0';

        if (std::getline(is, customerName, ',') &&
            std::getline(is, foodDescription, ',') &&
            is >> price &&
            is.ignore() &&
            is.get(dailySpecial) &&
            is.ignore())
        {
            strncpy(g_customerName, customerName.c_str(), sizeof(g_customerName) - 1);
            g_customerName[10] = '\0';
            g_foodDescription = foodDescription;
            g_price = price;
            g_isDailySpecial = (dailySpecial == 'Y' || dailySpecial == 'y');
        }
        else
        {
            g_customerName[0] = '\0';
            g_foodDescription.clear();
            g_price = 0.0;
            g_isDailySpecial = false;

            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    }

    void FoodOrder::display()
    {
        static int counter = 1;

        cout << left << setw(2) << counter++ << ". ";

        if (g_customerName[0] == '\0')
        {
            cout << "No Order" << endl;
        }
        else
        {
            double priceWithTax = g_price * (1 + g_taxrate);

            cout << setw(10) << g_customerName << "|"
                << setw(25) << g_foodDescription << "|"
                << fixed << setprecision(2) << setw(12) << priceWithTax;

            if (g_isDailySpecial)
            {
                double dailySpecialPrice = priceWithTax + (priceWithTax * (1 - g_dailydiscount));
                cout << "|" << right << setw(13) << dailySpecialPrice;
            }
            else
            {
                cout << "|" << right << setw(13);
            }
            cout << endl;
        }
    }
		
}

