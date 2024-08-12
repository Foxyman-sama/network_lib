#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "../asio_include.hpp"
#include "../test_server.hpp"
#include "network_impl/asio/asio_tcp_socket.hpp"

using namespace testing;

// TODO Rework this test module.
int main() {
  InitGoogleTest();
  InitGoogleMock();
  return RUN_ALL_TESTS();
}

class receive_tests : public Test {
 public:
  void init(const std::string& message = test_message) {
    server.init_on_send(message);
    server.init_on_accept();
    server.start();

    const auto addr { make_address(test_ip.data(), std::to_string(test_port)) };
    conn = asio_connect(addr);
  }

  std::unique_ptr<TcpSocket> conn;
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