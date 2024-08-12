#ifndef TEST_SOCKET_HPP
#define TEST_SOCKET_HPP

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <chrono>
#include <print>

#include "network_impl/asio/asio_lib.hpp"
#include "test_constants.hpp"

constexpr auto dead_time { std::chrono::seconds(10) };

class TestBase {
 public:
  void init_on_receive() { mode = Mode::receive; }

  void prepare_async_receive() {
    const auto receive_func { [this](asio_lib::AsioErrorCode ec, std::size_t transferred) {
      std::print("Callback: receive_func\n");

      auto is { std::istream { &receive_buffer } };
      std::getline(is, result, asio_lib::end_delim);
    } };
    asio_lib::async_read_until(socket, receive_buffer, asio_lib::end_delim, receive_func);
  }

  void init_on_send(const std::string& message = test_message) {
    mode = Mode::send;
    send_message = message;
  }

  void prepare_async_send() {
    const auto send_func { [this](asio_lib::AsioErrorCode ec, std::size_t transferred) {
      std::print("Callback: send_func\n");
    } };
    asio_lib::async_write(socket, asio_lib::buffer(send_message + asio_lib::end_delim), send_func);
  }

  void start() {
    const auto context_func { [this]() { context.run_for(dead_time); } };
    task = std::async(std::launch::async, context_func);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  auto get_addr() { return boost::lexical_cast<std::string>(socket.remote_endpoint()); }

  const std::string& get_result() const noexcept {
    task.wait();
    return result;
  }

 protected:
  enum class Mode { receive, send };

  asio_lib::AsioContext context;
  asio_lib::AsioTcpSocket socket { context };
  Mode mode { Mode::receive };
  asio_lib::AsioStreamBuf receive_buffer;
  std::string send_message;
  std::string result;
  std::future<void> task;
};

#endif