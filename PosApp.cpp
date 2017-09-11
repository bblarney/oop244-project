#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "PosApp.h"

using namespace std;

namespace ict {

	PosApp::PosApp(const char* filename, const char* billfname) {
		
		strcpy(m_filename, filename);
		strcpy(m_billfname, billfname);
	}



	int PosApp::menu() {
		cout << "The Sene-Store" << endl;
		cout << "1- List items" << endl;
		cout << "2- Add Perishable item" << endl;
		cout << "3- Add Non-Perishable item" << endl;
		cout << "4- Update item quantity" << endl;
		cout << "5- Show Item" << endl;
		cout << "6- POS" << endl;
		cout << "0- exit program" << endl;

		cout << "> ";
		int input;
		cin >> input;
		cin.clear();

		if (input > 6 || input < 0) {
			input = -1;
		}

		cout << endl;

		cin.ignore(2000, '\n');

		return input;
	}

	void PosApp::deallocateItems() {
		for (int i = 0; i < m_noOfItems; i++) {
			m_items[i] = nullptr;
			delete m_items[i];
		}
		m_noOfItems = 0;
	}

	void PosApp::loadRecs() {
		deallocateItems();

		fstream recFile;
		recFile.open(m_filename, ios::in);

		if (!recFile) {
			recFile.clear();
			recFile.close();
			recFile.open(m_filename, ios::out);
			recFile.close();
		}
		else {
			char c;

			while (!recFile.eof()) {
				recFile.get(c);
				if (c == 'P') {
					m_items[m_noOfItems] = new Perishable();

					recFile.get();
					m_items[m_noOfItems]->load(recFile);
					m_noOfItems++;
				}
				else if (c == 'N') {
					m_items[m_noOfItems] = new NonPerishable();

					recFile.get();
					m_items[m_noOfItems]->load(recFile);
					m_noOfItems++;
				}
			}

			recFile.close();
		}

	}

	void PosApp::saveRecs() {

		fstream recFile;
		recFile.open(m_filename, ios::out);

		for (int i = 0; i < m_noOfItems; i++) {
			if ((m_items[i]->quantity()) > 0) {
				m_items[i]->save(recFile);
			}
		}

		recFile.close();
		loadRecs();
	}

	int PosApp::searchItem(const char* sku) const {
		for (int i = 0; i < m_noOfItems; i++) {
			if (*m_items[i]==sku) {
				return i;
			}
		}
		return -1;
	}

	void PosApp::updateQty() {
		char sku[MAX_SKU_LEN];
		int purchased;
		cout << "Please enter the SKU: ";
		cin >> sku;

		int index = searchItem(sku);
		
		if (index == -1) {
			cout << "Not found!" << endl;
		}
		else {
			m_items[index]->write(cout, false);

			cout << endl;

			cout << "Please enter the number of purchased items: ";
			cin >> purchased;

			*m_items[index] += purchased;

			saveRecs();

			cout << "Updated!" << endl << endl;
		}
	}

	void PosApp::addItem(bool isPerishable) {

		Item* p;

		if (isPerishable) {
			p = new Perishable();
		}
		else {
			p = new NonPerishable();
		}

		p->read(cin);
		if (cin.fail()) {
			cin.clear();
			//clear input buffer
			cin.ignore(2000, '\n');

			p->write(cout, false);
			cout << endl;
		}
		else {
			m_items[m_noOfItems] = p;

			m_noOfItems++;
			saveRecs();
			cout << "Item added." << endl << endl;
		}	
	}

	void PosApp::listItems() {

		double total = 0;

		cout << " Row " << "|" << setw(MAX_SKU_LEN+1) << left << " SKU " << "|" << setw(20) << " Item Name" << "|" << setw(7) << " Price" << "|TX |" << setw(4) << "Qty" << "|" << setw(9) << right << "Total " << "|" << endl;
		cout << "-----|--------|--------------------|-------|---|----|---------|" << endl;

		for (int i = 0; i < m_noOfItems; i++) {
			cout << right << setw(4) << i + 1 << " | ";
			m_items[i]->write(cout, true);
			total += (m_items[i]->cost()*m_items[i]->quantity());
			cout << endl;
		}
			
		cout << "-----^--------^--------------------^-------^---^----^---------^" << endl;
		cout << "                               Total Asset: $  |" << setw(14) << right << total << "|" << endl;
		cout << "-----------------------------------------------^--------------^";

		cout << endl << endl;
		
	}

	void PosApp::truncateBillFile() {
		fstream billFile;
		billFile.open(m_billfname, ios::out | ios::trunc);
		billFile.close();

	}

	void PosApp::showBill() {

		fstream billFile;
		billFile.open(m_billfname,ios::in);
		double total = 0;

		//cout.left;
		cout << "v--------------------------------------------------------v" << endl;

		cout  << "|" << Date() << setw(40) << "|" << endl;

		cout << "|" << setw(MAX_SKU_LEN+1) << left << " SKU" << "|" << setw(20) << " Item Name" << "|" << setw(7) << " Price" << "|TX |" << setw(4) << "Qty" << "|" << setw(9) << right << "Total " << "|" << endl;

		cout << "|--------|--------------------|-------|---|----|---------|" << endl;

		if (!billFile) {
			billFile.clear();
			billFile.close();
			billFile.open(m_billfname, ios::out);
			billFile.close();
		}		

		else {
			char c;
			while (!billFile.eof()) {
				billFile.get(c);
				if (c == 'P') {
					m_items[m_noOfItems] = new Perishable();

					billFile.get();
					m_items[m_noOfItems]->load(billFile);
					cout << "| ";
					m_items[m_noOfItems]->write(cout, true);
					total += m_items[m_noOfItems]->cost();
					cout << endl;
				}
				else if (c == 'N') {
					m_items[m_noOfItems] = new NonPerishable();

					billFile.get();
					m_items[m_noOfItems]->load(billFile);
					cout << "| ";
					m_items[m_noOfItems]->write(cout, true);
					total += m_items[m_noOfItems]->cost();
					cout << endl;
				}
			}
		}

		cout << "^--------^--------------------^-------^---^----^---------^" << endl;

		cout << "|                               Total: $  |" << setw(14) << right << total << "|" << endl;

		cout << "^-----------------------------------------^--------------^" << endl << endl;

		billFile.close();
		truncateBillFile();

	}

	void PosApp::addToBill(Item& I) {

		fstream billFile;
		billFile.open(m_billfname, ios::out|ios::app);
		int quant = I.quantity();

		I.quantity(1);

		I.save(billFile);

		I.quantity(quant - 1);

		billFile.close();

		saveRecs();

	}

	void PosApp::POS() {

		std::string sku_string;
		char sku[MAX_SKU_LEN];

		bool done = false;

		while (!done) {

			cout << "Sku: ";
			getline(cin, sku_string);
			if (sku_string == "") {
				showBill();
				done = true;
			}

			else
			{
				strcpy(sku, sku_string.c_str());
				if (searchItem(sku) != -1) {
					cout << "v------------------->" << endl;
					cout << "| " << m_items[searchItem(sku)]->name() << endl;
					cout << "^------------------->" << endl;
					addToBill(*m_items[searchItem(sku)]);
				}
					else {
					cout << "Not found!" << endl;
				}
			}

		}

	}

	void PosApp::run() {

		m_noOfItems = 0;

		loadRecs();

		bool exit = false;

		while (!exit) {

			int choice = menu();

			if (choice == 1) {
				listItems();
			}
			else if (choice == 2) {
				addItem(true);
			}
			else if (choice == 3) {
				addItem(false);
			}
			else if (choice == 4) {
				updateQty();
			}
			else if (choice == 5) {

				char sku[MAX_SKU_LEN];
				cout << "Please enter the SKU: ";
				cin >> sku;

				if (searchItem(sku) != -1) {
					cout << "v-----------------------------------v" << endl;
					m_items[searchItem(sku)]->write(cout, false);
					cout << "^-----------------------------------^" << endl << endl;
				}
				else {
					cout << "Not found!" << endl << endl;
				}
			}

			else if (choice == 6) {
				POS();
			}
			else if (choice == 0) {
				cout << "Goodbye!" << endl << endl;
				exit = true;
			}
			else {
				cout << "===Invalid Selection, try again===" << endl;
			}
		}

	}

}


































/*
ouputs:
-------------------------------------
update:
Please enter the SKU: 1313
Name:
Paper Tissue
Sku: 1313
Price: 1.22
Price after tax: 1.38
Quantity: 194
Total Cost: 267.45

Please enter the number of purchased items: 12
Updated!

------------------------------
Please enter the SKU: 3434
Not found!

-------------------------------------
add item:
Perishable Item Entry:
Sku: 5656
Name:
Honey
Price: 12.99
Taxed: y
Quantity: 12
Expiry date (YYYY/MM/DD): 1200/10/12
Invalid Year in Date Entry

Perishable Item Entry:
Sku: 5656
Name:
Honey
Price: 12.99
Taxed: y
Quantity: 12
Expiry date (YYYY/MM/DD): 2017/5/15
Item added.

--------------------------------------------
list item:
 Row | SKU    | Item Name          | Price |TX |Qty |   Total |
-----|--------|--------------------|-------|---|----|---------|
   1 | 1234   |Milk                |   3.99|  P|   2|     7.98|
   2 | 3456   |Paper Cups          |   5.99| TN|  38|   257.21|
   3 | 4567   |Butter              |   4.56| TP|   9|    46.38|
   4 | 1212   |Salted Butter       |   5.99|  P| 111|   664.89|
   5 | 1313   |Paper Tissue        |   1.22| TN| 206|   283.99|
   6 | 5656   |Honey               |  12.99| TP|  12|   176.14|
-----^--------^--------------------^-------^---^----^---------^
                               Total Asset: $  |       1436.59|
-----------------------------------------------^--------------^


--------------------------------------
printbill:
v--------------------------------------------------------v
| 2017/04/02, 12:42                                      |
| SKU    | Item Name          | Price |TX |Qty |   Total |
|--------|--------------------|-------|---|----|---------|
| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
| 1313   |Paper Tissue        |   1.22| TN|   1|     1.38|
| 5656   |Honey               |  12.99| TP|   1|    14.68|
^--------^--------------------^-------^---^----^---------^
|                               Total: $  |         22.05|
^-----------------------------------------^--------------^

-------------------------------------------------------
POS:
Sku: 1212
v------------------->
| Salted Butter
^------------------->
Sku: 1212
v------------------->
| Salted Butter
^------------------->
Sku: 1313
v------------------->
| Paper Tissue
^------------------->
Sku: 1234
v------------------->
| Milk
^------------------->
Sku: 7654
Not found!
Sku: 5656
v------------------->
| Honey
^------------------->
Sku:
v--------------------------------------------------------v
| 2017/04/02, 12:58                                      |
| SKU    | Item Name          | Price |TX |Qty |   Total |
|--------|--------------------|-------|---|----|---------|
| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
| 1313   |Paper Tissue        |   1.22| TN|   1|     1.38|
| 1234   |Milk                |   3.99|  P|   1|     3.99|
| 5656   |Honey               |  12.99| TP|   1|    14.68|
^--------^--------------------^-------^---^----^---------^
|                               Total: $  |         32.03|
^-----------------------------------------^--------------^

------------------------------------------------------
run:
The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> 5

Please enter the SKU: 5656
v-----------------------------------v
Name:
Honey
Sku: 5656
Price: 12.99
Price after tax: 14.68
Quantity: 10
Total Cost: 146.79
Expiry date: 2017/05/15
^-----------------------------------^

The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> 5

Please enter the SKU: 12345
Not found!

The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> five

===Invalid Selection, try again===

The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> 0

Goodbye!

*/