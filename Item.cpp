#define _CRT_SECURE_NO_WARNINGS  
// Lib includes
#include <iostream>
#include <cstring>

// inlcude Item and POS header files
#include "Item.h"
#include "POS.h"
#include "PosIO.h"

using namespace std;

namespace ict{
  // class Item implementaion
	//constructors
	Item::Item() {
		m_sku[0] = '\0';
		m_name = nullptr;
		m_price = 0;
		m_taxed = false;
		m_quantity = 0;
	}
	Item::Item(const char sku[], const char name[], double price, bool taxed) {
		strcpy(m_sku, sku);

		m_name = new char[sizeof(name)];
		strcpy(m_name, name);

		m_quantity = 0;
		m_price = price;
		m_taxed = taxed;
	}
	Item::Item(const Item &obj) {
		*this = obj;
	}
	Item::~Item() {
		m_name = nullptr;
		delete m_name;
	}

	//setters
	void Item::sku(const char sku[]) {
		strcpy(m_sku, sku);
	}
	void Item::price(double price) {
		m_price = price;
	}
	void Item::name(const char name[]) {
		m_name = new char[100];//[sizeof(name)];
		strcpy(m_name, name);
	}
	void Item::taxed(bool taxed) {
		m_taxed = taxed;
	}
	void Item::quantity(int quantity) {
		m_quantity = quantity;
	}

	//getters
	const char* Item::sku() const {
		return m_sku;
	}
	double Item::price() const {
		return m_price;
	}
	const char* Item::name() const {
		return m_name;
	}
	bool Item::taxed() const {
		return m_taxed;
	}
	int Item::quantity() const {
		return m_quantity;
	}

	double Item::cost() const {
		if (m_taxed) {
			return (m_price + (m_price * TAX));
		}
		else { return m_price; }
	}
	bool Item::isEmpty() const {
		if ((m_sku[0] == '\0') && (m_name == nullptr) && (m_price == 0) && (m_taxed == false) && (m_quantity == 0)) {
			return true;
		}
		else return false;
	}

	//operators
	Item& Item::operator=(const Item& obj) {
		if (obj.isEmpty()) {
			return *this;
		}
		else{
			strcpy(m_sku, obj.m_sku);
			m_name = obj.m_name;
			m_price = obj.m_price;
			m_taxed = obj.m_taxed;
			m_quantity = obj.m_quantity;

			return *this;
		}
	}

	bool Item::operator==(const char sku[]) {
		for (unsigned int i = 0; i < sizeof(sku); i++) {
			if (sku[i] != m_sku[i]) {
				return false;
			}
		}
		return true;
	}

	int Item::operator+=(int rhs) {
		m_quantity = m_quantity + rhs;
		return m_quantity;
	}

	int Item::operator-=(int rhs) {
		m_quantity = m_quantity - rhs;
		return m_quantity;
	}

	//non-member operators
	double operator+=(double& d, const Item& I) {
		return (d + (I.quantity()*I.cost()));
	}


	std::istream& operator>>(std::istream& is, Item& I) {
		return I.read(is);
	}

	std::ostream& operator<<(std::ostream& ost, const Item& I) {
		return I.write(ost, true);
	}

}