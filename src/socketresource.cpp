#include "socketresource.hpp"

namespace ss
{
    SocketResource::SocketResource(Family fam, Type ty)
    {
        auto init_socket = socket_resource.get_resource(); //default resource value -1 invalid socket
        auto family = fam == Family::IPv4 ? AF_INET : AF_INET6;

        switch (ty)
        {
        case Type::TCP:
            init_socket = socket(family, SOCK_STREAM, 0);
            break;
        
        case Type::UDP:
            init_socket = socket(family, SOCK_DGRAM, 0);
            break;    
        
        default:
            break;
        }

        if (init_socket < 0)
        {
            socket_resource.reset_resource();
            throw std::system_error(init_socket, std::system_category());
        }

        socket_resource.set_resource(init_socket);
    }
    UniqueResource<int, -1> &SocketResource::get_socket()
    {
        return socket_resource;
    }
}