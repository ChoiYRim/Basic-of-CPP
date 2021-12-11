#include <array>
#include <iostream>
#include <type_traits> // this library offers many APIs to sort the argument's data type

template <typename ... Args> // variable factors template
auto build_array(Args&& ... args) -> std::array<typename std::common_type<Args...>::type, sizeof ...(args)>
{
	using commonType = typename std::common_type<Args ...>::type;
	return {std::forward<commonType>((Args&&)args)...};
}

int main(int argc,char* argv[])
{
	auto data = build_array(1,0u,'a',3.2f,false);

	for(auto i : data)
		std::cout << i << ' ';
	std::cout << '\n';
	return 0;
}
