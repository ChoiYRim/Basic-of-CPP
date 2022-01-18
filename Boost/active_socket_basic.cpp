#include <iostream>
#include <boost/asio.hpp>

using namespace boost;

int main()
{
    // 1
    // asio::io_service가 Boost.Asio I/O 구조의 핵심
    // Boost.Asio 소켓은 이 클래스의 객체를 통해야만 네트워크 서비스를 사용 가능.
    asio::io_service ios;
    
    // 2
    // 통신 프로토콜을 의미함. 데이터 구조체에 가깝다
    // asio::ip::tcp::v4() , asio::ip::tcp::v6()냐에 따라 IPv4, IPv6가 갈린다.
    asio::ip::tcp protocol = asio::ip::tcp::v4();
    
    // 3
    asio::ip::tcp::socket sock(ios);
    //boost::system::error_code ec;
    
    // 4
//    sock.open(protocol,ec);
//    if(ec.value() != 0)
//    {
//        // error
//        std::cerr << "Failed to open the socket! Error Code = " << ec.value() << ". Message : " << ec.message();
//        return ec.value();
//    }
    
    try{
        asio::ip::tcp::socket sock(ios,protocol);
    }catch (const boost::system::system_error& e) {
        std::cerr << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
    }
    
    return 0;
}
