#include <iostream>

bool isPrime(int n)
{
    if(n == 2) return true;
    if(n == 3) return true;
    
    for(int i = 2; i <= n; i++)
        if(n % i == 0)
            return false;
    
    return true;
}

template <int N>
struct INT
{
    static const int num = N;
};

template <typename a,typename b>
struct add
{
    typedef INT<a::num + b::num> result;
};

template <typename a,typename b>
struct divide
{
    typedef INT<a::num / b::num> result;
};

using one = INT<1>;
using two = INT<2>;
using three = INT<3>;

template <typename N, typename d>
struct check_div
{
    static const bool result = (N::num % d::num == 0) || check_div<N,typename add<d,one>::result>::result;
};

template <typename N>
struct prime
{
    static const bool result = !check_div<N,two>::result;
};

template <>
struct prime<two>
{
    static const bool result = true;
};

template <>
struct prime<three>
{
    static const bool result = true;
};

template <typename N>
struct check_div<N,typename divide<N,two>::result>
{
    static const bool result = (N::num % (N::num/2) == 0);
};


int main()
{
    std::cout << std::boolalpha;
    
    std::cout << "Is 2 prime ? :: " << prime<INT<2>>::result << std::endl;
    std::cout << "Is 10 prime ? :: " << prime<INT<10>>::result << std::endl;
    std::cout << "Is 11 prime ? :: " << prime<INT<11>>::result << std::endl;
    std::cout << "Is 61 prime ? :: " << prime<INT<61>>::result << std::endl;
    return 0;
}
