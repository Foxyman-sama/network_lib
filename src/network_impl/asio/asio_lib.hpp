#ifndef NETWORK_LIB_WRAPPER_HPP
#define NETWORK_LIB_WRAPPER_HPP

#include <boost/asio.hpp>

#include "boost/asio/connect.hpp"
#include "boost/asio/ip/address.hpp"

namespace asio_lib {

using AsioContext = boost::asio::io_context;
using AsioTcpResolver = boost::asio::ip::tcp::resolver;
using AsioTcpSocket = boost::asio::ip::tcp::socket;
using AsioTcpAcceptor = boost::asio::ip::tcp::acceptor;
using AsioTcpEndpoint = boost::asio::ip::tcp::endpoint;
using AsioErrorCode = boost::system::error_code;
using AsioStreamBuf = boost::asio::streambuf;

using boost::asio::async_connect;
using boost::asio::async_read_until;
using boost::asio::async_write;
using boost::asio::buffer;
using boost::asio::connect;
using boost::asio::read;
using boost::asio::read_until;
using boost::asio::write;
using boost::asio::ip::make_address;

using boost::asio::ip::tcp::socket::shutdown_both;

inline auto v4() noexcept { return boost::asio::ip::tcp::v4(); }

inline auto reuse_address(bool value) { return boost::asio::ip::tcp::acceptor::reuse_address(value); }

constexpr char end_delim { '\0' };

}  // namespace asio_lib

#endif