#include "spreadsheet.h"

Spreadsheet::Spreadsheet(size_t width,size_t height) : mWidth(std::min(kMaxWidth,width)), mHeight(std::min(kMaxHeight,height)), mId(sCounter++)
{
	std::cout << "Normal constructor" << '\n';
	mCells = new SpreadsheetCell*[mWidth];
	for (size_t i = 0; i < mWidth; i++)
		mCells[i] = new SpreadsheetCell[mHeight];
} 

Spreadsheet::Spreadsheet(const Spreadsheet& src) : Spreadsheet(src.mWidth,src.mHeight)
{
	std::cout << "Copy constructor" << '\n';
	for(size_t i = 0; i < mWidth; i++)
		for(size_t j = 0; j < mHeight; j++)
			mCells[i][j] = src.mCells[i][j];
}


Spreadsheet::Spreadsheet(Spreadsheet&& src) noexcept
{
	std::cout << "Move constructor" << '\n';
	swap(*this,src);
	//moveFrom(src);
}

void Spreadsheet::setCellAt(size_t x,size_t y,const SpreadsheetCell& cell)
{
//	if(!inRange(x,mWidth) || !inRange(y,mHeight)) // code duplication
//		throw std::out_of_range("");

	verifyCoordinate(x,y);
	mCells[x][y] = cell;
}

const SpreadsheetCell& Spreadsheet::getCellAt(size_t x,size_t y) const
{
	verifyCoordinate(x,y);
	return mCells[x][y];
}

SpreadsheetCell& Spreadsheet::getCellAt(size_t x,size_t y)
{
	return const_cast<SpreadsheetCell&>(std::as_const(*this).getCellAt(x,y));
}

//SpreadsheetCell& Spreadsheet::getCellAt(size_t x,size_t y)
//{
////	if(!inRange(x,mWidth) || !inRange(y,mHeight)) // code duplication
////		throw std::out_of_range("");
//
//	verifyCoordinate(x,y);
//	return mCells[x][y];
//}


Spreadsheet::~Spreadsheet()
{
	if(mCells != nullptr)
	{
		for(size_t i = 0; i < mWidth; i++)
			delete[] mCells[i];
		delete[] mCells;
		mCells = nullptr;
	}
	sCounter--;
}

Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
{
	std::cout << "Copy assignment operator" << '\n';

	if(this == &rhs)
		return *this;

	for(size_t i = 0; i < mWidth; i++)
		delete[] mCells[i];
	delete[] mCells;
	mCells = nullptr;

	mWidth = rhs.mWidth;
	mHeight = rhs.mHeight;

	Spreadsheet temp(rhs); // 복제 생성자 호출
	swap(*this,temp);
	return *this;

// 여기서부터 만약 메모리를 할당하는데 문제가 생겼다면 *this를 리턴해도 제대로 된 데이터가 아닐 수 있다.
//	mCells = new SpreadsheetCell*[mWidth];
//	for(size_t i = 0; i < mWidth; i++)
//		mCells[i] = new SpreadsheetCell[mHeight];
//
//	for(size_t i = 0; i < mWidth; i++)
//		for(size_t j = 0; j < mHeight; j++)
//			mCells[i][j] = rhs.mCells[i][j];

	return *this;
}

Spreadsheet& Spreadsheet::operator=(Spreadsheet&& rhs) noexcept
{
	std::cout << "Move assignment operator" << '\n';

	Spreadsheet tmp(std::move(rhs));
	swap(*this,tmp);
	return *this;
}

void swap(Spreadsheet& first,Spreadsheet& second) noexcept
{
	using std::swap;

	swap(first.mWidth,second.mWidth);
	swap(first.mHeight,second.mHeight);
	swap(first.mCells,second.mCells);
}

void Spreadsheet::verifyCoordinate(size_t x,size_t y) const
{
	if(x >= mWidth || y >= mHeight || x < 0 || y < 0)
		throw std::out_of_range("out of range exception occurs...");
}

void Spreadsheet::cleanup() noexcept
{
	for(size_t i = 0; i < mWidth; i++)
		delete[] mCells[i];
	delete[] mCells;
	mCells = nullptr;
	mWidth = mHeight = 0;
}

void Spreadsheet::moveFrom(Spreadsheet& src) noexcept
{
	// 객체를 복사하지 않고 말 그대로 값을 이동(copy)시켜준다.
	mName = std::move(src.mName);

	// shallow copy - 우측값 레퍼런스의 메모리를 버리고 새로 생성해서 대입하는 것이 아니라 메모리 절약 가능
	mWidth = src.mWidth;
	mHeight = src.mHeight;
	mCells = src.mCells;

	// 소유권이 이전됐기 때문에 소스 객체를 리셋
	src.mWidth = src.mHeight = 0;
	src.mCells = nullptr;
}
