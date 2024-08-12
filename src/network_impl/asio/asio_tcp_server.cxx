#include "asio_tcp_server.hpp"

#include "asio_tcp_socket.hpp"

namespace network::tcp_server::asio {

AsioTcpServer::AsioTcpServer(unsigned short port) : acceptor { context } {
  const auto protocol { asio_lib::v4() };
  acceptor.open(protocol);

  const auto endpoint { asio_lib::AsioTcpEndpoint { protocol, port } };
  acceptor.bind(endpoint);
  acceptor.set_option(asio_lib::reuse_address(true));
  acceptor.listen();
}

std::unique_ptr<tcp_socket::TcpSocket> AsioTcpServer::accept() {
  return std::make_unique<tcp_socket::asio::AsioTcpSocket>(acceptor.accept());
}

}  // namespace network::tcp_server::asio