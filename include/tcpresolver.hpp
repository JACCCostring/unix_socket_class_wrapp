#ifndef __TCPRESOLVER__

#define __TCPRESOLVER__

#include <sys/types.h>
#include <netdb.h>

#include <string>

#include <endpoint.hpp>

namespace ss
{
    class TcpResolver
    {
        public:

            class Result
            {
                public:
                    Result(addrinfo* info): _info{info}
                    {}

                    sockaddr_in get_nativeSocketAddress()
                    {
                        return *reinterpret_cast<sockaddr_in *>(_info->ai_addr);
                    }

                    ss::EndPoint endpoint()
                    {
                        auto addr = this->get_nativeSocketAddress().sin_addr.s_addr;
                        auto port = this->get_nativeSocketAddress().sin_port;

                        return ss::EndPoint{addr, port};
                    }

                    ~Result()
                    {
                        if (_info)
                            freeaddrinfo(_info);
                    }

                private:
                    addrinfo* _info {nullptr};
            };


            static Result resolve(const std::string& host, const std::string& service)
            {
                addrinfo hints
                {
                    .ai_family = AF_INET,
                    .ai_socktype = SOCK_STREAM,
                    .ai_protocol = IPPROTO_TCP
                };

                addrinfo* r;

                std::ignore = getaddrinfo(host.c_str(), service.c_str(), &hints, &r);

                return Result{r};
            }

    };
}

#endif