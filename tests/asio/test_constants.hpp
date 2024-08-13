#ifndef TEST_CONSTANTS_HPP
#define TEST_CONSTANTS_HPP

#include <string>
#include <string_view>

constexpr auto test_ip { std::string_view { "127.0.0.1" } };
inline const auto test_port { 9090 };
inline const auto test_message { std::string { "Hello, World!" } };

#endif