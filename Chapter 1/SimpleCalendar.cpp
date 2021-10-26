#include <ctime>
#include <iostream>

class Date
{
private:
    int year_;
    int month_;
    int day_;
    
public:
    void SetDate(int year,int month,int date);
    void AddDay(int inc);
    void AddMonth(int inc);
    void AddYear(int inc);
    
    int GetCurrentMonthTotalDays(int year,int month);
    
    void ShowDate();
    
    // Date() = default; // define a default constructor - since C++11
    
    Date()
    {
        year_ = 1;
        month_ = 1;
        day_ = 1;
    }
    Date(int year,int month,int day)
    {
        year_ = year;
        month_ = month;
        day_ = day;
    }
};

void Date::ShowDate()
{
    std::cout << year_ << "." << month_ << "." << day_ << '\n';
}

void Date::SetDate(int year, int month, int date)
{
    year_ = year;
    month_ = month;
    day_ = date;
}

int Date::GetCurrentMonthTotalDays(int year, int month)
{
    static int month_day[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    if(month != 2)
        return month_day[month-1];
    else if(!(year % 4) && !(year % 100)) // leap year
        return 29;
    return 28;
}

void Date::AddDay(int inc)
{
    while(true)
    {
        int current_month_total_days = GetCurrentMonthTotalDays(year_, month_);
        
        if(day_ + inc <= current_month_total_days)
        {
            day_ += inc;
            return;
        }
        else
        {
            inc -= (current_month_total_days - day_ + 1);
            day_ = 1;
            AddMonth(1);
        }
    }
}

void Date::AddMonth(int inc)
{
    AddYear((inc + month_ -1) / 12);
    month_ = month_ + inc % 12;
    month_ = (month_ == 12 ? 12 : month_% 12);
}

void Date::AddYear(int inc)
{
    year_ += inc;
}

int main(void)
{
    struct tm CurrentTimeStructure;
    time_t cur_time = time(nullptr);
    
    localtime_r(&cur_time,&CurrentTimeStructure);
    int current_year = CurrentTimeStructure.tm_year + 1900;
    int current_month = CurrentTimeStructure.tm_mon + 1;
    int current_day = CurrentTimeStructure.tm_mday;
    Date day(current_year,current_month,current_day);
    
    day.ShowDate();
    day.AddYear(10);
    day.ShowDate();
    return 0;
}
