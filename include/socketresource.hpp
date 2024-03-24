#ifndef __ABSTRACTSOCKET__

#define __ABSTRACTSOCKET__

#include <system_error>

#include <sys/socket.h>
// #include <errno.h>

#include <uniqueresource.hpp>

namespace ss
{
    class SocketResource
    {
        public:
            enum class Family{IPv4 = AF_INET, IPv6 = AF_INET6};
            enum class Type{TCP = SOCK_STREAM, UDP = SOCK_DGRAM};

            SocketResource(Family fam = Family::IPv4, Type ty = Type::TCP);

            UniqueResource<int, -1>& get_socket();

            ~SocketResource() = default;

        private:
            UniqueResource<int, -1> socket_resource;

    };
}

#endif