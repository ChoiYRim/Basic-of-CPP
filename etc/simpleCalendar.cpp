#include <iostream>

using namespace std;

int ty,tm; // target year , month , day

// sunday ~ saturday : 0 ~ 6

bool leapYear(int year)
{
    if(((year % 4 == 0) && !(year % 100 == 0)) || (year % 400 == 0))
        return true;
    else
        return false;
}

int getDaysOfMonth(int month,int year)
{
    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;
    else if(month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    return (leapYear(year) ? 29 : 28);
}

// 1.1 is a monday (1)
int main(int argc,char* argv[])
{
    int totalDays = 0;
    
    cin >> ty >> tm;
    
    for(int year = 0; year < ty; year++)
    {
        if(!leapYear(year))
            totalDays+=365;
        else
            totalDays+=366;
    }
    
    for(int month = 1; month < tm; month++)
        totalDays += getDaysOfMonth(month,ty);
    
    cout << (totalDays-1)%7 << '\n';
    cout << "SUN " << "MON " << "TUE " << "WED " << "THR " << "FRI " << "SAT\n";
    if((totalDays-1)%7 != 0)
        for(int i = 0; i < (totalDays-1)%7; i++)
            cout << '\t';
        
    for(int day = 1; day <= getDaysOfMonth(tm, ty); day++)
    {
        cout << day << '\t';
        totalDays++;
        if((totalDays-1)%7 == 0)
            cout << '\n';
    }
    cout << '\n';
    return 0;
}

