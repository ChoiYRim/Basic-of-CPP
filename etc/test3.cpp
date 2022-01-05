#include <exception>
#include <iostream>
#include <string_view>
#include <string>

class MyException : public std::exception
{
	public:
		MyException(std::string_view message) : mMessage(message) { }
		virtual const char* what() const noexcept override
		{
			return mMessage.c_str();
		}

	private:
		std::string mMessage;
};

void doSomething()
{
	try
	{
		throw std::runtime_error("Throwing a runtime_error exception");
	}
	catch(const std::runtime_error& e)
	{
		std::cout << __func__ << " caught a runtime error" << std::endl;
		std::cout << __func__ << " throwing MyException" << std::endl;
		throw_with_nested(MyException("MyException with nested runtime error"));
	}
}

int main()
{
	try
	{
		doSomething();
	}
	catch(const MyException& e)
	{
		std::cout << __func__ << " caught Myexception: " << e.what() << std::endl;
		const auto* pNested = dynamic_cast<const std::nested_exception*>(&e);

		if(pNested)
		{
			try
			{
				pNested->rethrow_nested();
			}
			catch(const std::runtime_error& e)
			{
				std::cout << " Nested exception: " << e.what() << std::endl;
			}
		}
	}
	return 0;
}
