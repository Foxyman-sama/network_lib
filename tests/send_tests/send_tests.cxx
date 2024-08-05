#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "tcp_connection.hpp"

using namespace testing;

int main() {
  InitGoogleTest();
  InitGoogleMock();
  return RUN_ALL_TESTS();
}