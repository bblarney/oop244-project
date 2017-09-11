//Error.h
//BLARNEY
//Winter 2017

// compilation safegaurds
#ifndef ICT_Error_H_
#define ICT_Error_H

#include <iostream>
namespace ict {
   class Error {
      char* m_message;
   public:
   // constructors
	   Error();
	  Error(const char* errorMessage);

   // destructor
	  virtual ~Error();

   // deleted constructor and operator=
	  Error& operator=(const Error& em) = delete;

	  Error(const Error& em) = delete;

   // operator= for c-style strings
	  void operator=(const char* errorMessage);

   // methods
	  void clear();

	  bool isClear()const;

	  void message(const char* value);
	  
	  char* getMessage() const;

   // cast overloads
	  operator const char*() const;

	  operator bool()const;

   };
   // operator << overload prototype for cout
   std::ostream& operator << (std::ostream& ost, const Error& E);
}

#endif


