#include <tcpsocket.hpp>

#include <iostream>

namespace ss
{
    TcpSocket::TcpSocket(SocketResource::Family fam, SocketResource::Type typ): _socket{fam, typ}
    {}

    bool TcpSocket::Connect(const sockaddr_in& addr)
    {
        ::connect(_socket.get_socket().get_resource(), reinterpret_cast<const sockaddr *>(&addr), sizeof(addr));
        
        if (_socket.get_socket().get_resource() < 0)
        {
            _socket.get_socket().reset_resource();
            throw std::system_error(_socket.get_socket().get_resource(), std::system_category());
        }

        if (_socket.get_socket().get_resource() == 0) 
            return true;

        return false;
    }

    std::size_t TcpSocket::Send(const std::string& data, int flags)
    {
        if (data.empty())
            throw std::invalid_argument("data is empty!");

        if (data.length() > std::numeric_limits<std::size_t>::max())
            throw std::overflow_error("data is too long to send!");

        auto bytes_sent = ::send(_socket.get_socket().get_resource(), data.data(), data.length(), flags);

        if (bytes_sent < 0)
            throw std::system_error(_socket.get_socket().get_resource(), std::system_category());

        if (bytes_sent == 0)
            return 0;
        
        return bytes_sent;
    }

    std::string TcpSocket::Receive(std::size_t bytes, int flags)
    {
        std::string buffer;

        buffer.resize(static_cast<std::size_t>(bytes));

        auto bytes_recv = ::recv(_socket.get_socket().get_resource(), reinterpret_cast<char *>(buffer.data()), buffer.length(), flags);

        if (bytes_recv < 0)
            throw std::system_error(_socket.get_socket().get_resource(), std::system_category());

        if (bytes_recv == 0)
        {
            buffer.clear();
            buffer = "";
            return buffer;
        }

        return buffer;
    }

    void TcpSocket::Bind(const sockaddr_in &addr)
    {
        auto r_bind = ::bind(_socket.get_socket().get_resource(), reinterpret_cast<const sockaddr *>(&addr), sizeof(sockaddr_in));
    
        if (r_bind < 0)
            throw std::system_error(_socket.get_socket().get_resource(), std::system_category());
    }

    TcpSocket TcpSocket::Accept()
    {
        TcpSocket incoming_socket{::accept(_socket.get_socket().get_resource(), nullptr, nullptr)};

        if (! incoming_socket._socket.get_socket())
            throw std::system_error(_socket.get_socket().get_resource(), std::system_category());

        return incoming_socket;
    }

    void TcpSocket::Listen(std::size_t backlog)
    {
        auto r_listen = ::listen(_socket.get_socket().get_resource(), backlog);

        if (r_listen < 0)
            throw std::system_error(_socket.get_socket().get_resource(), std::system_category());
    }

    //private constructor to help, Accept method, to create a new comming socket
    TcpSocket::TcpSocket(int accept_socket) noexcept
    {
        _socket.get_socket().set_resource(accept_socket);
    }
}