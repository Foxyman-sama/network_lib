#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "tcp_connection.hpp"

using namespace testing;

Context test_context;

int main() {
  InitGoogleTest();
  InitGoogleMock();
  return RUN_ALL_TESTS();
}

TEST(connection_tests, correct_connection) { ASSERT_NO_THROW(make_tcp_connection(test_context, "google.com", "9090")); }

TEST(connection_tests, wrong_connection) {
  ASSERT_ANY_THROW(make_tcp_connection(test_context, "127.0.11111.1", "9090"));
}