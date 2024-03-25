#include <iostream>
#include <thread>
#include <chrono>

#include <tcpsocket.hpp>
#include <netinet/in.h>

int main(int argc, char **argv)
{
    std::thread new_thread([]{
        ss::TcpSocket client_socket;

        sockaddr_in ss;

        ss.sin_family = AF_INET;
        ss.sin_port = htons(3333);
        ss.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

        client_socket.Connect(ss);
        std::string buffer{"hola"};

        std::this_thread::sleep_for(std::chrono::seconds(3));

        client_socket.Send(buffer);

    });

    ss::TcpSocket s;
    
    sockaddr_in ss;

    ss.sin_family = AF_INET;
    ss.sin_port = htons(3333);
    ss.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    s.Bind(ss);
    s.Listen();

    std::cout << "listening on port " << ss.sin_port << std::endl;

    ss::TcpSocket connection = s.Accept();
    std::string buffer = connection.Receive(5);

    std::cout << buffer << std::endl;

    new_thread.join();

    // std::cout << std::boolalpha;
    // std::cout << v << std::endl;
    return 0;
}