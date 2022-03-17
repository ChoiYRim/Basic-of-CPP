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

		std::string command = commands[0];

		if(command == "exit")
		{
			// 현재 작동 중인 스레드 종료
			for(auto& ele : _table) erase_worker(ele.first);
			_table.clear();
			break;
		}
		else if(command == "add") add(commands);
		else if(command == "remove") remove(commands);
		else if(command == "compare") compare(commands);
		else if(command == "recover") recover(commands);
		else if(command == "list") list(commands);
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

bool Program::spawn_worker(int types, const std::vector<std::string>& cmds)
{
	// option : add(m,n,t,d), remove(a), recover(n) -> 1,2,3,4,5,6
	int period = 0;
	int option = 0;
	int maximum_file_numbers = 0;
	int store_time = 0;
	std::filesystem::path path;

	if(types == ADD)
	{
		// add [file name] [period] ...
		if(cmds.size() < 3)
			return false;

		if(!get_add_options(period, option, maximum_file_numbers, store_time, path, cmds)) return false;

		// if option d

		// else
		std::thread thread(Worker(path, period, option, maximum_file_numbers, store_time,"add"));
		_table[path.string()] = thread.native_handle();
		thread.detach();
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

void Program::erase_worker(const std::string& file_name)
{
	auto it = _table.find(file_name);
	if(it != _table.end())
		pthread_cancel(it->second);
}

int Program::add(const std::vector<std::string>& cmds)
{
	if(!spawn_worker(ADD,cmds))
	{
		std::cerr << "command is invalid...\n";
		return 1;
	}
	return 0;
}

bool Program::get_add_options(int& period,int& option,int& maximum_file_numbers,int& store_time,std::filesystem::path& path,const std::vector<std::string>& cmds)
{
	if(cmds[1] == "-d")
	{
		if(cmds.size() < 4)
			return false;

		path = std::filesystem::path(cmds[2]);
		if(std::filesystem::exists(path) != true)
			return false;
		if(std::filesystem::is_directory(path) != true)
			return false;
		path = std::filesystem::absolute(path);
		for(auto i = 0; i < cmds[3].length(); i++)
			if(cmds[3][i] < '0' || cmds[3][i] > '9')
				return false;
		period = stoi(cmds[3]);

		// options
		option |= option_ad;
		for(auto i = 4; i < cmds.size(); i++)
		{
			std::string cmd = cmds[i];
			if(cmd[0] == '-') // option flag
			{
				if(cmd[1] != 'm' && cmd[1] != 'n' && cmd[1] != 't') // wrong flag
					return false;
				if(cmd[1] == 'm')
					option |= option_am;
				else if(cmd[1] == 'n')
				{
					option |= option_an;
					if(i+1 >= cmds.size()) return false;
					for(auto j = 0; j < cmds[i+1].length(); j++)
						if(cmds[i+1][j] < '0' || cmds[i+1][j] > '9') return false;
					maximum_file_numbers = stoi(cmds[i+1]);
					i++;
				}
				else if(cmd[1] == 't')
				{
					option |= option_at;
					if(i+1 >= cmds.size()) return false;
					for(auto j = 0; j < cmds[i+1].length(); j++)
						if(cmds[i+1][j] < '0' || cmds[i+1][j] > '9') return false;
					store_time = stoi(cmds[i+1]);
					i++;
				}
			}
			else
				return false;
		}

		return true;
	}

	path = std::filesystem::path(cmds[1]);
	if(std::filesystem::exists(path) != true)
		return false;
	path = std::filesystem::absolute(path);
	for(auto i = 0; i < cmds[2].length(); i++)
		if(cmds[2][i] < '0' || cmds[2][i] > '9')
			return false;
	period = stoi(cmds[2]);

	// options
	for(auto i = 3; i < cmds.size(); i++)
	{
		std::string cmd = cmds[i];
		if(cmd[0] == '-') // option flag
		{
			if(cmd[1] != 'm' && cmd[1] != 'n' && cmd[1] != 't' && cmd[1] != 'd') // wrong
				return false;
			if(cmd[1] == 'm')
				option |= option_am;
			else if(cmd[1] == 'n')
			{
				option |= option_an;
				if(i+1 >= cmds.size()) return false;
				for(auto j = 0; j < cmds[i+1].length(); j++)
					if(cmds[i+1][j] < '0' || cmds[i+1][j] > '9') return false;
				maximum_file_numbers = stoi(cmds[i+1]);
				i++;
			}
			else if(cmd[1] == 't')
			{
				option |= option_at;
				if(i+1 >= cmds.size()) return false;
				for(auto j = 0; j < cmds[i+1].length(); j++)
					if(cmds[i+1][j] < '0' || cmds[i+1][j] > '9') return false;
				store_time = stoi(cmds[i+1]);
				i++;
			}
			else
			{
				option |= option_ad;
				if(std::filesystem::is_directory(path) != true) return false;
			}
		}
		else
			return false;
	}
	
	if(!(option & option_ad))
		if(std::filesystem::is_regular_file(path) != true) return false;
	return true;
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

Program::~Program()
{
	for(auto& ele : _table) erase_worker(ele.first);
}