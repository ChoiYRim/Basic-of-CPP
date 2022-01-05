#include <string>
#include <iostream>

class Book
{
	public:
		virtual ~Book() = default;
		virtual std::string getDescription() const { return "Book"; }
		virtual int getHeight() const { return 120; }
};

class Paperback : public Book
{
	public:
		virtual std::string getDescription() const override
		{
			return "Paperback " + Book::getDescription();
		}
};

class Romance : public Paperback
{
	public:
		virtual std::string getDescription() const override
		{
			return "Romance " + Paperback::getDescription();
		}
		virtual int getHeight() const override
		{
			return Paperback::getHeight() / 2;
		}
};

class Technical : public Book
{
	public:
		virtual std::string getDescription() const override
		{
			return "Technical "+Book::getDescription();
		}
};

int main(int argc,char* argv[])
{
	Book book;
	Romance novel;

	std::cout << novel.getDescription() << '\n'; // Romance Paperback Book
	std::cout << book.getDescription() << '\n'; // Book
	std::cout << novel.getHeight() << '\n'; // 60
	std::cout << book.getHeight() << '\n'; // 120
	return 0;
}
