#include "tcp_connection.hpp"

using namespace boost::asio;

TCPConnection::TCPConnection(Context &context, const std::string_view &addr, const std::string_view &port)
    : socket { context } {
  ip::tcp::resolver resolver { context };
  connect(socket, resolver.resolve(addr, port));
}

std::unique_ptr<TCPConnection> make_tcp_connection(Context &io, const std::string_view &addr,
                                                   const std::string_view &port) {
  return std::unique_ptr<TCPConnection> { new TCPConnection { io, addr, port } };
}