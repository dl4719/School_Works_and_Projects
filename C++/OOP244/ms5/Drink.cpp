#include <iomanip>
#include <fstream>
#include "Drink.h"
#include "Utils.h"
#include "Menu.h"

using namespace std;
namespace seneca {
	ostream& Drink::print(ostream& ostr) const
	{
		char name[26]{};
		ut.strcpy(name, *this, 25);
		ostr << std::left << std::setw(28) << std::setfill('.') << name;

		switch (m_size) {
		case 'S':
			ostr << "SML..";
			break;
		case 'M':
			ostr << "MID..";
			break;
		case 'L':
			ostr << "LRG..";
			break;
		case 'X':
			ostr << "XLR..";
			break;
		default:
			ostr << ".....";
		}
		ostr << std::right << std::setw(7) << std::fixed << std::setfill(' ') << std::setprecision(2) << price();
		return ostr;
	}
	bool Drink::order()
	{
		Menu drinkMenu("Drink Size Selection", "Back", 3);
		drinkMenu << "Small" << "Medium" << "Larg" << "Extra Large";
		int selection = drinkMenu.select();

		switch (selection) {
		case 1:
			m_size = 'S';
			break;
		case 2:
			m_size = 'M';
			break;
		case 3:
			m_size = 'L';
			break;
		case 4:
			m_size = 'X';
			break;
		default:
			m_size = char(0);
		} 
		return ordered();
	}
	bool Drink::ordered() const
	{
		return static_cast<bool>(m_size);
	}
	ifstream& Drink::read(ifstream& file)
	{
		char buffer[99];
		double tempPrice;
		file.getline(buffer, 99, ',');
		file >> tempPrice;
		file.ignore(1000, '\n');
		if (file) {
			Billable::name(buffer);
			Billable::price(tempPrice);
			m_size = char(0);
		}
		return file;
	}
	double Drink::price() const
	{
		switch (m_size) {
		case 'S':
			return Billable::price() * 0.5;
		case 'M':
			return Billable::price() * 0.75;
		case 'X':
			return Billable::price() * 1.5;
		default:
			return Billable::price();
		}
	}
}