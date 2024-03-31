#ifndef __ENDPOINT__

#define __endpoint__

#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdint>

#include <string>

namespace ss
{
    class EndPoint
    {
        public:

            EndPoint(uint32_t raw_byte_addr, uint16_t raw_port): nativeAddress
            {
                .sin_family = AF_INET ,
                .sin_port = htons(raw_port) ,
                .sin_addr = htonl(raw_byte_addr) 
            }

            {}

            uint16_t port() const 
            {
                return nativeAddress.sin_port;
            }

            std::string toString()
            {
                std::string convert{};
                convert.resize(INET_ADDRSTRLEN);
                auto addr = nativeAddress.sin_addr.s_addr;

                inet_ntop(AF_INET, &addr, convert.data(), INET_ADDRSTRLEN);

                return convert;
            }

        private:
            sockaddr_in nativeAddress {.sin_family = AF_INET }; 

    };
}

#endif