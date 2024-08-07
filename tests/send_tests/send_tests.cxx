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

class send_tests : public Test {
 public:
  void SetUp() override {
    server.make_acceptor();
    server.init_on_receive();
    server.start();
    conn = make_tcp_connection(test_ip.data(), std::to_string(test_port));
  }

  void TearDown() override { server.drop(); }

  std::unique_ptr<TCPConnection> conn;
  TestServer server;
};

TEST_F(send_tests, correct_sending_hello_world) {
  conn->send(test_message.data());

  ASSERT_EQ(test_message, server.get_result());
}

TEST_F(send_tests, correct_sending_empty_string) {
  conn->send("");

  ASSERT_EQ("", server.get_result());
}