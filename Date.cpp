//Date.cpp
//BLARNEY
//Winter 2017

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;
#include "Date.h"
#include "POS.h"


namespace ict {

	Date::Date() {
		m_dateOnly = false;
		set();
		m_readErrorCode = 0;
	}

	Date::Date(int year, int mon, int day) {
		m_dateOnly = true;
		m_year = year;
		m_mon = mon;
		m_day = day;

		m_hour = 0;
		m_min = 0;

		m_readErrorCode = 0;
	}

	Date::Date(int year, int mon, int day, int hour, int min) {
		m_dateOnly = false;
		m_year = year;
		m_mon = mon;
		m_day = day;
		m_hour = hour;
		m_min = min;

		m_readErrorCode = 0;
	}


	//Setting the date to current date and time
	void Date::set() {
		time_t t = time(NULL);
		tm lt = *localtime(&t);
		m_day = lt.tm_mday;
		m_mon = lt.tm_mon + 1;
		m_year = lt.tm_year + 1900;
		if (dateOnly()) {
			m_hour = m_min = 0;
		}
		else {
			m_hour = lt.tm_hour;
			m_min = lt.tm_min;
		}
	}

	//returns unique date number, if one date value > another, the first date is later than the second
	int Date::value()const {
		return m_year * 535680 + m_mon * 44640 + m_day * 1440 + m_hour * 60 + m_min;
	}

	//
	int Date::mdays()const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
		mon--;
		return days[mon] + int((mon == 1)*((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
	}

	void Date::errCode(int errorCode) {
		m_readErrorCode = errorCode;
	}

	void Date::set(int year, int mon, int day, int hour, int min) {
		m_year = year;
		m_mon = mon;
		m_day = day;
		m_hour = hour;
		m_min = min;
		m_readErrorCode = 0;
	}

	int Date::errCode() const {
		return m_readErrorCode;
	}
	bool Date::bad() const {
		if (m_readErrorCode == 0) {
			return false;
		}
		else
			return true;
	}
	bool Date::dateOnly() const {
		return m_dateOnly;
	}
	void Date::dateOnly(bool value) {
		m_dateOnly = value;

		if (value) {
			m_hour = 0;
			m_min = 0;
		}
	}

	bool Date::operator==(const Date& D) const {
		if (this->value() == D.value()) {
			return true;
		}
		else { return false; }
	}

	bool Date::operator!=(const Date& D) const {
		if (this->value() != D.value()) {
			return true;
		}
		else { return false; }
	}

	bool Date::operator<(const Date& D) const {
		if (this->value() < D.value()) {
			return true;
		}
		else { return false; }
	}

	bool Date::operator>(const Date& D) const {
		if (this->value() > D.value()) {
			return true;
		}
		else { return false; }
	}

	bool Date::operator<=(const Date& D) const {
		if (this->value() <= D.value()) {
			return true;
		}
		else { return false; }
	}

	bool Date::operator>=(const Date& D) const {
		if (this->value() >= D.value()) {
			return true;
		}
		else { return false; }
	}

	std::istream& Date::read(std::istream& is = std::cin) {
		errCode(0);
		if (dateOnly() == true) {
			is >> m_year;
			if (is.fail()) { m_readErrorCode = 1; }
			is.get();

			is >> m_mon;
			if (is.fail()) { m_readErrorCode = 1;}
			is.get();

			is >> m_day;
			if (is.fail()) { m_readErrorCode = 1;}
		}

		else {
			is >> m_year;
			if (is.fail()) { m_readErrorCode = 1; }
			is.get();
			is >> m_mon;
			if (is.fail()) { m_readErrorCode = 1; }
			is.get();
			is >> m_day;
			if (is.fail()) { m_readErrorCode = 1; }
			is.get();
			is.get();
			is >> m_hour;
			if (is.fail()) { m_readErrorCode = 1; }
			is.get();
			is >> m_min;
			if (is.fail()) { m_readErrorCode = 1; }
		}


		if (m_readErrorCode != 1) {
			if ((m_year < MIN_YEAR) || (m_year > MAX_YEAR)) {
				m_readErrorCode = 2;
			}
			else if ((m_mon < 1) || (m_mon > 12)) {
				m_readErrorCode = 3;
			}
			else if ((m_day < 1) || (m_day > mdays())) {
				m_readErrorCode = 4;
			}
			else if ((m_hour < 0) || (m_hour > 23)) {
				m_readErrorCode = 5;
			}
			else if ((m_min < 0) || (m_min > 59)) {
				m_readErrorCode = 6;
			}
		}

		return is;
	}

	std::ostream& Date::write(std::ostream& ostr = std::cout) const {
		if (dateOnly()) {
			ostr << m_year << "/";
			if (m_mon < 10) { ostr << "0"; }
			ostr << m_mon << "/";
			if (m_day < 10) { ostr << "0"; }
			ostr << m_day;
		}
		else {
			ostr << m_year << "/";
			if (m_mon < 10) { ostr << "0"; }
			ostr << m_mon << "/";
			if (m_day < 10) { ostr << "0"; }
			ostr << m_day << ", ";
			if (m_hour < 10) { ostr << "0"; }
			ostr << m_hour << ":";
			if (m_min < 10) { ostr << "0"; }
			ostr << m_min;
		}

		return ostr;
	}

	std::istream& operator >> (std::istream& is, Date& D) {
		return D.read(is);
	}

	std::ostream& operator << (std::ostream& ost, const Date& D) {
		return D.write(ost);
	}
  

}
