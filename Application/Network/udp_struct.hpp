#pragma once

#include <string>
#include <vector>
#include "InputComponent.hpp"

enum PacketType
{
    CLIENT,
    SERVER
};

/// Structure to hold information about a single stock.
typedef struct udp_struct_s
{
    int id; // all
    float x; // server -> client
    float y; // server -> client
    PacketType connection_type; // all
    Eligos::input_keys input; // client->server
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & input;
        ar & connection_type;
        ar & y;
        ar & x;
        ar & id;
    }
} udp_struct_t;