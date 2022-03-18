#include "header.h"

Worker::Worker(const std::filesystem::path& p,int period,int opt,int mfn,int st,std::string_view cmd) : _absolute_path(p), _period(period), _option(opt), _maximum_file_numbers(mfn), _time(st) { }

void Worker::operator()() // backup thread 
{
	struct tm cur_tm;
	time_t cur_time;
	long long start;
	std::string relative_path = get_relative_path();
	int cur_year,cur_month,cur_day,cur_hour,cur_minute,cur_second;
	auto init_mtime = std::filesystem::last_write_time(_absolute_path);
	std::filesystem::path backup(std::filesystem::current_path()/"BACKUP");
	std::queue<std::pair<std::filesystem::path,long long>> q; // [백업한 파일 이름, 백업한 시점]

	cur_time = time(nullptr);
	localtime_r(&cur_time,&cur_tm);

	cur_year = cur_tm.tm_year+1900;
	cur_month = cur_tm.tm_mon+1;
	cur_day = cur_tm.tm_mday;
	cur_hour = cur_tm.tm_hour;
	cur_minute = cur_tm.tm_min;
	cur_second = cur_tm.tm_sec;
	start = get_time(cur_year,cur_month,cur_day,cur_hour,cur_minute,cur_second);

	// TODO : 시작하기 전에 이전에 있는 파일들 정리 
	
	while(true)
	{
		long long cur;

		cur_time = time(nullptr);
		localtime_r(&cur_time,&cur_tm);

		cur_year = cur_tm.tm_year+1900;
		cur_month = cur_tm.tm_mon+1;
		cur_day = cur_tm.tm_mday;
		cur_hour = cur_tm.tm_hour;
		cur_minute = cur_tm.tm_min;
		cur_second = cur_tm.tm_sec;
		cur = get_time(cur_year,cur_month,cur_day,cur_hour,cur_minute,cur_second);

		// period마다 백업 수행
		if(start+static_cast<long long>(_period) <= cur)
		{
			int year = cur_year%100;
			int q_size = static_cast<int>(q.size());
			std::string backup_time = "";
			std::string file_name = "";

			backup_time = get_backup_time(year,cur_month,cur_day,cur_hour,cur_minute,cur_second);
			file_name = backup.string()+"/"+relative_path+"_"+backup_time;	

			if(_option & option_am) // mtime이 바뀌었을 때마다 수행
			{
				auto new_mtime = std::filesystem::last_write_time(_absolute_path);
				if(init_mtime == new_mtime) 
				{
					start = start+_period;
					continue;
				}
				init_mtime = new_mtime;
			}
			
			if(_option & option_an) // 백업한 파일들의 최대 개수 (최근 maximum_file_numbers 개를 제외하곤 모두 삭제)
			{
				while(!q.empty() && q_size > _maximum_file_numbers)
				{
					auto file_path = q.front().first;
					std::filesystem::remove(file_path);
					q.pop();
				}
			}
			if(_option & option_at) // 보관한 시간이 _time을 넘어가면 삭제
			{
				while(!q.empty())
				{
					auto file_path = q.front().first;
					auto store_time = q.front().second;
					long long diff = cur-store_time;

					if(diff > static_cast<long long>(_time))
					{
						std::filesystem::remove(file_path);
						q.pop();
						continue;
					}
					break;
				}
			}

			// TODO : logger
			try {
				std::filesystem::copy_file(_absolute_path,file_name);
			} catch(std::filesystem::filesystem_error & e)
			{
				// logger error message
				start = start+_period;
				continue;
			}

			q.push({file_name,cur});
			start = start+_period;
		}
	}
}

std::string Worker::get_relative_path()
{
	std::string result = "";
	std::string abs_path = _absolute_path.string();
	
	while(abs_path.length() > 0 && abs_path.back() != '/')
	{
		result.push_back(abs_path.back());
		abs_path.pop_back();
	}

	std::reverse(result.begin(),result.end());
	return result;
}

long long Worker::get_time(int& year,int& month,int& day,int& hour,int& minute,int& second)
{
	long long result = 0;

	result += (year*60*60*24*12);
	result += (month*60*60*24);
	result += (day*60*60*24);
	result += (hour*60*60);
	result += (minute*60);
	result += second;

	return result;
}

std::string Worker::get_backup_time(int& year,int& month,int& day,int& hour,int& minute,int& second)
{
	std::string str_year = std::to_string(year);
	std::string str_month = std::to_string(month);
	std::string str_day = std::to_string(day);
	std::string str_hour = std::to_string(hour);
	std::string str_minute = std::to_string(minute);
	std::string str_second = std::to_string(second);

	if(str_year.length() < 2) str_year = "0"+str_year;
	if(str_month.length() < 2) str_month = "0"+str_month;
	if(str_day.length() < 2) str_day = "0"+str_day;
	if(str_hour.length() < 2) str_hour = "0"+str_hour;
	if(str_minute.length() < 2) str_minute = "0"+str_minute;
	if(str_second.length() < 2) str_second = "0"+str_second;
	
	return str_year+str_month+str_day+str_hour+str_minute+str_second;
}
