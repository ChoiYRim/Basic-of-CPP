#include <vector>
#include <string>
#include <iostream>

std::vector<std::string> parseString(const std::string& str)
{
    size_t pos = 0,idx = 0;
    std::vector<std::string> ret;
    std::string delimiter = " ";
    
    while((pos = str.find(delimiter,idx)) != std::string::npos)
    {
        if(pos+1 != std::string::npos && s[idx] == delimiter)
        {
            idx++;
            continue;
        }
        
        std::string tmp = str.substr(idx,pos-idx);
        ret.push_back(tmp);
        idx = pos+1;
    }
    
    ret.push_back(str.substr(idx,pos));
    return ret;
}

template<typename T>
void printVector(const std::vector<T>& v)
{
    for(auto ele : v)
        std::cout << ele << std::endl;
}

int main()
{
    std::vector<std::string> v;
    std::string str = "I am about to parse this string";
    
    v = parseString(str);
    printVector(v);
    return 0;
}
