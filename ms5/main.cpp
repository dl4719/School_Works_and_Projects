#include <iostream>
#include "Menu.h"
#include "Ordering.h"

using namespace std;
using namespace seneca;

int main()
{
	Ordering ord("drinks.csv", "foods.csv");

	// ord will point to nullptr if the data files are not opened or corrupted
	if (ord) // ord != nullptr
	{
		size_t appSel{}, ordSel{};

		// Create a main menu
		//Seneca Restaurant, with one extra space at the end
		Menu appMenu("Seneca Restaurant ", "End Program");
		appMenu << "Order" << "Print Bill" << "Start a New Bill" << "List Foods" << "List Drinks";

		Menu orderMenu("Order Menu", "Back to main menu", 1);

		orderMenu << "Food" << "Drink";
		
		do 
		{
			switch (appSel = appMenu.select()) {
			case 1:
				do {
					switch (ordSel = orderMenu.select()) {
					case 1:
						ord.orderFood();
						break;
					case 2:
						ord.orderDrink();
						break;
					}
				} while (ordSel);
				break;
			case 2:
				ord.printBill(cout);
				break;
			case 3:
				ord.resetBill();
				break;
			case 4:
				ord.listFoods();
				break;
			case 5:
				ord.listDrinks();
				break;
			}
			if (appSel == 0 && ord.hasUnsavedBill()) {
				Menu areYouSure("You have bills that are not saved, are you sue you want to exit?", "No");
				areYouSure << "Yes";
				//if the user selects yes, the program will exit
				if (areYouSure.select() == 0) {
					appSel = 1; //to exit the program
				}
			}
		} while (appSel);
	}
	else {
		// if the data files are not opened or corrupted
		cout << "Failed to open data files or the data files are corrupted!" << endl;
	}
}