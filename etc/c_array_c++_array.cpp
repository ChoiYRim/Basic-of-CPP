#include <array>
#include <iostream>

template <size_t s>
void cpp_copy_test(std::array<int,s> arr)
{
	arr[0] = 32;
}

void c_copy_test(int* arr)
{
	arr[0] = 32;
}

int main(int argc,char* argv[])
{
	std::array<int,16> arr1;
	int arr2[16] = {0,};

	for(int i = 0; i < 16; i++)
	{
		arr1[i] = i+1;
		arr2[i] = i+1;
	}

	std::cout << "< Before test >" << '\n';
	std::cout << "C style array : ";
	for(int i = 0; i < 16; i++)
		std::cout << arr1[i] << ' ';
	std::cout << '\n';
	std::cout << "C++ style array : ";
	for(int i = 0; i < 16; i++)
		std::cout << arr2[i] << ' ';
	std::cout << '\n';

	cpp_copy_test(arr1);
	c_copy_test(arr2);

	std::cout << "< After test >" << '\n';
	std::cout << "C style array : ";
	for(int i = 0; i < 16; i++)
		std::cout << arr1[i] << ' ';
	std::cout << '\n';
	std::cout << "C++ style array : ";
	for(int i = 0; i < 16; i++)
		std::cout << arr2[i] << ' ';
	std::cout << '\n';
	return 0;
}
