#include "heap.h"
//#include <queue>

void printVector(const std::vector<int>& v)
{
    for(auto i : v)
        std::cout << i << ' ';
    std::cout << std::endl;
}

void test(const std::vector<int>& v)
{
    auto great = [](const int& i1,const int& i2){
        return i1 > i2;
    };
    
    std::vector<int> result = v;
    std::make_heap(result.begin(),result.end(),great);
    printVector(result);
    std::pop_heap(result.begin(), result.end(),great);
    printVector(result);
    
//    std::priority_queue<int,std::vector<int>,std::less<int>> pq;
//    for(auto i : v)
//        pq.push(i);
//
//    while(!pq.empty())
//    {
//        std::cout << pq.top() << '\n';
//        pq.pop();
//    }
}

int main()
{
    std::vector<int> v1 = {1,3,8,15,105};
    std::vector<int> v2 = {2,3,10,11,16,20,25};
    std::vector<int> v3 = {-2,100,1000};
    std::vector<int> v4 = {-1,0,14,18};
    auto result = merge({v1,v2,v3,v4});
    printVector(result);
    
    //test(v1);
    return 0;
}
