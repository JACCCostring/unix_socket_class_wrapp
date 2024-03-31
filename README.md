unix socket wrapper class, for Tcp Client/Server RAII, take in account for better resource management, very intuitive and understandable.

<h1>Install</h1>

Just clone this repo: ```git clone https://github.com/JACCCostring/unix_socket_class_wrapp.git```
make a directory call: ```mkdir build```
go to directory call: ```cd build```
to configure call: ```cmake ..```
to build call: ```make```

the executable will bbe located at project_name/build/app/main_exec.exe

<h1>Example</h1>

```cpp

#include <iostream>
#include <string>

#include <tcpsocket.hpp>
#include <tcpresolver.hpp>

int main(int argc, char **argv)
{
    ss::TcpSocket socket;

    auto result = ss::TcpResolver::resolve("localhost", "5555");

    std::cout << "testing new endpoint str addr class " << result.endpoint().toString() << std::endl;
    std::cout << "testing new endpoint port class " << result.endpoint().port() << std::endl;

    socket.Bind(result.get_nativeSocketAddress());

    socket.Listen();

    std::cout << "listen on port " << result.endpoint().port() << std::endl;

    while (true)
    {
        auto connection = socket.Accept();

        connection.Send("HTTP/1.1 200 Ok\r\n");
        connection.Send("\r\n");
        connection.Send("{'status': 200}");

        auto recv_from_client = connection.Receive(1024);

        std::cout << recv_from_client << std::endl;
    }

    return 0;
}

```