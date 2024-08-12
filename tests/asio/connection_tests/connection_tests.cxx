#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../asio_include.hpp"
#include "network_impl/asio/asio_tcp_socket.hpp"

using namespace testing;

int main() {
  InitGoogleTest();
  InitGoogleMock();
  return RUN_ALL_TESTS();
}

class connection_tests : public Test {};

TEST_F(connection_tests, correct_connection) {
  const auto addr { make_address("google.com", "80") };
  ASSERT_NO_THROW(asio_connect(addr));
}

TEST_F(connection_tests, wrong_connection) {
  const auto addr { make_address("127.0.11111.1", "80") };
  ASSERT_ANY_THROW(asio_connect(addr));
}