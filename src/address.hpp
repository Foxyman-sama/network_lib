#ifndef NETWORK_LIB_ADDRESS_HPP
#define NETWORK_LIB_ADDRESS_HPP

#include <string>

namespace network::tcp_socket {

class Address {
 public:
  Address() = default;

  explicit Address(const std::string &ip, const std::string &port) noexcept : ip { ip }, port { port } {}
  // TODO Checks on correct ip
  void set_ip(const std::string &ip) noexcept { this->ip = ip; }
  // TODO Checks on correct port
  void set_port(const std::string &port) noexcept { this->port = port; }

  const std::string &get_ip() const noexcept { return ip; }

  const std::string &get_port() const noexcept { return port; }

 private:
  std::string ip;
  std::string port;
};

inline Address make_address(const std::string &ip, const std::string &port) { return Address { ip, port }; }

inline bool operator==(const Address &lhs, const Address &rhs) noexcept {
  const auto ip_comparison { lhs.get_ip() == rhs.get_ip() };
  const auto port_comparison { lhs.get_port() == rhs.get_port() };
  return ip_comparison & port_comparison;
}

}  // namespace network::tcp_socket

#endif