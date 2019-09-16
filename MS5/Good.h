// Final Project Milestone 3 - The Good Module & 5
// Good.h
// Jihyun Lee, 141859181
// 2019/8/05
#ifndef AID_GOOD_H__
#define AID_GOOD_H__
#include "iGood.h"
#include "Error.h"

namespace aid {

	const int max_sku_length = 7; 
	const int max_unit_length = 10; 
	const int max_name_length = 75;
	const float tax_rate = 0.13;

	class Good: public iGood {
		char m_type; //the type of the Good
		char m_sku[max_sku_length + 1]; //stock keeping unit
		char m_unit[max_unit_length + 1]; //describes the Good’s unit
		char* m_name; //containing the name of the Good
		int m_currentQty; // the number of units of the Good currently on hand
		int m_neededQty;
		double m_price; //the price of a single unit of the Good before applying any taxes
		bool m_taxable;

	protected:
		Error errOfGood; //A statically allocated Error object that holds the error state of the Good object.
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
		bool operator>(const iGood& rhs) const; //to receive a reference
		int operator+=(int noOfUnits); 

		// my member functions
		void setEmpty();
		void setNameEmpty();

	};
	std::ostream& operator<<(std::ostream& os, const iGood& rhs); //to receive a reference
	std::istream& operator>>(std::istream& is, iGood& rhs); //to receive a reference
	double operator+=(double&, const iGood& rhs); //to receive a reference
	
}

#endif 
