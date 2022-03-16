#include "header.h"

void Program::start()
{
	system("clear");
	while(true)
	{
		std::string input = "";

		std::cout << "> ";
		std::getline(std::cin,input);	

		auto commands = split_commands(input);
		if(commands.size() <= 0)
			continue;
		// getopt ??

		std::string command = commands[0];

		if(command == "add") add(commands);
		else if(command == "remove") remove(commands);
		else if(command == "compare") compare(commands);
		else if(command == "recover") recover(commands);
		else if(command == "list") list(commands);
		else if(command == "exit") break;
		else if(command == "clear") system("clear");
		else general_command(commands);
	}
}

std::vector<std::string> Program::split_commands(const std::string& input)
{
	std::vector<std::string> ret;
	std::stringstream stream(input);
	std::string word = "";

	if(input.length() == 0)
	{
		std::cerr << "input length must be over 0.\n";
		return ret;
	}

	while(std::getline(stream,word,' ')) ret.push_back(word);	
	return ret;
}

bool Program::check_command_validity(int types,const std::vector<std::string>& cmds)
{
	if(types == ADD)
	{
		// add [file name] [period] [options]
//		if(cmds.size() < 3) 
//		{
//			std::cerr << "add [FILENAME] [PERIOD] ...{options}...\n";
//			return false;
//		}
//
//		std::filesystem::path path;
//		std::string absolute_path = "";
//		int period = 0,option = 0,maximum_file_numbers = 0;
//
//		if(cmds[1] == "-d") // d option : directory
//		{
//			path = std::filesystem::path(cmds[2]);
//			if(!std::filesystem::exists(path))
//			{
//				std::cerr << path << " does not exist.\n";
//				return false;
//			}
//			if(!std::filesystem::is_directory(path))
//			{
//				std::cerr << path << " is not a directory.\n";
//				return false;
//			}
//			absolute_path = std::filesystem::absolute(path);
//			
//			return true;
//		}
//
//		path = std::filesystem::path(cmds[1]);
//		if(!std::filesystem::exists(path))
//		{
//			std::cerr << path << " does not exist.\n";
//			return false;
//		}
//		if(!std::filesystem::is_regular_file(path))
//		{
//			std::cerr << path << " is not a directory.\n";
//			return false;
//		}
//		absolute_path = std::filesystem::absolute(path);
//
	}
	else if(types == REMOVE)
	{
	}
	else if(types == COMPARE)
	{
	}
	else if(types == RECOVER)
	{
	}
	else if(types == LIST)
	{
	}

	return true;
}

int Program::add(const std::vector<std::string>& cmds)
{
	if(!check_command_validity(ADD,cmds))
		return 1;
	return 0;
}

int Program::remove(const std::vector<std::string>& cmds)
{
	return 0;
}

int Program::compare(const std::vector<std::string>& cmds)
{
	return 0;
}

int Program::recover(const std::vector<std::string>& cmds)
{
	return 0;
}

int Program::list(const std::vector<std::string>& cmds)
{
	return 0;
}

void Program::general_command(const std::vector<std::string>& cmds)
{
	FILE* p = NULL;
	char args[kbuffer_length];
	int cmd_len = static_cast<int>(cmds.size());

	memset((char*)args,0,sizeof(args));
	sprintf(args, "%s ", cmds[0].c_str());
	for(int i = 1; i < cmd_len && cmds[i].length()+strlen(args) < kbuffer_length; i++)
		sprintf(args, "%s %s ", args, cmds[i].c_str());

	if((p = popen(args,"r")) == NULL)
	{
		std::cerr << "popen() error\n" << std::endl;
		return;
	}

	memset((char *)args,0,sizeof(args));
	while(fgets(args,kbuffer_length,p) != NULL)
	{
		std::cout << args;
		memset((char *)args,0,sizeof(args));
	}
}
