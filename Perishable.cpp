#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include <iostream>
#include <string>

#include "Perishable.h"

using namespace std;

namespace ict {

	Perishable::Perishable() {
		m_expiry.dateOnly(true);
	}

	char Perishable::signature() const {
		return 'P';
	}

	std::fstream& Perishable::save(std::fstream& file) const {
		NonPerishable::save(file);
		file << "," << m_expiry;

		return file;
	}

	std::fstream& Perishable::load(std::fstream& file) {
		NonPerishable::load(file);
		file.ignore(1);
		file >> m_expiry;
		return file;
	}

	ostream& Perishable::write(ostream& ostr, bool linear) const {
		NonPerishable::write(ostr, linear);

		if (ok() && linear == false) {
			ostr << "Expiry date: " << m_expiry << endl;
		}

		return ostr;
	}

	std::istream& Perishable::read(std::istream& istr) {
		cout << "Perishable ";
		NonPerishable::read(istr);

		if (ok()) {
			cout << "Expiry date (YYYY/MM/DD): ";

			istr >> m_expiry;

			if (m_expiry.errCode() == CIN_FAILED) {
				error("Invalid Date Entry");
				istr.setstate(ios::failbit);
			}
			else if (m_expiry.errCode() == YEAR_ERROR) {
				error("Invalid Year in Date Entry");
				istr.setstate(ios::failbit);
			}
			else if (m_expiry.errCode() == MON_ERROR) {
				error("Invalid Month in Date Entry");
				istr.setstate(ios::failbit);
			}
			else if (m_expiry.errCode() == DAY_ERROR) {
				error("Invalid Day in Date Entry");
				istr.setstate(ios::failbit);
			}
		}
		return istr;
	}
}
