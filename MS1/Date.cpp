// Milestone1 - THE DATE MODULE
// Date.cpp
// Jihyun Lee , 141859181
// 2019/7/16

#define _CRT_SECURE_NO_WARNINGS
#include  <iomanip>
#include "Date.h"

namespace aid {

	Date::Date() {
		setEmpty();
	}

	Date::Date(int year, int month, int day) {
		setEmpty(); 
		setDate(year, month, day);
		
	}

	void Date::setEmpty() {
		m_year = 0;
		m_month = 0;
		m_day = 0;
		m_dayOfMonth = 0;
		m_comparator = 0;
		m_errorState = NO_ERROR;
	}

	void Date::setDate(int year, int month, int day) {

		if (year <= max_year && year >= min_year) {
			if (month > 0 && month < 13) {
				int dayOfMonth = mdays(year, month);
				if (day > 0 && day <= dayOfMonth) {
					int comparator = year * 372 + month * 31 + day;
					if (comparator > min_date) {
						m_year = year;
						m_month = month;
						m_day = day;
						m_comparator = m_year * 372 + m_month * 31 + m_day;
						m_errorState = NO_ERROR;
					}
					else {
						m_errorState = PAST_ERROR;
					}
				}
				else
					m_errorState = DAY_ERROR;
			}
			else
				m_errorState = MON_ERROR;
		}
		else
			m_errorState = YEAR_ERROR;
	}


	void Date::errCode(int errorCode) {
		m_errorState = errorCode;
	}

	int Date::errCode() const {
		return m_errorState;
	}

	int Date::mdays(int year, int mon) const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	bool Date::bad(void) const {
		return (m_errorState != NO_ERROR);
	}

	bool Date::operator==(const Date& rhs) const {
		bool result = false;
		if (this != nullptr && &rhs != nullptr) {
			if (this != &rhs) {
				result = (m_year == rhs.m_year && m_month == rhs.m_month && m_day == rhs.m_day);
			}
		}
		return result;
	}

	bool Date::operator!=(const Date& rhs) const {
		return !(*this == rhs);
	}

	bool Date::operator<(const Date& rhs) const {
		return m_comparator < rhs.m_comparator;
	}

	bool Date::operator>(const Date& rhs) const {
		return m_comparator > rhs.m_comparator;
	}

	bool Date::operator<=(const Date& rhs) const {
		return m_comparator <= rhs.m_comparator;
	}

	bool Date::operator>=(const Date& rhs) const {
		return m_comparator >= rhs.m_comparator;
	}

	std::istream& Date::read(std::istream& istr) {
		int year = 0;
		int month = 0;
		int day = 0;
		char mark1;
		char mark2;

		istr >> year >> mark1 >> month >> mark2 >> day;
		if (istr.fail()) {
			setEmpty();
			m_errorState = CIN_FAILED;
		}
			
		else
			setDate(year, month, day);
		
		return istr;
	}

	std::ostream& Date::write(std::ostream& ostr) const {
		ostr << m_year << "/" << std::setfill('0') << std::setw(2) << m_month << "/" << std::setfill('0') << std::setw(2) << m_day;
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, Date& rhs) {
		return rhs.read(istr);
	}
	std::ostream& operator<<(std::ostream& ostr, Date& rhs) {
		return rhs.write(ostr);
	}

}