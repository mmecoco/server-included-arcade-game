#include "UdpClient.hpp"

UdpClient::UdpClient(boost::asio::io_service& io_s, const std::string host, const std::string &port) : sock(io_s, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)), resolver(io_s), query(boost::asio::ip::udp::v4(), host.c_str(), port.c_str()), io_service_(io_s)
{
  it = resolver.resolve(query);
  sock.send_to(boost::asio::buffer("0", 1), *it);
  //sock.receive_from(boost::asio::buffer(data, 1024), sender_endpoint);
  std::vector<stock> target;
  stock toto;
  toto.id = "mmecoco";
  toto.connecton_type = 0;
  toto.host = false;
  toto.ip = "127.0.0.1";
  toto.num_player = 5;
  toto.port = 1111;
  toto.room_name = "toto";
  toto.request = RequestCode::CONNECT;
  std::string input;

  while (true) {
    std::cout << "Enter name :";
    std::cin >> input;
    toto.id = input;
    target.push_back(toto);
    send(target);
    target.clear();
    read();
  }
}


void UdpClient::start()
{
  io_service_.run();
}

void UdpClient::stop()
{
  io_service_.stop();
}

void UdpClient::send(std::vector<stock> target)
{
  std::stringstream ss;
  std::string res;
  boost::archive::text_oarchive oarchive(ss);
  oarchive << target;
  res = ss.str();
  sock.send_to(boost::asio::buffer(res), *it);
}

void UdpClient::read()
{
  std::vector<stock> stocks;
  std::cout << "Alive\n";
  size_t length = sock.receive_from(boost::asio::buffer(data, 1024), sender_endpoint);
  std::cout << "Got " << length << std::endl;
  std::cout<<"Data in raw: \n";
  std::cout.write(data,length);
  std::cout << "Alive\n";
  std::string archive_data(&data[0], length);
  std::cout << "Alive\n";
  std::istringstream archive_stream(archive_data);
  std::cout << "Alive\n";
  boost::archive::text_iarchive archive(archive_stream);
  std::cout << "Alive\n";
  archive >> stocks;
  std::cout << "Alive\n";

  std::cout << "name " << stocks[0].id << std::endl;
}
