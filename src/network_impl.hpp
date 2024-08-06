#ifndef NETWORK_IMPL_HPP
#define NETWORK_IMPL_HPP

#include "net_lib_wrapper.hpp"

class NetworkImpl {
 public:
  void connect(const std::string &ip, const std::string &port) {
    const auto endpoints { resolver.resolve(ip, port) };
    net_lib::connect(socket, endpoints);
  }

  void send(const std::string &message) {
    const auto buf { net_lib::buffer(message + net_lib::end_delim) };
    net_lib::write(socket, buf);
  }

  std::string receive() {
    auto buf { net_lib::StreamBuf {} };
    net_lib::read_until(socket, buf, net_lib::end_delim);

    auto is { std::istream { &buf } };
    auto result { std::string {} };
    std::getline(is, result, net_lib::end_delim);
    return result;
  }

 private:
  net_lib::Context context;
  net_lib::TCPResolver resolver { context };
  net_lib::TCPSocket socket { context };
};

#endif