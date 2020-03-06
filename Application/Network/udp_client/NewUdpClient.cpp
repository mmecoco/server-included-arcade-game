#include "NewUdpClient.hpp"

NewUdpClient::NewUdpClient(boost::asio::io_service &io, unsigned short port, std::string host) : m_sock(io, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)), m_port(port), m_host(host)
{
    m_acceptor_threads.create_thread(boost::bind(&NewUdpClient::main_game, this));
    m_acceptor_threads.create_thread(boost::bind(&NewUdpClient::connection, this));
}

void NewUdpClient::start()
{
    m_acceptor_threads.join_all();
}

void NewUdpClient::main_game()
{
    while (true);
        std::cout << "main game\n";
}

void NewUdpClient::send(std::vector<udp_struct_t> &buff)
{
    std::stringstream ss;
    std::string str;
    boost::archive::text_oarchive oarchive(ss);
    oarchive << buff;
    str = ss.str();

    size_t read_size = m_sock.send_to(boost::asio::buffer(str), m_sender_endpoint);
}

std::vector<udp_struct_t> NewUdpClient::receive(std::vector<udp_struct_t> &buff)
{
    char data[1024];
    std::vector<udp_struct_t> target;

    size_t send_size = m_sock.receive_from(boost::asio::buffer(data, 1024), m_sender_endpoint);
    std::string str(&data[0], 1024);
    std::istringstream archive_stream(str);
    boost::archive::text_iarchive iarchive(archive_stream);
    iarchive >> target;

    return (target);
}

void NewUdpClient::connection()
{
    boost::asio::ip::udp::endpoint sender_endpoint(boost::asio::ip::address::from_string(m_host.c_str()), m_port);
    m_sender_endpoint = sender_endpoint;
    std::string target;

    try {
        while (true) { // possible to have a bool to know if the game loop is alive
            std::cout << "Client on\n";
            std::vector<udp_struct_t> buffer;
            std::vector<udp_struct_t> got;
            udp_struct_t toto;
            toto.name = "mmecoco";
            toto.int_size = 3;
            toto.vec_int = {4, 3, 5};
            toto.char_size = 2;
            toto.vec_char = {'h', 'j', 'p'};
            toto.float_size = 5;
            toto.vec_float = {123.2, 32.3, 23.1, 11.1, 2222.22};
            buffer.push_back(toto);
            send(buffer);
            got = receive(buffer);
            std::cout << "name got is " << got[0].name << std::endl;
            std::cout << "size of int is " << got[0].int_size << std::endl;
        }
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        exit(84);
    }
}