//Date.h
//BLARNEY
//Winter 2017

// compilation safegaurds
#ifndef ICT_Date_H_
#define ICT_Date_H

#include <iostream>
// ict namespace 
namespace ict {
   // Date defined Error values

	#define NO_ERROR (0)
	#define CIN_FAILED (1)
	#define YEAR_ERROR (2)
	#define MON_ERROR (3)
	#define DAY_ERROR (4)
	#define HOUR_ERROR (5)
	#define MIN_ERROR (6)

   class Date {
   private:
      // member variables
	   int m_year;
	   int m_mon;
	   int m_day;
	   int m_hour;
	   int m_min;
	   int m_readErrorCode;

	   bool m_dateOnly;


     // private methods
      int value()const;

	  void errCode(int errorCode);

	  int mdays() const;

	  void set();

	  void set(int year, int mon, int day, int hour, int min);


   public:
      // constructors

	  Date();
	  Date(int year, int mon, int day);
      Date(int year, int mon, int day, int hour, int min = 0);

      // operator ovrloads
	  bool operator==(const Date& D)const; 
	  bool operator!=(const Date& D)const; 
	  bool operator<(const Date& D)const; 
	  bool operator>(const Date& D)const;
	  bool operator<=(const Date& D)const; 
	  bool operator>=(const Date& D)const;

      // methods
	  int errCode() const;
	  bool bad() const;
	  bool dateOnly() const;
	  void dateOnly(bool value);

      // istream  and ostream read and write methods

	  std::istream& read(std::istream&);

	  std::ostream& write(std::ostream&) const;

   };
   // operator<< and >> overload prototypes for cout and cin

	std::istream& operator >> (std::istream& is, Date& D);
	std::ostream& operator << (std::ostream& ost, const Date& D);


}

#endif