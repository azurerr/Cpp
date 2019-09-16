// Final Project Milestone 2 - Error Class
// Error.cpp
// Jihyun Lee, 141859181
// 2019/7/19

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include "Error.h"

namespace aid {

	Error::Error(const char* errorMessage) : m_message (nullptr) {

		if (errorMessage == nullptr || errorMessage[0] == '\0')
			m_message = nullptr;

		else
			message(errorMessage);
	}

	Error::~Error() {
		clear();
	}

	void Error::clear() {
		
		delete[] m_message;
		m_message = nullptr;
	}

	bool Error::isClear() const {
		return (m_message == nullptr || m_message[0] == '\0');
	}


	void Error::message(const char* str) {

		clear();
		if (str != nullptr || str[0] != '\0') {

			m_message = new char[strlen(str) + 1];
			strncpy(m_message, str, strlen(str));
			m_message[strlen(str)] = '\0';
		}

	}

	const char* Error::message() const {
		return m_message;		
	}


	std::ostream& operator<<(std::ostream& os, const Error& rhs) {
		if (!(rhs.isClear()))
			os << rhs.message();
		return os;
	}


}
