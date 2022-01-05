#include <iostream>

int main(int argc,char* argv[])
{
	int num = 1;
	const int* const ptr1 = &num;
	int const* const ptr2 = &num;
	return 0;
}
