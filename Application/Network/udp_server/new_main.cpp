#include "NewUdpServer.hpp"

int main()
{
    boost::asio::io_service io;
    NewUdpServer toto(io, 4242, "127.0.0.1");

    toto.start();
    return (0);
}