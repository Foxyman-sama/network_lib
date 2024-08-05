#include "tcp_connection.hpp"

#include <memory>

std::unique_ptr<TCPConnection> make_tcp_connection(const std::string &ip, const std::string &port) {
  auto result { std::make_unique<TCPConnection>(ip, port, new NetworkImpl) };
  result->connect();
  return result;
}