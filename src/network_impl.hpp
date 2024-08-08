#ifndef NETWORK_LIB_NETWORK_IMPL_HPP
#define NETWORK_LIB_NETWORK_IMPL_HPP

#include "address.hpp"

namespace network::network_impl {

class TCPNetwork {
 public:
  virtual ~TCPNetwork() = default;

  virtual void connect(const Address &addr) = 0;

  virtual void send(const std::string &message) = 0;

  virtual std::string receive() = 0;
};  // namespace network::client::classTCPNetwork

class TCPAcceptor {};

}  // namespace network::network_impl

#endif