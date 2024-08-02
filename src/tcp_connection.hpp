#ifndef NETWORK_LIB_TCP_CONNECTION_HPP
#define NETWORK_LIB_TCP_CONNECTION_HPP

#include <boost/asio.hpp>
#include <memory>
#include <string_view>

using Context = boost::asio::io_context;

class TCPConnection {
 public:
  TCPConnection(Context &context, const std::string_view &addr, const std::string_view &port);

 private:
  boost::asio::ip::tcp::socket socket;
};

std::unique_ptr<TCPConnection> make_tcp_connection(Context &io, const std::string_view &addr,
                                                   const std::string_view &port);
#endif