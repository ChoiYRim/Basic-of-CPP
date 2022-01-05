#include <vector>
#include "spreadsheet.h"

Spreadsheet createObject()
{
	return Spreadsheet(3,2);
}

int main(int argc,char* argv[])
{
	std::vector<Spreadsheet> vec;
	for(int i = 0; i < 2; ++i)
	{
		std::cout << "Iteration " << i << '\n';
		vec.push_back(Spreadsheet(100,100));
	}

	Spreadsheet s(2,3);
	s = createObject();

	Spreadsheet s2(5,6);
	s2 = s;
	return 0;
}
