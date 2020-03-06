#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <vector>
#include "connection.hpp" // Must come before boost/serialization headers.
#include <boost/serialization/vector.hpp>
#include "stock.hpp"
#include "TcpClient.hpp"
#include "NewUdpClient.hpp"
#include "Client.hpp"

TcpClient::TcpClient(boost::asio::io_service& io_service,
	       const std::string& host, const std::string& service)
  : connection_(io_service), io_service_(io_service), m_host(host)
  {
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(host, service);
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    boost::asio::async_connect(connection_.socket(), endpoint_iterator,
			       boost::bind(&TcpClient::handle_accept, this,
					   boost::asio::placeholders::error, nullptr));
  }

void TcpClient::handle_accept(const boost::system::error_code& e , connection_ptr conn)
{
  if (!e) {
    stock toto;
    std::string input;
    std::cout << "id:";
    std::cin >> input;
    toto.id = input;
    m_id = input;
    std::cout << "connection type:";
    std::cin >> input;
    toto.connecton_type= atoi(input.c_str());
    std::cout << "host:";
    std::cin >> input;
    if (input == "true")
      toto.host = true;
    else
      toto.host = false;
    std::cout << "room name:";
    std::cin >> input;
    toto.room_name = input;
    toto.request = RequestCode::CONNECT;
    toto.num_player = 2;
	  std::vector<stock> target;
    target.push_back(toto);
	  write(target);
	  read();
	// generate code here if possible TT
  }
  else {
	  std::cerr << e.message() << std::endl;
  }
}

void TcpClient::handle_read(const boost::system::error_code& e, connection_ptr conn)
{
  if (!e) {
    std::cout << "OK" << std::endl;
    if (stocks_[0].request == RequestCode::STARTGAME) {
      // START THE GAME
      boost::asio::io_service io_service;
      std::cout << "TCP client got a server start request with following informations:\n";
      for (auto it = stocks_.begin(); it != stocks_.end();  it++) {
	std::cout << "##########" << std::endl;
	std::cout << "id : " << it->id << std::endl;
	std::cout << "ip : " << it->ip << std::endl;
	std::cout << "port : " << it->port << std::endl;
      }
      Client client(stocks_, m_id);

      client.run();
      // instead of instencing the NewUdpClient, instenciate the Eligos::Client with stocks_[0]
      
      std::cout << "PLOPI" << std::endl;
      //client.start(); // same
      std::cout << "Client Udp connection ready!" << std::endl;
    }
    else {
      std::cout << "Got " << stocks_[0].request << std::endl;
    }
  }
  else
  {
    std::cerr << e.message() << std::endl;
  }
  read();
}

void TcpClient::handle_write(const boost::system::error_code& e, connection_ptr conn)
{
  stocks_.clear();
}

void TcpClient::read()
{
  connection_.async_read(stocks_,
			 boost::bind(&TcpClient::handle_read, this,
				     boost::asio::placeholders::error, nullptr));
}

void TcpClient::write(std::vector<stock> target)
{
  connection_.async_write(target,
			  boost::bind(&TcpClient::handle_write,
				      this,
				      boost::asio::placeholders::error, nullptr)); 
}
