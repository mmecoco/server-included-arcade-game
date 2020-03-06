#include "ReceiveSystem.hpp"

void ReceiveSystem::init(boost::asio::ip::udp::socket *target_socket, boost::asio::ip::udp::endpoint target_endpoint)
{
  m_sock = target_socket;
  m_endpoint = target_endpoint;
  m_server = false;
  m_is_thread_enable = true;
}

void ReceiveSystem::init(boost::asio::ip::udp::socket *target_socket, std::vector<boost::asio::ip::udp::endpoint> endpoint_vector)
{
  m_sock = target_socket;
  m_vector_endpoint = endpoint_vector;
  m_server = true;
  m_is_thread_enable = true;
}

void ReceiveSystem::receive_from_endpoint(boost::asio::ip::udp::endpoint target_endpoint)
{
  m_is_thread_enable = false;
  char data[1024];
  std::vector<udp_struct_t> got;

  size_t read_size = m_sock->receive_from(boost::asio::buffer(data, 1024), target_endpoint);
  std::string str(&data[0], 1024);
  std::cout << "str is " << str << std::endl;
  std::istringstream archive_stream(str);
  boost::archive::text_iarchive iarchive(archive_stream);
  iarchive >> got;

  // need to differenciate if the packet is from server or from client
  for (auto it = got.begin(); it != got.end(); it++) {
    if (it->connection_type == PacketType::CLIENT) {
      std::cout << "Received from the client\n";
      for (auto &inp : *m_input) {
        if (inp->getEntityId() == it->id)
          inp->m_input = it->input;
      }
    }
    else { // SERVER
    std::cout << "Received from the server\n";
    if (m_position->size() == 0)
      std::cout << "position is not in the system\n";
    else
      std::cout << "valid position\n";
      for (auto &itt : *m_position) {
        if (it->id == itt->getEntityId()) {
          itt->x = it->x;
          itt->y = it->y;
        }
      }
    }
  }
  std::cout << "Treatement done!" << std::endl;

  m_is_thread_enable = true;
}

void ReceiveSystem::update(EventManager &eventManager, std::vector<Entities> &m_entities)
{
  std::cout <<  "position size = " << m_position->size() << std::endl;
  std::cout << "segs here\n";
  std::cout << "input size = " << m_input->size() << std::endl;
  std::vector<udp_struct_t> toto;
  if (m_server) {
    for (auto it = m_vector_endpoint.begin(); it != m_vector_endpoint.end(); it++) {
      if (m_is_thread_enable) {
	//std::cout << "RECEIVING from " << it->port() << std::endl;
	boost::thread(boost::bind(&ReceiveSystem::receive_from_endpoint, this, *it));
      }
    }
  }
  else {
    if (m_is_thread_enable) {
      //std::cout << "RECEIVING from " << m_endpoint.port() << std::endl;
      boost::thread(boost::bind(&ReceiveSystem::receive_from_endpoint, this, m_endpoint));
    }
  }
}
