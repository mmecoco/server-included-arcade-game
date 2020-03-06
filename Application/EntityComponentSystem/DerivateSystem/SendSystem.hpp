#include <vector>
#pragma once
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
#include "DerivateComponent/DirectionComponent.hpp"
#include "DerivateComponent/TextureComponent.hpp"
#include "DerivateComponent/InputComponent.hpp"
#include "DrawableComponent.hpp"

class SendSystem : public SystemBase
{
private:
  bool m_server;
  std::vector<DrawableComponent *> *m_drawable;
  std::vector<PositionComponent *> *m_position;
  std::vector<InputComponent *> *m_input;
  std::string m_host;
  std::map<std::string, boost::asio::ip::udp::endpoint> m_endpoint_map; // id : endpoint
  unsigned short m_port;
  boost::asio::ip::udp::socket *m_sock;
  boost::asio::ip::udp::endpoint m_endpoint;
  std::vector<boost::asio::ip::udp::endpoint> m_vector_endpoint;
  
  char m_data[1024];

public:
  SendSystem() : SystemBase(10) {}
  void init(std::vector<PositionComponent *> *position) {m_position = position;};
  void init(std::vector<DrawableComponent *> *drawable) {m_drawable = drawable;};
  void init(std::vector<InputComponent *> *input) {m_input = input;};
  void init(boost::asio::ip::udp::socket *target_socket, boost::asio::ip::udp::endpoint target_endpoint);
  void init(boost::asio::ip::udp::socket *target_socket, std::vector<boost::asio::ip::udp::endpoint> endpoint_vector);
  void init(boost::shared_ptr<boost::asio::ip::udp::socket> target_socket, boost::asio::ip::udp::endpoint target_endpoint);
  void init(boost::shared_ptr<boost::asio::ip::udp::socket> target_socket, std::vector<boost::asio::ip::udp::endpoint> endpoint_vector);
  virtual void dump() {std::cout << "I am in the SendSystem" << std::endl;
    std::cout << "host" << m_host << m_port << m_server << std::endl;};
  virtual void update(EventManager &eventManager, std::vector<Entities> &m_entities);
  static SystemBase *Create() {return new SendSystem;};
};
