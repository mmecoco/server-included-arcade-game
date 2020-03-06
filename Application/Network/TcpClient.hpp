#pragma once
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <vector>
#include "connection.hpp"
#include <boost/serialization/vector.hpp>
#include "stock.hpp"

class TcpClient
{
public:
  TcpClient(boost::asio::io_service &io_service, const std::string& host, const std::string& service);
  void handle_accept(const boost::system::error_code &e, connection_ptr conn);
  void handle_read(const boost::system::error_code &e, connection_ptr conn);
  void handle_write(const boost::system::error_code &e, connection_ptr conn);
  void read();
  void write(std::vector<stock> target);
private:
  connection connection_;
  std::vector<stock> stocks_;
  boost::asio::io_service &io_service_;
  const std::string & m_host;
  std::string m_id;
};
