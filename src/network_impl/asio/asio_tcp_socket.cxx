#include "asio_tcp_socket.hpp"

#include <memory>

#include "network_impl/asio/asio_lib.hpp"
#include "tcp_socket.hpp"

namespace network::tcp_socket::asio {

AsioTcpSocket::AsioTcpSocket(asio_lib::AsioTcpSocket&& socket) noexcept : socket { std::move(socket) } {};

AsioTcpSocket::~AsioTcpSocket() {
  auto ec { asio_lib::AsioErrorCode {} };
  auto _ { socket.shutdown(asio_lib::shutdown_both, ec) };
  socket.close();
}

void AsioTcpSocket::send(const std::string& message) {
  const auto buf { asio_lib::buffer(message + asio_lib::end_delim) };
  asio_lib::write(socket, buf);
}

std::string AsioTcpSocket::receive() {
  auto buf { receive_into_buffer() };
  return extract_from_buffer(*buf);
}

std::unique_ptr<asio_lib::AsioStreamBuf> AsioTcpSocket::receive_into_buffer() {
  auto buf { std::make_unique<asio_lib::AsioStreamBuf>() };
  asio_lib::read_until(socket, *buf, asio_lib::end_delim);
  return buf;
}

std::string AsioTcpSocket::extract_from_buffer(asio_lib::AsioStreamBuf& buf) {
  auto is { std::istream { &buf } };
  auto result { std::string {} };
  std::getline(is, result, asio_lib::end_delim);
  return result;
}

auto& get_context() {
  static auto context { asio_lib::AsioContext {} };
  return context;
}

auto& get_resolver() {
  static auto resolver { asio_lib::AsioTcpResolver { get_context() } };
  return resolver;
}

std::unique_ptr<TcpSocket> asio_connect(const Address& addr) {
  auto& context { get_context() };
  auto& resolver { get_resolver() };

  const auto endpoint { resolver.resolve(addr.get_ip(), addr.get_port()) };

  auto socket { asio_lib::AsioTcpSocket { context } };
  asio_lib::connect(socket, endpoint);

  return std::make_unique<AsioTcpSocket>(std::move(socket));
}

}  // namespace network::tcp_socket::asio