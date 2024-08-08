#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "../test_constants.hpp"
#include "../test_server.hpp"
#include "address.hpp"
#include "network_impl/asio/asio_network_impl_sync.hpp"
#include "tcp_connection.hpp"

using namespace network::client;
using namespace network::client::network_impl;
using namespace network::client::network_impl::asio;
using namespace testing;

// TODO Rework this test module.
int main() {
  InitGoogleTest();
  InitGoogleMock();
  return RUN_ALL_TESTS();
}

class receive_tests : public Test {
 public:
  void init(const std::string &message = test_message) {
    server.init_on_send(message);
    server.init_on_accept();
    server.start();

    const auto addr { make_address(test_ip.data(), std::to_string(test_port)) };
    conn = make_tcp_connection(addr, std::make_unique<AsioNetworkImplSync>());
  }

  std::unique_ptr<TCPConnection> conn;
  TestServer server;
};

TEST_F(receive_tests, correct_receiving_message) {
  init();

  const auto actual { conn->receive() };

  ASSERT_EQ(test_message, actual);
}

TEST_F(receive_tests, correct_receiving_empty_string) {
  init("");

  const auto actual { conn->receive() };

  ASSERT_EQ("", actual);
}

TEST_F(receive_tests, correct_receiving_message_multiple_times) {
  init();

  for (auto i { int { 0 } }; i < 5; ++i) {
    const auto actual { conn->receive() };
    ASSERT_EQ(test_message, actual);
    server.prepare_async_send();
  }
}