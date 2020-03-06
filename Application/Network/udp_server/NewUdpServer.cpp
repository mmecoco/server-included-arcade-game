#include "NewUdpServer.hpp"

NewUdpServer::NewUdpServer(boost::asio::io_service &io, unsigned short port, std::string host) : m_sock(io, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(host.c_str()), port))
{
    m_acceptor_threads.create_thread(boost::bind(&NewUdpServer::main_game, this));
    m_acceptor_threads.create_thread(boost::bind(&NewUdpServer::connection, this));
}

void NewUdpServer::start()
{
    m_acceptor_threads.join_all();
}

void NewUdpServer::main_game()
{
    while (true);
        std::cout << "main game\n";
}

void NewUdpServer::send(std::vector<udp_struct_t> &buff)
{
    std::stringstream ss;
    std::string str;
    boost::archive::text_oarchive oarchive(ss);
    oarchive << buff;
    str = ss.str();

    size_t read_size = m_sock.send_to(boost::asio::buffer(str), m_sender_endpoint);
}

std::vector<udp_struct_t> NewUdpServer::receive(std::vector<udp_struct_t> &buff)
{
    char data[1024];
    std::vector<udp_struct_t> target;

    size_t send_size = m_sock.receive_from(boost::asio::buffer(data, 1024), m_sender_endpoint);
    std::string str(&data[0], 1024);
    std::cout << "Got " << str << std::endl;
    std::istringstream archive_stream(str);
    boost::archive::text_iarchive iarchive(archive_stream);
    iarchive >> target;
    target[0].name = target[0].name + "S";

    return (target);
}

void NewUdpServer::connection()
{
    boost::asio::ip::udp::endpoint sender_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 4252);
    m_sender_endpoint = sender_endpoint;

    try {
        while (true) { // possible to have a bool to know if the game is killed
            //std::cout << "Server on\n";
            std::vector<udp_struct_t> buffer;
            std::vector<udp_struct_t> got;
            got = receive(buffer);
            send(got);
        }
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        exit(84);
    }
}