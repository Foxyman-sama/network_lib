#ifndef NETWORK_LIB_TCP_CONNECTION_HPP
#define NETWORK_LIB_TCP_CONNECTION_HPP

#include <memory>
#include <string>

#include "acceptor.hpp"
#include "address.hpp"

class TCPNetwork {
 public:
  virtual ~TCPNetwork() = default;

  virtual void connect(const Address &addr) = 0;

  virtual void send(const std::string &message) = 0;

  virtual std::string receive() = 0;
};

class TCPConnection {
 public:
  explicit TCPConnection(const Address &addr, std::unique_ptr<TCPNetwork> impl);

  void connect();

  void send(const std::string &message);

  std::string receive();

 private:
  Address addr;
  std::string ip;
  std::string port;
  std::unique_ptr<TCPNetwork> impl;
};

std::unique_ptr<TCPConnection> make_tcp_connection(const Address &addr, std::unique_ptr<TCPNetwork> impl);

#endif