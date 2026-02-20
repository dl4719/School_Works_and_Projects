#include <iostream>
#include "dma.h"
using namespace std;
namespace seneca {

	void reverse() {

		int n; /// stores the number of double datatype numbers
		//double userIn = 0; /// stores the user input of double numbers

		cout << "Enter the number of double values:\n> ";
		cin >> n;

		double* arr = new double[n];


		for (int i = 0; i < n; i++) { /// for user input
			cout << i+1 << "> ";
			cin >> arr[i];
		}

		for (int j = n - 1; j >= 0; j--) {
			cout << arr[j] << endl;
		}

		delete [] arr;
		arr = nullptr;
	}

	Contact *getContact() {
		
		Contact* contactInfo = new Contact;

		cout << "Name: ";
		cin >> contactInfo->m_name;

		cout << "Last name: ";
		cin >> contactInfo->m_lastname;

		cout << "Phone number: ";
		cin >> contactInfo->m_phoneNumber;

		return contactInfo;
	}

	void display(const Contact c) {

		cout << c.m_name << " " << c.m_lastname << ", +" << c.m_phoneNumber << endl;
	}

	void deallocate(Contact *c) {

		delete c;

	}

	void setEmpty(Contact &c) {
		
		c.m_name[0] = '\0';
		c.m_lastname[0] = '\0';
		c.m_phoneNumber = 0;

	}

}
