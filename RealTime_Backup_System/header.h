#ifndef _REALTIME_BACKUP_SYSTEM_
#define _REALTIME_BACKUP_SYSTEM_

#include <unordered_map>
#include <string_view>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <memory>
#include <thread>
#include <mutex>
#include <list>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

const size_t kbuffer_length = 1024;

enum
{
	ADD = 0,
	REMOVE,
	COMPARE,
	RECOVER,
	LIST
};

//inline bool is_ascii(int ch) { return (ch >= 0 && ch <= 127); }

class Worker;
class Logger;

class Program
{
	public:
		Program() = default;

		void start();
		
		int add(const std::vector<std::string>& cmds);

		int remove(const std::vector<std::string>& cmds);

		int compare(const std::vector<std::string>& cmds);

		int recover(const std::vector<std::string>& cmds);

		int list(const std::vector<std::string>& cmds);

		void general_command(const std::vector<std::string>& cmds);

		virtual ~Program() = default;

	private:
		std::vector<std::string> split_commands(const std::string& input);
		bool spawn_worker(int types,const std::vector<std::string>& cmds);
		std::unordered_map<std::string,std::unique_ptr<std::thread>> _table;
};

class Worker
{
	public:
		Worker() : _period(10), _option(0), _maximum_file_numbers(100) { }

		Worker(std::filesystem::path& p,int period,int opt,int mfn,int st,std::string_view cmd);

		void operator()(); 

		virtual ~Worker() = default;

	private:
		std::filesystem::path _absolute_path;
		int _period;
		int _option; // bit masking
		int _maximum_file_numbers;
		int _time;
};

class Logger
{
	public:
		Logger() = default;

		virtual ~Logger() = default;

	private:
};

#endif
