#ifndef NETWORK_LIB_TCP_CONNECTION_HPP
#define NETWORK_LIB_TCP_CONNECTION_HPP

#include <memory>
#include <string>

#include "acceptor.hpp"
#include "address.hpp"
#include "network_impl.hpp"

namespace network::client {

class TCPConnection {
 public:
  explicit TCPConnection(const Address &addr, std::unique_ptr<network_impl::TCPNetwork> impl);

  void connect();

  void send(const std::string &message);

  std::string receive();

 private:
  Address addr;
  std::string ip;
  std::string port;
  std::unique_ptr<network_impl::TCPNetwork> impl;
};

std::unique_ptr<TCPConnection> make_tcp_connection(const Address &addr, std::unique_ptr<network_impl::TCPNetwork> impl);

}  // namespace network::client

#endif