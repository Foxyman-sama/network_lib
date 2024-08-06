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
  void SetUp() {
    server.init_on_send();
    server.start();
    conn = make_tcp_connection(test_ip.data(), std::to_string(test_port));
  }

  std::unique_ptr<TCPConnection> conn;
  TestServer server;
};

TEST_F(receive_tests, correct_receive_hello_world) {
  const auto actual { conn->receive() };

  ASSERT_EQ(test_message, actual);
}