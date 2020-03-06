#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <map>
#include <vector>
#include "connection.hpp" // Must come before boost/serialization headers.
#include <boost/serialization/vector.hpp>
#include "stock.hpp"
#include "Room.hpp"
#include "Fork.hpp"

class TcpServer
{
public:
  TcpServer(boost::asio::io_service &io_service, unsigned short port, std::string host);

  void start();
  void stop() {};
  void read();
  void write(std::vector<stock> target);
  void handle_accept(const boost::system::error_code &e, connection_ptr conn);
  void handle_read(const boost::system::error_code &e, connection_ptr conn);
  void handle_write(const boost::system::error_code &e, connection_ptr conn);
  int getClientNum() const {return client_num_;};
private:
  int client_num_;
  boost::asio::io_service _io_service;
  boost::asio::ip::tcp::acceptor acceptor_;
  std::vector<stock> stocks_;
  std::vector<stock> write_stocks_;
  std::vector<stock> _read_stocks;
  std::string m_host;
  unsigned short m_port;
  
  std::map<std::string, Room *> rooms_;
};
