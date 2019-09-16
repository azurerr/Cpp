// Final Project Milestone 2 - Error Class
// Error.h
// Jihyun Lee, 141859181
// 2019/7/19

#ifndef AID_ERROR_H__
#define AID_ERROR_H__
#include <iostream>

namespace aid {

	class Error {

		char* m_message;

	public:
		explicit Error(const char* errorMessage = nullptr);
		virtual ~Error();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;
	};

	std::ostream& operator<<(std::ostream& os, const Error& rhs);

}


#endif // !SICT_ERROR_H__

