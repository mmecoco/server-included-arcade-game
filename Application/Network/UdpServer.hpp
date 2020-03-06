#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <vector>
#include "connection.hpp" // Must come before boost/serialization headers.
#include <boost/serialization/vector.hpp>
#include "stock.hpp"
#include "AUdp.hpp"

class UdpServer : public AUdp
{
private:
  std::vector<stock> stocks_; // this vector is for read
  boost::asio::ip::udp::socket sock_;
  boost::asio::ip::udp::endpoint sender_endpoint;
  char data[1024];
  boost::asio::io_service &io_service_;
public:
  UdpServer(boost::asio::io_service& io_s, const std::string host, const std::string &port);
  void start();
  void stop();
  void send(std::vector<stock> target);
  void read();
};
