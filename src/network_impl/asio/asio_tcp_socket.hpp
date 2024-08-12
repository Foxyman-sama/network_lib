#ifndef NETWORK_LIB_ASIO_TCP_SOCKET_HPP
#define NETWORK_LIB_ASIO_TCP_SOCKET_HPP

#include <memory>

#include "address.hpp"
#include "asio_lib.hpp"
#include "tcp_socket.hpp"

namespace network::tcp_socket::asio {

class AsioTcpSocket : public TcpSocket {
 public:
  explicit AsioTcpSocket(asio_lib::AsioTcpSocket &&socket) noexcept;

  ~AsioTcpSocket() override;

  void send(const std::string &message) override;

  std::string receive() override;

 private:
  std::string extract_from_buffer(asio_lib::AsioStreamBuf &buf);

  asio_lib::AsioTcpSocket socket;
};

std::unique_ptr<TcpSocket> asio_connect(const Address &addr);

}  // namespace network::tcp_socket::asio

#endif