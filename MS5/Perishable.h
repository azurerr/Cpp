// Final Project Milestone 5 - THE GOOD HIERARCHY
// Perishable.h
// Jihyun Lee, 141859181
// 2019/8/06

#ifndef AID_PERISHABLE_H__
#define AID_PERISHABLE_H__
#include "Good.h"
#include "Date.h"

namespace aid {

	class Perishable: public Good {
		Date expiryDate;

	public:
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;
		
	};

	iGood* CreateProduct(char tag);

}



#endif // !AID_PERISHABLE_H__
