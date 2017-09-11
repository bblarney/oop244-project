#ifndef ICT_PosApp_H__
#define ICT_PosApp_H__

#include "POS.h"
#include "PosIO.h"
#include "Item.h"
#include "Perishable.h"
#include "NonPerishable.h"


using namespace std;

namespace ict {

	class PosApp {

	private: 
		//prevent copy
		//PosApp(const PosApp&);
		//PosApp& operator=(const PosApp&);

		char m_filename[128];
		char m_billfname[128];
		Item* m_items[MAX_NO_ITEMS];
		int m_noOfItems;

		int menu();
		void deallocateItems();
		void loadRecs();
		void saveRecs();
		int searchItem(const char* sku) const;
		void updateQty();
		void addItem(bool isPerishable);
		void listItems();

		void truncateBillFile();
		void showBill();
		void addToBill(Item& I);
		void POS();

	public:
		PosApp(const char* filename, const char* billfname);

		void run();

	};
}
#endif