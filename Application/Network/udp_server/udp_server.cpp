#include "UdpServer.hpp"

UdpServer::UdpServer(boost::asio::io_service &io_s ,const std::string host, const std::string &port) : sock_(io_s, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), atoi(port.c_str()))), io_service_(io_s)
{
  while (true) {
    std::cout << "Waiting for the recetion of the auth\n";
    sock_.receive_from(boost::asio::buffer(data, 1024), sender_endpoint); // for the auth
    std::cout << "Authentification has been done\n";
    read();
    send(stocks_);
    //sock_.send_to(boost::asio::buffer(data, 1024), sender_endpoint);
  }
}


void UdpServer::start()
{
  io_service_.run();
}

void UdpServer::stop()
{
  io_service_.stop();
}

void UdpServer::send(std::vector<stock> target)
{
  std::cout << "Sending to the clinet the target" << std::endl;
  std::stringstream ss;
  std::string res;
  boost::archive::text_oarchive oarchive(ss);
  oarchive << target;
  res = ss.str();
  
  sock_.send_to(boost::asio::buffer(res), sender_endpoint);
}

void UdpServer::read()
{
  std::vector<stock> target;
  
  sock_.receive_from(boost::asio::buffer(data, 1024), sender_endpoint);
  try {
    std::string archive_data(&data[0], 1042);
    std::cout << "Got " << archive_data << std::endl;
    std::istringstream archive_stream(archive_data);
    boost::archive::text_iarchive i_archive(archive_stream);
    i_archive >> target;
  // treatements
  // example is for read but we have 2 sollutions : generate code here
  // or take a callback function to treat all infos

    for (std::size_t i = 0; i < target.size(); i++) {
      std::cout << i << std::endl;
      // std::cout << "Server side name " << target[i].name << std::endl;
      // std::cout << "Server side size " << target[i].size << std::endl;
      // std::cout << "Server side value " << target[i].value << std::endl;
   }
    target[0].id = target[0].id + " from server";
    stocks_ = target;
  }
  catch (std::exception& e) {
    std::cerr << "failed to get packets\n";
  }
}
