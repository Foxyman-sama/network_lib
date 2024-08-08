#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../test_constants.hpp"
#include "../test_server.hpp"
#include "network_impl/asio/asio_network_impl_sync.hpp"
#include "tcp_connection.hpp"

using namespace network::client;
using namespace network::client::network_impl;
using namespace network::client::network_impl::asio;
using namespace testing;

int main() {
  InitGoogleTest();
  InitGoogleMock();
  return RUN_ALL_TESTS();
}

class send_tests : public Test {
 public:
  void SetUp() override {
    server.init_on_receive();
    server.init_on_accept();
    server.start();

    const auto addr { make_address(test_ip.data(), std::to_string(test_port)) };
    conn = make_tcp_connection(addr, std::make_unique<AsioNetworkImplSync>());
  }

  std::unique_ptr<TCPConnection> conn;
  TestServer server;
};

TEST_F(send_tests, correct_sending_message) {
  conn->send(test_message);

  ASSERT_EQ(test_message, server.get_result());
}

TEST_F(send_tests, correct_sending_empty_string) {
  conn->send("");

  ASSERT_EQ("", server.get_result());
}

TEST_F(send_tests, correct_sending_message_multiple_times) {
  for (auto i { int { 0 } }; i < 5; ++i) {
    conn->send(test_message);
    ASSERT_EQ(test_message, server.get_result());
    server.prepare_async_receive();
  }
}