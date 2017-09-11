//Error.h
//BLARNEY
//Winter 2017

#define _CRT_SECURE_NO_WARNINGS 

#include "Error.h"
#include <cstring>

namespace ict{

	// constructors
	Error::Error() {
		m_message = nullptr;
	}
	Error::Error(const char* errorMessage) {
		m_message = nullptr;
		message(errorMessage);
	}

	// destructor
	Error::~Error() {
		delete m_message;
		m_message = nullptr;
	}

	// operator= for c-style strings
	void Error::operator=(const char* errorMessage) {
		clear();

		message(errorMessage);
	}

	// methods
	void Error::clear() {
		delete m_message;
		m_message = nullptr;
	}

	bool Error::isClear() const {
		if (m_message == nullptr) {
			return true;
		}
		else { return false; }
	}

	void Error::message(const char* value) {
		delete m_message;

		m_message = new char[strlen(value) + 1];
		strcpy(m_message, value);
	}

	//how do i get the message to the ostream overload without this?
	char* Error::getMessage() const {
		return m_message;
	}

	// cast overloads
	Error::operator const char*() const {
		return m_message;
	}

	Error::operator bool()const {
		if (m_message == nullptr) {
			return true;
		}
		else { return false; }
	}

	std::ostream& operator << (std::ostream& ost, const Error& E) {
		if (!E.isClear()) {
			ost << E.getMessage();
		}

		return ost;
	}
  
}