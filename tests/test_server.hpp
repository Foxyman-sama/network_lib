#ifndef TEST_SERVER_HPP
#define TEST_SERVER_HPP

#include <boost/asio.hpp>
#include <future>
#include <memory>
#include <print>

#include "net_lib_wrapper.hpp"
#include "test_constants.hpp"

const auto dead_time { std::chrono::seconds(5) };

class TestServer {
 public:
  void make_acceptor() {
    acceptor = std::make_unique<net_lib::TCPAcceptor>(context, net_lib::TCPEndpoint { net_lib::v4(), test_port });
  }

  void init_on_receive() {
    const auto receive_func { [this](net_lib::ErrorCode ec, net_lib::TCPSocket socket) {
      auto buf { net_lib::StreamBuf {} };
      net_lib::read_until(socket, buf, net_lib::end_delim);

      auto is { std::istream { &buf } };
      std::getline(is, result, net_lib::end_delim);
    } };
    acceptor->async_accept(receive_func);
  }

  void init_on_send(const std::string message = test_message) {
    const auto send_func { [this, message](net_lib::ErrorCode ec, net_lib::TCPSocket socket) {
      const auto buf { net_lib::buffer(message + net_lib::end_delim) };
      net_lib::write(socket, buf);
    } };
    acceptor->async_accept(send_func);
  }

  void start() {
    // FIXME Что-то не так с функией приёма или ожидания
    task = std::async(std::launch::async, [this]() {
      context.run_one_for(std::chrono::seconds(5));
      std::print("Server is closed\n");
    });
    // It's necessary because a connection will be created faster than server start accepting connections.
    task.wait_for(std::chrono::seconds(2));
  }

  void drop() {
    net_lib::ErrorCode ec;
    ec = acceptor->cancel(ec);
    ec = acceptor->close(ec);
    acceptor.reset();
    context.reset();
    result.clear();
  }

  const std::string &get_result() const noexcept {
    task.wait();
    return result;
  }

 private:
  net_lib::Context context;
  std::unique_ptr<net_lib::TCPAcceptor> acceptor;

  std::string result;
  std::future<void> task;
};

#endif