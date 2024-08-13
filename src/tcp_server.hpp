#ifndef NETWORK_LIB_TCP_SERVER_HPP
#define NETWORK_LIB_TCP_SERVER_HPP

#include <memory>

#include "tcp_socket.hpp"

namespace network::tcp_server {

class TcpServer {
 public:
  virtual ~TcpServer() = default;

  virtual std::unique_ptr<tcp_socket::TcpSocket> accept() = 0;
};

}  // namespace network::tcp_server

#endif