#ifndef NETWORK_LIB_TCP_SOCKET_HPP
#define NETWORK_LIB_TCP_SOCKET_HPP

#include <string>

namespace network::tcp_socket {

class TcpSocket {
 public:
  virtual ~TcpSocket() = default;

  virtual void send(const std::string &message) = 0;

  virtual std::string receive() = 0;
};  // namespace network::client::classTCPNetwork

}  // namespace network::tcp_socket

#endif