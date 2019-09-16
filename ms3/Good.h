// Final Project Milestone 3 - The Good Module
// Good.h
// Jihyun Lee, 141859181
// 2019/8/01
#ifndef AID_GOOD_H__
#define AID_GOOD_H__
#include "Error.h"

namespace aid {

	const int max_sku_length = 7; 
	const int max_unit_length = 10; 
	const int max_name_length = 75;
	const float tax_rate = 0.13;

	class Good {
		char m_type; //the type of the Good
		char m_sku[max_sku_length + 1]; //stock keeping unit
		char m_unit[max_unit_length + 1]; //describes the Good’s unit
		char* m_name; //containing the name of the Good
		int m_currentQty; // the number of units of the Good currently on hand
		int m_neededQty;
		double m_price; //the price of a single unit of the Good before applying any taxes
		bool m_taxable;
		Error errOfGood; //A statically allocated Error object that holds the error state of the Good object.

	protected:
		void name(const char* name);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double itemPrice() const;
		double itemCost() const;
		void message(const char* err);
		bool isClear() const;

	public:
		Good(char type = 'N');
		Good(const char* sku, const char* name, const char* unit, int currentQty = 0, 
			bool taxable = true, double price = 0, int needQty = 0);
		Good(const Good& rhs);
		virtual ~Good();
		Good& operator=(const Good& rhs);

		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char* sku) const;
		bool operator>(const Good& rhs) const;
		int operator+=(int noOfUnits);

		// my member functions
		void setEmpty();
		void setNameEmpty();

	};
	std::ostream& operator<<(std::ostream& os, const Good& rhs);
	std::istream& operator>>(std::istream& is, Good& rhs);
	double operator+=(double&, const Good& rhs);
	
}

#endif 
