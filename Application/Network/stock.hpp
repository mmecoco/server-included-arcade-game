#ifndef SERIALIZATION_STOCK_HPP
#define SERIALIZATION_STOCK_HPP

#include <string>

enum RequestCode
  {
   NOERROR = 0,
   ERROR,
   CONNECT,
   STARTGAME
  };

/// Structure to hold information about a single stock.
struct stock
{
  // tcp client side
  std::string id;
  int connecton_type; // specifies the type of the connection 0 for tcp and 1 for udp
  bool host; // if true he creates the game and else join the room
  std::string room_name; // name of the room
  int num_player;

  // tcp server side
  RequestCode request; // status of the connection defined chez alioune
  std::string ip; // ip host for the udp connection server
  unsigned short port; // port number that will be used to open for the udp server of the game

  // udp server

  // udp client

  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & id;
    ar & connecton_type;
    ar & host;
    ar & host;
    ar & room_name;
    ar & num_player;
    ar & request;
    ar & ip;
    ar & port;
  }
};


#endif // SERIALIZATION_STOCK_HPP
