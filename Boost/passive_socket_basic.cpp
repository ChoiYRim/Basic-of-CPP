#include <iostream>
#include <boost/asio.hpp>

using namespace boost;

int main()
{
    // Step 1
    asio::io_service ios;
    
    // Step 2
    asio::ip::tcp protocol = asio::ip::tcp::v6();
    
    // Step 3
    asio::ip::tcp::acceptor acceptor(ios);
    boost::system::error_code ec;
    
    // Step 4
    acceptor.open(protocol,ec); // OS에서 실제 소켓이 할당되는 명령어
    if(ec.value() != 0)
    {
        // error message
        return ec.value();
    }
    
    return 0;
}
