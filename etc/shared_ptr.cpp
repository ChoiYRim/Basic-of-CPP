#include <iostream>
#include <memory>

class Simple
{
	public:
		Simple() 
		{ 
			std::cout << "Simple constructor called..." << '\n'; 
		}

		~Simple() 
		{ 
			std::cout << "Simple destructor called..." << '\n'; 
		}

	private:
		int mData;
};

//void double_delete()
//{
//	Simple* simple = new Simple();
//	std::shared_ptr<Simple> share1(simple);
//	std::shared_ptr<Simple> share2(simple);
//}

void no_double_delete()
{
	auto share1 = std::make_shared<Simple>();
	std::shared_ptr<Simple> share2(share1); 

	std::cout << "share1 : " << share1.get() << '\n';
	std::cout << "share2 : " << share2.get() << '\n';
	std::cout << "Count : " << share1.use_count() << '\n';
}

int main()
{
//	std::cout << "test double delete()" << '\n';
//	double_delete();

	std::cout << "test no double delete()" << '\n';
	no_double_delete();

	return 0;
}
