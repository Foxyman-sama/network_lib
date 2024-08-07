#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../test_constants.hpp"
#include "../test_server.hpp"
#include "tcp_connection.hpp"

using namespace testing;

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
    conn = make_tcp_connection(test_ip.data(), std::to_string(test_port));
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