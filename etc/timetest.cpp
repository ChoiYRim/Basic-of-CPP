#include <iostream>
#include <chrono>

int main(int argc,char* argv[])
{
	std::chrono::system_clock::time_point begin,end;

	begin = std::chrono::system_clock::now();
	for(int i = 0; i < 1000000; i++);
	end = std::chrono::system_clock::now();

	auto result_us = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
	std::cout << "executing time : " << result_us.count() << " us" << '\n';
	auto result_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
	std::cout << "executing time : " << result_ms.count() << " ms" << '\n';
	return 0;
}
