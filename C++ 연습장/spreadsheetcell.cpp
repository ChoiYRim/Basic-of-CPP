#include "spreadsheetcell.h"

SpreadsheetCell::SpreadsheetCell(double initialValue)
{
	mValue = initialValue;
}

SpreadsheetCell::SpreadsheetCell(std::string_view initialValue)
{
	mValue = stringToDouble(initialValue);
}

SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell& src) : mValue(src.mValue)
{
	// mValue = src.mValue; 를 사용하면 대입 연산자가 호출됨
}

void SpreadsheetCell::setValue(double inValue)
{
	mNumAccesses++;
	mValue = inValue;
}

double SpreadsheetCell::getValue() const
{
	mNumAccesses++;
	return mValue;
}

void SpreadsheetCell::setString(std::string_view inString)
{
	mValue = stringToDouble(inString);
}

std::string SpreadsheetCell::getString() const
{
	return doubleToString(mValue);
}

// private으로 helper method를 선언해놨기 때문에 이 기능이 바뀌더라도 이 함수를 사용하는 다른 함수들까지 고칠 필요가 없다.
//static std::string SpreadsheetCell::doubleToString(double inValue)
//{
//	return std::to_string(inValue);
//}
//
//static double SpreadsheetCell::stringToDouble(std::string_view inString)
//{
//	return strtod(inString.data(),nullptr);
//}

SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& rhs)
{
	if(this == &rhs)
		return *this;

	mValue = rhs.mValue;
	return *this;
}

SpreadsheetCell SpreadsheetCell::operator+(const SpreadsheetCell& rhs) const
{
	return SpreadsheetCell(getValue()+rhs.getValue());
}

SpreadsheetCell SpreadsheetCell::operator-(const SpreadsheetCell& rhs) const
{
	return SpreadsheetCell(getValue()-rhs.getValue());
}

SpreadsheetCell SpreadsheetCell::operator*(const SpreadsheetCell& rhs) const
{
	return SpreadsheetCell(getValue()*rhs.getValue());
}

SpreadsheetCell SpreadsheetCell::operator/(const SpreadsheetCell& rhs) const
{
	return SpreadsheetCell(getValue()/rhs.getValue());
}

SpreadsheetCell operator+(const SpreadsheetCell& lhs,const SpreadsheetCell& rhs)
{
	return SpreadsheetCell(lhs.getValue()+rhs.getValue());
}

SpreadsheetCell operator-(const SpreadsheetCell& lhs,const SpreadsheetCell& rhs)
{
	return SpreadsheetCell(lhs.getValue()-rhs.getValue());
}

SpreadsheetCell operator*(const SpreadsheetCell& lhs,const SpreadsheetCell& rhs)
{
	return SpreadsheetCell(lhs.getValue()*rhs.getValue());
}

SpreadsheetCell operator/(const SpreadsheetCell& lhs,const SpreadsheetCell& rhs)
{
	return SpreadsheetCell(lhs.getValue()/rhs.getValue());
}
