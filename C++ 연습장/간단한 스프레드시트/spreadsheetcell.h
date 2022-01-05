#pragma once

#include <iostream>
#include <algorithm>

#include <string>
#include <string_view>

// 표준 라이브러리에서 제공하는 모든 클래스들은 이니셜라이저 리스트 생성자를 지원한다.
#include <initializer_list>

class SpreadsheetCell
{
	public:
		SpreadsheetCell() = default; // default constructor

		SpreadsheetCell(double initialValue);

		SpreadsheetCell(std::string_view initialValue);

		SpreadsheetCell(const SpreadsheetCell& src); // reproduction constructor

		void setValue(double inValue);
		double getValue() const;

		void setString(std::string_view inString);
		std::string getString() const;

		SpreadsheetCell& operator=(const SpreadsheetCell& rhs); // rhs : right hand side
		SpreadsheetCell operator+(const SpreadsheetCell& rhs) const;
		SpreadsheetCell operator-(const SpreadsheetCell& rhs) const;
		SpreadsheetCell operator*(const SpreadsheetCell& rhs) const;
		SpreadsheetCell operator/(const SpreadsheetCell& rhs) const;

	private:
		static std::string doubleToString(double inValue) // helper method
		{
			return std::to_string(inValue);
		}
		static double stringToDouble(std::string_view inString) // helper method
		{
			return strtod(inString.data(),nullptr);
		}
		double mValue;
		mutable size_t mNumAccesses = 0;
};

SpreadsheetCell operator+(const SpreadsheetCell& lhs,const SpreadsheetCell& rhs);

SpreadsheetCell operator-(const SpreadsheetCell& lhs,const SpreadsheetCell& rhs);

SpreadsheetCell operator*(const SpreadsheetCell& lhs,const SpreadsheetCell& rhs);

SpreadsheetCell operator/(const SpreadsheetCell& lhs,const SpreadsheetCell& rhs);
