#pragma once

#include "AUdp.hpp"
#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <numeric>
#include <functional>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "udp_struct.hpp"
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class NewUdpServer : public AUdp
{
public:
    NewUdpServer(boost::asio::io_service &io, unsigned short port, std::string host);
    void start();
private:
    void main_game();
    void connection();

    boost::thread_group m_acceptor_threads;
    boost::asio::ip::udp::socket m_sock;
    boost::asio::ip::udp::endpoint m_sender_endpoint;

    // method function for the server udp
    //void send(std::vector<char> &buff);
    void send(std::vector<udp_struct_t> &buff);
    //std::string receive(std::vector<char> &buff);
    std::vector<udp_struct_t> receive(std::vector<udp_struct_t> &buff);
};