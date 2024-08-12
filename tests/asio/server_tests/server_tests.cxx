#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "../asio_include.hpp"
#include "../test_client.hpp"
#include "address.hpp"
#include "network_impl/asio/asio_tcp_socket.hpp"
#include "tests/asio/test_constants.hpp"

using namespace testing;

int main() {
  InitGoogleTest();
  InitGoogleMock();
  return RUN_ALL_TESTS();
}

class server_tests : public Test {
 public:
  const network::tcp_socket::Address server_addr { "127.0.0.1", std::to_string(test_port) };
};

TEST_F(server_tests, accept_tcp_connection) {}