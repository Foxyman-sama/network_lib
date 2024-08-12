#ifndef TEST_CLIENT_HPP
#define TEST_CLIENT_HPP

#include "network_impl/asio/asio_lib.hpp"
#include "test_constants.hpp"
#include "test_socket.hpp"

class TestClient : public TestBase {
 public:
  void init_on_connect() {
    const auto connect_func { [this](asio_lib::AsioErrorCode ec) {
      switch (mode) {
        case Mode::receive: {
          prepare_async_receive();
          break;
        }
        case Mode::send: {
          prepare_async_send();
          break;
        }
      }
    } };
    const auto endpoint { asio_lib::AsioTcpEndpoint { asio_lib::make_address("127.0.0.1"), test_port } };
    socket.async_connect(endpoint, connect_func);
  }

 private:
  asio_lib::AsioTcpEndpoint endpoint { asio_lib::v4(), test_port };
};

#endif