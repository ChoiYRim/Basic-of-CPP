#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

template <typename T>
auto compute_waiting_times(std::vector<T>& service_times)
{
    std::vector<T> W(service_times.size());
    W[0] = 0;
    
    for(auto i = 1; i < service_times.size(); i++)
        W[i] = W[i-1] + service_times[i-1]; // 현재 i번째 사람이 기다려야 하는 시간은 이전 사람의 서비스 시간 + 내 작업 시간
    
    return W;
}

template <typename T>
void print_vector(const std::vector<T>& V)
{
    for(auto& i : V)
    {
        std::cout.width(2);
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void compute_and_print_waiting_times(std::vector<T>& service_times)
{
    auto waiting_times = compute_waiting_times(service_times);
    
    std::cout << "- 처리 시간: ";
    print_vector<T>(service_times);
    
    std::cout << "- 대기 시간: ";
    print_vector<T>(waiting_times);
    
    auto ave_waiting_times = std::accumulate(waiting_times.begin(), waiting_times.end(), 0.0) / waiting_times.size();
    std::cout << "- 평균 대기 시간: " << ave_waiting_times << std::endl;
}

int main(int argc,char* argv[])
{
    std::vector<int> service_times {8,1,2,4,9,2,3,5};
    
    std::cout << "[처음 일 처리 시간 & 대기 시간]" << std::endl;
    compute_and_print_waiting_times<int>(service_times);
    
    std::sort(service_times.begin(),service_times.end());
    
    std::cout << std::endl;
    std::cout << "[정렬 후 일 처리 시간 & 대기 시간]" << std::endl;
    compute_and_print_waiting_times(service_times);
    
    return 0;
}
