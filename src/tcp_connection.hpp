#ifndef NETWORK_LIB_TCP_CONNECTION_HPP
#define NETWORK_LIB_TCP_CONNECTION_HPP

#include <memory>
#include <string>

#include "network_impl.hpp"

class TCPConnection {
 public:
  TCPConnection(const std::string &ip, const std::string &port, NetworkImpl *impl)
      : ip { ip }, port { port }, impl { impl } {}

  void connect() { impl->connect(ip, port); }

  void send(const std::string &message) { impl->send(message); }

  std::string receive() { return impl->receive(); }

 private:
  std::string ip;
  std::string port;
  std::unique_ptr<NetworkImpl> impl;
};

std::unique_ptr<TCPConnection> make_tcp_connection(const std::string &addr, const std::string &port);

#endif