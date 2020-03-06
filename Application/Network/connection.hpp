#ifndef SERIALIZATION_CONNECTION_HPP
#define SERIALIZATION_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

class connection
{
public:
  connection(boost::asio::io_service& io_service)
    : socket_(io_service)
  {
  }
  boost::asio::ip::tcp::socket& socket()
  {
    return socket_;
  }

  template <typename T, typename Handler>
  void async_write(const T& t, Handler handler)
  {
    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);
    archive << t;
    outbound_data_ = archive_stream.str();
    std::ostringstream header_stream;
    header_stream << std::setw(header_length)
      << std::hex << outbound_data_.size();
    if (!header_stream || header_stream.str().size() != header_length)
    {
      boost::system::error_code error(boost::asio::error::invalid_argument);
      socket_.get_io_service().post(boost::bind(handler, error));
      return;
    }
    outbound_header_ = header_stream.str();

    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back(boost::asio::buffer(outbound_header_));
    buffers.push_back(boost::asio::buffer(outbound_data_));
    boost::asio::async_write(socket_, buffers, handler);
  }

  std::string GetIp() const
  {
    std::string host_and_port = boost::lexical_cast<std::string>(socket_.remote_endpoint());
    std::string host = host_and_port.substr(0, host_and_port.find(":"));

    return (host);
  };

  unsigned short GetPort() const
  {
    unsigned short port = socket_.remote_endpoint().port(); 
    return (port);
  };
  template <typename T, typename Handler>
  void async_read(T& t, Handler handler)
  {
    void (connection::*f)(
        const boost::system::error_code&,
        T&, boost::tuple<Handler>)
      = &connection::handle_read_header<T, Handler>;
      std::cout << "Called async read\n";
    boost::asio::async_read(socket_, boost::asio::buffer(inbound_header_),
        boost::bind(f,
          this, boost::asio::placeholders::error, boost::ref(t),
          boost::make_tuple(handler)));
  }
  template <typename T, typename Handler>
  void handle_read_header(const boost::system::error_code& e,
      T& t, boost::tuple<Handler> handler)
  {
    if (e)
    {
      boost::get<0>(handler)(e);
    }
    else
    {
      std::istringstream is(std::string(inbound_header_, header_length));
      std::size_t inbound_data_size = 0;
      if (!(is >> std::hex >> inbound_data_size))
      {
        boost::system::error_code error(boost::asio::error::invalid_argument);
        boost::get<0>(handler)(error);
        return;
      }

      inbound_data_.resize(inbound_data_size);
      void (connection::*f)(
          const boost::system::error_code&,
          T&, boost::tuple<Handler>)
        = &connection::handle_read_data<T, Handler>;
        std::cout << "Called handle read" << std::endl;
      boost::asio::async_read(socket_, boost::asio::buffer(inbound_data_),
        boost::bind(f, this,
          boost::asio::placeholders::error, boost::ref(t), handler));
    }
  }

  template <typename T, typename Handler>
  void handle_read_data(const boost::system::error_code& e,
      T& t, boost::tuple<Handler> handler)
  {
    if (e)
    {
      boost::get<0>(handler)(e);
    }
    else
    {
      try
      {
        std::string archive_data(&inbound_data_[0], inbound_data_.size());
        std::cout << archive_data << std::endl;
        std::istringstream archive_stream(archive_data);
        boost::archive::text_iarchive archive(archive_stream);
        archive >> t;
      }
      catch (std::exception& e)
      {
        boost::system::error_code error(boost::asio::error::invalid_argument);
        boost::get<0>(handler)(error);
        return;
      }

      boost::get<0>(handler)(e);
    }
  }

private:
  boost::asio::ip::tcp::socket socket_;
  enum { header_length = 8 };
  std::string outbound_header_;
  std::string outbound_data_;
  char inbound_header_[header_length];
  std::vector<char> inbound_data_;
};

typedef boost::shared_ptr<connection> connection_ptr;

#endif
