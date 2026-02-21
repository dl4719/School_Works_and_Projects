#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H

#include <iostream>
#include <string>
namespace seneca
{
	class FoodOrder
	{
		double g_taxrate{};
		double g_dailydiscount{};

		char g_customerName[11]{};
		std::string g_foodDescription;

		double g_price{};
		bool g_isDailySpecial = false;
	
	public:
		FoodOrder() = default;
		~FoodOrder() = default;
		
		double getTaxRate() const;
		void setTaxRate(double tax);

		double getDailyDiscount() const;
		void setDailyDiscount(double discount);

		void read(std::istream& is);
		void display();
	};
}
#endif // !SENECA_FOODORDER_H