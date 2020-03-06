#pragma once

#include <vector>
#include <map>
#include <string>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "SystemBase.cpp"
#include "udp_struct.hpp"
#include "stock.hpp"
#include "DerivateComponent/PositionComponent.hpp"
#include "DerivateComponent/VelocityComponent.hpp"
#include "DerivateComponent/DirectionComponent.hpp"
#include "DerivateComponent/TextureComponent.hpp"
#include "DerivateComponent/InputComponent.hpp"
#include "DrawableObjectComponent.hpp"

class ReceiveSystem : public SystemBase
{
private:
  bool m_server;
  bool m_is_thread_enable;
  std::vector<PositionComponent *> *m_position;
  std::vector<InputComponent *> *m_input;
  std::string m_host;
  std::map<std::string, boost::asio::ip::udp::endpoint> m_endpoint_map; // id : endpoint
  unsigned short m_port;
  boost::asio::ip::udp::socket *m_sock;
  boost::asio::ip::udp::endpoint m_endpoint;
  std::vector<boost::asio::ip::udp::endpoint> m_vector_endpoint;
  
public:
  ReceiveSystem() : SystemBase(13) {}
  void init(std::vector<InputComponent *> *input) {
    m_input = input;
    std::cout<<"INPUT COMPONENT IS NOW SET TO THE RECEIVE\n";
  };
  void init(std::vector<PositionComponent *> *position) {m_position = position;};
  void init(boost::asio::ip::udp::socket *target_socket, boost::asio::ip::udp::endpoint target_endpoint);
  void init(boost::asio::ip::udp::socket *target_socket, std::vector<boost::asio::ip::udp::endpoint> endpoint_vector);
  virtual void dump() {std::cout << "I am in the ReceiveSystem" << std::endl;}
  virtual void update(EventManager &eventManager, std::vector<Entities> &m_entities);
  void receive_from_endpoint(boost::asio::ip::udp::endpoint target_endpoint);
  static SystemBase *Create() {return new ReceiveSystem;};
};
