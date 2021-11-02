#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

class MyString
{
private:
    char* string_content; // 문자열 데이터를 가리키는 포인터
    int string_length; // 문자열 길이
    int memory_capacity; // 현재 할당된 공간의 크기(바이트)
    
public:
    MyString(char c);
    
    explicit MyString(int capacity);
    
    MyString(const char* str);
    
    MyString(const MyString& str);
    
    ~MyString();
    
    int length() const;
    
    int capacity() const;
    
    char* get_string() const;
    
    void print() const;
    
    void println() const;
    
    MyString& assign(const char* str);
    
    MyString& assign(const MyString& str);
    
    void reserve(int size);
    
    MyString& insert(int loc,const char* str);
    
    MyString& insert(int loc,const MyString& str);
    
    MyString& insert(int loc,char c);
    
    MyString& erase(int loc,int num);
    
    int find(int find_from,MyString& str) const;
    
    int find(int find_from,const char* str) const;
    
    int find(int find_from,char c) const;
    
    int compare(const MyString& str) const;
    
    bool operator==(MyString& str);
    
    bool operator!=(MyString& str);
    
    bool operator=(const MyString& str);
    
    bool operator>(const MyString& str);
    
    bool operator<(const MyString& str);
    
    bool operator>=(const MyString& str);
    
    bool operator<=(const MyString& str);
    
    MyString operator+(const MyString& str);
    
    void pop_back();
    
    char& operator[](const int index);
    
    friend std::ostream& operator<<(std::ostream& os,const MyString& str); // 불완전
    
    friend std::istream& operator>>(std::istream& is,const MyString& str); // 불완전
};

MyString::MyString(char c)
{
    string_content = new char[1];
    string_content[0] = c;
    memory_capacity = 1;
}

MyString::MyString(int capacity)
{
    string_content = new char[capacity];
    string_length = 0;
    memory_capacity = capacity;
}

MyString::MyString(const char* str)
{
    string_length = (int)strlen(str);
    string_content = new char[string_length];
    strcpy(string_content,str);
    memory_capacity = string_length;
}

MyString::MyString(const MyString& str)
{
    char* tmp = str.get_string();
    
    string_length = str.length();
    string_content = new char[string_length];
    for(int i = 0; i < string_length; i++)
        string_content[i] = tmp[i];
    memory_capacity = string_length;
}

MyString::~MyString()
{
    delete[] string_content;
}

int MyString::length() const { return string_length; }

int MyString::capacity() const { return memory_capacity; }

char* MyString::get_string() const { return string_content; }

void MyString::print() const { std::cout << string_content; }

void MyString::println() const { std::cout << string_content << '\n'; }

MyString& MyString::assign(const char *str)
{
    // str이 의도한 값이 아니라면?
    if(!str)
    {
        std::cerr << "Error occured!\n";
        exit(0);
    }
    
    if(strlen(str) > memory_capacity)
        delete[] string_content;
    
    string_content = new char[strlen(str)];
    string_length = (int)strlen(str);
    for(int i = 0; i < string_length; i++)
        string_content[i] = str[i];
    memory_capacity = string_length;
    
    return *this;
}

MyString& MyString::assign(const MyString &str)
{
    if(!str.get_string())
    {
        std::cerr << "Error occured!\n";
        exit(0);
    }
    
    if(str.length() > memory_capacity)
        delete[] string_content;
    
    char* tmp = str.get_string();
    string_content = new char[str.length()];
    string_length = str.length();
    for(int i = 0; i < string_length; i++)
        string_content[i] = tmp[i];
    memory_capacity = string_length;
    
    return *this;
}

void MyString::reserve(int size)
{
    if(size > memory_capacity)
    {
        char* prev_string = string_content;
        
        string_content = new char[size];
        memory_capacity = size;
        
        for(int i = 0; i < string_length; i++)
            string_content[i] = prev_string[i];
        
        delete [] prev_string;
    }
}

MyString& MyString::insert(int loc,const char* str)
{
    MyString tmp(str);
    return insert(loc,tmp);
}

MyString& MyString::insert(int loc,const MyString& str)
{
    if(!str.get_string())
        return *this;
    
    if(loc < 0 || loc > string_length)
        return *this;
    if(string_length+str.length() > memory_capacity)
    {
        //memory_capacity = string_length+str.length(); // 비효율적임 : 만약에 메모리가 꽉찼는데 1바이트씩 계속 들어온다면?
        
        if(memory_capacity*2 > string_length+str.length())
            memory_capacity *= 2;
        else
            memory_capacity = string_length+str.length();
        
        int i;
        char* prev_string = string_content;
        string_content = new char[memory_capacity];
        
        for(i = 0; i < loc; i++)
            string_content[i] = prev_string[i];
        for(i = loc; i < loc+str.length(); i++)
            string_content[i] = str.get_string()[i-loc];
        for(i = loc+str.length(); i < memory_capacity; i++)
            string_content[i] = prev_string[i-str.length()];
        
        delete [] prev_string;
        
        string_length = string_length+str.length();
    
        return *this;
    }
    
    if(str.string_length <= 0)
    {
        if(!string_content)
            string_content = new char;
        return *this;
    }
    
    for(int i = string_length-1; i >= loc; i++)
        string_content[i+str.length()] = string_content[i];
    for(int i = 0; i < str.length(); i++)
        string_content[i+loc] = str.get_string()[i];
    string_length += str.length();
    
    return *this;
}

MyString& MyString::insert(int loc,char c)
{
    MyString tmp(c);
    return insert(loc,tmp);
}

MyString& MyString::erase(int loc,int num)
{
    if(num < 0 || loc < 0 || loc > string_length)
        return *this;
    
    if(num > string_length)
    {
        string_length = memory_capacity = 0;
        delete [] string_content;
        string_content = nullptr;
        return *this;
    }
    
    for(int i = loc+num; i < string_length; i++)
        string_content[i-num] = string_content[i];
    
    string_length -= num;
    return *this;
}

int MyString::find(int find_from,MyString& str) const
{

    /* 아래의 방식은 굉장히 naive한 방식 */

//    int i,j;
//
//    if(string_length <= 0)
//        return -1;
//
//    for(i = find_from; i <= string_length-str.length(); i++)
//    {
//        for(j = 0; j < str.length(); j++)
//        {
//            if(string_content[i+j] != str.get_string()[j])
//                break;
//        }
//
//        if(!(j-str.length()))
//            return i;
//    }
    
    // Boyer-Moore Algorithm
    
    int pos_idx,pos_txt,len;
    char* pattern = str.get_string();
    std::vector<int> skip(128,str.length());
    
    if(string_length <= 0 || find_from < 0)
        return -1;
    if(!pattern || str.length() <= 0)
        return -1;
    
    len = str.length();
    for(int i = 0; i < len; i++)
    {
        char ch = pattern[i];
        skip[ch] = std::min(skip[ch],len-i-1);
    }
    
    pos_txt = len-1;
    while(pos_txt < string_length)
    {
        pos_idx = len-1;
        while(string_content[pos_txt] == pattern[pos_idx])
        {
            if(!pos_idx)
                return pos_txt;
            pos_txt--;
            pos_idx--;
        }
        
        pos_txt += skip[string_content[pos_txt]];
    }
    
    return -1;
}

int MyString::find(int find_from,const char* str) const
{
    MyString tmp(str);
    return find(find_from,tmp);
}

int MyString::find(int find_from,char c) const
{
    MyString tmp(c);
    return find(find_from,tmp);
}

int MyString::compare(const MyString& str) const
{
    return strcmp(string_content,str.get_string());
}

bool MyString::operator==(MyString& str)
{
    return !compare(str);
}

bool MyString::operator!=(MyString& str)
{
    return (compare(str) ? true : false);
}

bool MyString::operator=(const MyString& str)
{
    if(str.capacity() <= 0)
        return false;
    if(string_content != nullptr)
        delete [] string_content;
    
    string_length = str.length();
    memory_capacity = string_length;
    string_content = new char[memory_capacity];
    strcpy(string_content, str.get_string());
    return true;
}

bool MyString::operator>(const MyString& str)
{
    if(compare(str) < 0)
        return true;
    return false;
}

bool MyString::operator<(const MyString& str)
{
    if(compare(str) > 0)
        return true;
    return false;
}

bool MyString::operator>=(const MyString& str)
{
    if(compare(str) <= 0)
        return true;
    return false;
}

bool MyString::operator<=(const MyString& str)
{
    if(compare(str) >= 0)
        return true;
    return false;
}

MyString MyString::operator+(const MyString& str)
{
    MyString tmp(strcat(string_content,str.get_string()));
    return tmp;
}

void MyString::pop_back()
{
    if(memory_capacity <= 0 || string_length <= 0)
        return;
    
    char* tmp = new char[string_length-1];
    for(int i = 0; i < string_length-1; i++)
        tmp[i] = string_content[i];
    
    delete[] string_content;
    
    string_content = new char[string_length-1];
    strcpy(string_content,tmp);
    memory_capacity = string_length-1;
    string_length -= 1;
}

MyString operator+(const MyString& str1,const MyString& str2)
{
    MyString tmp(str1);
    return tmp.operator+(str2);
}

char& MyString::operator[](const int index)
{
    if(memory_capacity >= index)
        return string_content[index];
    std::cerr << "Invalid index referred...\n";
    exit(1);
}

std::ostream& operator<<(std::ostream& os,const MyString& str)
{
    os << str.string_content;
    os << "\n";
    return os;
}

std::istream& operator>>(std::istream& is,const MyString& str)
{
    /* 미완성 */
    
    return is;
}

int main()
{
    MyString str1("very very very long string");
    MyString str2("very long");
    str1.reserve(32);
    
    if(str1 == str2)
        std::cout << "str1 and str2 is same" << '\n';
    else
        std::cout << "str1 and str2 is not same" << '\n';
    
    if(str1 != str2)
        std::cout << "str1 and str2 is not same" << '\n';
    else
        std::cout << "str1 and str2 is same" << '\n';
    
    std::cout << "Capacity : " << str1.capacity() << '\n';
    std::cout << "String length : " << str1.length() << '\n';
    str1.println();
    std::cout << str1[1] << '\n';
    
    str1 = str2;
    //str1.println();
    
    str1 = str1+" "+str2;
    //str1.println();
    
    //std::cin >> str1;
    //std::cout << str1;
    
    str1.pop_back();
    //str1.println();
    std::cout << str1;
    
    std::cout << "Location of 'str2' in the string : "
    << str1.find(0,str2) << '\n';
    
    std::cout << "compare str1 with str2 : " << str1.compare(str2) << '\n';
    return 0;
}
