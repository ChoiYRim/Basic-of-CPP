#include <iostream>
#include <boost/asio.hpp>

using namespace boost;

int main()
{
    // Step 1: 클라이언트 프로그램이 연결할 서버 프로그램의 IP주소와 프로토콜 포트 번호를 이미 알고 있다고 가정
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;
    // IP 주소를 분석하는 동안 발생할 수 있는 오류 정보를 저장하는 용도로 쓰인다.
    boost::system::error_code ec;
    
    // Step 2: IP 프로토콜 버전과 관계 없는 주소 형식을 사용한다.
    /*
        asio::ip::address_v4 : IPv4
        asio::ip::address_v6 : IPv6
        asio::ip::address    : IPv4 , IPv6 모두 가능
    */
    
    asio::ip::address ip_address = asio::ip::address::from_string(raw_ip_address,ec); // 유효한 IP인지 검증
    if(ec.value() != 0)
    {
        std::cerr << "Failed to parse the IP address. Error code = "
        << ec.value() << ". Message : " << ec.message();
        return ec.value();
    }
    
    // Step 3
    /*
        보통 아래와 같은 방식은 추천하지 않는다.
        서버 프로그램은 들어오는 모든 메시지를 들어야 하기 때문에 대체로 프로토콜 포트 번호만을 제공한다.
        대부분의 서버 프로그램은 호스트에서 사용할 수 있는 모든 IP 주소로 들어오는 메시지를 듣고 싶어 하므로 IP 주소를 지정하지 않는다.
        
        asio::ip::address_v4 와 asio::ip::address_v6는 호스트에서 사용할 수 있는 모든 IP 주소라는 개념을 나타내는 특별한 객체를 만드는
        정적 메서드인 any()를 제공한다.
     
        asio::ip::address는 any()의 사용이 불가하다.
    */
    asio::ip::tcp::endpoint ep(ip_address,port_num); // (IP address , port number)를 인자로 객체 인스턴스화 -> ep로 서버 프로그램을 가리킴.
    
    
    // Step 4
    
    return 0;
}
