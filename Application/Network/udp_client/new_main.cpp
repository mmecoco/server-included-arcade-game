#include "NewUdpClient.hpp"

int main()
{
    boost::asio::io_service io;
    NewUdpClient toto(io, 4242, "10.41.164.68");

    toto.start();
    return 0;
}