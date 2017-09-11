#ifndef ICT_ITEM_H__
#define ICT_ITEM_H__
// inlcude PosIO and POS header files
#include "PosIO.h"
#include "POS.h"
#include <iostream>
#include <cstring>

using namespace std;

namespace ict {
	// class Item
	class Item : public PosIO {

	private:
		char m_sku[MAX_SKU_LEN + 1];
		char *m_name;
		double m_price;
		bool m_taxed;
		int m_quantity;

	public:
		Item();
		Item(const char sku[], const char name[], double price, bool taxed = true);
		Item(const Item &obj);
		~Item();

		//Item& operator=(const Item& I);

		void sku(const char sku[]);
		void price(double price);
		void name(const char name[]);
		void taxed(bool taxed);
		void quantity(int quantity);

		const char* sku() const;
		double price() const;
		const char* name() const;
		bool taxed() const;
		int quantity() const;
		double cost() const;
		bool isEmpty() const;

		Item& operator=(const Item& obj);
		bool operator==(const char sku[]);
		int operator+=(int rhs);
		int operator-=(int rhs);

	};

	// end class Item
	// operator += 
	double operator+=(double& d, const Item& I);
	// operator << and operator >>
	std::istream& operator>>(std::istream& is, Item& I);

	std::ostream& operator<<(std::ostream& ost, const Item& I);


}
#endif