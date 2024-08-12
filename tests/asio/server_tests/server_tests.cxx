#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "../asio_include.hpp"
#include "../test_server.hpp"
#include "network_impl/asio/asio_tcp_socket.hpp"

using namespace testing;

int main() {
  InitGoogleTest();
  InitGoogleMock();
  return RUN_ALL_TESTS();
}
