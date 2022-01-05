#pragma once

#include <cstddef>
#include <utility>
#include "spreadsheetcell.h"

// Spreadsheet Class를 관리하기 위한 SpreadsheetApplication Class가 필요한데
// Spreadsheet Class의 멤버 변수로 두기보단 MVC 기법으로 설계/구현하는 것이 더 바람직하다.

class Spreadsheet
{
	public:
		static const inline size_t kMaxWidth = 100;
		static const inline size_t kMaxHeight = 100;

		Spreadsheet(size_t width,size_t height);
		Spreadsheet(const Spreadsheet& src);
		Spreadsheet(Spreadsheet&& src) noexcept; // 이동 생성자

		void setCellAt(size_t x,size_t y, const SpreadsheetCell& cell);
		const SpreadsheetCell& getCellAt(size_t x,size_t y) const;
		SpreadsheetCell& getCellAt(size_t x,size_t y);

		~Spreadsheet();

		Spreadsheet& operator=(const Spreadsheet& rhs); // right hand side
		Spreadsheet& operator=(Spreadsheet&& rhs) noexcept; // 이동 대입 연산자

		friend void swap(Spreadsheet& first,Spreadsheet& second) noexcept;

	private:
		//bool inRange(size_t value,size_t upper) const;
		Spreadsheet() = default; // 디폴트 생성자를 사용할 일은 없기에 private로 선언
		void verifyCoordinate(size_t x,size_t y) const;
		void cleanup() noexcept;
		void moveFrom(Spreadsheet& src) noexcept;

		size_t mId = 0;
		size_t mWidth = 0;
		size_t mHeight = 0;
		std::string mName = "";
		static inline size_t sCounter = 0; // class member 변수에 inline을 적어두면 .cpp 파일에서 따로 얘를 명시 안해줘도 된다.
		SpreadsheetCell** mCells = nullptr; // C++에서 최근엔 일반 포인터를 사용하지 않지만 레거시 코드에 간혹 존재하므로 일단 사용해본다.
};
