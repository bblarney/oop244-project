#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include "NonPerishable.h"
#include <string>
#include <iomanip>

using namespace std;

namespace ict {

	bool NonPerishable::ok() const {
		if (m_err.isClear()) {
			return true;
		}
		else { return false; }
	}
	void NonPerishable::error(const char* message) {
		m_err = message;
	}
	char NonPerishable::signature() const {
		return 'N';
	}

	std::fstream& NonPerishable::save(std::fstream& file) const {
		file << signature() << "," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity();
		return file;
	}
	std::fstream& NonPerishable::load(std::fstream& file) {
		char s;
		string tempSku, tempName;
		double tempPrice;
		int tempTaxed, tempQuantity;

		getline(file, tempSku, ',');
		getline(file, tempName, ',');
		file >> tempPrice >> s >> tempTaxed >> s >> tempQuantity;

		sku(tempSku.c_str());
		name(tempName.c_str());
		price(tempPrice);
		quantity(tempQuantity);
		taxed(tempTaxed);

		return file;
	}

	ostream& NonPerishable::write(ostream& ostr, bool linear) const {
		if (!ok()) {
			ostr << m_err;
			return ostr;
		}
		else {
			if (linear) {
				ostr << setw(MAX_SKU_LEN) << left << sku() << "|" << setw(20) << name() << "|" << right << setw(7) << setprecision(2) << fixed << price() << "|" << " ";
				if (taxed()) {
					ostr << "T";
				}
				else { ostr << " "; }
				ostr << signature() << "|" << setw(4) << scientific << quantity() << "|" << fixed << setw(9);
				if (taxed()) {
					ostr << ((quantity()*price()) * (1 + TAX)) << "|";
				}
				else {
					ostr << ((quantity()*price())) << "|";
				}
			}
			else {
				ostr << left << /*setw(80) <<*/ "Name:" << endl << name() << endl;
				ostr << "Sku: " << sku() << endl;
				ostr << "Price: " << price() << endl;
				if (taxed()) {
					ostr << "Price after tax: " << (price() * (1 + TAX)) << endl;
					ostr << "Quantity: " << quantity() << endl;
					ostr << "Total Cost: " << ((quantity()*price()) * (1 + TAX)) << endl;
				}
				else {
					ostr << "Price after tax: N/A" << endl;
					ostr << "Quantity: " << quantity() << endl;
					ostr << "Total Cost: " << (quantity() * price()) << endl;
				}
			}
		}
		return ostr;
	}

	std::istream& NonPerishable::read(std::istream& is) {
		if (is.fail()) {
			return is;
		}
		m_err.clear();

		string tempSku, tempName;
		double tempPrice;
		char tempTaxed;
		int tempQuantity;
		cout << "Item Entry:" << endl;

		cout << "Sku: ";
		is >> tempSku;

		cout << "Name:" << endl;
		is >> tempName;
		
		cout << "Price: ";
		is >> tempPrice;
		if (is.fail()) { 
			m_err = "Invalid Price Entry"; 
			return is;
		}

		cout << "Taxed: ";
		is >> tempTaxed;
		if (tempTaxed != 'y' && tempTaxed != 'n') { 
			is.setstate(ios::failbit);
			m_err = "Invalid Taxed Entry, (y)es or (n)o"; 
			return is;
		}

		cout << "Quantity: ";
		is >> tempQuantity;
		if (is.fail()) {
			m_err = "Invalid Quantity Entry"; 
			return is;
		}

		sku(tempSku.c_str());
		name(tempName.c_str());
		price(tempPrice);
		quantity(tempQuantity);

		if (tempTaxed == 'y') {
			taxed(true);
		}
		else if (tempTaxed == 'n') {
			taxed(false);
		}

		return is;
	}
}