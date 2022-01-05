#include <iostream>

class Base
{
	public:
		Base() 
		{
			std::cout << "Base constructor" << '\n';
		}
		virtual ~Base() 
		{
			std::cout << "Base destructor" << '\n';
		}
};

class Derived : public Base
{
	public:
		Derived()
		{
			mString = new char[32];
			std::cout << "Derived constructor" << '\n';
			std::cout << "mString allocated..." << '\n';
		}

		~Derived()
		{
			delete[] mString;
			std::cout << "Derived destructor" << '\n';
			std::cout << "mString deallocated..." << '\n';
		}

	private:
		char* mString;
};

int main(int argc,char* argv[])
{
	Base* myBase = new Derived();
	delete myBase;
	return 0;
}
