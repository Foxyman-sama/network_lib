#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "address.hpp"
#include "network_impl/asio/asio_network_impl_sync.hpp"
#include "tcp_connection.hpp"

using namespace network::client;
using namespace network::network_impl;
using namespace network::network_impl::asio;
using namespace testing;

int main() {
  InitGoogleTest();
  InitGoogleMock();
  return RUN_ALL_TESTS();
}

class connection_tests : public Test {};

TEST_F(connection_tests, correct_connection) {
  const auto addr { make_address("google.com", "80") };
  ASSERT_NO_THROW(make_tcp_connection(addr, std::make_unique<AsioNetworkImplSync>()));
}

TEST_F(connection_tests, wrong_connection) {
  const auto addr { make_address("127.0.11111.1", "80") };
  ASSERT_ANY_THROW(make_tcp_connection(addr, std::make_unique<AsioNetworkImplSync>()));
}
