#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>

struct comp
{
    comp() = default;
    
    bool operator()(const int& n)
    {
        int num = n;
        while(num != 0)
        {
            int cur = num%10;
            if(cur != 0 && cur % 3 == 0 && cur / 3 <= 1)
                return true;
            num /= 10;
        }
        return false;
    }
};

void setVector(std::vector<int>& v)
{
    for(int i = 0; i < 10000; i++)
    {
        v.push_back(i);
    }
}

void printVector(const std::vector<int>& v)
{
    for(int i = 0; i < (int)v.size(); i++)
        std::cout << v[i] << ' ';
    std::cout << std::endl;
}

int main()
{
    std::vector<int> v1,v2;
    std::chrono::system_clock::time_point begin,end;
    
    setVector(v1);
    setVector(v2);
    
    begin = std::chrono::system_clock::now();
    for(int i = 0; i < (int)v1.size(); i++)
    {
        bool chk = false;
        int num = v1[i];
        
        while(num != 0)
        {
            int cur = num%10;
            if(cur != 0 && cur % 3 == 0 && cur / 3 <= 1)
            {
                chk = true;
                break;
            }
            num /= 10;
        }
        if(chk)
        {
            v1.erase(v1.begin()+i);
            i--;
        }
    }
    end = std::chrono::system_clock::now();
    auto result1 = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    
    begin = std::chrono::system_clock::now();
    v2.erase(std::remove_if(v2.begin(),v2.end(),comp()),v2.end());
    end = std::chrono::system_clock::now();
    auto result2 = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    
    //printVector(v1);
    
    std::cout << "result without std::remove_if() : " << result1.count() << std::endl;
    std::cout << "result with std::remove_if() : " << result2.count() << std::endl;
    return 0;
}
