#ifndef TEST_CONSTANTS_HPP
#define TEST_CONSTANTS_HPP

#include <climits>
#include <random>
#include <string_view>

inline const unsigned short generate_random_port() noexcept {
  auto rd { std::random_device {} };
  auto seed { std::mt19937 { rd() } };
  auto range { std::uniform_int_distribution<unsigned short>(0, USHRT_MAX) };
  return range(seed);
}

constexpr auto test_ip { std::string_view { "127.0.0.1" } };
inline const auto test_port { generate_random_port() };
inline const auto test_message { std::string { "Hello, World!" } };

#endif