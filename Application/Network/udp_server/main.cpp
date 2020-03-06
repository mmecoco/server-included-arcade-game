#include "UdpServer.hpp"

int main(int argc, char* argv[])
{
  try
  {
    // Check command line arguments.
    if (argc != 3)
    {
      std::cerr << "Usage: server <host> <port>" << std::endl;
      return 1;
    }
    
    boost::asio::io_service io_service;
    UdpServer server(io_service, argv[1], argv[2]);
    std::cout << "TTTT\n";
    server.start();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
