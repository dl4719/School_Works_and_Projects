#include <iostream>
#include "Menu.h"
#include "Utils.h"
#include "constants.h"

using namespace std;
namespace seneca {
	MenuItem::MenuItem(const char* contentName, size_t numOfIndents, size_t sizeOfIndents, int numOfRows):
		content{ ut.alocpy(contentName) }, noOfIndents{ numOfIndents }, indentSize{ sizeOfIndents }, rows{numOfRows}
	{
		if (numOfRows > static_cast<int>(MaximumNumberOfMenuItems) || numOfIndents > 4 || sizeOfIndents > 4 || ut.isspace(content)) {
			delete[] content;
			content = nullptr;
		}
	}

	MenuItem::~MenuItem()
	{
		delete[] content;
	}

	MenuItem::operator bool() const
	{
		return content != nullptr;
	}

	std::ostream& MenuItem::display(std::ostream& os) const
	{
		if (content) {
			os.fill(' ');
			os.width(noOfIndents * indentSize);
			os << "";
			if (rows >= 0) {
				os.width(2);
				os.setf(ios::right);
				os << rows << "- ";
				os.unsetf(ios::right);
			}
			char* c = content;
			while (ut.isspace(*c)) {
				c++;
			}
			os << c;
		}
		else {
			os << "??????????";
		}
		return os;
	}

}