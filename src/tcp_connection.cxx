#include "tcp_connection.hpp"

namespace network::client {

using namespace network_impl;

TCPConnection::TCPConnection(const Address &addr, std::unique_ptr<TCPNetwork> impl)
    : addr { addr }, impl { std::move(impl) } {}

void TCPConnection::connect() { impl->connect(addr); }

void TCPConnection::send(const std::string &message) { impl->send(message); }

std::string TCPConnection::receive() { return impl->receive(); }

std::unique_ptr<TCPConnection> make_tcp_connection(const Address &addr, std::unique_ptr<TCPNetwork> impl) {
  auto result { std::make_unique<TCPConnection>(addr, std::move(impl)) };
  result->connect();
  return result;
}

}  // namespace network::client