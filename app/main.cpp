#include <iostream>

#include <tcpsocket.hpp>
#include <netinet/in.h>

int main(int argc, char **argv)
{
    ss::TcpSocket s;
    
    sockaddr_in ss;

    ss.sin_family = AF_INET;
    ss.sin_port = htons(3333);
    ss.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    s.Bind(ss);
    s.Listen();

    ss::TcpSocket connection = s.Accept();

    // std::cout << std::boolalpha;
    // std::cout << v << std::endl;
    return 0;
}