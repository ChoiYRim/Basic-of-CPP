#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

std::vector<std::string> split(std::string& str)
{
    size_t idx = 0,pos = 0;
    std::vector<std::string> ret;
    
    while(str.back() == ' ')
        str.pop_back();
    while((pos = str.find(' ',idx)) != std::string::npos)
    {
        std::cout << "pos: " << pos << "\t";
        std::cout << "idx: " << idx << std::endl;

        if(pos+1 != std::string::npos && str[idx] == ' ')
        {
            idx++;
            continue;
        }

        ret.push_back(str.substr(idx,pos-idx));
        idx = pos+1;
    }

    ret.push_back(str.substr(idx,pos-idx));
    return ret;
}

void print_vector(const std::vector<std::string>& v)
{
    for(auto& str : v)
        std::cout << str << std::endl;
}

void show_string(const std::string& str)
{
    for(size_t i = 0; i < str.length(); i++)
        printf("%2zu ", i);
    printf("\n");
    for(size_t i = 0; i < str.length(); i++)
        printf("%2c ", str[i]);
    printf("\n");
}

int main(int argc,char* argv[])
{
    std::string str = "This       is a example string   ";
    show_string(str);
    auto words = split(str);
    print_vector(words);
    return 0;
}

