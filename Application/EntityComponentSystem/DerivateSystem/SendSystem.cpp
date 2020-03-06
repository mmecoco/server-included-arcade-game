#include "SendSystem.hpp"
#include <stdlib.h>

void SendSystem::init(boost::asio::ip::udp::socket *target_socket, boost::asio::ip::udp::endpoint target_endpoint)
{
  m_sock = target_socket;
  m_endpoint = target_endpoint;
  m_server = false;
}

void SendSystem::init(boost::asio::ip::udp::socket *target_socket, std::vector<boost::asio::ip::udp::endpoint> endpoint_vector)
{
  m_sock = target_socket;
  m_vector_endpoint = endpoint_vector;
  m_server = true;
}

void SendSystem::update(EventManager &eventManager, std::vector<Entities> &m_entities)
{ 
  if (m_server) {
    std::vector<udp_struct_t> toto;
    udp_struct_t packet;

    for (auto &it : *m_drawable) {
      if (it->m_Drawable) {
        for (auto &itt : *m_position) {
          if (itt->getEntityId() == it->getEntityId()) {
            packet.connection_type = PacketType::SERVER;
            packet.id = it->getEntityId();
            packet.x = itt->x;
            packet.y = itt->y;
            toto.push_back(packet);
          }
        }
      }
    }

    std::stringstream ss;
    std::string target;
    boost::archive::text_oarchive oarchive(ss);
    oarchive << toto; // the targeted struct vector
    target = ss.str();
    for (auto it = m_vector_endpoint.begin(); it != m_vector_endpoint.end(); it++) {
      m_sock->send_to(boost::asio::buffer(target), *it);
    }
  }
  else { // client
    std::vector<udp_struct_t> toto;
    udp_struct_t packet;

    packet.connection_type = PacketType::CLIENT;
    packet.input = m_input->front()->m_input;
    packet.id = m_input->front()->getEntityId();
    toto.push_back(packet);

    std::stringstream ss;
    std::string target;
    boost::archive::text_oarchive oarchive(ss);
    oarchive << toto; // the targeted struct vector
    target = ss.str();
    m_sock->send_to(boost::asio::buffer(target), m_endpoint);
    std::cout << "sendt to :" << m_endpoint << std::endl;
  }
}
