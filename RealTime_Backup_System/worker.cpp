#include "header.h"

Worker::Worker(std::filesystem::path& p,int period,int opt,int mfn,int st,std::string_view cmd) : _absolute_path(p), _period(period), _option(opt), _maximum_file_numbers(mfn), _time(st)
{
	std::cout << "COMMAND : " << cmd.data() << std::endl;
	std::cout << "ABSOLUTE PATH : " << _absolute_path << std::endl;
	std::cout << "PERIOD  : " << _period << std::endl;

	if(_option & option_am)
	{
		std::cout << "add m option" << std::endl;
	}
	if(_option & option_an)
	{
		std::cout << "add n option" << std::endl;
	}
	if(_option & option_at)
	{
		std::cout << "add t option" << std::endl;
	}
	if(_option & option_ad)
	{
		std::cout << "add d option" << std::endl;
	}
	if(_option & option_ra)
	{
		std::cout << "remove a option" << std::endl;
	}
	if(_option & option_rn)
	{
		std::cout << "recover n option" << std::endl;
	}
}

void Worker::operator()()
{
	while(true)
	{
	}
	//std::cout << "thread worked!" << std::endl;
}
