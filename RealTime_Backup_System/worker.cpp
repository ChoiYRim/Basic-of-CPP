#include "header.h"

Worker::Worker(std::filesystem::path& p,int period,int opt,int mfn,int st,std::string_view cmd) : _absolute_path(p), _period(period), _option(opt), _maximum_file_numbers(mfn), _time(st)
{
	//std::cout << "making worker thread success..." << std::endl;
	std::cout << "COMMAND : " << cmd.data() << std::endl;
	std::cout << "ABSOLUTE PATH : " << _absolute_path << std::endl;
	std::cout << "PERIOD  : " << _period << std::endl;

	if(_option & (1 << 1))
	{
		std::cout << "add m option" << std::endl;
	}
	else if(_option & (1 << 2))
	{
		std::cout << "add n option" << std::endl;
	}
	else if(_option & (1 << 3))
	{
		std::cout << "add t option" << std::endl;
	}
	else if(_option & (1 << 4))
	{
		std::cout << "add d option" << std::endl;
	}
	else if(_option & (1 << 5))
	{
		std::cout << "remove a option" << std::endl;
	}
	else if(_option & (1 << 6))
	{
		std::cout << "recover n option" << std::endl;
	}
}

void Worker::operator()()
{
}
