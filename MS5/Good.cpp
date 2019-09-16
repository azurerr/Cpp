// Final Project Milestone 3 - The Good Module & 5
// Good.cpp
// Jihyun Lee, 141859181
// 2019/8/06
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Good.h"


using namespace std;

namespace aid {


	// Constructors ***********************

	Good::Good(char type) {

		m_type = type;
		setEmpty();
	}

	Good::Good(const char* sku, const char* name, const char* unit, int currentQty, bool taxable, double price, int neededQty) {

		setEmpty();
		strncpy(m_sku, sku, max_sku_length);
		m_sku[max_sku_length] = '\0'; // same with  = 0

		strncpy(m_unit, unit, max_unit_length);
		m_unit[max_unit_length] = '\0';

		Good::name(name);
		
		m_currentQty = currentQty;
		m_neededQty = neededQty;
		m_price = price;
		m_taxable = taxable;
	}

	// Deconstructor ***********************
	Good::~Good() {
		setNameEmpty();
	}


	// protected **************************

	void Good::name(const char* name) {


		if (name != nullptr) {
			m_name = new char[strlen(name) + 1];
			strncpy(m_name, name, strlen(name));
			m_name[strlen(name)] = 0;
		}
		else
			m_name[0] = 0;
	}

	const char* Good::name() const {
		return m_name;
	}

	const char* Good::sku() const {
		return m_sku;
	}

	const char* Good::unit() const {
		return m_unit;
	}

	bool Good::taxed() const {
		return m_taxable;
	}

	double Good::itemPrice() const {
		return m_price;
	}

	double Good::itemCost() const {

		return m_taxable ? (m_price * (1 + tax_rate)) : m_price;
	}

	void Good::message(const char* err) {

		errOfGood.message(err);
	}

	bool Good::isClear() const {
		return (errOfGood.isClear());
	}


	// public *****************************************

	Good::Good(const Good& rhs) {
		*this = rhs;
	}

	//copy assingment operator
	Good& Good::operator=(const Good& rhs) {

		if (this != &rhs) {
			m_type = rhs.m_type;
			strncpy(m_sku, rhs.m_sku, strlen(rhs.m_sku));
			m_sku[strlen(rhs.m_sku)] = '\0';

			strncpy(m_unit, rhs.m_unit, strlen(rhs.m_unit));
			m_unit[strlen(rhs.m_unit)] = '\0';

			name(rhs.m_name);
			
			m_currentQty = rhs.m_currentQty;
			m_neededQty = rhs.m_neededQty;
			m_price = rhs.m_price;
			m_taxable = rhs.m_taxable;
		}
		return *this;
	}

	std::fstream& Good::store(fstream& file, bool newLine) const {

		//file.open("filename.txt", ios::out | ios::app);

		file << m_type << "," << m_sku << "," << m_name << "," << m_unit << ","
			<< m_taxable << "," << m_price << "," << m_currentQty << "," << m_neededQty;
		if (newLine) {
			file << endl;
		}
		return file;
	}

	fstream& Good::load(std::fstream& file) {

		Good temp;
		temp.m_name = new char[max_name_length + 1];
		file.getline(temp.m_sku, max_sku_length, ',');
		temp.m_sku[strlen(temp.m_sku)] = '\0';
		file.getline(temp.m_name, max_name_length, ',');
		temp.m_name[strlen(temp.m_name)] = '\0';
		file.getline(temp.m_unit, max_name_length, ',');
		temp.m_unit[strlen(temp.m_unit)] = '\0';
		file >> temp.m_taxable;
		file.ignore();
		file >> temp.m_price;
		file.ignore();
		file >> temp.m_currentQty;
		file.ignore();
		file >> temp.m_neededQty;
		file.ignore();
		
		*this = temp;
		temp.setEmpty();

		return file;
	}

	std::ostream& Good::write(std::ostream& os, bool linear) const {

		if (errOfGood.isClear() && !isEmpty()) {
			if (linear) {
				os << setw(max_sku_length) << left << m_sku << '|' << setw(20) << left << ((m_name == nullptr)? "" : m_name) << '|'
					<< setw(7) << fixed << setprecision(2) << right << itemCost() << '|' << setw(4) << right << m_currentQty << '|'
					<< setw(10) << left << m_unit << '|' << setw(4) << right << m_neededQty << '|';
			}

			else {
				os << " Sku: " << m_sku << endl
					<< " Name (no spaces): " << m_name << endl
					<< " Price: " << m_price << endl;
				if (m_taxable)
					os << " Price after tax: " << itemCost() << endl;
				else
					os << " Price after tax:  N/A" << endl;

				os << " Quantity on Hand: " << m_currentQty << " " << m_unit << endl
					<< " Quantity needed: " << m_neededQty;
			}
		}
		else if (!errOfGood.isClear())
			os << errOfGood.message();
		else if (isEmpty())
			;
		return os;
	}

	std::istream& Good::read(std::istream& is) {

		char* tempName = new char[max_name_length + 1];
		cout << " Sku: ";
		is >> m_sku;
		cout << " Name (no spaces): ";
		is >> tempName;
		name(tempName);
		cout << " Unit: ";
		is >> m_unit;
		cout << " Taxed? (y/n): ";
		char temp;
		is >> temp;
		if (!(temp == 'y' || temp == 'Y' || temp == 'N' || temp == 'n')) {
			is.setstate(std::ios::failbit);
			message("Only (Y)es or (N)o are acceptable");
		}
		else {
			m_taxable = (temp == 'y' || temp == 'Y') ? true : false;

			cout << " Price: ";
			is >> m_price;
			if (is.fail() || m_price < 0) {
				is.setstate(std::ios::failbit);
				message("Invalid Price Entry");
			}
			else {

				cout << " Quantity on hand: ";
				is >> m_currentQty;
				if (is.fail() || m_currentQty < 0) {
					is.setstate(std::ios::failbit);
					message("Invalid Quantity Entry");
				}
				else {
					cout << " Quantity needed: ";
					is >> m_neededQty;
                                        cin.ignore();
					if (is.fail() || m_currentQty < 0) {
						is.setstate(std::ios::failbit);
						message("Invalid Quantity Needed Entry");
					}
					else
						errOfGood.clear();
				}

			}
		}
			
		
		return is;
	}

	bool Good::operator==(const char* rhs) const {

		return (m_sku == rhs);
	}

	double Good::total_cost() const {

		return (itemCost() * m_currentQty);
	}

	void Good::quantity(int units) {

		if (units > 0)
			m_currentQty = units;
	}

	bool Good::isEmpty() const {
		// return (m_sku == nullptr || m_sku[0] == '\0');
		return (m_sku[0] == '\0' && isClear()) ? true : false;


	}

	int Good::qtyNeeded() const {
		return m_neededQty;
	}

	int Good::quantity() const {
		return m_currentQty;
	}

	bool Good::operator>(const char* sku) const {
		return (m_sku > sku);
	}

	bool Good::operator>(const iGood& rhs) const {
		return (m_name > rhs.name());
	}

	int Good::operator+=(int noOfUnits) {
		if (noOfUnits > 0)
			m_currentQty += noOfUnits;
		return m_currentQty;
	}

	// Helper functions ************************************

	std::ostream& operator<<(std::ostream& os, const iGood& rhs) {
		return rhs.write(os, true);
	}

	std::istream& operator>>(std::istream& is, iGood& rhs) {
		return rhs.read(is);
	}

	double operator+=(double& price, const iGood& rhs) {
		return (price += rhs.total_cost());
	}


	// my member functions ************************************
	void Good::setEmpty() {

		m_sku[0] = '\0';
		m_unit[0] = '\0';
		m_name = nullptr;
		m_currentQty = 0; // the number of units of the Good currently on hand
		m_neededQty = 0;
		m_price = 0; //the price of a single unit of the Good before applying any taxes
		m_taxable = true;

	}

	void Good::setNameEmpty() {

		delete[] m_name;
		m_name = nullptr;

	}


}
