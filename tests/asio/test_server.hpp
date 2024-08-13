#ifndef TEST_SERVER_HPP
#define TEST_SERVER_HPP

#include "network_impl/asio/asio_lib.hpp"
#include "test_constants.hpp"
#include "test_socket.hpp"

class TestServer : public TestBase {
 public:
  void init_on_accept() {
    set_up_acceptor();

    const auto accept_func { [this](asio_lib::AsioErrorCode ec, asio_lib::AsioTcpSocket new_socket) {
      socket = std::move(new_socket);

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
    acceptor->async_accept(accept_func);
  }

 private:
  void set_up_acceptor() {
    if (acceptor->is_open() == false) {
      acceptor->open(asio_lib::v4());
      acceptor->set_option(asio_lib::reuse_address(true));
      acceptor->bind(endpoint);
      acceptor->listen();
    }
  }

  std::unique_ptr<asio_lib::AsioTcpAcceptor> acceptor { std::make_unique<asio_lib::AsioTcpAcceptor>(context) };
};

#endif