#ifndef NETWORK_LIB_ASIO_TCP_SERVER_HPP
#define NETWORK_LIB_ASIO_TCP_SERVER_HPP

#include <memory>

#include "asio_lib.hpp"
#include "tcp_server.hpp"

namespace network::tcp_server::asio {

class AsioTcpServer : public TcpServer {
 public:
  explicit AsioTcpServer(unsigned short port);

  std::unique_ptr<tcp_socket::TcpSocket> accept();

 private:
  asio_lib::AsioContext context;
  asio_lib::AsioTcpAcceptor acceptor;
};

}  // namespace network::tcp_server::asio

#endif