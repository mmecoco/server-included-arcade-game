#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <vector>
#include "connection.hpp" // Must come before boost/serialization headers.
#include <boost/serialization/vector.hpp>
#include "stock.hpp"
#include "AUdp.hpp"

//TODO : GO END GET A LOOK OF UDP_SERVER AND DO IMITATE THE FORMAT OF THE SERVER'S CLASS

class UdpClient : public AUdp
{
public:
  UdpClient(boost::asio::io_service& io_s, const std::string host, const std::string& port);
  void start();
  void stop();
  void send(std::vector<stock> target);
  void read();
private:
  
  boost::asio::ip::udp::socket sock;
  
  std::vector<stock> stocks_;
  
  boost::asio::ip::udp::resolver resolver;
  boost::asio::ip::udp::resolver::query query;
  boost::asio::ip::udp::resolver::iterator it;
  boost::asio::io_service &io_service_;
  boost::asio::ip::udp::endpoint sender_endpoint;
  char data[1024];
};
