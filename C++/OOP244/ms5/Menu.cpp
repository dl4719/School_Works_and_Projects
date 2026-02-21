#include <iostream>
#include "Menu.h"
#include "Utils.h"
#include "constants.h"
using namespace std;
namespace seneca {
	MenuItem::MenuItem(const char* contentName, size_t numOfIndents, size_t sizeOfIndents, int numOfRows = -1) :
		content{ ut.alocpy(contentName) }, noOfIndents{ numOfIndents }, indentSize{ sizeOfIndents }, rows{ numOfRows }
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

	Menu::Menu(const char* title, const char* exitText, size_t indentation, size_t indentationSize) :
		noOfIndentations{ indentation }, 
		sizeOfIndentations{ indentationSize }, 
		title{ title, noOfIndentations, sizeOfIndentations}, 
		entryPrompt{ "> ", noOfIndentations, sizeOfIndentations }, 
		exitOption{ exitText, noOfIndentations, sizeOfIndentations, 0 }
	{
	}

	Menu& Menu::operator<<(const char* menuItem)
	{
		if (numOfMenuItems < MaximumNumberOfMenuItems) {
			m_items[numOfMenuItems] = new MenuItem(menuItem, noOfIndentations, sizeOfIndentations, numOfMenuItems + 1);
			
			numOfMenuItems++;
		}

		return *this;
	}

	size_t Menu::select() const
	{
		if (title) {
			title.display();
			cout << '\n';
		}

		for (size_t i = 0; i < numOfMenuItems; i++) {
			m_items[i]->display() << '\n';
		}
		exitOption.display();
		cout << '\n';
		entryPrompt.display();

		return ut.getInt(0, static_cast<int>(numOfMenuItems));
	}

	Menu::~Menu()
	{
		for (size_t i = 0; i < numOfMenuItems; i++) {
			if (m_items[i] != nullptr) {
				delete m_items[i];
				m_items[i] = nullptr;
			}
		}
	}

	size_t operator<<(std::ostream& ostr, const Menu& m)
	{
		if (&ostr == &std::cout) {
			return m.select();
		}
		return 0;
	}

}