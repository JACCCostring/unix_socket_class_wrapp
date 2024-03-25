#ifndef __TCPSOCKET__

#define __TCPSOCKET__

#include <socketresource.hpp>
// #include <uniqueresource.hpp>

#include <netinet/in.h>

#include <limits>
#include <string>

namespace ss
{
    class TcpSocket
    {
        public:
            TcpSocket(SocketResource::Family fam = SocketResource::Family::IPv4, SocketResource::Type typ = SocketResource::Type::TCP);

            bool Connect(const sockaddr_in& addr);

            std::size_t Send(const std::string& data, int flags = 0);

            std::string Receive(std::size_t bytes, int flags = 0);

            void Bind(const sockaddr_in& addr);
            
            TcpSocket Accept();

            void Listen(std::size_t backlog = 10);

        private:
            SocketResource _socket;

            //private constructor to help Accept method
            explicit TcpSocket(int accept_socket) noexcept;
    };
}

#endif