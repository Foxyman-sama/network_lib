#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "tcp_connection.hpp"

using namespace testing;

int main() {
  InitGoogleTest();
  InitGoogleMock();
  return RUN_ALL_TESTS();
}

class connection_tests : public Test {};

TEST_F(connection_tests, correct_connection) { ASSERT_NO_THROW(make_tcp_connection("google.com", "80")); }

TEST_F(connection_tests, wrong_connection) { ASSERT_ANY_THROW(make_tcp_connection("127.0.11111.1", "80")); }