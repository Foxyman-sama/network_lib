#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "../asio_include.hpp"
#include "../test_server.hpp"
#include "network_impl/asio/asio_tcp_socket.hpp"
#include "tcp_socket.hpp"

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
    conn = asio_connect(addr);
  }

  std::unique_ptr<TcpSocket> conn;
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