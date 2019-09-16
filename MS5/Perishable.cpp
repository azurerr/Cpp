// Final Project Milestone 5 - THE GOOD HIERARCHY
// Perishable.cpp
// Jihyun Lee, 141859181
// 2019/8/06

#include "Perishable.h"

using namespace std;
namespace aid {

	Perishable::Perishable(): Good('P') {
		setEmpty();
		expiryDate.setEmpty();
		// set the current obj to a safe empty state
	}
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const {
		Good::store(file, false);
		file << ",";
		expiryDate.write(file);
		if (newLine)
			file << endl;
		return file;
	}

	std::fstream& Perishable::load(std::fstream& file) {
		Good::load(file);
		expiryDate.read(file);
		file.ignore();
		return file;
	}
	
	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		Good::write(os, linear);
		if (isClear() && !isEmpty()) {
			if (linear)
				expiryDate.write(os);
			else {
				os << endl << " Expiry date: ";
				expiryDate.write(os);
			}
		}
		return os;
	}

	std::istream& Perishable::read(std::istream& is) {

		Good::read(is);

		if (isClear()) {
			cout << " Expiry date (YYYY/MM/DD): ";
			expiryDate.read(is);
		}

		if (expiryDate.errCode() == CIN_FAILED) {
			message("Invalid Date Entry");
			is.setstate(std::ios::failbit);
		}
	
		else if (expiryDate.errCode() == YEAR_ERROR) {
			message("Invalid Year in Date Entry"); 
			is.setstate(std::ios::failbit);
		}
			
		else if (expiryDate.errCode() == MON_ERROR) {
			message("Invalid Month in Date Entry");
			is.setstate(std::ios::failbit);
		}

		else if (expiryDate.errCode() == DAY_ERROR) {
			message("Invalid Day in Date Entry");
			is.setstate(std::ios::failbit);
		}
		else if (expiryDate.errCode() == PAST_ERROR) {
			message("Invalid Expiry in Date Entry");
			is.setstate(std::ios::failbit);
		}
		else
			errOfGood.clear();

		return is;
	}

	const Date& Perishable::expiry() const {
		return expiryDate;
	}

	iGood* CreateProduct(char tag) {

		iGood* temp = nullptr;

		if (tag == 'N' || tag == 'n')
			temp = new Good();
		else if (tag == 'P' || tag == 'p')
			temp = new Perishable();

		return temp;
	}

}
