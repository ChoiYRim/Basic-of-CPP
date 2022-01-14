#include <iostream>
#include <string>

template <typename T>
void print(T arg)
{
    std::cout << arg << std::endl;
}

template <typename T,typename... Types>
void print(T arg,Types... args)
{
    std::cout << arg << ", ";
    print(args...);
}

template <typename String>
std::string StrCat(const String& s)
{
    return std::string(s)+std::string("\n");
}

template <typename String,typename... Strings>
std::string StrCat(const String& s,Strings... ss)
{
    return std::string(s)+StrCat(ss...);
}

int sum_all() { return 0; }

template <typename... Ints>
int sum_all(int num,Ints... nums)
{
    return num + sum_all(nums...);
}

template <typename... Ints>
double average(Ints... nums)
{
    return static_cast<double>(sum_all(nums...)) / sizeof...(nums);
}

int main()
{
    std::cout << "------ 가변인자 템플릿을 이용한 print함수 구현 ------" << std::endl;
    print(1,3.1,"ABC");
    print(1,2,3,4,5,6,7);
    
    std::cout << "------ 가변인자 템플릿을 이용한 strcat함수 구현 ------" << std::endl;
    std::cout << StrCat(std::string("this")," ","is"," ",std::string("a")," ",std::string("sentence."));
    
    std::cout << "------ 가변인자 템플릿을 이용한 average함수 구현 ------" << std::endl;
    std::cout << average(1,4,2,3,10) << std::endl;
    return 0;
}
