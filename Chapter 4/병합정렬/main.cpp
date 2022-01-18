#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

const int kLimit = 10000;

void insert_random_numbers(std::vector<int>& v)
{
    std::random_device rd; // get a number from my HW
    std::mt19937 rand(rd()); // make a random number with MT19937
    std::uniform_int_distribution<std::mt19937::result_type> range(0,kLimit);
    
    for(int i = 0; i < kLimit; i++)
    {
        v.push_back(range(rand));
    }
}

std::vector<int> merge(std::vector<int> v1,std::vector<int> v2)
{
    std::vector<int> merged;
    auto left_it = v1.begin();
    auto right_it = v2.begin();
    
    while(left_it != v1.end() && right_it != v2.end())
    {
        if(*left_it < *right_it)
        {
            merged.emplace_back(*left_it);
            left_it++;
        }
        else
        {
            merged.emplace_back(*right_it);
            right_it++;
        }
    }
    
    for(; left_it != v1.end(); left_it++)
        merged.emplace_back(*left_it);
    for(; right_it != v2.end(); right_it++)
        merged.emplace_back(*right_it);
    
    return merged;
}

std::vector<int> merge_sort(std::vector<int> v)
{
    if(v.front() != v.back())
    {
        auto mid = v.size() / 2;
        auto left = merge_sort(std::vector<int>(v.begin(),v.begin()+mid));
        auto right = merge_sort(std::vector<int>(v.begin()+mid,v.end()));
        
        return merge(left,right);
    }
    
    return v;
}

int main(int argc,char* argv[])
{
    std::chrono::system_clock::time_point begin,end;
    std::vector<int> v,sorted;
    
    begin = std::chrono::system_clock::now();
    insert_random_numbers(v);
    sorted = merge_sort(v);
    end = std::chrono::system_clock::now();
    auto result = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    std::cout << "병합 정렬 시간 : " << result.count() << std::endl;
    
    v.clear(); sorted.clear();
    
    begin = std::chrono::system_clock::now();
    insert_random_numbers(v);
    std::sort(v.begin(),v.end());
    end = std::chrono::system_clock::now();
    result = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    std::cout << "std::sort 시간 : " << result.count() << std::endl;
    return 0;
}
