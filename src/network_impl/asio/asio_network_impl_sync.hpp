#ifndef NETWORK_LIB_ASIO_NETWORK_IMPL_SYNC_HPP
#define NETWORK_LIB_ASIO_NETWORK_IMPL_SYNC_HPP

#include "address.hpp"
#include "asio_lib_wrapper.hpp"
#include "tcp_connection.hpp"

namespace network::client::network_impl::asio {

class AsioNetworkImplSync : public TCPNetwork {
 public:
  ~AsioNetworkImplSync() override;

  void connect(const Address &addr) override;

  void send(const std::string &message) override;

  std::string receive() override;

 private:
  std::string extract_from_buffer(net_lib::StreamBuf &buf);

  net_lib::Context context;
  net_lib::TCPResolver resolver { context };
  net_lib::TCPSocket socket { context };
};

}  // namespace network::client::network_impl::asio

#endif