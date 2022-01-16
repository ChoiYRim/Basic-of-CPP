#include <vector>
#include <cstring>
#include <iostream>

class MyString
{
    char* string_content;
    int string_length;
    int memory_capacity;
    
public:
    MyString();
    
    MyString(const char* str);
    
    MyString(const MyString& str);
    
    MyString(MyString&& str) noexcept;
    
    void reserve(int size);
    
    MyString operator+(const MyString& s);
    MyString& operator=(const MyString& s);
    
    ~MyString();
    
    int length() const;
    
    void print();
    void println();
    
    friend MyString operator+(const MyString& s1,const MyString& s2);
    friend void swap(MyString& lhs,MyString& rhs);
    friend std::ostream& operator<<(std::ostream& os,const MyString& s);
};

MyString::MyString()
{
    std::cout << "일반 생성자 호출!" << std::endl;
    string_length = 0;
    memory_capacity = 0;
    string_content = nullptr;
}

MyString::MyString(const char* str)
{
    std::cout << "일반 생성자 호출!" << std::endl;
    string_length = static_cast<int>(strlen(str));
    memory_capacity = string_length;
    
    string_content = new char[string_length];
    for(int i = 0; i < string_length; i++)
        string_content[i] = str[i];
}

MyString::MyString(const MyString& str)
{
    std::cout << "복사 생성자 호출!" << std::endl;
    string_length = str.string_length;
    memory_capacity = str.memory_capacity;
    
    string_content = new char[string_length];
    for(int i = 0; i < string_length; i++)
        string_content[i] = str.string_content[i];
}

MyString::MyString(MyString&& str) noexcept
{
    std::cout << "이동 생성자 호출!" << std::endl;
    string_length = str.string_length;
    string_content = str.string_content;
    memory_capacity = str.memory_capacity;
    
    // 임시 객체 소멸 시에 메모리를 해제하지 못하게 한다.
    str.string_content = nullptr;
}

MyString::~MyString() { delete[] string_content; }

void MyString::reserve(int size)
{
    if(size > memory_capacity)
    {
        char* prev_string_content = string_content;
        
        string_content = new char[size];
        memory_capacity = size;
        
        for(int i = 0; i < string_length; i++)
            string_content[i] = prev_string_content[i];
        
        if(prev_string_content != nullptr)
            delete[] prev_string_content;
    }
}

MyString MyString::operator+(const MyString& s)
{
    MyString str;
    
    str.reserve(string_length+s.string_length);
    for(int i = 0; i < string_length; i++)
        str.string_content[i] = string_content[i];
    for(int i = 0; i < s.string_length; i++)
        str.string_content[string_length+i] = s.string_content[i];
    str.string_length = string_length + s.string_length;
    
    return str;
}

MyString& MyString::operator=(const MyString &s)
{
    std::cout << "복사!" << std::endl;
    if(s.string_length > memory_capacity)
    {
        delete [] string_content;
        string_content = new char[s.string_length];
        memory_capacity = s.string_length;
    }
    
    string_length = s.string_length;
    if(string_content == nullptr)
        string_content = new char[string_length];
    for(int i = 0; i < string_length; i++)
        string_content[i] = s.string_content[i];
    
    return *this;
}

int MyString::length() const { return string_length; }

void MyString::print()
{
    for(int i = 0; i < string_length; i++)
        std::cout << string_content[i];
}

void MyString::println()
{
    print();
    std::cout << std::endl;
}

MyString operator+(const MyString& s1,const MyString& s2)
{
    MyString str;
    
    str.reserve(s1.string_length+s2.string_length);
    for(int i = 0; i < s1.string_length; i++)
        str.string_content[i] = s1.string_content[i];
    for(int i = 0; i < s2.string_length; i++)
        str.string_content[s1.string_length+i] = s2.string_content[i];
    str.string_length = s1.string_length + s2.string_length;
    
    return str;
}

void swap(MyString& lhs,MyString& rhs)
{
    std::swap(lhs.memory_capacity,rhs.memory_capacity);
    std::swap(lhs.string_length,rhs.string_length);
    std::swap(lhs.string_content,rhs.string_content);
}

std::ostream& operator<<(std::ostream& os,const MyString& s)
{
    return os << s.string_content;
}

template <typename T>
void my_swap(T& a,T& b)
{
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}


int main()
{
    MyString str1("abc");
    MyString str2("def");
    std::cout << "Swap 전 ----" << std::endl;
    std::cout << str1 << std::endl;
    std::cout << str2 << std::endl;
    
    std::cout << "Swap 후 ---" << std::endl;
    //swap(str1,str2);
    my_swap(str1,str2);
    std::cout << str1 << std::endl;
    std::cout << str2 << std::endl;
    
    return 0;
}
