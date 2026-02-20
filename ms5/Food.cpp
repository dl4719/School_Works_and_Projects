#include <iostream>
#include <fstream>
#include <iomanip>
#include "Food.h"
#include "Menu.h"
#include "Utils.h"
using namespace std;
namespace seneca {
	Food::Food()
	{
		m_customize = nullptr;
		m_ordered = false;
		m_child = false;
	}
	Food::Food(const Food& src) : Billable(src)
	{
		if (this != &src) {
			ut.alocpy(m_customize, src.m_customize);
			m_ordered = src.m_ordered;
			m_child = src.m_child;
		}
	}
	Food::~Food()
	{
		delete[] m_customize;
	}
	Food& Food::operator=(const Food& src)
	{
		if (this != &src) {
			Billable::operator=(src);
			ut.alocpy(m_customize, src.m_customize);
			m_ordered = src.m_ordered;
			m_child = src.m_child;
		}
		return *this;
	}
	ostream& Food::print(ostream& ostr) const
	{
		char name[26]{};
		ut.strcpy(name, *this, 25);
		ostr << std::left << std::setw(28) << std::setfill('.') << name;

		if (ordered() && m_child) {
			ostr << "Child";
		}
		else if (ordered()) {
			ostr << "Adult";
		}
		else {
			ostr << ".....";
		}

		ostr << std::right << std::setw(7) << std::fixed << std::setfill(' ') << std::setprecision(2) << price();

		if (m_customize && &ostr == &std::cout) {
			char limit[31];
			ut.strcpy(limit, m_customize, 30);
			ostr << " >> " << limit;
		}
		return ostr;
	}
	bool Food::order()
	{
		Menu foodMenu("Food Size Selection", "Back", 3);
		foodMenu << "Adult" << "Child";
		int selection = foodMenu.select();
		char* instructions{};

		switch (selection) {
		case 1:
			m_ordered = true;
			m_child = false;
			break;
		case 2:
			m_ordered = true;
			m_child = true;
			break;
		default:
			m_ordered = false;
			m_child = false;
			delete[] instructions;
			instructions = nullptr;
		}

		if (ordered()) {
			cout << "Special instructions\n> ";
			//cin.ignore(1000, '\n'); // clear buffer
			char buffer[100];
			cin.getline(buffer, 99);
			if (buffer[0] != '\0') {
				ut.alocpy(m_customize, buffer);
			}
			else {
				delete[] m_customize;
				m_customize = nullptr;
				//cin.ignore(1000, '\n'); // clear buffer
			}
			
			return true;
		}
		
		return false;
	}
	bool Food::ordered() const
	{
		return m_ordered;
	}
	ifstream& Food::read(ifstream& file)
	{
		char buffer[99];
		double tempPrice;
		file.getline(buffer, 99, ',');
		file >> tempPrice;
		file.ignore(1000, '\n');
		if (file) {
			Billable::name(buffer);
			Billable::price(tempPrice);
			m_ordered = false;
			m_child = false;
		}
		return file;
	}
	double Food::price() const
	{
		if (ordered() && (m_child)) {
			return Billable::price() * 0.5;
		}

		return Billable::price();
	}
}