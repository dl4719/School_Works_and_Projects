#include "Employee.h"

namespace seneca {
	class Professor :public Employee {
		char* subjectName{}; // {} sets variable to default value, nullptr
		size_t m_noSections{}; // {} sets variable to defauly value, 0

		double devPay() const;
	
	public:
		Professor() = default;
		Professor(const char* name, const char* subject, size_t noSections, size_t employeeNo, double salary);
		~Professor();
		std::istream& read(std::istream& istr = std::cin);
		std::ostream& write(std::ostream& ostr = std::cout)const;
		std::ostream& title(std::ostream& ostr = std::cout)const;
	};
	std::ostream& operator<<(std::ostream& ostr, const Professor& P);
	std::istream& operator>>(std::istream& istr, Professor& P);

}