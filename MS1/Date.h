// Milestone1 - THE DATE MODULE
// Date.h
// Jihyun Lee , 141859181
// 2019/7/16

#ifndef AID_DATE_H__
#define AID_DATE_H__

#define NO_ERROR   0  
#define CIN_FAILED 1  
#define DAY_ERROR  2  
#define MON_ERROR  3  
#define YEAR_ERROR 4 
#define PAST_ERROR 5 

#include <iostream>

namespace aid {

	const int min_year = 2018;
	const int max_year = 2038;
	const int min_date = 751098 ;


	class Date {

		int m_year;
		int m_month;
		int m_day;
		int m_dayOfMonth; 
		int m_comparator;
		int m_errorState;
		
		void errCode(int errorCode);
		int mdays(int year, int mon) const;
		void setEmpty();
		void setDate(int year, int month, int day);

	public:
		Date();
		Date(int year, int month, int day);
		int errCode() const;
		bool bad(void) const;
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;

	};
	std::istream& operator>>(std::istream& istr, Date&);
	std::ostream& operator<<(std::ostream& ostr, Date&);
}



#endif // !


