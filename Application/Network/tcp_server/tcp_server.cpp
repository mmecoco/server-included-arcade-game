#include "TcpServer.hpp"
#include "UdpServer.hpp"
#include "NewUdpServer.hpp"

TcpServer::TcpServer(boost::asio::io_service& io_service, unsigned short port, std::string host)
  : acceptor_(io_service,
	      boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host.c_str()), port)), m_host(host), m_port(port)
{
  client_num_ = 0;

  connection_ptr new_conn(new connection(acceptor_.get_io_service()));
  acceptor_.async_accept(new_conn->socket(),
			 boost::bind(&TcpServer::handle_accept, this,
				     boost::asio::placeholders::error, new_conn));
  // note that we need to make a disconnection handler for the sockets
}

void TcpServer::handle_accept(const boost::system::error_code& e, connection_ptr conn)
{
  std::cout << "New Connection " << client_num_ << std::endl;
  std::cout << "Printing stat of the Rooms" << std::endl;
  for (auto it = rooms_.begin(); it != rooms_.end(); it++) {
    std::cout << it->first << ":" << std::endl;
    std::map<std::string, std::pair<std::string, unsigned short>> datas = it->second->GetDatas();
    for (auto toto = datas.begin(); toto != datas.end(); toto++) {
      std::cout << "name : " << toto->first << " : " << toto->second.first << " : " << toto->second.second << std::endl;
    }
  }
  if (!e)
    {
      client_num_ =  client_num_ + 1;
      conn->async_read(stocks_,
		       boost::bind(&TcpServer::handle_read,
				   this,
				   boost::asio::placeholders::error, conn));
    }
  
  connection_ptr new_conn(new connection(acceptor_.get_io_service()));
  acceptor_.async_accept(new_conn->socket(),
			 boost::bind(&TcpServer::handle_accept, this,
				     boost::asio::placeholders::error, new_conn));
}

void TcpServer::handle_read(const boost::system::error_code& e, connection_ptr conn)
{
  if (!e) {
    //suppose that we are using 1 vector each
    std::cout << "Printing packets read\n";
    std::cout << stocks_[0].connecton_type << std::endl;
    std::cout << stocks_[0].host << std::endl;
    std::cout << stocks_[0].id << std::endl;
    std::cout << stocks_[0].num_player << std::endl;
    std::cout << stocks_[0].room_name << std::endl;
    if (stocks_[0].host) {
      Room *new_room = new Room(stocks_[0].room_name, stocks_[0].num_player);

      new_room->AddPlayer(stocks_[0].id, conn->GetIp(), conn->GetPort(), conn);
      rooms_[stocks_[0].room_name] = new_room;
      std::cout << "Room Created!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

      stock send_to;
      send_to.request = RequestCode::CONNECT;
    }
    else {
      if (rooms_.find(stocks_[0].room_name) != rooms_.end())
        rooms_[stocks_[0].room_name]->AddPlayer(stocks_[0].id, conn->GetIp(), conn->GetPort(), conn);
      else
        std::cout << "No rooms fucker\n";

      stock send_to_error;
      send_to_error.request = RequestCode::ERROR;
    }

    if (rooms_[stocks_[0].room_name]->GetPlayerNum() == rooms_[stocks_[0].room_name]->GetMaxPlayerNum()) {
      std::vector<connection_ptr> connection_list = rooms_[stocks_[0].room_name]->GetConnection();
      std::map<std::string, std::pair<std::string, unsigned short>> client_data = rooms_[stocks_[0].room_name]->GetDatas();
      std::vector<stock> udp_client_info;
      stock iterator_struct;

      for (auto it = client_data.begin(); it != client_data.end(); it++) {
	iterator_struct.id = it->first;
	iterator_struct.connecton_type = 0;
	iterator_struct.host = false;
	iterator_struct.room_name = "client";
	iterator_struct.num_player = 2;
	iterator_struct.request = RequestCode::CONNECT;
	iterator_struct.ip = it->second.first;
	iterator_struct.port = it->second.second;
	udp_client_info.push_back(iterator_struct);
      }

      std::vector<stock> start_packet;
      stock success;

      success.request = RequestCode::STARTGAME;
      success.ip = m_host;
      success.port = m_port;
      success.connecton_type = 0;
      success.host = false;
      success.id = "";
      success.num_player = 2;
      success.room_name = "";
      start_packet.push_back(success);

      start_packet.insert(start_packet.end(), udp_client_info.begin(), udp_client_info.end()); // added all packets that are required
      
      std::cout << "Ready to send starting packet for clients\n";
      for (auto it : connection_list) {
        std::cout << "Send ok?\n";
        it->async_write(start_packet,
			                    boost::bind(&TcpServer::handle_write, this,
                          boost::asio::placeholders::error, it));
        std::cout << "Send ok\n";
      }
      boost::asio::io_service is;
      //      Server *toto = new Server(udp_client_info, m_host, m_port);
      //NewUdpServer *toto = new NewUdpServer(is, m_port, m_host);
      // instead of initializing the NewUdpServer, initialize the Eligos::Server with udp client info

      std::cout	<< "TCP client got a server start request with following informations:\n";
      std::cout << "size of the packet = " << start_packet.size() << std::endl;
      for (auto it = start_packet.begin(); it != start_packet.end();  it++) {
        std::cout << "##########" << std::endl;
        std::cout << "id : " <<	it->id << std::endl;
        std::cout << "ip : " <<	it->ip << std::endl;
        std::cout << "port : " << it->port << std::endl;
      }
      
      std::cout << "udp server created\n";
      Fork forke(udp_client_info, m_host, m_port); // modify the fork class or create a new one that capt a Elogis::Server
      std::cout << "udp server set\n";
      std::cout << "Server side alive\n";
    }
  }
  else
    std::cerr << e.message() << std::endl;
}

void TcpServer::handle_write(const boost::system::error_code& e, connection_ptr conn)
{
  std::cout << "Write done" << std::endl;
}
