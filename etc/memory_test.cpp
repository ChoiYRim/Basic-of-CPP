#include <iostream>

int* assign_memory()
{
	int* dynamic_memory = new int[16];
	return dynamic_memory;
}

int main(int argc,char* argv[])
{
	int static_memory[16] = {0,};
	int* dynamic_memory = assign_memory();

	char array_str[16] = "hello1";
	char* pointer_str = "hello2"; // warning because of C++11 standard

	std::cout << "static memory size : " << sizeof(static_memory) << '\n'; // it is a contiguous memory chunk
	std::cout << "dynamic memory size : " << sizeof(dynamic_memory) << '\n'; // although it was assigned, it is just a pointer

	for(int i = 0; i < sizeof(static_memory)/sizeof(int); i++)
	{
		//static_memory[i] = i+1;
		dynamic_memory[i] = i+1;
	}

	for(int i = 0; i < sizeof(static_memory)/sizeof(int); i++)
	{
		//std::cout << "static memory [" << i << "] : " << static_memory[i] << '\n';
		std::cout << "dynamic memory [" << i << "] : " << dynamic_memory[i] << '\n';
	}

	std::cout << "array string : " << array_str << '\n';
	std::cout << "pointer string : " << pointer_str << '\n';

	array_str[0] = 't';
	std::cout << "array string : " << array_str << '\n';
	// A string pointer can't change the element of value it points to.
	//pointer_str[0] = 't';
	//std::cout << "pointer string : " << pointer_str << '\n';

	delete dynamic_memory;
	return 0;
}
