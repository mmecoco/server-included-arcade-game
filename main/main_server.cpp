#include "TcpServer.hpp"

int main(int argc, char* argv[])
{
      if (argc != 3)
	{
	  std::cerr << "Usage: TcpServer <port> <host>" << std::endl;
	  return 1;
	}
      unsigned short port = boost::lexical_cast<unsigned short>(argv[1]);
      
      boost::asio::io_service io_service;
      TcpServer TcpServer(io_service, port, argv[2]);
      io_service.run();
  
  return 0;
}
