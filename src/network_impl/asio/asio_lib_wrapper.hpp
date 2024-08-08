#ifndef NETWORK_LIB_WRAPPER_HPP
#define NETWORK_LIB_WRAPPER_HPP

#include <boost/asio.hpp>

namespace network::client::network_impl::asio::net_lib {

using Context = boost::asio::io_context;
using TCPResolver = boost::asio::ip::tcp::resolver;
using TCPSocket = boost::asio::ip::tcp::socket;
using TCPAcceptor = boost::asio::ip::tcp::acceptor;
using TCPEndpoint = boost::asio::ip::tcp::endpoint;
using ErrorCode = boost::system::error_code;
using StreamBuf = boost::asio::streambuf;

using boost::asio::async_read_until;
using boost::asio::async_write;
using boost::asio::buffer;
using boost::asio::connect;
using boost::asio::read;
using boost::asio::read_until;
using boost::asio::write;

using boost::asio::ip::tcp::socket::shutdown_both;

inline auto v4() noexcept { return boost::asio::ip::tcp::v4(); }

inline auto reuse_address(bool value) { return boost::asio::ip::tcp::acceptor::reuse_address(value); }

constexpr char end_delim { '\0' };

}  // namespace network::client::network_impl::asio::net_lib

#endif