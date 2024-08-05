#ifndef NETWORK_LIB_TCP_CONNECTION_HPP
#define NETWORK_LIB_TCP_CONNECTION_HPP

#include <boost/asio.hpp>
#include <memory>
#include <string>

using Context = boost::asio::io_context;

class NetworkImpl {
 public:
  void connect(const std::string &ip, const std::string &port) {
    const auto endpoints { resolver.resolve(ip, port) };
    boost::asio::connect(socket, endpoints);
  }

 private:
  Context context;
  boost::asio::ip::tcp::resolver resolver { context };
  boost::asio::ip::tcp::socket socket { context };
};

class TCPConnection {
 public:
  TCPConnection(const std::string &ip, const std::string &port, NetworkImpl *impl)
      : ip { ip }, port { port }, impl { impl } {}

  void connect() { impl->connect(ip, port); }

 private:
  std::string ip;
  std::string port;
  std::unique_ptr<NetworkImpl> impl;
};

std::unique_ptr<TCPConnection> make_tcp_connection(const std::string &addr, const std::string &port);
#endif