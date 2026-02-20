#include "Billable.h"
#include "Utils.h"

namespace seneca {
	void Billable::price(double value)
	{
		m_price = value;
	}
	void Billable::name(const char* name)
	{
		ut.alocpy(m_name, name);
	}
	Billable::Billable(const Billable& src)
	{
		*this = src;
	}
	Billable& Billable::operator=(const Billable& src)
	{
		if (this != &src) {
			//ut.alocpy(m_name, src.m_name);
			name(src.m_name);
			m_price = src.m_price;
		}
		return *this;
	}
	Billable::~Billable()
	{
		delete[] m_name;
	}
	double Billable::price() const
	{
		return m_price;
	}
	Billable::operator const char* () const
	{
		return m_name;
	}
	double operator+(double money, const Billable& B)
	{
		return money + B.price();
	}
	double& operator+=(double& money, const Billable& B)
	{
		return money += B.price();
	}
}
