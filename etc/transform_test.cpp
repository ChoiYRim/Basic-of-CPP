#include <vector>
#include <iostream>
#include <algorithm>

void setVector(std::vector<int>& v)
{
    for(int i = 0; i < 1000; i++)
    {
        v.push_back(i);
    }
}

void printVector(const std::vector<int>& v)
{
    for(auto i : v)
        std::cout << i << ' ';
    std::cout << std::endl;
}

int main()
{
    std::vector<int> v;
    auto add = [](const int& i) {
        return i*2;
    };
    
    setVector(v);
    std::transform(v.begin(),v.end(),v.begin(), add);
    printVector(v);
    return 0;
}
