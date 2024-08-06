#ifndef NET_LIB_WRAPPER_HPP
#define NET_LIB_WRAPPER_HPP

#include <boost/asio.hpp>

namespace net_lib {

using Context = boost::asio::io_context;
using TCPResolver = boost::asio::ip::tcp::resolver;
using TCPSocket = boost::asio::ip::tcp::socket;
using TCPAcceptor = boost::asio::ip::tcp::acceptor;
using TCPEndpoint = boost::asio::ip::tcp::endpoint;
using ErrorCode = boost::system::error_code;
using StreamBuf = boost::asio::streambuf;

using boost::asio::buffer;
using boost::asio::connect;
using boost::asio::read;
using boost::asio::read_until;
using boost::asio::write;

inline auto v4() noexcept { return boost::asio::ip::tcp::v4(); }

constexpr char end_delim { '\0' };

}  // namespace net_lib

#endif