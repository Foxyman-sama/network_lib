#ifndef TEST_SERVER_HPP
#define TEST_SERVER_HPP

#include <boost/asio.hpp>
#include <chrono>
#include <future>
#include <print>
#include <thread>

#include "network_impl/asio/asio_lib.hpp"
#include "test_constants.hpp"

const auto dead_time { std::chrono::seconds(10) };

class TestServer {
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

  void init_on_receive() { mode = Mode::receive; }

  void init_on_send(const std::string &message = test_message) {
    mode = Mode::send;
    send_message = message;
  }

  void start() {
    const auto context_func { [this]() { context.run_for(dead_time); } };
    task = std::async(std::launch::async, context_func);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  const std::string &get_result() const noexcept {
    task.wait();
    return result;
  }

  void prepare_async_receive() {
    const auto receive_func { [this](asio_lib::AsioErrorCode ec, std::size_t transferred) {
      std::print("Callback: receive_func\n");

      auto is { std::istream { &receive_buffer } };
      std::getline(is, result, asio_lib::end_delim);
    } };
    asio_lib::async_read_until(socket, receive_buffer, asio_lib::end_delim, receive_func);
  }

  void prepare_async_send() {
    const auto send_func { [this](asio_lib::AsioErrorCode ec, std::size_t transferred) {
      std::print("Callback: send_func\n");
    } };
    asio_lib::async_write(socket, asio_lib::buffer(send_message + asio_lib::end_delim), send_func);
  }

 private:
  enum class Mode { receive, send };

  void set_up_acceptor() {
    if (acceptor->is_open() == false) {
      acceptor->open(asio_lib::v4());
      acceptor->set_option(asio_lib::reuse_address(true));
      acceptor->bind(endpoint);
      acceptor->listen();
    }
  }

  asio_lib::AsioContext context;
  std::unique_ptr<asio_lib::AsioTcpAcceptor> acceptor { std::make_unique<asio_lib::AsioTcpAcceptor>(context) };
  asio_lib::AsioTcpEndpoint endpoint { asio_lib::v4(), test_port };

  asio_lib::AsioTcpSocket socket { context };
  Mode mode { TestServer::Mode::receive };

  asio_lib::AsioStreamBuf receive_buffer;
  std::string send_message;

  std::string result;
  std::future<void> task;
};

#endif