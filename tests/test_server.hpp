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
  void init_on_receive() {
    make_acceptor();
    acceptor->async_accept([this](net_lib::ErrorCode ec, net_lib::TCPSocket socket) {
      auto buf { net_lib::StreamBuf {} };
      net_lib::read_until(socket, buf, net_lib::end_delim);

      auto is { std::istream { &buf } };
      std::getline(is, result, net_lib::end_delim);
    });
  }

  void init_on_send() {
    make_acceptor();
    acceptor->async_accept([this](net_lib::ErrorCode ec, net_lib::TCPSocket socket) {
      const auto buf { net_lib::buffer(test_message + net_lib::end_delim) };
      net_lib::write(socket, buf);
    });
  }

  void start() {
    task = std::async(std::launch::async, [this]() {
      context.run_one_for(dead_time);
      std::print("Server is closed\n");
    });
    // It's necessary because a connection will create faster than server start accepting connections.
    task.wait_for(std::chrono::seconds(2));
  }

  void drop() {
    net_lib::ErrorCode ec;
    acceptor->cancel(ec);
    acceptor->close(ec);
    acceptor.reset();
    context.reset();
    result.clear();
    task.wait();
  }

  const std::string &get_result() const noexcept {
    task.wait();
    return result;
  }

 private:
  void make_acceptor() {
    acceptor = std::make_unique<net_lib::TCPAcceptor>(context, net_lib::TCPEndpoint { net_lib::v4(), test_port });
  }

  net_lib::Context context;
  std::unique_ptr<net_lib::TCPAcceptor> acceptor;

  std::string result;
  std::future<void> task;
};

#endif