#include "asio_network_impl_sync.hpp"
AsioNetworkImplSync::~AsioNetworkImplSync() {
  auto ec { net_lib::ErrorCode {} };
  auto _ { socket.shutdown(net_lib::shutdown_both, ec) };
  socket.close();
}

void AsioNetworkImplSync::connect(const Address &addr) {
  const auto endpoints { resolver.resolve(addr.get_ip(), addr.get_port()) };
  net_lib::connect(socket, endpoints);
}

void AsioNetworkImplSync::send(const std::string &message) {
  const auto buf { net_lib::buffer(message + net_lib::end_delim) };
  net_lib::write(socket, buf);
}

std::string AsioNetworkImplSync::receive() {
  auto buf { net_lib::StreamBuf {} };
  net_lib::read_until(socket, buf, net_lib::end_delim);
  return extract_from_buffer(buf);
}

std::string AsioNetworkImplSync::extract_from_buffer(net_lib::StreamBuf &buf) {
  auto is { std::istream { &buf } };
  auto result { std::string {} };
  std::getline(is, result, net_lib::end_delim);
  return result;
}